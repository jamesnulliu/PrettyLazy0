#pragma once
#include <fstream>
#include <array>
#include <string_view>

namespace plazy
{
constexpr auto PLAZY_EOF = std::char_traits<char>::eof();

// else?
constexpr std::array<std::string_view, 13> KEYWORDS = {
    "const", "var", "procedure", "begin", "end",   "if",  "then",
    "while", "do",  "call",      "odd",   "write", "read"};

constexpr std::array<char, 6> SINGLE_OPERATORS = {'+', '-', '*', '/', '=', '#'};
constexpr std::array<char, 3> SPECIAL_OPERATORS = {'<', '>', ':'};

constexpr std::array<char, 5> DELIMITERS = {'(', ')', ',', ';', '.'};
}  // namespace plazy
