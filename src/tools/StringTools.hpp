#ifndef STRING_TOOLS_HPP
#define STRING_TOOLS_HPP

#pragma once
#include <string>
#include <vector>

std::string operator*(const std::string& str, size_t n);

namespace strtools {
    std::vector<std::string> split(const std::string& str, char delimiter = ' ');
}

#endif // STRING_TOOLS_HPP
