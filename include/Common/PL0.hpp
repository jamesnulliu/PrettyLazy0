#pragma once

#include <array>
#include <string>
#include <string_view>

namespace plazy
{
enum class TokenType
{
    IDENT,
    NUMBER,
    KEYWORD,
    SYMBOL,
};

struct Token
{
    TokenType type;
    std::string value;
};

inline constexpr auto KEYWORDS = std::array{"const", "var", "procedure", "begin", "end",   "if",  "then",
                                            "while", "do",  "call",      "odd",   "write", "read"};

}  // namespace plazy