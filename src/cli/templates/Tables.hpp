#ifndef PROORIOKS_SRC_CLI_TEMPLATES_TABLES_HPP
#define PROORIOKS_SRC_CLI_TEMPLATES_TABLES_HPP

#pragma once
#include <string>
#include <vector>

namespace tmpl {
    class HTable {
        public:
        HTable(const std::string& name, const std::vector<std::string>& columns, const size_t max_width = 30);

        void addRow(const std::vector<std::string>& values);
        void print(bool with_name = false) const;

    private:
        std::string name_; size_t max_width_;
        std::vector<std::string> columns_;
        std::vector<std::vector<std::string>> rows_{};
        std::vector<size_t> max_column_widths_;
        std::vector<size_t> max_row_heights_{};
    };
}

#endif // PROORIOKS_SRC_CLI_TEMPLATES_TABLES_HPP
