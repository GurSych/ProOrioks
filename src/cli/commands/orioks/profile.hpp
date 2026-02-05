#ifndef PROFILE_HPP
#define PROFILE_HPP

#pragma once
#include "../../TinyColor.hpp"
#include "../../Command.hpp"
#include "../../../network/OrioksHandler.hpp"
#include <iostream>

namespace cmd {
    class Profile : public cli::Command {
    public:
        Profile() : Command("profile", "Display information about you",
            "Command displays information from your Orioks profile", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            if(!app.orioksHandler().is_api_token_set()) {
                std::cerr << tcl::colorize("API token is not set =(\nPlease set it using 'login' command.", tcl::RED) << std::endl;
                return 1;
            }
            auto response = app.orioksHandler().get("/student");
            json data = json::parse(response.text);
            if(response.status_code != 200) {
                std::cerr << tcl::colorize("Failed to fetch profile information =(", tcl::RED) << std::endl;
                std::cerr << response.text << std::endl;
                return 1;
            }
            std::cout << tcl::colorize("Orioks profile information\n", tcl::BOLD) << std::endl;
            std::cout << tcl::colorize(std::string{"Full name: "} + data["full_name"].get<std::string>(), tcl::BOLD) << std::endl;
            std::cout << "Student's record book: " << data["record_book_id"].get<int>() << std::endl;
            std::cout << tcl::colorize(std::string{"Study direction: "} + data["study_direction"].get<std::string>(), tcl::BOLD) << std::endl;
            std::cout << "Study profile: " << data["study_profile"].get<std::string>() << std::endl;
            std::cout << "Department: " << data["department"].get<std::string>() << std::endl;
            std::cout << tcl::colorize(std::string{"Group: "} + data["group"].get<std::string>(), tcl::BOLD) << std::endl;
            std::cout << "Course: " << data["course"].get<int>() << "\t" << "Semester: " << data["semester"].get<int>() << std::endl;
            std::cout << "Educational year: " << data["year"].get<std::string>() << std::endl;
            return 0;
        }
    };
}

#endif // PROFILE_HPP
