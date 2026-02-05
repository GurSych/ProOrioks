#ifndef ORIOKS_LINE_HPP
#define ORIOKS_LINE_HPP

#pragma once
#include <string>
#include <cstddef>
#include "../TinyColor.hpp"
#include "../../tools/StringTools.hpp"

namespace tmpl {
    std::string OrioksLine(size_t level = 1ull) {
        return tcl::colorize("ProOrioks",{tcl::WHITE,tcl::BKG_CYAN}) + std::string{" >"}*level + " ";
    }
}

#endif // ORIOKS_LINE_HPP
