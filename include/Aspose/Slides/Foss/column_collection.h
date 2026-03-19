// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/i_column_collection.h>

namespace Aspose::Slides::Foss {

/// Represents collection of columns in a table.
class ColumnCollection final : public IColumnCollection {
public:
    ColumnCollection() = default;
    ~ColumnCollection() override = default;

    /// Returns the number of columns.
    [[nodiscard]] std::size_t size() const noexcept override { return columns_.size(); }

    /// Returns the column at the given index.
    [[nodiscard]] Column& operator[](std::size_t index) override;
    [[nodiscard]] const Column& operator[](std::size_t index) const override;

    /// Adds a column to the collection.
    Column& add(std::unique_ptr<Column> col);

    /// Clones the given template column and appends it to the end.
    std::vector<Column*> add_clone(const Column& templ, bool with_attached_columns) override;

    /// Clones the given template column and inserts it at the specified index.
    std::vector<Column*> insert_clone(std::size_t index, const Column& templ,
                                      bool with_attached_columns) override;

    /// Removes the column at the given index.
    /// @throws std::out_of_range if the index is out of bounds.
    void remove_at(std::size_t first_column_index, bool with_attached_rows) override;

    /// Removes the column at the given index (convenience overload).
    void remove_at(std::size_t index);

    /// Removes all columns.
    void clear() noexcept { columns_.clear(); }

    /// Returns a snapshot of the columns as raw pointers.
    [[nodiscard]] std::vector<Column*> as_i_collection() const override;

    /// Returns a snapshot of the columns as raw pointers (same as as_i_collection).
    [[nodiscard]] std::vector<Column*> as_i_enumerable() const override;

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<Column>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Column>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return columns_.begin(); }
    [[nodiscard]] iterator end() noexcept { return columns_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return columns_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return columns_.end(); }

private:
    /// Deep-clones a Column (width + cells).
    [[nodiscard]] static std::unique_ptr<Column> clone_column(const Column& src);

    std::vector<std::unique_ptr<Column>> columns_;
};

} // namespace Aspose::Slides::Foss
