#include "core/Application.hpp"
#include "cli/commands/about.hpp"
#include "cli/commands/service.hpp"
#include "cli/commands/help.hpp"
#include <memory>

int main(int argc, char* argv[]) {
    cli::CommandManager commandManager{};
    gst::Application app{commandManager};
    app.commandManager.registerCommand(std::make_unique<cmd::About>());
    app.commandManager.registerCommand(std::make_unique<cmd::Service>());
    app.commandManager.registerCommand(std::make_unique<cmd::Help>());

    app.run();

    return 0;
}
