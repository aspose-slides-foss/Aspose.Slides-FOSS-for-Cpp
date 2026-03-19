// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <vector>

namespace Aspose::Slides::Foss {

class Column;
class IColumn;

/// Interface for a collection of table columns.
class IColumnCollection {
public:
    virtual ~IColumnCollection() = default;

    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual Column& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const Column& operator[](std::size_t index) const = 0;

    /// Clones the given template column and appends it to the end.
    /// @param templ The column to clone.
    /// @param with_attached_columns If true, clone attached columns as well.
    /// @return A vector containing a pointer to the newly added column.
    virtual std::vector<Column*> add_clone(const Column& templ, bool with_attached_columns) = 0;

    /// Clones the given template column and inserts it at the specified index.
    /// @param index The position at which to insert.
    /// @param templ The column to clone.
    /// @param with_attached_columns If true, clone attached columns as well.
    /// @return A vector containing a pointer to the inserted column.
    virtual std::vector<Column*> insert_clone(std::size_t index, const Column& templ,
                                              bool with_attached_columns) = 0;

    /// Removes the column at the given index.
    /// @param first_column_index The index of the column to remove.
    /// @param with_attached_rows If true, remove attached rows as well.
    virtual void remove_at(std::size_t first_column_index, bool with_attached_rows) = 0;

    /// Returns a snapshot of the columns as raw pointers.
    [[nodiscard]] virtual std::vector<Column*> as_i_collection() const = 0;

    /// Returns a snapshot of the columns as raw pointers (same as as_i_collection).
    [[nodiscard]] virtual std::vector<Column*> as_i_enumerable() const = 0;
};

} // namespace Aspose::Slides::Foss
