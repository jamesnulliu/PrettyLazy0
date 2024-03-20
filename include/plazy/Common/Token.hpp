#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace plazy
{
enum class TokenType : uint8_t
{
    None = 0,
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

constexpr std::string_view KEYWORDS[] = {"const", "var",   "procedure", "begin", "end",
                                         "if",    "then",  "while",     "do",    "call",
                                         "odd",   "write", "read"};

constexpr std::array<char, 9> OPERATORS = {'+', '-', '*', '/', '=', '#', '<', '>', ':'};  // Single

constexpr std::array<char, 11> DELIMITERS = {'(', ')', ',', ';', '.'};

bool isKeyword(const std::string& word);
bool isOperator(char c);
bool isDelimiter(char c);
bool isNumber(const std::string& word);
}  // namespace plazy