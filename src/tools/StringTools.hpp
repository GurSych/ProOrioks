#ifndef STRING_TOOLS_HPP
#define STRING_TOOLS_HPP

#pragma once
#include <string>
#include <vector>
#include "base64pp/base64pp.h"

std::string operator*(const std::string& str, size_t n);

namespace strtools {
    std::vector<std::string> split(const std::string& str, char delimiter = ' ');
    std::string str_to_base64(const std::string& str);
    std::string base64_to_str(const std::string& str);
}

#endif // STRING_TOOLS_HPP
