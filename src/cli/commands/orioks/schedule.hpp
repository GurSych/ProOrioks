#ifndef PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP
#define PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP

#pragma once
#include "../../TinyColor.hpp"
#include "../../Command.hpp"
#include "../../../network/OrioksHandler.hpp"
#include "../../templates/Tables.hpp"
#include "../../../tools/TimeTools.hpp"
#include "config.hpp"
#include <iostream>
#include <string>

namespace cmd {
    class Schedule : public cli::Command {
    public:
        Schedule() : Command("schedule", "Display your schedule",
            "Command displays schedule of chosen group (user group by default).\n"
            "Usage: schedule [<group_id>/timetable [fetch]]\n"
            "If no arguments are specified, the schedule of the user's group will be displayed.\n"
            "If a group name is specified, the schedule of that group will be displayed.\n"
            "If 'timetable' is provided, the classes timetable will be displayed. If 'fetch' is provided, the schedule will be fetched from the server.", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool timetable = false; bool fetch_flag = false;
            std::string group_id;
            if(!args.empty()) {
                if(args[0] == "timetable") {
                    timetable = true;
                    if(args.size() > 1)
                        if(args[1] == "fetch") fetch_flag = true;
                }
                else group_id = args[0];
            }
            if(timetable && fetch_flag) {
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
                tmpl::HTable timetable("Timetable (fetched)",{"Lesson","Start","End"});
                for(auto& [lesson, range] : data.items()) {
                    timetable.addRow({lesson, range[0].get<std::string>(), range[1].get<std::string>()});
                }
                timetable.print(true);
                return 0;
            }
            if(timetable) {
                tmpl::HTable timetable("Timetable",{"Lesson","Start","End"});
                for(auto& [lesson, range] : app.uniLessonsTimetable()) {
                    timetable.addRow({std::to_string(lesson), range.first, range.second});
                }
                timetable.print(true);
                return 0;
            }
            std::cout << "In development..." << std::endl;
            return 0;
        }
    };
}

#endif //PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP
