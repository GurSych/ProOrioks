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
        for(size_t i{}; i < columns.size(); ++i) max_column_widths_[i] = std::max(max_column_widths_[i], columns[i].size());
    }

void HTable::addRow(const std::vector<std::string>& values) {
    if (values.size() != columns_.size()) {
        throw std::invalid_argument("Number of cells does not match number of columns");
    }
    max_row_heights_.emplace_back();
    for (size_t i{}; i < values.size(); ++i) {
        auto lines = strtools::split(values[i], '\n');
        max_row_heights_.back() = std::max(max_row_heights_.back(), lines.size());
        max_column_widths_[i]   = std::max(max_column_widths_[i], std::max_element(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); })->size());
    }
    rows_.push_back(values);
}

void HTable::print(bool with_name) const {
    if(with_name) {
        size_t table_width = std::accumulate(max_column_widths_.begin(), max_column_widths_.end(), 0) + 3*columns_.size() + 1;
        size_t left_padding  = (table_width - name_.size()) / 2;
        size_t right_padding = table_width - name_.size() - left_padding;
        std::cout << "┌" <<  std::string{"—"}*(left_padding-2) << " " << tcl::colorize(name_,tcl::BOLD) << " " << std::string{"—"}*(right_padding-2) << "┐" << std::endl;
    }
    std::cout << "┌";
    for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┬";
    std::cout << tcl::left(1) << "┐" << std::endl << "│ ";
    for (size_t i{}; i < columns_.size(); ++i) {
        size_t left_empty  = (max_column_widths_[i]-columns_[i].size())/2;
        size_t right_empty = max_column_widths_[i]-columns_[i].size()-left_empty;
        std::cout << std::string(left_empty,' ')+tcl::colorize(columns_[i],tcl::BOLD)+std::string(right_empty,' ') << " │ ";
    }
    std::cout << std::endl << "├";
    for (size_t i{}; i < columns_.size(); ++i) std::cout << std::string{"—"}*(max_column_widths_[i]+2) << "┼";
    std::cout << tcl::left(1) << "┤" << std::endl;
    for (size_t row_i{}; row_i < rows_.size(); ++row_i) {
        auto& row = rows_[row_i];
        std::vector<std::vector<std::string>> cells_lines{};
        for (size_t i{}; i < columns_.size(); ++i) cells_lines.push_back(strtools::split(row[i], '\n'));
        for (size_t line_i{}; line_i < max_row_heights_[row_i]; ++line_i) {
            std::cout << "│ ";
            for (size_t i{}; i < columns_.size(); ++i) {
                if (line_i < cells_lines[i].size()) {
                    size_t left_empty  = (max_column_widths_[i]-cells_lines[i][line_i].size())/2;
                    size_t right_empty = max_column_widths_[i]-cells_lines[i][line_i].size()-left_empty;
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
