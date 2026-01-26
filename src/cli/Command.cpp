#include "Command.hpp"

using namespace cli;

Command::Command(const std::string& name, const std::string& description)
    : name_(name), description_(description) { }

const std::string& Command::name() const {
    return name_;
}

const std::string& Command::description() const {
    return description_;
}
