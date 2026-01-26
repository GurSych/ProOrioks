#pragma once
#include <string>
#include <vector>

namespace cli {

    class Command {
    public:
        Command(const std::string& name, const std::string& description);
        virtual ~Command() = default;

        const std::string& name() const;
        const std::string& description() const;

        virtual int execute(const std::vector<std::string>& args) = 0;

    private:
        std::string name_;
        std::string description_;
    };

}
