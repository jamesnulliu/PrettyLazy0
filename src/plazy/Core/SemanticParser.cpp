#include "plazy/Core/SemanticParser.hpp"
#include "plazy/Common/Exceptions.hpp"
#include "plazy/Common/Logger.hpp"
#include <format>

namespace plazy
{
SemanticParser::SemanticParser(const std::vector<Token>& tokens)
{
    initSyntax();

    // Input stack
    // e.g. 3 + 5 * 2  =>  3 + 5 * 2 ENDSYM
    //                      ------->
    m_tokenStack.push_back(Token(TokenType::ENDOFFILE, ENDSYM));
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        m_tokenStack.push_back(*it);
    }

    // Element stack
    // Initial state (The bottom is at index 0):
    // ----------------
    // |  #  Ssyn  S      <---
    // ----------------
    m_elemStack.push_back(Element(ENDSYM));
    m_elemStack.push_back(Element(m_analyzer.getBeginSym(), true));
    m_elemStack.push_back(Element(m_analyzer.getBeginSym()));
}

void SemanticParser::addSyntax(const Symbol& lhs, const std::vector<Symbol>& rhs, int indexOffset)
{
    m_rhsWithActions.push_back(rhs);

    // Remove all the actions on the right-hand side of the syntax,
    // then pass the syntax to the syntax analyzer.
    std::vector<Symbol> rhsCopy;
    for (const Symbol& sym : rhs) {
        // If a symbol begins with a digit, it is an action.
        if (!std::isdigit(sym[0])) {
            rhsCopy.push_back(sym);
        }
    }
    m_analyzer.addSyntax(lhs, rhsCopy);

    // Add the index offset
    m_indexOffsets.push_back(indexOffset);
}

void SemanticParser::setActionFunc(const std::string& index, const ActionFunc& func)
{
    if (m_actionFuncs.find(index) != m_actionFuncs.end()) {
        throw std::runtime_error(std::format("Action {} already exists", index));
    }
    m_actionFuncs[index] = func;
}

void SemanticParser::generateTables()
{
    const auto& syntaxes = m_analyzer.getSyntaxes();
    for (size_t i = 0; i < syntaxes.size(); ++i) {
        const Symbol& lhs = syntaxes[i].lhs;
        const std::set<Symbol>& selectSet = m_analyzer.getSelectSet(i);

        for (const Symbol& sym : selectSet) {
            m_predictionTable[lhs][sym] = m_rhsWithActions[i];
            m_indexOffsetTable[lhs][sym] = m_indexOffsets[i];
        }
    }
}

