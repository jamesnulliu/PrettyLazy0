#pragma once
#include "plazy/Common/PreDefined.hpp"
#include "plazy/Core/Symbol.hpp"
#include "plazy/Core/SyntaxAnalyzer.hpp"
#include <functional>
#include <map>

namespace plazy
{
constexpr int NO_VALUE = -999999999;

class SemanticParser
{
    using ActionFunc = std::function<int(const std::vector<int>&)>;

public:
    SemanticParser(const std::vector<Token>& tokens);

    void parseArithmeticExpr();

private:
    void initSyntax();

    void addSyntax(const Symbol& lhs, const std::vector<Symbol>& rhs, int indexOffset = NO_VALUE);
    void setActionFunc(const std::string& index, const ActionFunc& func);

    void generateTables();

private:
    std::vector<Token> m_tokenStack;
    std::vector<Element> m_elemStack;
    SyntaxAnalyzer m_analyzer;

    std::vector<std::vector<Symbol>> m_rhsWithActions;
    std::vector<int> m_indexOffsets;

    std::map<Symbol, std::map<Symbol, std::vector<Symbol>>> m_predictionTable;
    // Locate where the value of an non-terminal symbol should be passed to.
    std::map<Symbol, std::map<Symbol, int>> m_indexOffsetTable;
    std::map<std::string, ActionFunc> m_actionFuncs;
};

}  // namespace plazy