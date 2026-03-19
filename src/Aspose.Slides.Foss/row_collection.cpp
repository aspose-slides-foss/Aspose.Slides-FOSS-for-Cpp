// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/row_collection.h>

#include <stdexcept>
#include <string>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/text_frame.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// XML-backed internal API
// ---------------------------------------------------------------------------

void RowCollection::init_internal(pugi::xml_node tbl_element,
                                  std::function<void()> save_callback,
                                  Internal::pptx::SlidePart* slide_part,
                                  IBaseSlide* parent_slide,
                                  Table* table) {
    tbl_element_ = tbl_element;
    save_callback_ = std::move(save_callback);
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;
    table_ = table;
    parse_rows();
}

void RowCollection::rebuild() {
    parse_rows();
}

void RowCollection::parse_rows() {
    rows_.clear();
    if (!tbl_element_) {
        return;
    }
    int row_idx = 0;
    for (auto tr : tbl_element_.children("a:tr")) {
        auto row = std::make_unique<Row>();
        row->init_internal(tr, row_idx, slide_part_, parent_slide_, table_);
        rows_.push_back(std::move(row));
        ++row_idx;
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

Row& RowCollection::operator[](std::size_t index) {
    if (index >= rows_.size()) {
        throw std::out_of_range("RowCollection index out of range");
    }
    return *rows_[index];
}

const Row& RowCollection::operator[](std::size_t index) const {
    if (index >= rows_.size()) {
        throw std::out_of_range("RowCollection index out of range");
    }
    return *rows_[index];
}

Row& RowCollection::add(std::unique_ptr<Row> row) {
    rows_.push_back(std::move(row));
    return *rows_.back();
}

std::unique_ptr<Row> RowCollection::clone_row(const Row& src) {
    auto row = std::make_unique<Row>(src.height());
    row->set_minimal_height(src.minimal_height());
    // Clone cells from the source row.
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
        row->add(std::move(cell));
    }
    return row;
}

std::vector<Row*> RowCollection::add_clone(const Row& templ, bool /*with_attached_rows*/) {
    auto cloned = clone_row(templ);
    rows_.push_back(std::move(cloned));
    return {rows_.back().get()};
}

std::vector<Row*> RowCollection::insert_clone(std::size_t index, const Row& templ,
                                               bool /*with_attached_rows*/) {
    auto cloned = clone_row(templ);
    if (index > rows_.size()) {
        throw std::out_of_range("RowCollection::insert_clone: index out of range");
    }
    auto it = rows_.begin() + static_cast<std::ptrdiff_t>(index);
    it = rows_.insert(it, std::move(cloned));
    return {it->get()};
}

void RowCollection::remove_at(std::size_t first_row_index, bool /*with_attached_rows*/) {
    if (first_row_index >= rows_.size()) {
        throw std::out_of_range("Row index " + std::to_string(first_row_index) + " out of range");
    }

    // Remove corresponding <a:tr> element from XML if backed by XML.
    if (tbl_element_) {
        std::size_t idx = 0;
        for (auto tr : tbl_element_.children("a:tr")) {
            if (idx == first_row_index) {
                tbl_element_.remove_child(tr);
                break;
            }
            ++idx;
        }
        rebuild();
        if (save_callback_) {
            save_callback_();
        }
        return;
    }

    rows_.erase(rows_.begin() + static_cast<std::ptrdiff_t>(first_row_index));
}

void RowCollection::remove_at(std::size_t index) {
    remove_at(index, false);
}

std::vector<Row*> RowCollection::as_i_collection() const {
    std::vector<Row*> result;
    result.reserve(rows_.size());
    for (const auto& r : rows_) {
        result.push_back(r.get());
    }
    return result;
}

std::vector<Row*> RowCollection::as_i_enumerable() const {
    return as_i_collection();
}

} // namespace Aspose::Slides::Foss
