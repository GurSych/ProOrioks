#include "core/Application.hpp"
#include "cli/commands/about.hpp"
#include "cli/commands/service.hpp"
#include "cli/commands/help.hpp"
#include "cli/commands/quit.hpp"
#include "cli/commands/check-connection.hpp"
#include "cli/commands/orioks/login.hpp"
#include "cli/commands/orioks/profile.hpp"
#include <memory>

int main(int argc, char* argv[]) {
    cli::CommandManager  commandManager{};
    net::OrioksHandler   orioksHandler{};
    storage::DataStorage dataStorage{};
    gst::Application app{commandManager, orioksHandler, dataStorage};
    app.commandManager().registerCommand(std::make_unique<cmd::About>());
    app.commandManager().registerCommand(std::make_unique<cmd::Service>());
    app.commandManager().registerCommand(std::make_unique<cmd::Help>());
    app.commandManager().registerCommand(std::make_unique<cmd::Quit>());
    app.commandManager().registerCommand(std::make_unique<cmd::Check>());
    app.commandManager().registerCommand(std::make_unique<cmd::Login>());
    app.commandManager().registerCommand(std::make_unique<cmd::Profile>());

    app.run();

    return 0;
}
