#include "DataStorage.hpp"
#include <fstream>
#include "../cli/TinyColor.hpp"

using namespace storage;

storage::DataStorage::DataStorage() {
    init();
}

storage::DataStorage::~DataStorage() { }

void DataStorage::init() {
    config_path_ = get_config_path();
    fsys::create_directories(config_path_.parent_path());
    if(!fsys::exists(config_path_)) {
        json config = {
            {"orioks-user",
                {
                    {"login", ""},
                    {"password", ""},
                    {"api-token", ""},
                    {"old-tokens", json::array()}
                }
            }
        };
        save_config(config);
    }
    get_config();
}

void DataStorage::quit() {

}

void DataStorage::save_config() {
    save_config(config_);
}

void DataStorage::save_config(const json& config) {
    config_ = config;
    std::ofstream file(config_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Application failed to access a configuration file");
    }
    file << std::setw(4) << config << std::endl;
}

void DataStorage::get_config() {
    std::ifstream file(config_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Application failed to access a configuration file");
    }
    file >> config_;
}

bool DataStorage::hasLoginInfo() const {
    try {
        return !config_["orioks-user"]["login"].get<std::string>().empty() && !config_["orioks-user"]["password"].get<std::string>().empty();
    } catch (const json::exception&) {
        return false;
    }
}

bool DataStorage::hasApiToken() const {
    try {
        return !config_["orioks-user"]["api-token"].get<std::string>().empty();
    } catch (const json::exception&) {
        return false;
    }
}

std::string DataStorage::getApiToken() const {
    return config_["orioks-user"]["api-token"].get<std::string>();
}

void DataStorage::saveLoginInfo(const std::string& username, const std::string& password) {
    config_["orioks-user"]["login"]    = username;
    config_["orioks-user"]["password"] = password;
    try {
        save_config();
    } catch (const std::exception& e) {
        std::cerr << tcl::colorize("Failed to save login info: ", tcl::RED) << e.what() << std::endl;
    }
}

void DataStorage::setupApiToken(const std::string& token) {
    config_["orioks-user"]["old-tokens"].push_back(config_["orioks-user"]["api-token"].get<std::string>());
    config_["orioks-user"]["api-token"] = token;
    try {
        save_config();
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to save API token: " + std::string{e.what()});
    }
}

fsys::path DataStorage::get_config_path() {
    #if defined(_WIN32)
        const char* data_path = std::getenv("APPDATA");
        if (!data_path) return fsys::current_path() / "config.json";
        return fsys::path(data_path) / "ProOrioks" / "config.json";
    #elif defined(__linux__) || defined(__APPLE__)
        const char* data_path = std::getenv("HOME");
        if (!data_path) return fsys::current_path() / "config.json";
        return fsys::path(data_path) / ".config" / "ProOrioks" / "config.json";
    #else
        return fsys::current_path() / "config.json";
    #endif
}
