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

std::string strtools::single_split(const std::string& str, char delimiter) {
    size_t pos = str.find(delimiter);
    if (pos == std::string::npos) return "";
    return str.substr(0, pos);
}

std::vector<std::string> strtools::split_by_length(const std::string& str, size_t length) {
    size_t char_size = str.size() / strtools::utf8_strlen(str);
    size_t local_length{};
    std::vector<std::string> output;
    while(local_length < str.size()) {
        output.push_back(str.substr(local_length, length*char_size));
        local_length += length*char_size;
    }
    return output;
}

std::string strtools::multiline(const std::string& str, size_t max_line_length) {
    std::string output;
    auto words = split(str, ' ');
    size_t current_line_length = 0;
    for (const auto& word : words) {
        if (current_line_length + strtools::utf8_strlen(word) > max_line_length) {
            output = std::string(output.begin(), output.end()-1); output += "\n";
            if(strtools::utf8_strlen(word) > max_line_length) {
                auto split_word = strtools::split_by_length(word, max_line_length-1);
                for (const auto& split : split_word) {
                    output += split + "-\n";
                    current_line_length = strtools::utf8_strlen(split) + 1;
                }
                output = std::string(output.begin(), output.end()-2) + " ";
                continue;
            }
            current_line_length = 0;
        }
        output += word + " ";
        current_line_length += strtools::utf8_strlen(word) + 1;
    }
    return output;
}

std::string strtools::merge(const std::vector<std::string>& strs, const std::string& delimiter) {
    std::string output;
    for (size_t i = 0; i < strs.size(); ++i) {
        output += strs[i];
        if (i < strs.size() - 1) output += delimiter;
    }
    return output;
}

std::string strtools::str_to_base64(const std::string& str) {
    return base64pp::encode({reinterpret_cast<uint8_t const*>(str.data()),reinterpret_cast<uint8_t const*>(str.data()) + str.size()});
}

std::string strtools::base64_to_str(const std::string& str) {
    std::string b64 = str;
    while (!b64.empty() && (b64.back() == '\n' || b64.back() == '\r' || b64.back() == ' ' || b64.back() == '\t'))
        b64.pop_back();
    auto decoded = base64pp::decode(b64);
    if(!decoded) return {};
    return std::string{decoded->begin(), decoded->end()};
}

size_t strtools::utf8_strlen(const std::string& str) {
    size_t count = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) ++count;
    }
    return count;
}
