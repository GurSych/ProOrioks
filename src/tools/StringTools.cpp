#include "StringTools.hpp"
#include <sstream>

std::string operator*(const std::string& str, size_t n) {
    std::string result{};
    result.reserve(str.size() * n);
    for (size_t i{}; i < n; ++i) result += str;
    return result;
}

std::vector<std::string> strtools::split(const std::string& str, char delimiter) {
    std::vector<std::string> output;
    std::string part;
    std::istringstream str_stream{str};
    while (std::getline(str_stream, part, delimiter)) {
        output.push_back(part);
    }
    return output;
}
