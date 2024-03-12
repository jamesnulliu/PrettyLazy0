#pragma once

#include "PL0.hpp"
#include <string>

namespace plazy
{
    
consteval bool is_keyword(const char* str)
{
    for (const auto& keyword : KEYWORDS) {
        if (str == keyword) {
            return true;
        }
    }
    return false;
}

inline bool is_keyword(const std::string& str)
{
    for (const auto& keyword : KEYWORDS) {
        if (str == keyword) {
            return true;
        }
    }
    return false;
}

} // namespace plazy
