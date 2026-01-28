cmake_minimum_required(VERSION 3.10)
project(ProOrioks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_VERSION "0.1.1 Pre-Alpha")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/config.hpp @ONLY)

add_executable(ProOrioks
    src/main.cpp
    src/core/Application.cpp
    src/cli/Command.cpp
    src/cli/CommandManager.cpp
    src/tools/StringTools.cpp
)

target_include_directories(ProOrioks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ProOrioks PRIVATE ${CMAKE_BINARY_DIR}/include)
