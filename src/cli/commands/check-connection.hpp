#ifndef CHECK_CONNECTION_HPP
#define CHECK_CONNECTION_HPP

#pragma once
#include "../TinyColor.hpp"
#include "../Command.hpp"
#include <iostream>

namespace cmd {
    class Check : public cli::Command {
    public:
        Check() : Command("check-connection", "Check the status of the internet connection",
                    "Command checks internet connection with request to test url\n"
                    "Usage: check-connection [show]\n"
                    "If 'show' is specified, the response will be shown (if caught)", "hide") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool show_flag{false};
            for(const auto& arg : args) {
                if (arg == "show") show_flag = true;
            }
            std::clog << "Checking internet connection...";
            auto response = app.orioksHandler().checkConnection();
            std::cout << " done!" << std::endl;
            std::cout << tcl::colorize("Result: ",tcl::BOLD);
            if (response.status_code == 200) {
                std::cout << tcl::colorize("OK",{tcl::BOLD,tcl::GREEN}) << tcl::colorize(" =)",tcl::GREEN) << std::endl;
                if(show_flag) {
                    auto json_file = json::parse(response.text);
                    std::cout << "Response: " << std::endl;
                    std::cout << json_file.dump(4) << std::endl;
                }
            } else {
                std::cout << tcl::colorize("Failed",{tcl::BOLD,tcl::RED}) << tcl::colorize(" =(",tcl::RED) << std::endl;
            }
            return 0;
        }
    };
}

#endif // CHECK_CONNECTION_HPP
