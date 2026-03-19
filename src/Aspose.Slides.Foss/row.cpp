// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/row.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/cell.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::Elements;

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void Row::init_internal(pugi::xml_node tr_element,
                        int row_index,
                        Internal::pptx::SlidePart* slide_part,
                        IBaseSlide* parent_slide,
                        Table* table) {
    tr_element_ = tr_element;
    row_index_ = row_index;
    slide_part_ = slide_part;
    table_ = table;

    // Parse height from the 'h' attribute (EMUs), convert to points.
    if (auto h_attr = tr_element_.attribute("h"); h_attr) {
        height_ = h_attr.as_double() / Internal::pptx::kEmuPerPoint;
    }

    // Parse cells from <a:tc> children.
    std::vector<std::unique_ptr<Cell>> parsed_cells;
    int col_idx = 0;
    for (auto tc : tr_element_.children("a:tc")) {
        auto cell = std::make_unique<Cell>();
        cell->init_internal(tc, row_index, col_idx, slide_part, parent_slide, table);
        parsed_cells.push_back(std::move(cell));
        ++col_idx;
    }

    // Pass parsed cells to the CellCollection base.
    CellCollection::init_internal(std::move(parsed_cells), parent_slide);
}

} // namespace Aspose::Slides::Foss
