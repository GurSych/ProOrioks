#ifndef PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_GROUPS_HPP
#define PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_GROUPS_HPP

#pragma once
#include "../../TinyColor.hpp"
#include "../../Command.hpp"
#include "../../../network/OrioksHandler.hpp"
#include "../../templates/Tables.hpp"

namespace cmd {
    class Groups : public cli::Command {
    public:
        Groups() : Command("groups", "Display student groups and IDs",
            "Command displays all student groups and their IDs\n"
            "Usage: groups [<group>/split]\n"
            "If no arguments are specified, all groups will be displayed\n"
            "If group name is specified, only that group will be displayed (if found)\n"
            "If 'split' is specified, group names will be split into short names", "orioks") { }

        int execute(const std::vector<std::string>& args, gst::Application& app) override {
            bool split_flag{false};
            std::string group_name;
            if(!args.empty()) {
                if(args[0] == "split") split_flag = true;
                else                   group_name = args[0];
            }
            if(!app.orioksHandler().is_api_token_set()) {
                std::cerr << tcl::colorize("API token is not set =(\nPlease set it using 'login' command.", tcl::RED) << std::endl;
                return 1;
            }
            auto response = app.orioksHandler().get("/schedule/groups");
            if(response.status_code != 200) {
                std::cerr << tcl::colorize("Failed to fetch groups information =(", tcl::RED) << std::endl;
                std::cerr << response.text << std::endl;
                return 1;
            }
            json data = json::parse(response.text);
            if(group_name.empty()) {
                tmpl::HTable table("Groups", {"ID", "Name"});
                for(const auto& group : data) {
                    if(split_flag) table.addRow({std::to_string(group["id"].get<int>()), strtools::single_split(group["name"].get<std::string>(), ' ')});
                    else           table.addRow({std::to_string(group["id"].get<int>()), group["name"].get<std::string>()});
                }
                table.print();
                return 0;
            }
            tmpl::HTable table("Found group", {"ID", "Name"});
            for(const auto& group : data) {
                if(strtools::single_split(group["name"].get<std::string>(), ' ') == group_name) {
                    table.addRow({std::to_string(group["id"].get<int>()), group["name"].get<std::string>()});
                }
            }
            table.print();
            return 0;
        }
    };
}

#endif //PROORIOKS_SRC_CLI_COMMANDS_ORIOKS_GROUPS_HPP
