// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/cell_collection.h>
#include <Aspose/Slides/Foss/i_bulk_text_formattable.h>
#include <Aspose/Slides/Foss/i_row.h>
#include <Aspose/Slides/Foss/row_format.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class Table;

/// Represents a row in a table.
class Row final : public CellCollection, public IRow, public IBulkTextFormattable {
public:
    Row() = default;
    explicit Row(double height) : height_(height) {}

    /// Initialize this row from an XML `<a:tr>` element.
    /// Parses height and all `<a:tc>` children into Cell objects.
    /// @param tr_element  The XML node representing the table row (`<a:tr>`).
    /// @param row_index   The index of this row within the table.
    /// @param slide_part  The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    /// @param table       The parent table. May be nullptr.
    void init_internal(pugi::xml_node tr_element,
                       int row_index,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide,
                       Table* table);

    /// Returns the height of this row.
    [[nodiscard]] double height() const noexcept override { return height_; }
    void set_height(double value) noexcept { height_ = value; }

    /// Returns the minimal height of this row.
    [[nodiscard]] double minimal_height() const noexcept override { return minimal_height_; }
    void set_minimal_height(double value) noexcept override { minimal_height_ = value; }

    /// Returns the RowFormat object that contains formatting properties for this row. Read-only.
    [[nodiscard]] const RowFormat& row_format() const noexcept override { return row_format_; }

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
    double height_ = 0;
    double minimal_height_ = 0;
    RowFormat row_format_;

    // XML-backed state
    pugi::xml_node tr_element_;
    int row_index_ = 0;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    Table* table_ = nullptr;
};

} // namespace Aspose::Slides::Foss
