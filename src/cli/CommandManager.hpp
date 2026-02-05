#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#pragma once
#include "Command.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

namespace gst {
    class Application;
}

namespace cli {

    class Command;

    class CommandManager {
    public:
        CommandManager();
        ~CommandManager();

        void registerCommand(std::unique_ptr<Command> command);
        void unregisterCommand(const std::string& name);

        void printCommands(const std::string& tag = "") const;
        int  printDetailedDescription(const std::string& command) const;

        bool hasCommand(const std::string& name);
        int  executeCommand(const std::string& name, const std::vector<std::string>& args, gst::Application& app);

    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> commands_{};
    };

}

#endif // COMMAND_MANAGER_HPP
