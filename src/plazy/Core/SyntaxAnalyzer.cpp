#include "plazy/Core/SyntaxAnalyzer.hpp"
#include <format>
#include <iostream>
#include <ranges>

namespace plazy
{
void SyntaxAnalyzer::addSyntax(const Symbol& lhs, const std::vector<Symbol>& rhs)
{
    Syntax syntax{lhs, rhs};
    m_syntaxes.push_back(syntax);

    ///////////////////////////////////////////
    // Collect all terminals and non-terminals
    ///////////////////////////////////////////

    // For the left-hand side symbol, it must be a non-terminal.
    m_nonTerminals.insert(lhs);

    // For the right-hand side symbols, they can be terminals, non-terminals, or ε.
    if (rhs[0] == EPSILON) {  // Skip ε
        return;
    }

    for (const Symbol& sym : rhs) {
        if (std::isupper(sym[0])) {
            // If the symbol begins with A-Z, it is a non-terminal.
            m_nonTerminals.insert(sym);
        } else {
            // Otherwise, it is a terminal.
            // e.g. id, +, (
            m_terminals.insert(sym);
        }
    }
}

void SyntaxAnalyzer::calcFirstSets()
{
    m_firstSet.clear();

    //////////////////////////////////////////////////////
    // If X is a terminal symbol, then FIRST(X) = {X}.
    //////////////////////////////////////////////////////
    for (const Symbol& sym : m_terminals) {
        m_firstSet[sym] = {sym};
    }
    for (const Symbol& sym : m_nonTerminals) {
        m_firstSet[sym] = {};
    }

    // Keep iterating until no more symbols can be added to the FIRST set.
    bool updated;
    do {
        updated = false;
        m_firstSetCache.clear();

        for (const auto& syntax : m_syntaxes) {
            auto [firstSet, allHasEpsilon] = calcFirstSetOfSyms(syntax.rhs, 0, syntax.lhs.size());

            for (const Symbol& sym : firstSet) {
                auto [_, inserted] = m_firstSet[syntax.lhs].insert(sym);
                if (inserted) {
                    updated = true;
                }
            }

            if (!updated) {
                m_firstSetCache.push_back({firstSet, allHasEpsilon});
            }
        }
    } while (updated);
}

void SyntaxAnalyzer::calcFollowSets()
{
    m_followSet.clear();

    for (const auto& sym : m_nonTerminals) {
        m_followSet[sym] = {};
    }
    ///////////////////////////////////////////////////
    // Add # to the FOLLOW set of the begin symbol.
    ///////////////////////////////////////////////////
    m_followSet[m_beginSym].insert(ENDSYM);

    // Keep iterating until no more symbols can be added to the FOLLOW set.
    bool updated;
    do {
        updated = false;
        for (const auto& syntax : m_syntaxes) {
            const auto& lhs = syntax.lhs;
            const auto& rhs = syntax.rhs;

            for (size_t i = 0; i < rhs.size(); ++i) {
                const Symbol& rhsSym = rhs[i];

                if (isNonTerminal(rhsSym)) {
                    // Add the FIRST set of the next symbol to the FOLLOW set of the current symbol.
                    auto [firstSet, allHasEpsilon] = calcFirstSetOfSyms(rhs, i + 1, rhs.size());
                    for (const Symbol& sym : firstSet) {
                        if (sym != EPSILON) {
                            auto [_, inserted] = m_followSet[rhsSym].insert(sym);
                            if (inserted) {
                                updated = true;
                            }
                        }
                    }

                    // If the FIRST set of all symbols in the right-hand side contains ε, add the
                    // FOLLOW set of the left-hand side symbol.
                    if (allHasEpsilon) {
                        for (const Symbol& sym : m_followSet[lhs]) {
                            auto [_, inserted] = m_followSet[rhsSym].insert(sym);
                            if (inserted) {
                                updated = true;
                            }
                        }
                    }
                }
            }
        }
    } while (updated);
}

void SyntaxAnalyzer::calcSelectSets()
{
    calcFirstSets();
    calcFollowSets();

    m_selectSet.clear();
    m_selectSet.resize(m_syntaxes.size());

    for (size_t i = 0; i < m_syntaxes.size(); ++i) {
        const auto& lhs = m_syntaxes[i].lhs;
        const auto& rhs = m_syntaxes[i].rhs;

        auto [firstSet, allHasEpsilon] = m_firstSetCache[i];
        for (const Symbol& sym : firstSet) {
            if (sym != EPSILON) {
                m_selectSet[i].insert(sym);
            }
        }
        if (allHasEpsilon) {
            for (const Symbol& sym : m_followSet[lhs]) {
                m_selectSet[i].insert(sym);
            }
        }
    }

    m_firstSetCache.clear();
}

std::pair<std::set<Symbol>, bool> SyntaxAnalyzer::calcFirstSetOfSyms(const std::vector<Symbol>& syms,
                                                             size_t beginIdx, size_t endIdx) const
{
    std::set<Symbol> firstSet;

    //////////////////////////////////////////////////////////////////////////
    // If X -> ε, then add ε to FIRST(X).
    //////////////////////////////////////////////////////////////////////////
    if (syms[beginIdx] == EPSILON) {
        firstSet.insert(EPSILON);
        return {firstSet, true};
    }

    size_t i = beginIdx;
    for (; i < endIdx; ++i) {
        ////////////////////////////////////////////////////////////////////////////
        // If Y1, Y2, ..., Yi-1 => ε, then add First(Y1)-{ε}, First(Y2)-{ε}, ...,
        // First(Yi) to FIRST(X).
        ////////////////////////////////////////////////////////////////////////////
        if (isNonTerminal(syms[i])) {
            bool hasEpsilon = false;
            for (const Symbol& sym : m_firstSet.at(syms[i])) {
                if (sym != EPSILON) {
                    firstSet.insert(sym);
                } else {
                    hasEpsilon = true;
                }
            }

            if (!hasEpsilon) {
                break;
            }
        } else {
            //////////////////////////////////////////////////////////////////////////
            // If there is a terminal, then add it to FIRST(X) and stop the loop.
            //////////////////////////////////////////////////////////////////////////
            firstSet.insert(syms[i]);
            break;
        }
    }

    //////////////////////////////////////////////////////////////////
    // If Yi => ε for all i = 1, 2, ..., k, then add ε to FIRST(X).
    //////////////////////////////////////////////////////////////////
    bool allHasEpsilon = (i == endIdx);
    if (allHasEpsilon) {
        firstSet.insert(EPSILON);
    }
    return {firstSet, allHasEpsilon};
}

void SyntaxAnalyzer::clear()
{
    m_terminals.clear();
    m_nonTerminals.clear();
    m_firstSet.clear();
    m_followSet.clear();
    m_syntaxes.clear();
    m_selectSet.clear();
}

}  // namespace plazy