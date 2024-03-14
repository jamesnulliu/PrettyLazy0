#pragma once

#include "PL0.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace plazy
{

constexpr bool is_keyword(std::string_view str)
{
    return std::ranges::find(KEYWORDS, str) != std::end(KEYWORDS);
}

constexpr bool _isDelimiter(char c)
{
    return false;
}

template <typename... Delimiters>
constexpr bool _isDelimiter(char c, char delimiter, Delimiters... delimiters)
{
    return c == delimiter || _isDelimiter(c, delimiters...);
}

template <typename... Delimiters>
std::vector<std::string_view> split(std::string_view str, Delimiters... delimiters)
{
    std::vector<std::string_view> result;

    if (str.size() > 0 && _isDelimiter(str[0], delimiters...)) {
        result.push_back("");
    }
    size_t start = 0, end = 0;
    while (end <= str.size()) {
        if (end == str.size() || _isDelimiter(str[end], delimiters...)) {
            if (start != end) {
                result.push_back(str.substr(start, end - start));
            }
            start = end + 1;
        }
        end++;
    }
    if (str.size() > 0 && _isDelimiter(str[str.size() - 1], delimiters...)) {
        result.push_back("");
    }
    return result;
}

}  // namespace plazy
