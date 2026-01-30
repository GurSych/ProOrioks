# ProOrioks

**ProOrioks is my console mini-program to access information from MIET's Orioks system**<br>
_Latest version: 0.2.1 Pre-Alpha_

# Using program

> Program is in development so this section is updated together with program itself

Just run the program, it will start its own command line interface<br>
Usage: command \[options\]

> [!NOTE]
> You can always check the command list via `help` command

# Tech stack and dependencies
- C++17
- CMake
- cpr (C++ REST client)
- nlohmann_json (JSON library)

> Dependencies are automatically fetched from GitHub using CMake

## Project structure:

    ├─ src/                                Application source files
    │  ├─ core/                            Application core files
    │  │  ├─ Application.hpp               Application class header
    │  │  └─ Application.cpp               Application class implementation
    │  ├─ cli/                             Command line interface files
    │  │  ├─ commands/                     Commands source files
    │  │  │  └─ _commands source files_    _Commands source files_
    │  │  ├─ Command.hpp                   Command class header
    │  │  ├─ Command.cpp                   Command class implementation
    │  │  ├─ CommandManager.hpp            CommandManager class header
    │  │  ├─ CommandManager.cpp            CommandManager class implementation
    │  │  └─ TinyColor.hpp                 Header-only TinyColor library
    │  ├─ network/                         Network handling files
    │  │  ├─ OrioksHandler.hpp             OrioksHandler class header
    │  │  └─ OrioksHandler.cpp             OrioksHandler class implementation
    │  ├─ storage/                         Storage handling files
    │  │  ├─ DataStorage.hpp               DataStorage class header
    │  │  └─ DataStorage.cpp               DataStorage class implementation
    │  ├─ tools/                           Additional tools files
    │  │  ├─ StringTools.hpp               Header for StringTools functions
    │  │  └─ StringTools.cpp               Implementation for StringTools functions
    │  ├─ config.hpp.in                    CMake configurated config defines header
    │  └─ main.cpp                         Main application file
    └─ CMakeLists.txt                      CMake configuration file
