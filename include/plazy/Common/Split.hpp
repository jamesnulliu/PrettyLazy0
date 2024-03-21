#pragma once
#include <string>
#include <vector>

#include "plazy/Core/Lexer.hpp"

namespace plazy
{
    const std::vector<Token> &getTokens();

    void addToken(const std::string &word);
    void addToken(const std::string &word, TokenType type);

    void split(const std::string &str);
}