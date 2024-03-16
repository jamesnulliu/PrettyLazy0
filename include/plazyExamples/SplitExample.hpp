#include "plazy.hpp"

inline void printSplitedString(auto&& str)
{
    for (size_t i = 0; i < str.size(); i++) {
        PLAZY_PRINT("str[{:>2}]: {}\n", i, str[i]);
    }
}

inline void splitExample()
{
    PLAZY_CRITICAL("********** Split Example Begin **********");

    std::string str = ".Hello, World! I am Tom. "
                      "I love coding. My favorite language is C++.";

    PLAZY_INFO("Original String: {}", str);

    PLAZY_CRITICAL("Splitting by '.'; "
                   "Note that a '\\0' is kept at the end and begin of the result");
    printSplitedString(plazy::split(str, '.'));

    PLAZY_CRITICAL("Splitting by '+'; "
                   "Note that multiple delimiters are treated as one.");
    printSplitedString(plazy::split(str, '+'));

    PLAZY_CRITICAL("Splitting by ' ', ',', '+', '.' and '!' together");
    printSplitedString(plazy::split(str, std::array{',', '+'}, ' ', std::vector{'.', '!'}));

    PLAZY_CRITICAL("********** Split Example End **********");
}