#pragma once
#include <cstdint>
#include <string>

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

std::string TokenType2Str(TokenType tokenType);
std::string TokenType2Str(Token token);

}