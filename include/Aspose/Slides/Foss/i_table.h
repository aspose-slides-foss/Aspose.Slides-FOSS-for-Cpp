// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>

#include <Aspose/Slides/Foss/i_bulk_text_formattable.h>
#include <Aspose/Slides/Foss/i_graphical_object.h>
#include <Aspose/Slides/Foss/table_style_preset.h>

namespace Aspose::Slides::Foss {

class Cell;
class ColumnCollection;
class ITableFormat;
class RowCollection;

/// Interface for a table shape on a slide.
class ITable : public IGraphicalObject, public IBulkTextFormattable {
public:
    ~ITable() override = default;

    /// Returns the collection of rows. Read-only.
    [[nodiscard]] virtual RowCollection& rows() = 0;

    /// Returns the collection of columns. Read-only.
    [[nodiscard]] virtual ColumnCollection& columns() = 0;

    /// Returns the cell at the given row and column.
    [[nodiscard]] virtual Cell& cell(std::size_t row, std::size_t col) = 0;

    /// Returns the TableFormat object that contains formatting properties for this table. Read-only.
    [[nodiscard]] virtual ITableFormat& table_format() = 0;

    /// Gets the builtin table style. Read/write.
    [[nodiscard]] virtual TableStylePreset style_preset() const = 0;

    /// Sets the builtin table style.
    virtual void set_style_preset(TableStylePreset value) = 0;

    /// Determines whether the table has right to left reading order. Read/write.
    [[nodiscard]] virtual bool right_to_left() const = 0;

    /// Sets right to left reading order.
    virtual void set_right_to_left(bool value) = 0;

    /// Determines whether the first row of a table has to be drawn with a special formatting. Read/write.
    [[nodiscard]] virtual bool first_row() const = 0;

    /// Sets whether the first row has special formatting.
    virtual void set_first_row(bool value) = 0;

    /// Determines whether the first column of a table has to be drawn with a special formatting. Read/write.
    [[nodiscard]] virtual bool first_col() const = 0;

    /// Sets whether the first column has special formatting.
    virtual void set_first_col(bool value) = 0;

    /// Determines whether the last row of a table has to be drawn with a special formatting. Read/write.
    [[nodiscard]] virtual bool last_row() const = 0;

    /// Sets whether the last row has special formatting.
    virtual void set_last_row(bool value) = 0;

    /// Determines whether the last column of a table has to be drawn with a special formatting. Read/write.
    [[nodiscard]] virtual bool last_col() const = 0;

    /// Sets whether the last column has special formatting.
    virtual void set_last_col(bool value) = 0;

    /// Determines whether even rows have to be drawn with a different formatting. Read/write.
    [[nodiscard]] virtual bool horizontal_banding() const = 0;

    /// Sets whether even rows have different formatting.
    virtual void set_horizontal_banding(bool value) = 0;

    /// Determines whether even columns have to be drawn with a different formatting. Read/write.
    [[nodiscard]] virtual bool vertical_banding() const = 0;

    /// Sets whether even columns have different formatting.
    virtual void set_vertical_banding(bool value) = 0;

    /// Allows to get base IGraphicalObject interface. Read-only.
    [[nodiscard]] virtual IGraphicalObject& as_i_graphical_object() = 0;

    /// Allows to get base IBulkTextFormattable interface. Read-only.
    [[nodiscard]] virtual IBulkTextFormattable& as_i_bulk_text_formattable() = 0;

    /// Merges two cells, expanding cell1 to cover the area of both cells.
    /// @param cell1 The first cell to merge.
    /// @param cell2 The second cell to merge.
    /// @param allow_splitting If true, allow splitting of already-merged cells.
    /// @return Reference to the resulting merged cell.
    virtual Cell& merge_cells(Cell& cell1, Cell& cell2, bool allow_splitting) = 0;

protected:
    ITable() = default;
};

} // namespace Aspose::Slides::Foss
