#include <Yutils/ArgParser.hpp>
#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <vector>

#include "plazy.hpp"

int main(int argc, char* argv[])
{
    yutils::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "tests/data/results/tokens.out");
    argParser.parse(argc, argv);

    std::string srcPath, outputPath;
    auto value = argParser.get<std::string>("f");
    YTRACE("Source file: {}", *value);
    srcPath = *value;

    value = argParser.get<std::string>("o");
    YTRACE("Output file: {}", *value);
    outputPath = *value;

    std::ifstream inFile(srcPath);
    std::ofstream outFile(outputPath);

    std::string line;
    std::vector<plazy::Quadruple> inputQuadruples;
    while (std::getline(inFile, line)) {
        std::vector<std::string> quadItmes = plazy::split(line, ',');
        plazy::Quadruple quad;
        quad.op = quadItmes.at(0);
        quad.arg1 = quadItmes.at(1);
        quad.arg2 = quadItmes.at(2) == " " ? "" : quadItmes.at(2);
        quad.result = quadItmes.at(3);
        inputQuadruples.push_back(quad);
    }

    plazy::Optimizer optimizer;
    optimizer.buildDAG(inputQuadruples);

    auto resultQuadruples = optimizer.colloectQuadruples();
    for (auto& quad : resultQuadruples) {
        outFile << std::format("{}, {}, {}, {}\n", quad.op, quad.arg1, quad.arg2, quad.result);
    }

    outFile.close();
}