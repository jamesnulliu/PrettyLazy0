#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "plazy.hpp"

inline void recognizeIdent(const std::string& srcFile, const std::string& outputFile)
{
    plazy::Lexer lexer(srcFile);
    std::vector<std::pair<std::string, size_t>> identifiers;

    // Find out all identifiers
    while (lexer.fileIsOpen()) {
        plazy::Token token = lexer.nextToken();

        if (token.type == plazy::TokenType::IDENTIFIER) {
            auto it = std::ranges::find_if(
                identifiers, [&token](const auto& pair) { return pair.first == token.value; });

            if (it == identifiers.end()) {
                identifiers.push_back({token.value, 1});
            } else {
                it->second++;
            }
        }
    }

    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw plazy::FileOpenFailed(outputFile);
    }
    for (const auto& pair : identifiers) {
        output << std::format("({}: {})\n", pair.first, pair.second);
    }
    output.close();
}