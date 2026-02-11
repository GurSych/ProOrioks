# ProOrioks

**ProOrioks is my console mini-program to access information from MIET's Orioks system**<br>
_Latest version: 0.3.5 Alpha_

# Using program

> Program is in development so this section is updated together with program itself

Just run the program, it will start its own command line interface<br>
Usage: command \[options\]<br>

or you can run the program itself with a command you want to execute, this command will be executed and the program will quit automatically<br>
Usage: ProOrioks command \[options\]

> [!NOTE]
> You can always check the command list via `help` command

# Tech stack and dependencies
- C++20
- CMake
- libcpr/cpr (Request library)
- nlohmann/json (JSON library)
- matheusgomes28/base64pp (Base64 encoding library)

> Dependencies are automatically fetched from GitHub using CMake

## Project structure:

    ├─ src/                                Application source files
    │  ├─ core/                            Application core files
    │  │  ├─ Application.hpp               Application class header
    │  │  └─ Application.cpp               Application class implementation
    │  ├─ cli/                             Command line interface files
    │  │  ├─ commands/                     Commands source files
    │  │  │  └─ ...                        Commands source files
    │  │  ├─ templates/                    CLI templates source files
    │  │  │  └─ ...                        CLI templates source files
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
    │  │  ├─ StringTools.cpp               Implementation for StringTools functions
    │  │  ├─ TimeTools.hpp                 Header for TimeTools functions
    │  │  └─ TimeTools.cpp                 Implementation for TimeTools functions
    │  ├─ config.hpp.in                    CMake configurated config defines header
    │  └─ main.cpp                         Main application file
    └─ CMakeLists.txt                      CMake configuration file
