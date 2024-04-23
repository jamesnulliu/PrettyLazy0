#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <vector>

#include <Yutils/ArgParser.hpp>

#include "plazy.hpp"

void analyzeGrammar(std::string srcPath, std::string tokenOutputPath)
{
    plazy::Lexer lexer(srcPath);
    std::vector<plazy::Token> tokens;

    std::ofstream tokenOut(tokenOutputPath);
    if (!tokenOut.is_open()) {
        throw plazy::FileOpenFailed(tokenOutputPath);
    }

    for (plazy::Token token = lexer.nextToken(); token.type != plazy::TokenType::ENDOFFILE;
         token = lexer.nextToken()) {
        tokens.push_back(token);
    }

    plazy::Parser parser(tokens);
    try{
        parser.parseProgram();
    }catch(const plazy::Exception& e){
        YERROR("{}", e.what());
        return;
    }
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

    analyzeGrammar(srcFile, outputFile);
}