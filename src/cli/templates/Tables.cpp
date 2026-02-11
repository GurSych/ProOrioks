#include "Tables.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <numeric>
#include <vector>
#include "../TinyColor.hpp"
#include "../../tools/StringTools.hpp"

using namespace tmpl;

HTable::HTable(const std::string& name, const std::vector<std::string>& columns, const size_t max_width)
    : name_(name), columns_(columns), max_width_(max_width), max_column_widths_(columns.size(), 0) {
        for(size_t i{}; i < columns.size(); ++i) max_column_widths_[i] = std::max(max_column_widths_[i], strtools::utf8_strlen(columns[i]));
    }

void HTable::addRow(const std::vector<std::string>& values) {
    if (values.size() != columns_.size()) {
        throw std::invalid_argument("Number of cells does not match number of columns");
    }
    std::vector<std::string> local_values = values;
    max_row_heights_.emplace_back();
    for (size_t i{}; i < local_values.size(); ++i) {
        auto split_lines = strtools::split(local_values[i], '\n');
        std::vector<std::string> lines;
        for (const auto& line : split_lines) {
            if(strtools::utf8_strlen(line) > max_width_) {
                auto split_line = strtools::split(strtools::multiline(line, max_width_), '\n');
                lines.insert(lines.end(), split_line.begin(), split_line.end());
            } else {
                lines.push_back(line);
            }
        }
        local_values[i] = strtools::merge(lines,"\n");
        max_row_heights_.back() = std::max(max_row_heights_.back(), lines.size());
        max_column_widths_[i]   = std::max(max_column_widths_[i], strtools::utf8_strlen(*std::max_element(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) { return strtools::utf8_strlen(a) < strtools::utf8_strlen(b); })));
    }
    rows_.push_back(local_values);
}

void HTable::print(bool with_name) const {
    if(with_name) {
        size_t table_width = std::accumulate(max_column_widths_.begin(), max_column_widths_.end(), 0) + 3*columns_.size() + 1;
        if(strtools::utf8_strlen(name_) > table_width - 4) std::cout << "┌ " << tcl::colorize(name_,tcl::BOLD) << std::endl;
        else {
            size_t left_padding  = (table_width - strtools::utf8_strlen(name_)) / 2;
            size_t right_padding = table_width - strtools::utf8_strlen(name_) - left_padding;
            std::cout << "┌" <<  std::string{"—"}*(left_padding-2) << " " << tcl::colorize(name_,tcl::BOLD) << " " << std::string{"—"}*(right_padding-2) << "┐" << std::endl;
        }
    }
    std::cout << "┌";
    for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┬";
    std::cout << tcl::left(1) << "┐" << std::endl << "│ ";
    for (size_t i{}; i < columns_.size(); ++i) {
        size_t left_empty  = (max_column_widths_[i]-strtools::utf8_strlen(columns_[i]))/2;
        size_t right_empty = max_column_widths_[i]-strtools::utf8_strlen(columns_[i])-left_empty;
        std::cout << std::string(left_empty,' ')+tcl::colorize(columns_[i],tcl::BOLD)+std::string(right_empty,' ') << " │ ";
    }
    std::cout << std::endl << "├";
    for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┼";
    std::cout << tcl::left(1) << "┤" << std::endl;
    for (size_t row_i{}; row_i < rows_.size(); ++row_i) {
        auto& row = rows_[row_i];
        std::vector<std::vector<std::string>> cells_lines{};
        for (size_t i{}; i < columns_.size(); ++i) {
            auto lines = strtools::split(row[i], '\n');
            std::vector<std::string> cell_vector{};
            for (const auto& line : lines) {
                if(strtools::utf8_strlen(line) > max_width_) {
                    auto splited_line = strtools::split(strtools::multiline(line, max_width_),'\n');
                    cell_vector.insert(cell_vector.end(), splited_line.begin(), splited_line.end());
                } else {
                    cell_vector.push_back(line);
                }
            }
            cells_lines.push_back(cell_vector);
        }
        for (size_t line_i{}; line_i < max_row_heights_[row_i]; ++line_i) {
            std::cout << "│ ";
            for (size_t i{}; i < columns_.size(); ++i) {
                if (line_i < cells_lines[i].size()) {
                    size_t cell_width = strtools::utf8_strlen(cells_lines[i][line_i]);
                    size_t left_empty  = (max_column_widths_[i]-cell_width)/2;
                    size_t right_empty = max_column_widths_[i]-cell_width-left_empty;
                    std::cout << std::string(left_empty,' ')+cells_lines[i][line_i]+std::string(right_empty,' ') << " │ ";
                } else {
                    std::cout << std::string(max_column_widths_[i], ' ') << " │ ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "├";
        for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┼";
        std::cout << tcl::left(1) << "┤" << std::endl;
    }
    std::cout << tcl::up(1) << "└";
    for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┴";
    std::cout << tcl::left(1) << "┘" << std::endl;
}
