#ifndef HELP_HPP
#define HELP_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include <iostream>

namespace cmd {
    class Help : public cli::Command {
    public:
        Help() : Command("help", "Display help information",
                    "Command displays help information about program commands\n"
                    "Usage: help [command/all]\n"
                    "If no command is specified, displays a list of available commands\n"
                    "If a command is specified, displays detailed information about that command\n"
                    "If 'all' is specified, displays information about all commands (including hidden ones)", "system") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool show_all = false;
            if(!args.empty() && args[0] == "all") show_all = true;
            else if (!args.empty()) {
                std::string command = args[0];
                return app.commandManager().printDetailedDescription(command);
            }
            std::cout << tcl::colorize("System commands:",tcl::BOLD) << std::endl;
            app.commandManager().printCommands("system");
            std::cout << tcl::colorize("Orioks commands:",tcl::BOLD) << std::endl;
            app.commandManager().printCommands("orioks");
            if(show_all) {
                std::cout << tcl::colorize("Hidden commands:",tcl::BOLD) << std::endl;
                app.commandManager().printCommands("hide");
            }
            std::cout << "\nYou can use the 'help <command>' to get detailed information about a specific command\n";
            return 0;
        }
    };
}

#endif // HELP_HPP
