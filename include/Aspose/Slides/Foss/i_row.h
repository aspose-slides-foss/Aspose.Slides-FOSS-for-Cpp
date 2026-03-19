// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class ICellCollection;
class IBulkTextFormattable;
class IRowFormat;

/// Interface for a table row.
///
/// A row acts as both a cell collection and a bulk-text-formattable
/// element.  Concrete implementations inherit from ICellCollection and
/// IBulkTextFormattable; the `as_*` accessors expose those base interfaces.
class IRow {
public:
    virtual ~IRow() = default;

    /// Returns the height of a row. Read-only.
    [[nodiscard]] virtual double height() const = 0;

    /// Returns the minimal possible height of a row.
    [[nodiscard]] virtual double minimal_height() const = 0;

    /// Sets the minimal possible height of a row.
    virtual void set_minimal_height(double value) = 0;

    /// Returns the RowFormat object that contains formatting properties
    /// for this row. Read-only.
    [[nodiscard]] virtual const IRowFormat& row_format() const = 0;

    /// Allows to get the base ICellCollection interface. Read-only.
    [[nodiscard]] virtual ICellCollection& as_i_cell_collection() = 0;
    [[nodiscard]] virtual const ICellCollection& as_i_cell_collection() const = 0;

    /// Allows to get the base IBulkTextFormattable interface. Read-only.
    [[nodiscard]] virtual IBulkTextFormattable& as_i_bulk_text_formattable() = 0;
    [[nodiscard]] virtual const IBulkTextFormattable& as_i_bulk_text_formattable() const = 0;

protected:
    IRow() = default;
};

} // namespace Aspose::Slides::Foss
