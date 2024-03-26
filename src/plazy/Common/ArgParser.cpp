#include "plazy/Common/ArgParser.hpp"
#include "plazy/Common/Exceptions.hpp"
#include <iostream>

namespace plazy
{
void ArgParser::addOption(std::string_view name, std::string_view description,
                          std::string_view type, std::optional<std::string> defaultValue)
{
    if (m_options.find(name) != m_options.end()) {
        PLAZY_ERROR("Option \"{}\" already exists", name);
        return;
    }
    if (type != "string" && type != "int" && type != "float" && type != "bool") {
        PLAZY_ERROR("Invalid type: \"{}\"; Supported types are: string, int, float, bool", type);
        return;
    }
    if (defaultValue && type != "string") {
        if (type == "int") {
            try {
                std::stoi(defaultValue.value());
            } catch (const std::invalid_argument& e) {
                PLAZY_ERROR("Invalid default value for option \"{}\"; Expected type: int", name);
                return;
            }
        } else if (type == "float") {
            try {
                std::stof(defaultValue.value());
            } catch (const std::invalid_argument& e) {
                PLAZY_ERROR("Invalid default value for option \"{}\"; Expected type: float", name);
                return;
            }
        } else if (type == "bool") {
            if (defaultValue.value() != "true" && defaultValue.value() != "false") {
                PLAZY_ERROR("Invalid default value for option \"{}\"; Expected type: bool", name);
                return;
            }
        }
    }
    m_options[name] = {std::string(description), std::string(type), defaultValue};
}

bool ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        size_t dashCount = 0;
        if (arg.starts_with("--")) {
            dashCount = 2;
        } else if (arg.starts_with("-")) {
            dashCount = 1;
        } else {
            PLAZY_ERROR("Invalid argument: \"{}\"; "
                        "An argument must starts with \"-\" or \"--\"",
                        arg);
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
}  // namespace plazy