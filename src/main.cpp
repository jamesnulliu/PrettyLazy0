#include "plazy.hpp"
#include <format>
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    std::cout << std::format("'SHU' {} a PL/0 keyword\n", plazy::is_keyword("SHU") ? "is" : "is not");
    return 0;
}