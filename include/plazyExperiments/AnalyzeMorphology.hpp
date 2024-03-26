#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "plazy.hpp"

namespace plazy::Experiment
{
inline std::string getEncodedType(const plazy::Token& token)
{
    switch (token.type) {
    case plazy::TokenType::IDENTIFIER: {
        return "ident";
    }
    case plazy::TokenType::NUMBER: {
        return "number";
    }
    case plazy::TokenType::KEYWORD: {
        return token.value + "sym";
    }
    case plazy::TokenType::OPERATOR: {
        if (token.value == "+") {
            return "plus";
        } else if (token.value == "-") {
            return "minus";
        } else if (token.value == "*") {
            return "times";
        } else if (token.value == "/") {
            return "slash";
        } else if (token.value == "=") {
            return "eql";
        } else if (token.value == "#") {
            return "neq";
        } else if (token.value == "<") {
            return "lss";
        } else if (token.value == "<=") {
            return "leq";
        } else if (token.value == ">") {
            return "gtr";
        } else if (token.value == ">=") {
            return "geq";
        } else if (token.value == ":=") {
            return "becomes";
        } else {
            throw plazy::InvalidOperator(token.value);
        }
    }
    case plazy::TokenType::DELIMITER: {
        if (token.value == "(") {
            return "lparen";
        } else if (token.value == ")") {
            return "rparen";
        } else if (token.value == ",") {
            return "comma";
        } else if (token.value == ";") {
            return "semicolon";
        } else if (token.value == ".") {
            return "period";
        } else {
            throw plazy::InvalidOperator(token.value);
        }
    }
    }
    return "nul";
}

inline void analyzeMorphology(const std::string& srcFile, const std::string& outputFile)
{
    plazy::Lexer lexer(srcFile);

    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw plazy::FileOpenFailed(outputFile);
    }
    while (lexer.fileIsOpen()) {
        plazy::Token token = lexer.nextToken();
        std::string encodedType = getEncodedType(token);
        output << std::format("({}, {})\n", encodedType, token.value);
    }
    output.close();
}
}  // namespace plazy::Experiment