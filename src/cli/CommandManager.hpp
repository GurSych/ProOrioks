#pragma once
#include "Command.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

namespace cli {

    class CommandManager {
    public:
        CommandManager();
        ~CommandManager();

        void registerCommand(std::unique_ptr<Command> command);
        void unregisterCommand(const std::string& name);

        bool hasCommand(const std::string& name);
        int executeCommand(const std::string& name, const std::vector<std::string>& args);

    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> commands_{};
    };

}
