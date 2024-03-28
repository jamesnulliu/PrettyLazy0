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
        // PLAZY_INFO("{}", token.value);
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

int main(int argc, char* argv[])
{
    plazy::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    std::string srcFile, outputFile;
    auto value = argParser.get<std::string>("f");
    PLAZY_TRACE("Source file: {}", *value);
    srcFile = *value;

    value = argParser.get<std::string>("o");
    PLAZY_TRACE("Output file: {}", *value);
    outputFile = *value;

    recognizeIdent(srcFile, outputFile);
}