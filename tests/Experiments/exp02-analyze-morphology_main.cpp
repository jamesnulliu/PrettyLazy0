#include "plazy.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <format>
#include "Yutils/ArgParser.hpp"

using namespace plazy;

void analyzeMorphology(const std::string& srcFile, const std::string& outputFile)
{
    Lexer lexer(srcFile);

    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw FileOpenFailed(outputFile);
    }
    for (Token token = lexer.nextToken(); token.type != TokenType::ENDOFFILE;
         token = lexer.nextToken()) {
        std::string encodedType = Lexer::getEncodedType(token);
        output << std::format("({}, {})\n", encodedType, token.value);
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

    analyzeMorphology(srcFile, outputFile);
}