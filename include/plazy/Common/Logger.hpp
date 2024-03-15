#pragma once
#include <format>
#include <iostream>
#include <source_location>

namespace plazy
{
constexpr std::string_view _sourceFileName(std::string_view s)
{
#if defined(_WIN64) || defined(_WIN32)
    return s.substr(s.find_last_of('\\') + 1);
#else
    return s.substr(s.find_last_of('/') + 1);
#endif  // _WIN64 || _WIN32
}
}  // namespace plazy

#define _PLAZY_LOG_COLOR_RESET "\033[0m"
#define _PLAZY_LOG_RED "\033[1;31m"
#define _PLAZY_LOG_GREEN "\033[1;32m"
#define _PLAZY_LOG_YELLOW "\033[1;33m"
#define _PLAZY_LOG_BLUE "\033[1;34m"
#define _PLAZY_LOG_MAGENTA "\033[1;35m"
#define _PLAZY_LOG_CYAN "\033[1;36m"
#define _PLAZY_LOG_WHITE "\033[1;37m"

#define _PLAZY_LOG_FMT "[{}:{}|{}] >>> {}\n"

#define PLAZY_TRACE(...)                                                                           \
    std::cout << std::format(_PLAZY_LOG_FMT, plazy::_sourceFileName(__FILE__), __LINE__,           \
                             __FUNCTION__, std::format(__VA_ARGS__))

#define PLAZY_INFO(...)                                                                            \
    std::cout << std::format(_PLAZY_LOG_GREEN _PLAZY_LOG_FMT _PLAZY_LOG_COLOR_RESET,               \
                             plazy::_sourceFileName(__FILE__), __LINE__, __FUNCTION__,             \
                             std::format(__VA_ARGS__))

#define PLAZY_WARNING(...)                                                                         \
    std::cout << std::format(_PLAZY_LOG_YELLOW _PLAZY_LOG_FMT _PLAZY_LOG_COLOR_RESET,              \
                             plazy::_sourceFileName(__FILE__), __LINE__, __FUNCTION__,             \
                             std::format(__VA_ARGS__))

#define PLAZY_ERROR(...)                                                                           \
    std::cout << std::format(_PLAZY_LOG_RED _PLAZY_LOG_FMT _PLAZY_LOG_COLOR_RESET,                 \
                             plazy::_sourceFileName(__FILE__), __LINE__, __FUNCTION__,             \
                             std::format(__VA_ARGS__))

#define PLAZY_CRITICAL(...)                                                                        \
    std::cout << std::format(_PLAZY_LOG_CYAN _PLAZY_LOG_FMT _PLAZY_LOG_COLOR_RESET,                \
                             plazy::_sourceFileName(__FILE__), __LINE__, __FUNCTION__,             \
                             std::format(__VA_ARGS__))
