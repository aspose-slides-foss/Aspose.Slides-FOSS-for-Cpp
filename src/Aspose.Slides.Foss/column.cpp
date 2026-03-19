// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/column.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/table.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::Elements;

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void Column::init_internal(pugi::xml_node grid_col_element,
                           int col_index,
                           pugi::xml_node tbl_element,
                           Internal::pptx::SlidePart* slide_part,
                           IBaseSlide* parent_slide,
                           Table* table) {
    grid_col_element_ = grid_col_element;
    col_index_ = col_index;
    tbl_element_ = tbl_element;
    slide_part_ = slide_part;
    table_ = table;

    // Read width from the gridCol 'w' attribute (EMUs), convert to points.
    if (grid_col_element_) {
        if (auto w_attr = grid_col_element_.attribute("w"); w_attr) {
            width_ = w_attr.as_double() / Internal::pptx::kEmuPerPoint;
        }
    }

    // Parse cells: one per row at this column index.
    std::vector<std::unique_ptr<Cell>> cells;
    int row_idx = 0;
    for (auto tr : tbl_element_.children("a:tr")) {
        int tc_idx = 0;
        for (auto tc : tr.children("a:tc")) {
            if (tc_idx == col_index) {
                auto cell = std::make_unique<Cell>();
                cell->init_internal(tc, row_idx, col_index,
                                    slide_part, parent_slide, table);
                cells.push_back(std::move(cell));
                break;
            }
            ++tc_idx;
        }
        ++row_idx;
    }

    // Populate the inherited CellCollection.
    CellCollection::init_internal(std::move(cells), parent_slide);
}

} // namespace Aspose::Slides::Foss
