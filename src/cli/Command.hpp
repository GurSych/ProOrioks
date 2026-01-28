#ifndef COMMAND_HPP
#define COMMAND_HPP

#pragma once
#include "../core/Application.hpp"
#include <string>
#include <vector>

namespace gst {
    class Application;
}

namespace cli {

    class Command {
    public:
        Command(const std::string& name, const std::string& description, const std::string& tag);
        virtual ~Command() = default;

        const std::string& name() const;
        const std::string& description() const;
        const std::string& tag() const;

        virtual int execute(const std::vector<std::string>& args, gst::Application& app) = 0;

    private:
        std::string name_;
        std::string description_;
        std::string tag_;
    };

}

#endif // COMMAND_HPP
