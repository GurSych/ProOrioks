#include "CommandManager.hpp"
#include <iostream>

using namespace cli;

CommandManager::CommandManager() { }

CommandManager::~CommandManager() { }

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    commands_[command->name()] = std::move(command);
}

void CommandManager::unregisterCommand(const std::string& name) {
    commands_.erase(name);
}

void CommandManager::printCommands(const std::string& tag) const {
    for (const auto& command : commands_) {
        if (!tag.empty() && command.second->tag() == tag)
            std::cout << "\t" << command.second->name() << " — " << command.second->description() << std::endl;
    }
}

bool CommandManager::hasCommand(const std::string& name) {
    return commands_.find(name) != commands_.end();
}

int CommandManager::executeCommand(const std::string& name, const std::vector<std::string>& args, gst::Application& app) {
    auto it = commands_.find(name);
    if (it != commands_.end())
        return it->second->execute(args, app);
    return 2;
}
