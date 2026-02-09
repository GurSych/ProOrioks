#include "Application.hpp"
#include "../cli/TinyColor.hpp"
#include "../cli/templates/OrioksLine.hpp"
#include <iostream>
#include <string>

using namespace gst;

Application::Application(cli::CommandManager& commandManager, net::OrioksHandler& orioksHandler, storage::DataStorage& dataStorage)
        : commandManager_(commandManager), orioksHandler_(orioksHandler), dataStorage_(dataStorage) {
    init();
}

Application::~Application() { }

void Application::run() {
    while (true) {
        if (update() == -1) break;
    }
}

void Application::init() {
    std::string api_token = dataStorage_.getApiToken();
    orioksHandler_.set_api_token(api_token);
    int lessons_time = start_lessons_time;
    for (int i = 1; i < 9; ++i) {
        std::string start_time{}; std::string end_time{};
        if(i == 3) {
            start_time = timetools::to_time(lessons_time) + "\n" + timetools::to_time(lessons_time + lunch_duration_time);
            end_time   = timetools::to_time(lessons_time + duration_lesson_time) + "\n" + timetools::to_time(lessons_time + lunch_duration_time + duration_lesson_time);
            lessons_time += lunch_duration_time;
        } else {
            start_time = timetools::to_time(lessons_time);
            end_time   = timetools::to_time(lessons_time + duration_lesson_time);
        }
        uni_lessons_timetable[i] = std::make_pair(start_time, end_time);
        lessons_time += duration_lesson_time + break_duration_time;
    }
}

int Application::update() {
    std::string input{};
    std::cout << tmpl::OrioksLine();
    std::getline(std::cin, input);
    return executeLine(input);
}

int Application::executeLine(const std::string& line) {
    auto tokens = strtools::split(line);
    if (tokens.empty()) return 0;
    if (!commandManager_.hasCommand(tokens[0])) {
        std::cerr << tcl::colorize(std::string{"Unknown command: "}+tokens[0],{tcl::RED}) << std::endl;
        return 0;
    }
    std::cout << std::endl;
    int result = commandManager_.executeCommand(tokens[0],std::vector<std::string>{tokens.begin()+1,tokens.end()},*this);
    std::cout << std::endl;
    return result;
}
