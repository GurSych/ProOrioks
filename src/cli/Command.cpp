#include "Command.hpp"

using namespace cli;

Command::Command(const std::string& name, const std::string& description, const std::string& tag)
    : name_(name), description_(description), tag_(tag) { }

const std::string& Command::name() const {
    return name_;
}

const std::string& Command::description() const {
    return description_;
}

const std::string& Command::tag() const {
    return tag_;
}
