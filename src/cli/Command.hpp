#ifndef PROORIOKS_SRC_CLI_COMMAND_HPP
#define PROORIOKS_SRC_CLI_COMMAND_HPP

#pragma once
#include <string>
#include <vector>
#include "../core/Application.hpp"

namespace gst {
    class Application;
}

namespace cli {

    class Command {
    public:
        Command(const std::string& name, const std::string& description, const std::string& long_description, const std::string& tag);
        virtual ~Command() = default;

        const std::string& name() const;
        const std::string& description() const;
        const std::string& long_description() const;
        const std::string& tag() const;

        virtual int execute(const std::vector<std::string>& args, gst::Application& app) = 0;

    private:
        std::string name_;
        std::string description_;
        std::string long_description_;
        std::string tag_;
    };

}

#endif // PROORIOKS_SRC_CLI_COMMAND_HPP
