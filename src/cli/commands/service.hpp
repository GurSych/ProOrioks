#ifndef SERVICE_HPP
#define SERVICE_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include "config.hpp"
#include <iostream>

namespace cmd {
    class Service : public cli::Command {
    public:
        Service() : cli::Command("service", "Display service information", "hide") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            std::cout << "Service information\n" << std::endl;
            std::cout << "Version: " << __APP_VERSION__ << std::endl;
            std::cout << "Build OS/arch: "   << __BUILD_OS__ << "/" << __BUILD_ARCH__ << std::endl;
            std::cout << "Build compiler: "  << __BUILD_COMPILER__ << std::endl;
            std::cout << "Config path: " << app.dataStorage().config_path() << std::endl;
            std::cout << "ANSI format check: " << "standart text" << std::endl
                      << "                   " << tcl::colorize("    bold text\t",tcl::BOLD) << std::endl;
            std::cout << "ANSI color check: "
                << tcl::colorize(" #",{tcl::BLACK,tcl::BKG_BLACK}) << tcl::colorize(" #",{tcl::RED,tcl::BKG_RED})
                << tcl::colorize(" #",{tcl::GREEN,tcl::BKG_GREEN}) << tcl::colorize(" #",{tcl::YELLOW,tcl::BKG_YELLOW})   << std::endl
                << "                  "
                << tcl::colorize(" #",{tcl::BLUE,tcl::BKG_BLUE})   << tcl::colorize(" #",{tcl::MAGENTA,tcl::BKG_MAGENTA})
                << tcl::colorize(" #",{tcl::CYAN,tcl::BKG_CYAN})   << tcl::colorize(" #",{tcl::WHITE,tcl::BKG_WHITE})     << std::endl;
            std::cout << "Russian alphabet: " << "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" << std::endl
                      << "                  " << "абвгдеёжзийклмнопрстуфхцчшщъыьэюя" << std::endl;
            std::cout << "Special UNICODE symbols: " << "◎ —" << std::endl;
            return 0;
        }
    };
}

#endif // SERVICE_HPP
