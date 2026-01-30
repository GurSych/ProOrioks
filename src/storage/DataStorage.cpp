#include "DataStorage.hpp"

using namespace storage;

storage::DataStorage::DataStorage() {
    init();
}

storage::DataStorage::~DataStorage() { }

void DataStorage::init() {
    config_path_ = get_config_path();
}

void DataStorage::quit() {

}

const fsys::path& DataStorage::config_path() const {
    return config_path_;
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
