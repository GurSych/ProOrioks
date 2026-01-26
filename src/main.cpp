#include "core/Application.hpp"
#include "cli/commands/about.hpp"
#include <memory>

int main(int argc, char* argv[]) {
    gst::Application app{};
    app.commandManager.registerCommand(std::make_unique<cmd::About>());

    app.run();

    return 0;
}
