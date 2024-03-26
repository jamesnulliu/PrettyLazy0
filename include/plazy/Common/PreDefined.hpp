#pragma once
#include <array>
#include <fstream>
#include <string_view>

namespace plazy
{
constexpr auto PLAZY_EOF = std::char_traits<char>::eof();

constexpr std::array<std::string, 13> KEWORDS_STR = {
    "const", "var", "procedure", "begin", "end",   "if",  "then",
    "while", "do",  "call",      "odd",   "write", "read"};

constexpr std::array<char, 9> OPERATORS_CH = {'+', '-', '*', '/', '=', '#', '>', '<', ':'};

constexpr std::array<std::string, 11> OPERATORS_STR = {
    "+", "-", "*", "/", "=", "#=", "<", ">", "<=", ">=", ":="};

constexpr std::array<char, 5> DELIMITERS_CH = {'(', ')', ',', ';', '.'};
}  // namespace plazy
