#include <array>
#include <string_view>

namespace plazy
{
    constexpr std::array<std::string_view, 13> KEYWORDS = {
        "const", "var", "procedure", "begin", "end", "if", 
        "then", "while", "do", "call", "odd", "write", "read" 
    };
}