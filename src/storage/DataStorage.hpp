#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#pragma once
#include <filesystem>

namespace fsys = std::filesystem;

namespace storage {
    class DataStorage {
    public:
        DataStorage();
        ~DataStorage();

        void init();
        void quit();

        const fsys::path& config_path() const;

    private:
        fsys::path config_path_;

        fsys::path get_config_path();
    };
}

#endif // DATA_STORAGE_HPP
