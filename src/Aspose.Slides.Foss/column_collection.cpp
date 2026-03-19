// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/column_collection.h>

#include <stdexcept>
#include <string>

#include <Aspose/Slides/Foss/text_frame.h>

namespace Aspose::Slides::Foss {

Column& ColumnCollection::operator[](std::size_t index) {
    if (index >= columns_.size()) {
        throw std::out_of_range("ColumnCollection index out of range");
    }
    return *columns_[index];
}

const Column& ColumnCollection::operator[](std::size_t index) const {
    if (index >= columns_.size()) {
        throw std::out_of_range("ColumnCollection index out of range");
    }
    return *columns_[index];
}

Column& ColumnCollection::add(std::unique_ptr<Column> col) {
    columns_.push_back(std::move(col));
    return *columns_.back();
}

std::unique_ptr<Column> ColumnCollection::clone_column(const Column& src) {
    auto col = std::make_unique<Column>(src.width());
    // Clone cells from the source column.
    for (std::size_t i = 0; i < src.size(); ++i) {
        auto& src_cell = src[i];
        auto cell = std::make_unique<Cell>();
        cell->set_width(src_cell.width());
        cell->set_height(src_cell.height());
        cell->set_offset_x(src_cell.offset_x());
        cell->set_offset_y(src_cell.offset_y());
        cell->set_margin_left(src_cell.margin_left());
        cell->set_margin_right(src_cell.margin_right());
        cell->set_margin_top(src_cell.margin_top());
        cell->set_margin_bottom(src_cell.margin_bottom());
        cell->set_col_span(src_cell.col_span());
        cell->set_row_span(src_cell.row_span());
        cell->set_first_row_index(src_cell.first_row_index());
        cell->set_first_column_index(src_cell.first_column_index());
        cell->set_text_vertical_type(src_cell.text_vertical_type());
        cell->set_text_anchor_type(src_cell.text_anchor_type());
        cell->set_anchor_center(src_cell.anchor_center());
        cell->set_h_merge(src_cell.h_merge());
        cell->set_v_merge(src_cell.v_merge());
        if (src_cell.text_frame()) {
            cell->text_frame()->set_text(src_cell.text_frame()->text());
        }
        col->add(std::move(cell));
    }
    return col;
}

std::vector<Column*> ColumnCollection::add_clone(const Column& templ, bool /*with_attached_columns*/) {
    auto cloned = clone_column(templ);
    columns_.push_back(std::move(cloned));
    return {columns_.back().get()};
}

std::vector<Column*> ColumnCollection::insert_clone(std::size_t index, const Column& templ,
                                                     bool /*with_attached_columns*/) {
    auto cloned = clone_column(templ);
    if (index > columns_.size()) {
        throw std::out_of_range("ColumnCollection::insert_clone: index out of range");
    }
    auto it = columns_.begin() + static_cast<std::ptrdiff_t>(index);
    it = columns_.insert(it, std::move(cloned));
    return {it->get()};
}

void ColumnCollection::remove_at(std::size_t first_column_index, bool /*with_attached_rows*/) {
    if (first_column_index >= columns_.size()) {
        throw std::out_of_range("Column index " + std::to_string(first_column_index) + " out of range");
    }
    columns_.erase(columns_.begin() + static_cast<std::ptrdiff_t>(first_column_index));
}

void ColumnCollection::remove_at(std::size_t index) {
    remove_at(index, false);
}

std::vector<Column*> ColumnCollection::as_i_collection() const {
    std::vector<Column*> result;
    result.reserve(columns_.size());
    for (const auto& c : columns_) {
        result.push_back(c.get());
    }
    return result;
}

std::vector<Column*> ColumnCollection::as_i_enumerable() const {
    return as_i_collection();
}

} // namespace Aspose::Slides::Foss
