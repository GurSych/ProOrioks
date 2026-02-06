#ifndef LOGIN_HPP
#define LOGIN_HPP

#pragma once
#include "../../TinyColor.hpp"
#include "../../Command.hpp"
#include "../../../network/OrioksHandler.hpp"
#include "../../../tools/StringTools.hpp"
#include <iostream>

namespace cmd {
    class Login : public cli::Command {
    public:
        Login() : Command("login", "Login to Orioks",
                    "Command allows you to login to Orioks using your username and password\n"
                    "Usage: login [relogin/token]\n"
                    "If 'relogin' is specified and token is already saved, it starts a login process\n"
                    "If 'token' is specified, it starts a login process using your API token", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool relogin_flag{false}; bool token_flag{false};
            for(auto arg : args) {
                if(arg == "relogin") relogin_flag = true;
                if(arg == "token") token_flag = true;
            }
            bool has_login_info = app.dataStorage().hasLoginInfo();
            bool has_api_token  = app.dataStorage().hasApiToken();
            if(token_flag) {
                std::cout << "Logging in to " << tcl::colorize("◎Orioks",tcl::CYAN) << " via token..." << std::endl;
                std::cout << "Enter your token: ";
                std::string token;
                std::cin >> token;
                try {
                    app.dataStorage().setupApiToken(token);
                } catch (const std::exception& e) {
                    std::cerr << tcl::colorize(std::string{"Failed to save API token: "} + std::string{e.what()}, tcl::RED) << std::endl;
                    return 1;
                }
                app.orioksHandler().set_api_token(app.dataStorage().getApiToken());
                std::cout << tcl::colorize("Token is saved.", tcl::GREEN) << std::endl;
                return 0;
            }
            if(has_api_token && !relogin_flag) {
                std::cout << tcl::colorize("You have been already logged in!",tcl::GREEN) << std::endl;
                std::cout << "Use the 'relogin' flag to force relogin." << std::endl;
                return 0;
            }
            if(has_login_info && relogin_flag) {
                std::cout << tcl::colorize("Remember! The program does not manage your token on server!\nYou can get only 8 tokens! Current token will be just stored locally.",tcl::YELLOW) << std::endl;
                std::cout << "Do you want to continue? [yes/no]: ";
                std::string answer; std::cin >> answer;
                if(answer == "no") return 0;
                std::cout << std::endl;
            }
            std::cout << "Logging in to " << tcl::colorize("◎Orioks",tcl::CYAN) << "..." << std::endl;
            std::string username{}; std::string password{};
            auto get_login_info = [&]() {
                bool go_next{false};
                do {
                    std::cout << "Enter your Orioks login: ";    std::cin >> username;
                    std::cout << "Enter your Orioks password: "; std::cin >> password;
                    std::cout << tcl::up(1) << tcl::right(29+password.size()) << tcl::clear_line();
                    std::cout << "\rEnter your Orioks password: " << std::string(password.size(), '*') << std::endl;
                    std::cout << "Is your login information correct? [yes/no]: ";
                    std::string answer; std::cin >> answer;
                    if(answer == "yes") go_next = true;
                } while(!go_next);
                std::cout << "Do you want to save your login information? [yes/no]: ";
                std::string answer; std::cin >> answer;
                if(answer == "yes") app.dataStorage().saveLoginInfo(username, password);
            };
            if(!has_login_info) {
                get_login_info();
            } else {
                std::cout << "You have saved password for login '" << app.dataStorage().config()["orioks-user"]["login"].get<std::string>()
                    << "'\nDo you want to use them? [yes/no]: ";
                std::string answer; std::cin >> answer;
                if(answer == "yes") {
                    username = app.dataStorage().config()["orioks-user"]["login"].get<std::string>();
                    password = app.dataStorage().config()["orioks-user"]["password"].get<std::string>();
                } else {
                    get_login_info();
                }
            }
            std::string login_info = username + ":" + password;
            auto login_base64 = strtools::str_to_base64(login_info);
            cpr::Header auth_header = {{"Authorization","Basic " + login_base64}};
            cpr::Session session{};
            session.SetUrl(app.orioksHandler().make_url("/auth"));
            session.SetHeader(app.orioksHandler().make_header(auth_header));
            session.SetTimeout(cpr::Timeout{7000});
            auto response = session.Get();
            json j = json::parse(response.text);
            if(response.status_code != 200) {
                std::cerr << tcl::colorize(std::string{"Failed to login: "} + j["error"].get<std::string>() + " (" + std::to_string(response.status_code) + ")", tcl::RED) << std::endl;
                return 1;
            }
            try {
                app.dataStorage().setupApiToken(j["token"]);
            } catch (const std::exception& e) {
                std::cerr << tcl::colorize(std::string{"Failed to save API token: "} + std::string{e.what()}, tcl::RED) << std::endl;
                return 1;
            }
            app.orioksHandler().set_api_token(app.dataStorage().getApiToken());
            std::cout << tcl::colorize("Logged in successfully! Token is saved.", tcl::GREEN) << std::endl;
            return 0;
        }
    };
}

#endif // LOGIN_HPP
