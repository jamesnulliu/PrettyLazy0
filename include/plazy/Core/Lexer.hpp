#pragma once
#include <array>
#include <cstdint>
#include <fstream>
#include <string_view>
#include "plazy/Common/Predefine.hpp"

namespace plazy
{
enum class TokenType : uint16_t
{
    ENDOFFILE = 0,
    KEYWORD,
    OPERATOR,
    DELIMITER,
    IDENTIFIER,
    NUMBER
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

    bool fileIsOpen() const { return m_currentChar != PLAZY_EOF; }
    bool fileIsClosed() const { return !fileIsOpen(); }

private:
    void nextChar();
    void skipWhitespace();
    void skipComment();
    Token getNumber();
    Token getOperatorOrDelimiter();
    Token parseDelimiter();
    Token getKeywordOrIdentifier();
    // [ToDo]
    // Token parseString();

private:
    std::ifstream m_file;
    char m_currentChar = PLAZY_EOF;
};
}  // namespace plazy
