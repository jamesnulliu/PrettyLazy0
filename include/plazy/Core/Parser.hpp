#pragma once
#include "plazy/Core/Token.hpp"
#include <vector>

namespace plazy
{
class Parser
{
public:
    explicit Parser() = default;
    explicit Parser(const std::vector<Token>& tokens) : m_tokens(tokens)
    {
    }

    /**
     * @brief Parse the tokens.
     *        <program> ::= <constDeclaration> <varDeclaration> <block>
     */
    void parseProgram();

    /**
     * @brief Parse the constant declaration.
     *        <constDeclaration> ::= const <identifier> = <number> {, <identifier> = <number>};
     */
    void constDeclaration();

    /**
     * @brief Parse the variable declaration.
     *        <varDeclaration> ::= var <identifier> {, <identifier>};
     */
    void varDeclaration();

    /**
     * @brief Parse the block.
     *        <block> ::= begin <statement>; {<statement>;} end
     */
    void block();

    /**
     * @brief Parse the statement.
     *        <statement> ::= <if-statement> | <while-statement> | <assignment-statement>
     */
    void statement();

    /**
     * @brief Parse the if statement.
     *        <if-statement> ::= if <condition> then <statement>
     */
    void ifStatement();

    /**
     * @brief Parse the while statement.
     *        <while-statement> ::= while <condition> do <statement>
     */
    void whileStatement();

    /**
     * @brief Parse the assignment statement.
     *        <assignment-statement> ::= <identifier> := <expression>
     */
    void assignmentStatement();

    /**
     * @brief Parse the expression.
     *        <expression> ::= [+|-]<term> {<addop><term>}
     */
    void expression();

    /**
     * @brief Parse the term.
     *        <term> ::= <factor> {<mulop><factor>}
     */
    void term();

    /**
     * @brief Parse the factor.
     *        <factor> ::= <number> | <identifier> | "(" <expression> ")"
     */
    void factor();

    /**
     * @brief Parse the condition.
     *        <condition> ::= <expression> <relational-operator> <expression>
     */
    void condition();

private:
    /**
     * @brief Get the current token.
     *
     * @return Token that the parser is currently at.
     */
    const Token& curToken() const
    {
        return m_tokens.at(m_curTokenIdx);
    }

    const Token& lastToken() const 
    {
        return m_tokens.at(m_curTokenIdx - 1);
    }

    /**
     * @brief Check if the parser is at the end of the token list.
     *
     * @return <true> - If the parser is at the end of the token list.
     *         <false> - If the parser is not at the end of the token list.
     */
    inline bool isAtEnd() const
    {
        return m_curTokenIdx >= m_tokens.size();
    }

    /**
     * @brief Advance to the next token.
     *        If the end of the token list is reached, does nothing.
     */
    inline void advance()
    {
        if (!isAtEnd()) {
            m_curTokenIdx++;
        }
    }

    /**
     * @brief Go back to the previous token.
     *        If the current token is the first token, does nothing.
     */
    inline void previous()
    {
        if (m_curTokenIdx > 0) {
            m_curTokenIdx--;
        }
    }

    /**
     * @brief Consume the current token if it matches the given type and value.
     *        Both type and value must match.
     *
     * @param tokenType TokenType to match.
     * @param value Value to match.
     *
     * @return Token that was consumed.
     *
     * @throw `RuntimeError` If the current token does not match the given type and value.
     *
     * @note `advance()` would be called if the current token matches the given type and value.
     */
    Token consume(TokenType tokenType, const std::string& value);

    /**
     * @brief Check if the current token matches the given type and value.
     *        If param `value` is empty, only the type is checked.
     *
     * @param type TokenType to match.
     * @param value Value to match.
     *
     * @return <true> - If the current token matches the given type and value.
     *         <false> - If the current token does not match the given type and value.
     *
     * @note `advance()` would be called if the current token matches the given type and value.
     */
    bool match(TokenType type, const std::string& value = "");

    /**
     * @brief Check if the current token matches the given type and value.
     *        If param `value` is empty, only the type is checked.
     *
     * @param type TokenType to match.
     * @param value Value to match.
     *
     * @return <true> - If the current token matches the given type and value.
     *         <false> - If the current token does not match the given type and value.
     */
    template <typename... Args>
    bool match(TokenType type, const std::string& value, Args... values)
    {
        if (match(type, value)) {
            return true;
        }
        return match(type, std::forward<Args>(values)...);
    }

private:
    std::vector<Token> m_tokens = {};
    std::size_t m_curTokenIdx = 0;
};
}  // namespace plazy
