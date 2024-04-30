#pragma once
#include <array>
#include <cstdint>
#include <fstream>
#include <string_view>

#include "plazy/Common/PreDefined.hpp"
#include "plazy/Core/Token.hpp"

namespace plazy
{
/**
 * @brief PrettyLazy Lexer for PL/0 language
 */
class Lexer
{
public:
    explicit Lexer(const std::string& fileName);
    ~Lexer();
    /**
     * @brief Get next token from the file.
     *
     * @return plazy::Token, which consists of token type and its value.
     * @throw plazy::FileOpenFailed If file cannot be opened.
     * @throw plazy::NotImplemented If the function is not implemented.
     */
    Token nextToken();
    // [TODO] Remove these two functions. >>>>>>
    /**
     * @brief [Depricated] Determine whether the file is open.
     */
    bool fileIsOpen() const
    {
        return m_curChar != PLAZY_EOF;
    }
    /**
     * @brief [Depricated] Determine whether the file is closed.
     */
    bool fileIsClosed() const
    {
        return !fileIsOpen();
    }
    // [TODO] Remove these two functions. <<<<<<
    static inline bool cIsDelimiter(char c)
    {
        return std::ranges::find(DELIMITERS_CH, c) != DELIMITERS_CH.end();
    }
    /**
     * @brief Whether a character is in operator char set.
     * @see plazy::OPERATORS_CH
     *
     * @param c Character to check.
     * @return true - If character is an operator.
     * @return false - If character is not an operator.
     */
    static inline bool cIsOperator(char c)
    {
        return std::ranges::find(OPERATORS_CH, c) != OPERATORS_CH.end();
    }
    /**
     * @brief Whether a character is a digit.
     *
     * @param c Character to check.
     * @return true - If character is a digit.
     * @return false - If character is not a digit.
     */
    static inline bool cIsDigit(char c)
    {
        return std::isdigit(c);
    }
    /**
     * @brief Whether a character is an alphabet.
     *
     * @param c Character to check.
     * @return true - If character is an alphabet.
     * @return false - If character is not an alphabet.
     */
    static inline bool cIsAlpha(char c)
    {
        return std::isalpha(c);
    }
    /**
     * @brief Whether a character is an alphabet or a digit.
     *
     * @param c
     * @return true - If character is an alphabet or a digit.
     * @return false - If character is not an alphabet or a digit.
     */
    static inline bool cIsAlphaDigit(char c)
    {
        return cIsAlpha(c) || cIsDigit(c);
    }

    static std::string getEncodedType(const plazy::Token& token);

private:
    void nextChar();
    void skipWhitespace();
    void skipComment();
    Token parseNumber();
    Token parseDelimiter();
    Token parseOperator();
    Token parseKeywordOrIdentifier();
    Token parseUnknownSymbol();
    // [ToDo] >>>>>
    // Token parseString();
    // [ToDo] <<<<<

private:
    std::ifstream m_file;
    char m_curChar = PLAZY_EOF;
    std::uint32_t m_curLine = 1;
    std::uint32_t m_curCol = 0;
};
}  // namespace plazy
