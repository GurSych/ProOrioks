// Tiny and simple library for console colorization
// by Gur-Sych (https://github.com/GurSych)

#ifndef TINY_COLOR_HPP
#define TINY_COLOR_HPP

#pragma once
#include <initializer_list>
#include <iostream>
#include <string>

namespace tcl {
    enum OptionList {
        RESET       = 0,
        BOLD        = 1,
        UNDERLINE   = 4,
        BLACK       = 30,
        RED         = 31,
        GREEN       = 32,
        YELLOW      = 33,
        BLUE        = 34,
        MAGENTA     = 35,
        CYAN        = 36,
        WHITE       = 37,
        BKG_BLACK   = 40,
        BKG_RED     = 41,
        BKG_GREEN   = 42,
        BKG_YELLOW  = 43,
        BKG_BLUE    = 44,
        BKG_MAGENTA = 45,
        BKG_CYAN    = 46,
        BKG_WHITE   = 47
    };

    inline void set(OptionList option) {
        std::cout << "\033[" << option << "m";
    }

    inline void reset() {
        std::cout << "\033[" << RESET << "m";
    }

    inline std::string colorize(const std::string& text, OptionList option) {
        std::string out = "\033[";
        out += std::to_string(option) + "m" + text + "\033[" + std::to_string(RESET) + "m";
        return out;
    }

    inline std::string colorize(const std::string& text, std::initializer_list<OptionList> options) {
        std::string out = "\033[";
        for (auto option : options) {
            out += std::to_string(option) + ";";
        }
        out.pop_back();
        out += "m" + text + "\033[" + std::to_string(RESET) + "m";
        return out;
    }

}

#endif // TINY_COLOR_HPP
