#include "TimeTools.hpp"
#include <cmath>
#include <string>

int timetools::to_minutes(const std::string& time) {
    size_t pos = time.find(':');
    if (pos == std::string::npos) return -1;
    int hours   = std::stoi(time.substr(0, pos));
    int minutes = std::stoi(time.substr(pos + 1));
    return hours * 60 + minutes;
}

std::string timetools::to_time(int minutes) {
    int hours = minutes / 60;
    int mins  = minutes % 60;
    std::string result;
    if(hours < 10) result += "0";
    result += std::to_string(hours) + ":";
    if(mins < 10) result += "0";
    result += std::to_string(mins);
    return result;
}

int timetools::time_difference(int start_time, int end_time) {
    return std::abs(end_time - start_time);
}

int timetools::time_difference(const std::string& start_time, const std::string& end_time) {
    int start_minutes = to_minutes(start_time);
    int end_minutes   = to_minutes(end_time);
    if (start_minutes == -1 || end_minutes == -1) return -1;
    return timetools::time_difference(end_minutes, start_minutes);
}
