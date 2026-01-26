#include "Application.hpp"
#include "../cli/TinyColor.hpp"
#include "../tools/StringTools.hpp"
#include <iostream>
#include <string>

using namespace gst;

Application::Application() {
    init();
}

Application::~Application() { }

void Application::run() {
    while (true) {
        if (update() == -1) break;
    }
    std::cout << "\nGoodbye! Have a great day!\n" << std::endl;
}

void Application::init() { }

int Application::update() {
    std::string input{};
    std::cout << tcl::colorize("ProOrioks",{tcl::WHITE,tcl::BKG_CYAN}) + " > ";
    std::getline(std::cin, input);
    auto tokens = strtools::split(input);
    if (tokens.empty())      return 0;
    if (tokens[0] == "quit") return -1;
    if (!commandManager.hasCommand(tokens[0])) {
        std::cerr << tcl::colorize(std::string{"Unknown command: "}+tokens[0],{tcl::RED}) << std::endl;
        return 0;
    }
    std::cout << std::endl;
    int result = commandManager.executeCommand(tokens[0], std::vector<std::string>{tokens.begin()+1,tokens.end()});
    std::cout << std::endl;
    return result;
}
