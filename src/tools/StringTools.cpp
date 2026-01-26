#include "StringTools.hpp"
#include <sstream>

std::vector<std::string> strtools::split(const std::string& str, char delimiter) {
    std::vector<std::string> output;
    std::string part;
    std::istringstream str_stream{str};
    while (std::getline(str_stream, part, delimiter)) {
        output.push_back(part);
    }
    return output;
}
