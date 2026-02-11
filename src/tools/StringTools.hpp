#ifndef PROORIOKS_SRC_TOOLS_STRING_TOOLS_HPP
#define PROORIOKS_SRC_TOOLS_STRING_TOOLS_HPP

#pragma once
#include <string>
#include <vector>
#include "base64pp/base64pp.h"

std::string operator*(const std::string& str, size_t n);

namespace strtools {
    std::vector<std::string> split(const std::string& str, char delimiter = ' ');
    std::string single_split(const std::string& str, char delimiter = ' ');
    std::vector<std::string> split_by_length(const std::string& str, size_t length);

    std::string multiline(const std::string& str, size_t max_line_length);
    std::string merge(const std::vector<std::string>& strs, const std::string& delimiter = "");

    std::string str_to_base64(const std::string& str);
    std::string base64_to_str(const std::string& str);

    size_t utf8_strlen(const std::string& str);
}

#endif // PROORIOKS_SRC_TOOLS_STRING_TOOLS_HPP
