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

constexpr std::string strip(std::string_view str)
{
    size_t start = 0, end = str.size();
    while (start < str.size() && std::isspace(str[start])) {
        start++;
    }
    while (end > 0 && std::isspace(str[end - 1])) {
        end--;
    }
    return std::string(str.substr(start, end - start));
}

constexpr bool _isDelimiter(char c, char delim)
{
    return c == delim;
}

constexpr bool _isDelimiter(char c, const std::ranges::range auto& delims)
{
    return std::ranges::find(delims, c) != std::end(delims);
}

constexpr bool _checkDelimiter(char)
{
    return false;
}

template <typename Delim, typename... RestDelims>
bool _checkDelimiter(char c, Delim&& delim, RestDelims&&... restDelims)
{
    return _isDelimiter(c, std::forward<Delim>(delim)) ||
           _checkDelimiter(c, std::forward<RestDelims>(restDelims)...);
}

template <typename... Delims>
std::vector<std::string> split(std::string_view str, Delims&&... delims)
{
    if (str.empty()) {
        return {};
    }
    std::vector<std::string> result;
    // If the first character is a delimiter, add an empty string to the result
    if (_checkDelimiter(str[0], std::forward<Delims>(delims)...)) {
        result.emplace_back("");
    }
    size_t start = 0;
    for (size_t i = 0; i <= str.size(); ++i) {
        if (i == str.size() || _checkDelimiter(str[i], std::forward<Delims>(delims)...)) {
            if (start < i) {
                result.emplace_back(str.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    // If the last character is a delimiter, add an empty string to the result
    if (_checkDelimiter(str[str.size() - 1], std::forward<Delims>(delims)...)) {
        result.emplace_back("");
    }
    return result;
}

}  // namespace plazy
