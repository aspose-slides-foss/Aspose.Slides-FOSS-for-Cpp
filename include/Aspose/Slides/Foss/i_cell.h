// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>
#include <Aspose/Slides/Foss/text_vertical_type.h>

namespace Aspose::Slides::Foss {

class Column;
class Row;
class Table;
class TextFrame;
class CellFormat;

/// Interface for a table cell.
class ICell : public ISlideComponent, public virtual IPresentationComponent {
public:
    ~ICell() override = default;

    /// Returns the x offset from the left side of the table. Read-only.
    [[nodiscard]] virtual double offset_x() const = 0;

    /// Returns the y offset from the top side of the table. Read-only.
    [[nodiscard]] virtual double offset_y() const = 0;

    /// Returns the index of the first row covered by the cell. Read-only.
    [[nodiscard]] virtual int first_row_index() const = 0;

    /// Returns the index of the first column covered by the cell. Read-only.
    [[nodiscard]] virtual int first_column_index() const = 0;

    /// Returns the width of the cell. Read-only.
    [[nodiscard]] virtual double width() const = 0;

    /// Returns the height of the cell. Read-only.
    [[nodiscard]] virtual double height() const = 0;

    /// Returns the minimum height of the cell. Read-only.
    [[nodiscard]] virtual double minimal_height() const = 0;

    /// Returns the left margin in a TextFrame. Read/write.
    [[nodiscard]] virtual double margin_left() const = 0;
    virtual void set_margin_left(double value) = 0;

    /// Returns the right margin in a TextFrame. Read/write.
    [[nodiscard]] virtual double margin_right() const = 0;
    virtual void set_margin_right(double value) = 0;

    /// Returns the top margin in a TextFrame. Read/write.
    [[nodiscard]] virtual double margin_top() const = 0;
    virtual void set_margin_top(double value) = 0;

    /// Returns the bottom margin in a TextFrame. Read/write.
    [[nodiscard]] virtual double margin_bottom() const = 0;
    virtual void set_margin_bottom(double value) = 0;

    /// Returns the type of vertical text. Read/write.
    [[nodiscard]] virtual TextVerticalType text_vertical_type() const = 0;
    virtual void set_text_vertical_type(TextVerticalType value) = 0;

    /// Returns the text anchor type. Read/write.
    [[nodiscard]] virtual TextAnchorType text_anchor_type() const = 0;
    virtual void set_text_anchor_type(TextAnchorType value) = 0;

    /// Determines whether text box is centered inside the cell. Read/write.
    [[nodiscard]] virtual bool anchor_center() const = 0;
    virtual void set_anchor_center(bool value) = 0;

    /// Returns the first column of this cell. Read-only.
    [[nodiscard]] virtual Column* first_column() const = 0;

    /// Returns the first row of this cell. Read-only.
    [[nodiscard]] virtual Row* first_row() const = 0;

    /// Returns the number of grid columns spanned by this cell. Read-only.
    [[nodiscard]] virtual int col_span() const = 0;

    /// Returns the number of rows spanned by this cell. Read-only.
    [[nodiscard]] virtual int row_span() const = 0;

    /// Returns the text frame for this cell. Read-only.
    [[nodiscard]] virtual TextFrame* text_frame() = 0;

    /// Returns the parent table for this cell. Read-only.
    [[nodiscard]] virtual Table* table() const = 0;

    /// Returns true if the cell is merged with any adjacent cell. Read-only.
    [[nodiscard]] virtual bool is_merged_cell() const = 0;

    /// Returns the cell format. Read-only.
    [[nodiscard]] virtual CellFormat& cell_format() = 0;

    /// Returns this cell as an ISlideComponent. Read-only.
    [[nodiscard]] virtual ISlideComponent& as_i_slide_component() = 0;
};

} // namespace Aspose::Slides::Foss
