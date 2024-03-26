#include "plazy.hpp"
#include "plazy/Common/ArgParser.hpp"
#include "plazy/Common/Logger.hpp"

#include "plazyExamples/LoggerExample.hpp"
#include "plazyExamples/SplitExample.hpp"
#include "plazyExamples/LexerExample.hpp"

#include "plazyExperiments/RecognizeIdent.hpp"

int main(int argc, char* argv[])
{
    // for(size_t i=0; i<argc; ++i)
    // {
    //     PLAZY_TRACE("argv[{}]: {}", i, argv[i]);
    // }

    // loggerExample();
    // splitExample();
    // lexerExample();
    plazy::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    std::string srcFile, outputFile;
    auto value = argParser.get<std::string>("f");
    if (value) {
        PLAZY_TRACE("Source file: {}", value.value());
        srcFile = value.value();
    } else {
        PLAZY_ERROR("Source file not provided");
        return 1;
    }
    value = argParser.get<std::string>("o");
    if (value) {
        PLAZY_TRACE("Output file: {}", value.value());
        outputFile = value.value();
    } else {
        PLAZY_ERROR("Output file not provided");
        return 1;
    }

    plazy::Experiment::recognizeIdent(srcFile, outputFile);

    return 0;
}