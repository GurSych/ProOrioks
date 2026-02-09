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
#include <cctype>

namespace cmd {
    class Schedule : public cli::Command {
    public:
        Schedule() : Command("schedule", "Display your schedule",
            "Command displays schedule of chosen group (user group by default).\n"
            "Usage: schedule [<group_name/group_id>/timetable [fetch]]\n"
            "If no arguments are specified, the schedule of the user's group will be displayed.\n"
            "If a group name is specified, the schedule of that group will be displayed.\n"
            "If 'timetable' is provided, the classes timetable will be displayed. If 'fetch' is provided, the timetable will be fetched from the server.", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool timetable = false; bool fetch_flag = false;
            std::string group_spec;
            if(!args.empty()) {
                if(args[0] == "timetable") {
                    timetable = true;
                    if(args.size() > 1)
                        if(args[1] == "fetch") fetch_flag = true;
                }
                else group_spec = args[0];
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
            if(group_spec.empty()) {
                std::cout << "In development... please specify a group" << std::endl;
                return 0;
            }
            std::string group_id{}; std::string group_name{};
            auto group_response = app.orioksHandler().get("/schedule/groups");
            if(group_response.status_code != 200) {
                std::cerr << tcl::colorize("Failed to fetch groups information =(", tcl::RED) << std::endl;
                std::cerr << group_response.text << std::endl;
                return 1;
            }
            json group_data = json::parse(group_response.text);
            if(std::isdigit(group_spec[0])) {
                int id{};
                try {
                    id = std::stoi(group_spec);
                } catch (const std::invalid_argument&) {
                    std::cerr << tcl::colorize("Failed to fetch groups information =(\nIdentifier seems invalid", tcl::RED) << std::endl;
                    return 1;
                } catch (const std::out_of_range&) {
                    std::cerr << tcl::colorize("Failed to fetch groups information =(\nIdentifier seems invalid", tcl::RED) << std::endl;
                    return 1;
                }
                for(const auto& group : group_data) {
                    if(group["id"].get<int>() == id) {
                        group_id   = group_spec;
                        group_name = strtools::single_split(group["name"].get<std::string>(), ' ');
                        break;
                    }
                }
            } else {
                for(const auto& group : group_data) {
                    if(strtools::single_split(group["name"].get<std::string>(), ' ') == group_spec) {
                        group_id   = std::to_string(group["id"].get<int>());
                        group_name = strtools::single_split(group["name"].get<std::string>(), ' ');
                        break;
                    }
                }
            }
            if(group_id.empty()) {
                std::cout << tcl::colorize("Group not found...", tcl::YELLOW) << std::endl;
                return 0;
            }
            auto response = app.orioksHandler().get(std::string("/schedule/groups/") + group_id);
            if(response.status_code != 200) {
                std::cerr << tcl::colorize("Failed to fetch schedule information =(", tcl::RED) << std::endl;
                std::cerr << response.text << std::endl;
                return 1;
            }
            json data = json::parse(response.text);
            tmpl::HTable schedule_table(group_name + " schedule",{"Lesson", "Monday", "Tuesday", "Wednesday", "Thursday","Friday", "Saturday"});
            std::vector<std::vector<std::string>> schedule(8, std::vector<std::string>(7, " "));
            for(auto& lesson : data) {
                int class_           = lesson["class"].get<int>();
                int day              = lesson["day"].get<int>();
                int week             = lesson["week"].get<int>();
                int week_recurrence  = lesson["week_recurrence"].get<int>();
                std::string name     = lesson["name"].get<std::string>();
                std::string type     = lesson["type"].get<std::string>();
                std::string location = lesson["location"].get<std::string>();
                std::string teacher  = lesson["teacher"].get<std::string>();
                name = strtools::single_split(name, '(');
                name = std::string(name.begin(), name.end()-1);
                try {
                    schedule[class_-1][day] = name + "\n[" + type + "] | " + location + "\n" + teacher;
                } catch(const std::out_of_range& e) {
                    std::cerr << tcl::colorize("Invalid schedule data", tcl::RED) << std::endl;
                    return 1;
                }
            }
            for(int i{}; i < 8; i++) {
                std::vector<std::string> day_row{};
                if(i == 2) {
                    auto start_time = strtools::split(app.uniLessonsTimetable().at(i+1).first, '\n');
                    auto end_time   = strtools::split(app.uniLessonsTimetable().at(i+1).second, '\n');
                    day_row.push_back(std::to_string(i+1) + "\n" + start_time[0] + "│" + start_time[1] + "\n" + end_time[0] + "│" + end_time[1]);
                } else {
                    day_row.push_back(std::to_string(i+1) + "\n" + app.uniLessonsTimetable().at(i+1).first + "\n" + app.uniLessonsTimetable().at(i+1).second);
                }
                day_row.insert(day_row.end(), schedule[i].begin(), schedule[i].end()-1);
                schedule_table.addRow(day_row);
            }
            schedule_table.print(true);
            return 0;
        }
    };
}

#endif //PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_SCHEDULE_HPP
