#ifndef PROORIOKS_SRC_TOOLS_TIME_TOOLS_HPP
#define PROORIOKS_SRC_TOOLS_TIME_TOOLS_HPP

#include "StringTools.hpp"
#include <string>
#include <cstdlib>

namespace timetools {
    int to_minutes(const std::string& time);
    std::string to_time(int minutes);
    int time_difference(int start_time, int end_time);
    int time_difference(const std::string& start_time, const std::string& end_time);
}

#endif //PROORIOKS_SRC_TOOLS_TIME_TOOLS_HPP
