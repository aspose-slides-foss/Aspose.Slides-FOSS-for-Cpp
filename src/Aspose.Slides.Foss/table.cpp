// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/table.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/column.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::Elements;

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

static pugi::xml_node find_descendant(pugi::xml_node root, std::string_view name) {
    for (auto child : root.children()) {
        if (std::string_view(child.name()) == name) {
            return child;
        }
        auto result = find_descendant(child, name);
        if (result) {
            return result;
        }
    }
    return {};
}

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void Table::init_internal(pugi::xml_node xml_element,
                          Internal::pptx::SlidePart* slide_part,
                          IBaseSlide* parent_slide) {
    xml_element_ = xml_element;
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;

    // Locate the <a:tbl> element inside the graphicFrame.
    // Use prefix notation because pugixml stores tags as-is without namespace processing.
    tbl_ = find_descendant(xml_element, "a:tbl");
    if (tbl_) {
        tbl_pr_ = tbl_.child("a:tblPr");
        tbl_grid_ = tbl_.child("a:tblGrid");
    }

    // Initialize table format from the <a:tblPr> element.
    auto save_cb = [this]() {
        if (slide_part_) {
            slide_part_->save();
        }
    };
    if (tbl_pr_) {
        table_format_.init_internal(tbl_pr_, save_cb);

        // Read style boolean attributes from <a:tblPr>.
        first_row_ = get_bool_attr("firstRow");
        first_col_ = get_bool_attr("firstCol");
        last_row_ = get_bool_attr("lastRow");
        last_col_ = get_bool_attr("lastCol");
        horizontal_banding_ = get_bool_attr("bandRow");
        vertical_banding_ = get_bool_attr("bandCol");
        right_to_left_ = get_bool_attr("rtl");
    }

    // Parse rows from <a:tr> children of <a:tbl>.
    if (tbl_) {
        rows_.init_internal(tbl_, save_cb, slide_part, parent_slide, this);
    }

    // Parse columns from <a:tblGrid> children.
    if (tbl_grid_ && tbl_) {
        int col_idx = 0;
        for (auto grid_col : tbl_grid_.children("a:gridCol")) {
            auto col = std::make_unique<Column>();
            col->init_internal(grid_col, col_idx, tbl_,
                               slide_part, parent_slide, this);
            columns_.add(std::move(col));
            ++col_idx;
        }
    }
}

// ---------------------------------------------------------------------------
// get_tbl_pr / ensure_tbl_pr
// ---------------------------------------------------------------------------

pugi::xml_node Table::get_tbl_pr() const {
    return tbl_pr_ ? tbl_pr_ : pugi::xml_node{};
}

pugi::xml_node Table::ensure_tbl_pr() {
    if (tbl_pr_) {
        return tbl_pr_;
    }
    // Create <a:tblPr> and insert as first child of <a:tbl>.
    tbl_pr_ = tbl_.prepend_child("a:tblPr");
    return tbl_pr_;
}

// ---------------------------------------------------------------------------
// get_bool_attr / set_bool_attr
// ---------------------------------------------------------------------------

bool Table::get_bool_attr(std::string_view attr_name) const {
    auto tbl_pr = get_tbl_pr();
    if (!tbl_pr) {
        return false;
    }
    auto attr = tbl_pr.attribute(std::string(attr_name).c_str());
    if (!attr) {
        return false;
    }
    return std::string_view(attr.as_string()) == "1";
}

void Table::set_bool_attr(std::string_view attr_name, bool value) {
    auto tbl_pr = ensure_tbl_pr();
    std::string name_str(attr_name);
    if (value) {
        auto attr = tbl_pr.attribute(name_str.c_str());
        if (attr) {
            attr.set_value("1");
        } else {
            tbl_pr.append_attribute(name_str.c_str()) = "1";
        }
    } else {
        tbl_pr.remove_attribute(name_str.c_str());
    }
    if (slide_part_) {
        slide_part_->save();
    }
}

// ---------------------------------------------------------------------------
// find_style_element / read_style_guid
// ---------------------------------------------------------------------------

pugi::xml_node Table::find_style_element(pugi::xml_node tbl_pr) const {
    auto el = tbl_pr.child("a:tableStyleId");
    if (el) {
        return el;
    }
    return tbl_pr.child("a:tblStyle");
}

std::string Table::read_style_guid(pugi::xml_node style_el) const {
    if (!style_el) {
        return {};
    }
    // <a:tableStyleId> stores GUID as text content.
    auto text = style_el.child_value();
    if (text && text[0] != '\0') {
        std::string result(text);
        auto start = result.find_first_not_of(" \t\n\r");
        auto end = result.find_last_not_of(" \t\n\r");
        if (start == std::string::npos) {
            return {};
        }
        return result.substr(start, end - start + 1);
    }
    // Legacy <a:tblStyle> stores GUID as val attribute.
    return style_el.attribute("val").as_string("");
}

// ---------------------------------------------------------------------------
// cell
// ---------------------------------------------------------------------------

Cell& Table::cell(std::size_t row, std::size_t col) {
    return rows_[row][col];
}

Cell& Table::merge_cells(Cell& cell1, Cell& cell2, bool /*allow_splitting*/) {
    // Determine the bounding rectangle of the two cells.
    const int r1 = cell1.first_row_index();
    const int c1 = cell1.first_column_index();
    const int r2 = cell2.first_row_index();
    const int c2 = cell2.first_column_index();

    const int min_row = std::min(r1, r2);
    const int max_row = std::max(r1 + cell1.row_span() - 1, r2 + cell2.row_span() - 1);
    const int min_col = std::min(c1, c2);
    const int max_col = std::max(c1 + cell1.col_span() - 1, c2 + cell2.col_span() - 1);

    // The anchor cell is the top-left cell of the merged region.
    Cell& anchor = rows_[static_cast<std::size_t>(min_row)][static_cast<std::size_t>(min_col)];
    anchor.set_col_span(max_col - min_col + 1);
    anchor.set_row_span(max_row - min_row + 1);

    // Mark all other cells in the region as merged continuations.
    for (int r = min_row; r <= max_row; ++r) {
        for (int c = min_col; c <= max_col; ++c) {
            if (r == min_row && c == min_col) {
                continue;
            }
            Cell& other = rows_[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
            if (c != min_col) {
                other.set_h_merge(true);
            }
            if (r != min_row) {
                other.set_v_merge(true);
            }
        }
    }

    return anchor;
}

void Table::set_text_format(const IPortionFormat& /*source*/) {
    // Stub: bulk text formatting not yet wired to XML backend.
}

void Table::set_text_format(const IParagraphFormat& /*source*/) {
    // Stub: bulk text formatting not yet wired to XML backend.
}

void Table::set_text_format(const ITextFrameFormat& /*source*/) {
    // Stub: bulk text formatting not yet wired to XML backend.
}

} // namespace Aspose::Slides::Foss
