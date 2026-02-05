#ifndef ABOUT_HPP
#define ABOUT_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include "config.hpp"
#include <iostream>

namespace cmd {
    class About : public cli::Command {
    public:
        About() : Command("about", "Display information about the program",
                    "Command display information about the program", "system") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            std::cout << tcl::colorize("ProOrioks",{tcl::BOLD,tcl::WHITE,tcl::BKG_CYAN})
                        << tcl::colorize(" is a console mini-program to access and analyze information from the MIET's Orioks system",tcl::BOLD) << std::endl;
            std::cout << "Version: " << __APP_VERSION__ << std::endl;
            std::cout << "Author: " << tcl::colorize("Gur-Sych",tcl::BOLD) << " (https://github.com/GurSych)" << std::endl;
            std::cout << "Project Repository: https://github.com/GurSych/ProOrioks" << std::endl;
            std::cout << "Designed by " << tcl::colorize("|",{tcl::BOLD,tcl::RED}) << tcl::colorize("GST",tcl::BOLD)
                            << ", powered by " << tcl::colorize("◎Orioks",tcl::CYAN) << std::endl;
            return 0;
        }
    };
}

#endif // ABOUT_HPP
