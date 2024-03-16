#include "plazy/Common/ArgParser.hpp"
#include <iostream>

void plazy::ArgParser::addOption(std::string_view name, std::string_view description,
                                 std::string_view type, std::optional<std::string> defaultValue)
{
    m_options[name] = {description, type, defaultValue};
}

bool plazy::ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        size_t dashCount = 0;
        if (arg.starts_with("--")) {
            dashCount = 2;
        } else if (arg.starts_with("-")) {
            dashCount = 1;
        } else {
            PLAZY_ERROR("Invalid argument: \"{}\"; An argument must starts with \"-\" or \"--\"", arg);
            return false;
        }
        arg.remove_prefix(dashCount);
        auto it = m_options.find(arg);
        if (it != m_options.end()) {
            if (i + 1 < argc) {
                it->second.value = argv[i + 1];
                ++i;
            } else {
                PLAZY_ERROR("Option \"{}\" requires a value", arg);
                return false;
            }
        } else {
            PLAZY_ERROR("Unknown option: \"{}\"", arg);
            return false;
        }
    }
    return true;
}