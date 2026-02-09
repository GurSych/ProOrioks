cmake_minimum_required(VERSION 3.16)
project(ProOrioks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_VERSION_MAJOR    "0")
set(APP_VERSION_MINOR    "3")
set(APP_VERSION_PATCH    "2")
set(APP_VERSION_PRTAG    "Alpha")

set(ORIOKS_API_URL       "https://orioks.miet.ru/api/v1")
set(TEST_JSON_API_URL    "https://api.ipify.org?format=json")

include(FetchContent)

FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.13.0
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(base64pp
    GIT_REPOSITORY https://github.com/matheusgomes28/base64pp.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(base64pp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/config.hpp @ONLY)

add_executable(ProOrioks
    src/main.cpp
    src/core/Application.cpp
    src/cli/Command.cpp
    src/cli/CommandManager.cpp
    src/network/OrioksHandler.cpp
    src/storage/DataStorage.cpp
    src/tools/StringTools.cpp
    src/tools/TimeTools.cpp
    src/cli/templates/Tables.cpp
)

target_include_directories(ProOrioks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ProOrioks PRIVATE ${CMAKE_BINARY_DIR}/include)

target_link_libraries(ProOrioks PRIVATE cpr::cpr)
target_link_libraries(ProOrioks PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(ProOrioks PRIVATE base64pp)
