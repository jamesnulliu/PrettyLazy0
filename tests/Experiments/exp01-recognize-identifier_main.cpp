#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <format>

#include "plazy.hpp"
#include "Yutils/ArgParser.hpp"

using namespace plazy;

void recognizeIdent(const std::string& srcFile, const std::string& outputFile)
{
    Lexer lexer(srcFile);
    std::vector<std::pair<std::string, size_t>> identifiers;

    // Find out all identifiers
    for (Token token = lexer.nextToken(); token.type != TokenType::ENDOFFILE;
         token = lexer.nextToken()) {
        if (token.type == TokenType::IDENTIFIER) {
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
        throw FileOpenFailed(outputFile);
    }
    for (const auto& pair : identifiers) {
        output << std::format("({}: {})\n", pair.first, pair.second);
    }
    output.close();
}

int main(int argc, char* argv[])
{
    yutils::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    std::string srcFile, outputFile;
    auto value = argParser.get<std::string>("f");
    YTRACE("Source file: {}", *value);
    srcFile = *value;

    value = argParser.get<std::string>("o");
    YTRACE("Output file: {}", *value);
    outputFile = *value;

    recognizeIdent(srcFile, outputFile);
}