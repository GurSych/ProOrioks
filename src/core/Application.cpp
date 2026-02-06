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
