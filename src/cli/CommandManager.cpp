#include "CommandManager.hpp"

using namespace cli;

CommandManager::CommandManager() { }

CommandManager::~CommandManager() { }

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    commands_[command->name()] = std::move(command);
}

void CommandManager::unregisterCommand(const std::string& name) {
    commands_.erase(name);
}

bool CommandManager::hasCommand(const std::string& name) {
    return commands_.find(name) != commands_.end();
}

int CommandManager::executeCommand(const std::string& name, const std::vector<std::string>& args) {
    auto it = commands_.find(name);
    if (it != commands_.end())
        return it->second->execute(args);
    return 2;
}
