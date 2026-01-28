#ifndef HELP_HPP
#define HELP_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include <iostream>

namespace cmd {
    class Help : public cli::Command {
    public:
        Help() : Command("help", "Display help information", "system") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            std::cout << tcl::colorize("Usage: command [options]\n",tcl::BOLD) << std::endl;
            std::cout << tcl::colorize("System commands:",tcl::BOLD) << std::endl;
            app.commandManager.printCommands("system");
            std::cout << tcl::colorize("Orioks commands:",tcl::BOLD) << std::endl;
            app.commandManager.printCommands("orioks");
            std::cout << tcl::colorize("GST commands:",tcl::BOLD) << std::endl;
            app.commandManager.printCommands("gst");
            return 0;
        }
    };
}

#endif // HELP_HPP
