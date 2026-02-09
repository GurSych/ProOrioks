#ifndef PROORIOKS_SRC_STORAGE_DATA_STORAGE_HPP
#define PROORIOKS_SRC_STORAGE_DATA_STORAGE_HPP

#pragma once
#include <filesystem>
#include <exception>
#include <string>
#include <nlohmann/json.hpp>

namespace fsys = std::filesystem;
using json = nlohmann::json;

namespace storage {
    class DataStorage {
    public:
        DataStorage();
        ~DataStorage();

        void init();
        void quit();

        void save_config();
        void save_config(const json& config);
        void get_config();

        bool hasLoginInfo() const;
        bool hasApiToken() const;
        std::string getApiToken() const;
        void saveLoginInfo(const std::string& username, const std::string& password);
        void setupApiToken(const std::string& token);

        json& config() { return config_; }
        const fsys::path& config_path() const { return config_path_; }

    private:
        fsys::path config_path_;
        json config_;

        fsys::path get_config_path();
    };
}

#endif // PROORIOKS_SRC_STORAGE_DATA_STORAGE_HPP
