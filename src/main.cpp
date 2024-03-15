#include "plazy.hpp"
#include "plazy/Common/ArgParser.hpp"
#include "plazy/Common/Logger.hpp"

#include "example.hpp"

int main(int argc, char* argv[])
{
    loggerExample();

    plazy::ArgParser argParser;
    argParser.addOption("f", "The source file to be compiled", "string");
    argParser.addOption("o", "The output file", "string", "a.out");
    argParser.parse(argc, argv);

    PLAZY_TRACE("Source file: {}", *argParser.get<std::string>("f"));
    PLAZY_TRACE("Output file: {}", *argParser.get<std::string>("o"));

    return 0;
}