// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <vector>

namespace Aspose::Slides::Foss {

class Row;
class IRow;

/// Interface for a collection of table rows.
class IRowCollection {
public:
    virtual ~IRowCollection() = default;

    /// Returns the number of rows.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the row at the given index.
    [[nodiscard]] virtual Row& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const Row& operator[](std::size_t index) const = 0;

    /// Clones the given template row and appends it to the end.
    /// @param templ The row to clone.
    /// @param with_attached_rows If true, clone attached rows as well.
    /// @return A vector containing a pointer to the newly added row.
    virtual std::vector<Row*> add_clone(const Row& templ, bool with_attached_rows) = 0;

    /// Clones the given template row and inserts it at the specified index.
    /// @param index The position at which to insert.
    /// @param templ The row to clone.
    /// @param with_attached_rows If true, clone attached rows as well.
    /// @return A vector containing a pointer to the inserted row.
    virtual std::vector<Row*> insert_clone(std::size_t index, const Row& templ,
                                           bool with_attached_rows) = 0;

    /// Removes the row at the given index.
    /// @param first_row_index The index of the row to remove.
    /// @param with_attached_rows If true, remove attached rows as well.
    virtual void remove_at(std::size_t first_row_index, bool with_attached_rows) = 0;

    /// Returns a snapshot of the rows as raw pointers.
    [[nodiscard]] virtual std::vector<Row*> as_i_collection() const = 0;

    /// Returns a snapshot of the rows as raw pointers (same as as_i_collection).
    [[nodiscard]] virtual std::vector<Row*> as_i_enumerable() const = 0;

protected:
    IRowCollection() = default;
};

} // namespace Aspose::Slides::Foss
