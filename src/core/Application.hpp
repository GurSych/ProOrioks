#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#pragma once
#include "../cli/CommandManager.hpp"

namespace cli {
    class CommandManager;
}

namespace gst {

    class Application {
    public:
        Application(cli::CommandManager& commandManager);
        ~Application();

        void run();

        cli::CommandManager& commandManager;

    private:
        void init();
        int update();
    };
}

#endif // APPLICATION_HPP
