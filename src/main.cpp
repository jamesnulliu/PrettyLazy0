#include "plazy.hpp"
#include "plazy/Common/ArgParser.hpp"
#include "plazy/Common/Logger.hpp"

#include "plazyExamples/LoggerExample.hpp"
#include "plazyExamples/SplitExample.hpp"

#include "plazy/Experiment/RecognizeIdent.hpp"

int main(int argc, char* argv[])
{
    // for(size_t i=0; i<argc; ++i)
    // {
    //     PLAZY_TRACE("argv[{}]: {}", i, argv[i]);
    // }

    // loggerExample();
    // splitExample();

    plazy::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    // PLAZY_TRACE("Source file: {}", argParser.get<std::string>("f").value());
    // PLAZY_TRACE("Output file: {}", argParser.get<std::string>("o").value());

    // auto srcFile = argParser.get<std::string>("f").value();
    // auto outputFile = argParser.get<std::string>("o").value();

    recognizeIdent("../pl0-src-code/rec-ident-case1.pl0", "main.out");

    return 0;
}