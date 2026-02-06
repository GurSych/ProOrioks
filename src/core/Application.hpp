#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#pragma once
#include "../cli/CommandManager.hpp"
#include "../network/OrioksHandler.hpp"
#include "../storage/DataStorage.hpp"

namespace cli {
    class CommandManager;
}

namespace gst {

    class Application {
    public:
        Application(cli::CommandManager& commandManager,
                    net::OrioksHandler& orioksHandler,
                    storage::DataStorage& dataStorage);
        ~Application();

        void run();
        int executeLine(const std::string& line);

        cli::CommandManager&   commandManager() { return commandManager_; }
        net::OrioksHandler&    orioksHandler()  { return orioksHandler_; }
        storage::DataStorage&  dataStorage()    { return dataStorage_; }

    private:
        cli::CommandManager&   commandManager_;
        net::OrioksHandler&    orioksHandler_;
        storage::DataStorage&  dataStorage_;

        void init();
        int update();
    };
}

#endif // APPLICATION_HPP
