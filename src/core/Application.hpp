#ifndef PROORIOKS_SRC_APPLICATION_APPLICATION_HPP
#define PROORIOKS_SRC_APPLICATION_APPLICATION_HPP

#pragma once
#include "../cli/CommandManager.hpp"
#include "../network/OrioksHandler.hpp"
#include "../storage/DataStorage.hpp"
#include "../tools/TimeTools.hpp"
#include "config.hpp"
#include <string>
#include <map>

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

        const std::map<int, std::pair<std::string, std::string>>& uniLessonsTimetable() const { return uni_lessons_timetable; }

        const int start_lessons_time   = timetools::to_minutes(__LESSONS_START_TIME__);
        const int duration_lesson_time = timetools::to_minutes(__LESSONS_DURATION_TIME__);
        const int break_duration_time  = timetools::to_minutes(__BREAK_DURATION_TIME__);
        const int lunch_duration_time  = timetools::to_minutes(__LUNCH_DURATION_TIME__);

    private:
        cli::CommandManager&   commandManager_;
        net::OrioksHandler&    orioksHandler_;
        storage::DataStorage&  dataStorage_;

        std::map<int, std::pair<std::string, std::string>> uni_lessons_timetable{};

        void init();
        int update();
    };
}

#endif // PROORIOKS_SRC_APPLICATION_APPLICATION_HPP
