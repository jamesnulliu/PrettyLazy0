#include <algorithm>
#include <fstream>
#include <string>

#include "plazy.hpp"

void recognizeIdent(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        // Remove leading and trailing whitespaces
        plazy::strip(line);
        // To lower case
        std::ranges::transform(line, line.begin(), ::tolower);
        if (line.size() == 0 || line[0] == '{') {
            continue;
        }
    }
}