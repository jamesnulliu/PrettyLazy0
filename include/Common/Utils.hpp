#pragma once

#include "PL0.hpp"
#include <string>

namespace plazy
{

constexpr bool is_keyword(std::string_view str)
{
    return std::ranges::find(KEYWORDS, str) != std::end(KEYWORDS);
}

}  // namespace plazy
