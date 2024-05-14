#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <vector>
#include <Yutils/ArgParser.hpp>

#include "plazy.hpp"

void analyzeSemantics(std::string srcPath)
{
    plazy::Lexer lexer(srcPath);
    std::vector<plazy::Token> tokens;

    try{
        for (plazy::Token token = lexer.nextToken(); token.type != plazy::TokenType::ENDOFFILE;
            token = lexer.nextToken()) {
            tokens.push_back(token);
        }
    } catch (const plazy::Exception& e) {
        YERROR("{}", e.what());
        return;
    }

    plazy::SemanticParser parser(tokens);
    parser.parseArithmeticExpr();
}

int main(int argc, char* argv[])
{
    yutils::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.parse(argc, argv);

    std::string srcPath;
    auto value = argParser.get<std::string>("f");
    YTRACE("Source file: {}", *value);
    srcPath = *value;

    analyzeSemantics(srcPath);
}