#pragma once
#include <cstdint>
#include <limits>
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
    TokenType type = TokenType::NONE;
    std::string value = "";
    std::uint32_t line = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t col = std::numeric_limits<std::uint32_t>::max();
};

std::string TokenType2Str(TokenType tokenType);
std::string TokenType2Str(Token token);

}  // namespace plazy