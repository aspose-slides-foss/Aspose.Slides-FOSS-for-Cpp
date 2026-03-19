// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/cell.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/table.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::Elements;

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void Cell::init_internal(pugi::xml_node tc_element,
                         int row_index,
                         int col_index,
                         Internal::pptx::SlidePart* slide_part,
                         IBaseSlide* parent_slide,
                         Table* table) {
    tc_element_ = tc_element;
    first_row_index_ = row_index;
    first_column_index_ = col_index;
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;
    table_ = table;

    // Parse merge attributes.
    if (tc_element_) {
        if (auto gs = tc_element_.attribute("gridSpan"); gs) {
            col_span_ = gs.as_int(1);
        }
        if (auto rs = tc_element_.attribute("rowSpan"); rs) {
            row_span_ = rs.as_int(1);
        }
        if (auto hm = tc_element_.attribute("hMerge"); hm) {
            h_merge_ = std::string_view(hm.as_string()) == "1";
        }
        if (auto vm = tc_element_.attribute("vMerge"); vm) {
            v_merge_ = std::string_view(vm.as_string()) == "1";
        }
    }

    // Cache the <a:tcPr> node if present and init cell format.
    if (tc_element_) {
        tc_pr_ = tc_element_.child("a:tcPr");
        if (tc_pr_) {
            auto save_cb = [this]() {
                if (slide_part_) {
                    slide_part_->save();
                }
            };
            cell_format_.init_internal(tc_pr_, save_cb);
        }
    }

    // Parse text from <a:txBody>.
    if (tc_element_) {
        auto txbody = tc_element_.child("a:txBody");
        if (txbody && text_frame_) {
            text_frame_->init_internal(txbody, slide_part, parent_slide, nullptr);
        }
    }
}

// ---------------------------------------------------------------------------
// get_tc_pr / ensure_tc_pr
// ---------------------------------------------------------------------------

pugi::xml_node Cell::get_tc_pr() const {
    if (!tc_element_) {
        return {};
    }
    return tc_pr_ ? tc_pr_ : pugi::xml_node{};
}

pugi::xml_node Cell::ensure_tc_pr() {
    if (tc_pr_) {
        return tc_pr_;
    }
    // Create <a:tcPr> as a child of <a:tc>.
    tc_pr_ = tc_element_.append_child("a:tcPr");
    return tc_pr_;
}

Row* Cell::first_row() const noexcept {
    if (!table_) return nullptr;
    auto idx = static_cast<std::size_t>(first_row_index_);
    if (idx >= table_->rows().size()) return nullptr;
    return &table_->rows()[idx];
}

Column* Cell::first_column() const noexcept {
    if (!table_) return nullptr;
    auto idx = static_cast<std::size_t>(first_column_index_);
    if (idx >= table_->columns().size()) return nullptr;
    return &table_->columns()[idx];
}

Presentation* Cell::presentation() const noexcept {
    // Presentation access is through the slide; not wired up in this unit.
    return nullptr;
}

} // namespace Aspose::Slides::Foss
