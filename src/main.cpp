#include "plazy.hpp"
#include "Yutils/ArgParser.hpp"
#include "Yutils/Logger.hpp"

int main(int argc, char* argv[])
{
    for(size_t i=0; i<argc; ++i)
    {
        YTRACE("argv[{}]: {}", i, argv[i]);
    }

    yutils::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    std::string srcFile, outputFile;
    auto value = argParser.get<std::string>("f");
    if (value) {
        YTRACE("Source file: {}", value.value());
        srcFile = value.value();
    } else {
        YERROR("Source file not provided");
        return 1;
    }
    value = argParser.get<std::string>("o");
    if (value) {
        YTRACE("Output file: {}", value.value());
        outputFile = value.value();
    } else {
        YERROR("Output file not provided");
        return 1;
    }

    // plazy::Experiment::recognizeIdent(srcFile, outputFile);
    // plazy::Experiment::analyzeMorphology(srcFile, outputFile);

    return 0;
}