void SemanticParser::parseArithmeticExpr()
{
    try {
        // Translate the value of the token to a symbol.
        Symbol rtopSym = translate2Symbol(m_tokenStack.back());

        while (!m_elemStack.empty() && !m_tokenStack.empty()) {
            size_t atopIndex = m_elemStack.size() - 1;
            const Element& atop = m_elemStack.back();
            if (atop.type == SymbolType::TERMINAL || atop.type == SymbolType::ENDSYM) {
                // If these two symbols do not match, throw a syntax error.
                if (atop.symbol != rtopSym) {
                    throw SyntaxError(std::format("The terminal symbol {} does not match "
                                                  "the top of the input stack {}.",
                                                  atop.symbol, rtopSym));
                }

                // If the top is an identifier, throw a semantic error.
                if (atop.symbol == "id") {
                    throw SemanticError("Identifier is not allowed in the expression.");
                }

                ///////////////////////
                //    Top matched.   //
                ///////////////////////

                if (atop.symbol == "num") {
                    // Fetch the value of the number.
                    int num = std::stoi(m_tokenStack.back().value);

                    // Assign the value of the number to the new top.
                    // [NOTE] The new top is certainly an action: { F.val = num.val },
                    //        because only F -> num can produce a terminal symbol "num".
                    //        And it is safe to access elemStack[atopIndex - 1].
                    Element& newAtop = m_elemStack[atopIndex - 1];
                    newAtop.values.push_back(num);
                }

                // Pop elem stack and input stack
                m_elemStack.pop_back();
                m_tokenStack.pop_back();

                // Update the top symbol of the input stack.
                if (!m_tokenStack.empty()) {
                    rtopSym = translate2Symbol(m_tokenStack.back());
                }
            } else if (atop.type == SymbolType::NON_TERMINAL) {
                //////////////////////////////////////////////////////////////////////
                // Replace the top non-terminal symbol X with the corresponding syntax.
                //////////////////////////////////////////////////////////////////////

                // If there is no such syntax, throw a syntax error.
                const auto& allSyntaxes = m_predictionTable[atop.symbol];
                if (allSyntaxes.find(rtopSym) == allSyntaxes.end()) {  // Not found
                    throw SyntaxError(std::format("{} is not allowed.", rtopSym));
                }
                const auto& syntax = m_predictionTable[atop.symbol][rtopSym];

                // 1) Pop X
                Element oldAtop = atop;
                m_elemStack.pop_back();

                // 2) Push the symbols of the syntax in reverse order.
                for (auto it = syntax.rbegin(); it != syntax.rend(); ++it) {
                    if (*it != EPSILON) {  // Ignore ε
                        // If the symbol Y is a non-terminal,
                        // an additional synthesized attribute Ysyn should be pushed before Y.
                        //  ---------------------
                        //  |  ...  <-- Ysyn  Y
                        //  ---------------------
                        if (m_analyzer.isNonTerminal(*it)) {
                            m_elemStack.push_back(Element(*it, true));   // Ysyn
                            m_elemStack.push_back(Element(*it, false));  // Y
                        } else {
                            m_elemStack.push_back(Element(*it, false));
                        }
                    }
                }

                // 3) Assign the value of X to the ACTION that needs it.
                // [NOTE] It is guaranteed that non-terminal symbols have at most one value.
                if (oldAtop.values.size() == 1) {
                    // [NOTE] The index of the ACTION is stored in m_indexOffsetTable.
                    //        It is safe to access m_indexOffsetTable[oldAtop.symbol][rtopSym],
                    //        because the syntax is found in the prediction table.
                    int indexOffset = m_indexOffsetTable[oldAtop.symbol][rtopSym];
                    if (indexOffset != NO_VALUE) {
                        Element& e = m_elemStack[atopIndex + indexOffset];
                        e.values.push_back(oldAtop.values[0]);
                    }
                }
            } else if (atop.type == SymbolType::SYNTHESIZED) {
                ////////////////////////////////////////////////////////////////////////////////////
                // Assign the value of the synthesized attribute to the following action and pop it.
                ////////////////////////////////////////////////////////////////////////////////////

                // [NOTE] It is guaranteed that a synthesized attribute has at most one value.
                // For the following symbol of the synthesized attribute, there are two cases:
                // - Action (Esyn in this case):
                //     ------------------------
                //     | ... Ssyn {0} Esyn ...
                //     ------------------------
                // - End symbol (Ssyn in this case):
                //     ---------------------
                //     | # Ssyn {0} ...
                //     ---------------------
                // For the latter case, the value of the synthesized attribute is not needed.

                if (atop.values.size() == 1) {
                    auto it =
                        std::find_if(m_elemStack.rbegin(), m_elemStack.rend(),
                                     [](const Element& e) { return e.type == SymbolType::ACTION; });

                    if (it != m_elemStack.rend()) {
                        it->values.push_back(atop.values[0]);
                    }
                }
                m_elemStack.pop_back();
            } else if (atop.type == SymbolType::ACTION) {
                // For the following symbol of the action, there are three cases:
                // - Synthesized attribute ({0} and {3} in this case):
                //      -----------------------------------
                //      | ... Ssyn {0} Esyn {3} E'syn ....
                //      -----------------------------------
                // - Non-terminal symbol ({11} in this case):
                //      ----------------------------------
                //      | ... Tsyn {12} T'syn T' {11} ...
                //      ----------------------------------
                // - ')' ({18} in this case):
                //      -----------------------------
                //      | ... {11} Fsyn ) {18} Esyn
                //      -----------------------------

                // Find the nearest synthesized attribute or non-terminal symbol.
                auto it = std::find_if(m_elemStack.rbegin(), m_elemStack.rend(),
                                       [](const Element& e) {
                                           return e.type == SymbolType::SYNTHESIZED ||
                                                  e.type == SymbolType::NON_TERMINAL;
                                       });
                if (it == m_elemStack.rend()) {
                    throw SyntaxError(
                        "Missing synthesized attribute or non-terminal symbol after the action.");
                }

                // Perform the semantic action.
                ActionFunc& action = m_actionFuncs[atop.symbol];
                int result = action(atop.values);
                m_elemStack.pop_back();

                // Assign the result to the symbol.
                it->values.push_back(result);
            } else {
                throw SyntaxError("Unknown symbol type.");
            }
        }
    } catch (const SyntaxError& e) {
        YERROR("{}", e.what());
        return;
    } catch (const SemanticError& e) {
        YERROR("{}", e.what());
        return;
    }

    YINFO("Syntax and semantic analysis completed.");
}

