#include "plazy.hpp"
#include "plazy/Common/Logger.hpp"
#include "example.hpp"
#include <string>

void printSplitedString(auto&& str)
{
    for (size_t i=0;i<str.size();i++)
    {
        PLAZY_PRINT("str[{:>2}]: {}\n", i, str[i]);
    }
}

void splitExample()
{
    PLAZY_CRITICAL("********** Split Example Begin **********");

    std::string str = "Hello, World! I am Tom. "
                      "I love coding. My favorite language is C++.";
    
    PLAZY_INFO("Original String: {}", str);

    PLAZY_CRITICAL("Splitting by '.'; Note that a ' ' is kept at the end of the string");
    printSplitedString(plazy::split(str, '.'));

    PLAZY_CRITICAL("Splitting by '+'; Note that multiple delimiters are treated as one.");
    printSplitedString(plazy::split(str, '+'));

    PLAZY_CRITICAL("Splitting by ' ', ',', '+', '.' and '!' together");
    printSplitedString(plazy::split(str, ' ', ',', '+', '.', '!'));

    PLAZY_CRITICAL("********** Split Example End **********");
}