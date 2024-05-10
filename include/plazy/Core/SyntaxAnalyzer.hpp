#pragma once
#include "plazy/Core/SyntaxAnalyzer.hpp"
#include "plazy/Core/Symbol.hpp"
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

namespace plazy
{
// lhs -> rhs
struct Syntax
{
    Symbol lhs;
    std::vector<Symbol> rhs;
};

class SyntaxAnalyzer
{
public:
    void addSyntax(const Symbol& lhs, const std::vector<Symbol>& rhs);
    void calcSelectSets();

    inline void setBeginSym(const Symbol& sym)
    {
        m_beginSym = sym;
    }

    inline const Symbol& getBeginSym() const
    {
        return m_beginSym;
    }

    inline const std::vector<Syntax>& getSyntaxes() const
    {
        return m_syntaxes;
    }

    inline const std::set<Symbol>& getFirstSet(const Symbol& sym) const
    {
        return m_firstSet.at(sym);
    }

    inline const std::set<Symbol>& getFollowSet(const Symbol& sym) const
    {
        return m_followSet.at(sym);
    }

    inline const std::set<Symbol>& getSelectSet(size_t syntaxIndex) const
    {
        return m_selectSet[syntaxIndex];
    }

    inline bool isNonTerminal(const Symbol& sym) const
    {
        return m_nonTerminals.find(sym) != m_nonTerminals.end();
    }

    inline bool isTerminal(const Symbol& sym) const
    {
        return m_terminals.find(sym) != m_terminals.end();
    }

    void clear();

private:
    // Return <FirstSetOfsyms, allHasEpsilon>
    std::pair<std::set<Symbol>, bool> calcFirstSetOfSyms(const std::vector<Symbol>& syms,
                                                         size_t beginIdx, size_t endIdx) const;

    void calcFirstSets();
    void calcFollowSets();

private:
    Symbol m_beginSym;
    std::set<Symbol> m_terminals;
    std::set<Symbol> m_nonTerminals;

    // Use index to access syntaxes and select set.
    std::vector<Syntax> m_syntaxes;
    std::vector<std::set<Symbol>> m_selectSet;

    std::map<Symbol, std::set<Symbol>> m_firstSet;
    std::map<Symbol, std::set<Symbol>> m_followSet;

    // Save the result of FIRST set for SELECT set calculation.
    // Element: <FirstSetOfsyms, allHasEpsilon>
    mutable std::vector<std::pair<std::set<Symbol>, bool>> m_firstSetCache;
};

}  // namespace plazy
