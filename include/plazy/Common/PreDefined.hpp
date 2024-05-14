#pragma once
#include <array>
#include <cstdint>
#include <fstream>
#include <limits>
#include <string_view>

namespace plazy
{
constexpr auto PLAZY_EOF = std::char_traits<char>::eof();

constexpr std::array<std::string_view, 13> KEWORDS_STR = {
    "const", "var", "procedure", "begin", "end",   "if",  "then",
    "while", "do",  "call",      "odd",   "write", "read"};

constexpr std::array<char, 9> OPERATORS_CH = {'+', '-', '*', '/', '=', '#', '>', '<', ':'};

constexpr std::array<char, 5> DELIMITERS_CH = {'(', ')', ',', ';', '.'};

// Token >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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

// Token <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// Quadruple >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class Quadruple
{
public:
    Quadruple() = default;
    Quadruple(const std::string& _op, const std::string& _arg1, const std::string& _arg2,
              const std::string& _result)
        : op(_op), arg1(_arg1), arg2(_arg2), result(_result)
    {
    }

public:
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

// Quadruple <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}  // namespace plazy
