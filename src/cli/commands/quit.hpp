#ifndef QUIT_HPP
#define QUIT_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include "config.hpp"
#include <iostream>

namespace cmd {
    class Quit : public cli::Command {
    public:
        Quit() : Command("quit", "Quit the program", "Command provides a safe way to quit the program", "system") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            app.dataStorage().quit();
            std::cout << "Goodbye! Have a great day!" << std::endl;
            return -1;
        }
    };
}

#endif // QUIT_HPP
