// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class ColumnFormat;
class ICellCollection;
class IBulkTextFormattable;

/// Interface for a table column.
///
/// A column acts as both a cell collection and a bulk-text-formattable
/// element.  Concrete implementations inherit from ICellCollection and
/// IBulkTextFormattable; the `as_*` accessors expose those base interfaces.
class IColumn {
public:
    virtual ~IColumn() = default;

    /// Returns the width of the column.
    [[nodiscard]] virtual double width() const = 0;

    /// Sets the width of the column.
    virtual void set_width(double value) = 0;

    /// Returns the ColumnFormat object that contains formatting properties
    /// for this column.  Read-only.
    [[nodiscard]] virtual const ColumnFormat& column_format() const = 0;

    /// Allows to get the base ICellCollection interface.  Read-only.
    [[nodiscard]] virtual ICellCollection& as_i_cell_collection() = 0;
    [[nodiscard]] virtual const ICellCollection& as_i_cell_collection() const = 0;

    /// Allows to get the base IBulkTextFormattable interface.  Read-only.
    [[nodiscard]] virtual IBulkTextFormattable& as_i_bulk_text_formattable() = 0;
    [[nodiscard]] virtual const IBulkTextFormattable& as_i_bulk_text_formattable() const = 0;
};

} // namespace Aspose::Slides::Foss
