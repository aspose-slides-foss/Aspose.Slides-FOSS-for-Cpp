// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <stdexcept>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/cell_collection.h>
#include <Aspose/Slides/Foss/column_format.h>
#include <Aspose/Slides/Foss/i_bulk_text_formattable.h>
#include <Aspose/Slides/Foss/i_column.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class Table;

/// Represents a column in a table.
class Column final : public CellCollection, public IColumn, public IBulkTextFormattable {
public:
    Column() = default;
    explicit Column(double width) : width_(width) {}

    /// Initializes this column from XML elements.
    ///
    /// Parses one cell per row at the given column index from the
    /// \<a:tbl\> element, populating the inherited CellCollection.
    void init_internal(pugi::xml_node grid_col_element,
                       int col_index,
                       pugi::xml_node tbl_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide,
                       Table* table);

    /// Returns the width of this column.
    [[nodiscard]] double width() const noexcept override { return width_; }
    void set_width(double value) noexcept override { width_ = value; }

    /// Returns the ColumnFormat object that contains formatting properties for this column. Read-only.
    [[nodiscard]] const ColumnFormat& column_format() const noexcept override { return column_format_; }

    /// Returns this object as an ICellCollection reference.
    [[nodiscard]] ICellCollection& as_i_cell_collection() noexcept override { return *this; }
    [[nodiscard]] const ICellCollection& as_i_cell_collection() const noexcept override { return *this; }

    /// Returns this object as an IBulkTextFormattable reference.
    [[nodiscard]] IBulkTextFormattable& as_i_bulk_text_formattable() noexcept override { return *this; }
    [[nodiscard]] const IBulkTextFormattable& as_i_bulk_text_formattable() const noexcept override { return *this; }

    /// Sets the portion format for all child portions.
    void set_text_format(const IPortionFormat& /*source*/) override {
        // Stub: bulk text formatting not yet wired to XML backend.
    }

    /// Sets the paragraph format for all child paragraphs.
    void set_text_format(const IParagraphFormat& /*source*/) override {
        // Stub: bulk text formatting not yet wired to XML backend.
    }

    /// Sets the text frame format for all child text frames.
    void set_text_format(const ITextFrameFormat& /*source*/) override {
        // Stub: bulk text formatting not yet wired to XML backend.
    }

private:
    double width_ = 0;
    ColumnFormat column_format_;
    pugi::xml_node grid_col_element_;
    int col_index_ = 0;
    pugi::xml_node tbl_element_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    Table* table_ = nullptr;
};

} // namespace Aspose::Slides::Foss