void SemanticParser::initSyntax()
{
    // Arithmetic expression:
    //   S -> E {0}                 {0} : print(E.val)
    //   E -> + E' {1}              {1} : E.syn = E'.syn
    //   E -> - E' {2}              {2} : E.syn = -E'.syn
    //   E -> E' {3}                {3} : E.syn = E'.syn
    //   E' -> T {4} E'' {5}        {4} : E''.inh = T.val               {5} : E'.syn = E''.syn
    //   E'' -> + T {6} E''1 {7}    {6} : E''.inh = E''.inh + T.val     {7} : E''.syn = E''1.syn
    //   E'' -> - T {8} E''1 {9}    {8} : E''.inh = E''.inh - T.val     {9} : E''.syn = E''1.syn
    //   E'' -> ε {10}              {10} : E''.syn = E''.inh
    //   T -> F {11} T' {12}        {11} : T'.inh = F.val               {12} : T.val = T'.syn
    //   T' -> * F {13} T'1 {14}    {13} : T'1.inh = T'.inh * F.val     {14} : T'.syn = T'1.syn
    //   T' -> / F {15} T'1 {16}    {15} : if F.val == 0 then error; T'1.inh = T'.inh / F.val
    //                              {16} : T'.syn = T'1.syn
    //   T' -> ε {17}               {17} : T'.syn = T'.inh
    //   F -> ( E {18} )            {18} : F.val = E.val
    //   F -> id {19}               {19} : error
    //   F -> num {20}              {20} : F.val = num.val

    m_analyzer.setBeginSym("S");
    addSyntax("S", {"E", "0"});
    addSyntax("E", {"+", "E'", "1"});
    addSyntax("E", {"-", "E'", "2"});
    addSyntax("E", {"E'", "3"});
    addSyntax("E'", {"T", "4", "E''", "5"});
    addSyntax("E''", {"+", "T", "6", "E''", "7"}, 3);
    addSyntax("E''", {"-", "T", "8", "E''", "9"}, 3);
    addSyntax("E''", {EPSILON, "10"}, 0);
    addSyntax("T", {"F", "11", "T'", "12"});
    addSyntax("T'", {"*", "F", "13", "T'", "14"}, 3);
    addSyntax("T'", {"/", "F", "15", "T'", "16"}, 3);
    addSyntax("T'", {EPSILON, "17"}, 0);
    addSyntax("F", {"(", "E", "18", ")"});
    addSyntax("F", {"id", "19"});
    addSyntax("F", {"num", "20"});

    m_analyzer.calcSelectSets();
    generateTables();

    // Semantic actions
    setActionFunc("0", Action::print);
    setActionFunc("1", Action::assign);
    setActionFunc("2", Action::opposite);
    setActionFunc("3", Action::assign);
    setActionFunc("4", Action::assign);
    setActionFunc("5", Action::assign);
    setActionFunc("6", Action::add);
    setActionFunc("7", Action::assign);
    setActionFunc("8", Action::subtract);
    setActionFunc("9", Action::assign);
    setActionFunc("10", Action::assign);
    setActionFunc("11", Action::assign);
    setActionFunc("12", Action::assign);
    setActionFunc("13", Action::multiply);
    setActionFunc("14", Action::assign);
    setActionFunc("15", Action::divide);
    setActionFunc("16", Action::assign);
    setActionFunc("17", Action::assign);
    setActionFunc("18", Action::assign);
    setActionFunc("19", Action::assign);
    setActionFunc("20", Action::assign);
}
}  // namespace plazy