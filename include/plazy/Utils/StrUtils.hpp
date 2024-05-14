#include <charconv>
#include <concepts>
#include <optional>
#include <string>
#include <vector>

namespace plazy
{

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
std::vector<std::string> split(std::string str, Delimiters... delimiters)
{
    std::vector<std::string> result;

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

template <typename T>
    requires std::integral<T> || std::floating_point<T>
std::optional<T> string_to_number(const std::string& str)
{
    T value = 0;
    auto result = std::from_chars(str.data(), str.data() + str.size(), value);

    if (result.ec == std::errc{} && result.ptr == str.data() + str.size()) {
        return value;
    } else {
        return std::nullopt;
    }
}

}  // namespace plazy