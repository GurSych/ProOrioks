#pragma once
#include "../cli/CommandManager.hpp"

namespace gst {

    class Application {
    public:
        Application();
        ~Application();

        void run();

        cli::CommandManager commandManager{};

    private:
        void init();
        int update();
    };
}
