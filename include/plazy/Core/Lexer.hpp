#pragma once
#include "plazy/Common/PreDefined.hpp"
#include <array>
#include <cstdint>
#include <fstream>
#include <string_view>

namespace plazy
{
enum class TokenType : uint16_t
{
    NONE,
    KEYWORD,
    OPERATOR,
    DELIMITER,
    IDENTIFIER,
    NUMBER,
    ENDOFFILE
};

struct Token
{
    TokenType type;
    std::string value;
};

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
     * @throw plazy::InvalidWord If invalid word is found.
     * @throw plazy::UnknownOperator If unknown operator is found.
     */
    Token nextToken();

    bool fileIsOpen() const
    {
        return m_currentChar != PLAZY_EOF;
    }
    bool fileIsClosed() const
    {
        return !fileIsOpen();
    }
    static inline bool cIsDelimiter(char c)
    {
        return std::ranges::find(DELIMITERS_CH, c) != DELIMITERS_CH.end();
    }
    /**
     * @brief Whether a character is in operator char set.
     * @see plazy::OPERATORS_CH and plazy::OPERATORS_STR
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

private:
    void nextChar();
    void skipWhitespace();
    void skipComment();
    Token parseNumber();
    Token parseDelimiter();
    Token parseOpertor();
    Token getOperatorOrDelimiter();
    Token parseKeywordOrIdentifier();
    // [ToDo]
    // Token parseString();

private:
    std::ifstream m_file;
    char m_currentChar = PLAZY_EOF;
    size_t m_line = 1;
    size_t m_column = 1;
};
}  // namespace plazy
