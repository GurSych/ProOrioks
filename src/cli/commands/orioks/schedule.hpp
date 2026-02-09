#ifndef PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP
#define PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP

#include <string>
#pragma once
#include "../../TinyColor.hpp"
#include "../../Command.hpp"
#include "../../../network/OrioksHandler.hpp"
#include "../../templates/Tables.hpp"
#include "../../../tools/TimeTools.hpp"
#include <iostream>

namespace cmd {
    class Schedule : public cli::Command {
    public:
        Schedule() : Command("schedule", "Display your schedule",
            "Command displays schedule of chosen group (user group by default).\n"
            "Usage: schedule [<group_id>/timetable]\n"
            "If no arguments are specified, the schedule of the user's group will be displayed.\n"
            "If a group name is specified, the schedule of that group will be displayed.\n"
            "If 'timetable' is provided, the classes timetable will be displayed.", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool timetable = false; bool show_fetched = false;
            std::string group_id;
            if(!args.empty()) {
                if(args[0] == "timetable") {
                    timetable = true;
                    if(args.size() > 1) {
                        if(args[1] == "show-fetched") {
                            show_fetched = true;
                        }
                    }
                } else {
                    group_id = args[0];
                }
            }
            if(timetable) {
                if(!app.orioksHandler().is_api_token_set()) {
                    std::cerr << tcl::colorize("API token is not set =(\nPlease set it using 'login' command.", tcl::RED) << std::endl;
                    return 1;
                }
                auto response = app.orioksHandler().get("/schedule/timetable");
                if(response.status_code != 200) {
                    std::cerr << tcl::colorize("Failed to fetch timetable information =(", tcl::RED) << std::endl;
                    std::cerr << response.text << std::endl;
                    return 1;
                }
                json data = json::parse(response.text);
                auto range = data["1"];
                std::string start_time = range[0].get<std::string>();
                std::string end_time   = range[1].get<std::string>();
                int time_difference = timetools::time_difference(end_time, start_time);
                std::cout << "Fetched lesson duration: " << tcl::colorize(std::to_string(time_difference) + " minutes",tcl::BOLD) << std::endl;
                if(show_fetched || time_difference == 80) {
                    tmpl::HTable timetable("Timetable",{"Lesson","Start","End"});
                    for(auto& [lesson, range] : data.items()) {
                        timetable.addRow({lesson, range[0].get<std::string>(), range[1].get<std::string>()});
                    }
                    timetable.print(true);
                } else {
                    std::cout << "Timetable will fixed for " << tcl::colorize("80 minutes",tcl::BOLD) << " lesson (use 'show_fetched' argument to see fetched data)" << std::endl;
                    tmpl::HTable timetable("Timetable (Fixed)",{"Lesson","Start","End"});
                    int time_diff = timetools::time_difference(time_difference,80);
                    std::cout << time_diff << std::endl;
                    int time_shift = 0;
                    for(auto& [lesson, range] : data.items()) {
                        int start_time = timetools::to_minutes(range[0].get<std::string>()) - time_shift;
                        int end_time = start_time + 80;
                        timetable.addRow({lesson, timetools::to_time(start_time), timetools::to_time(end_time)});
                        time_shift += time_diff;
                    }
                    timetable.print(true);
                }
                return 0;
            }
            std::cout << "In development..." << std::endl;
            return 0;
        }
    };
}

#endif //PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP
