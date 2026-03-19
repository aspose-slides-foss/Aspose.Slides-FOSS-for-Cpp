// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

#include <Aspose/Slides/Foss/i_row_collection.h>
#include <Aspose/Slides/Foss/row.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class IBaseSlide;
class Table;

/// Represents collection of rows in a table.
class RowCollection final : public IRowCollection {
public:
    RowCollection() = default;
    ~RowCollection() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize the collection from a `<a:tbl>` XML element.
    /// Parses all `<a:tr>` children and creates corresponding Row objects.
    /// @param tbl_element The `<a:tbl>` XML node containing row elements.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide The slide that owns the table.
    /// @param table The parent table object.
    void init_internal(pugi::xml_node tbl_element,
                       std::function<void()> save_callback,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide,
                       Table* table);

    /// Rebuild the rows list from the stored XML element.
    /// Clears existing rows and re-parses all `<a:tr>` children.
    void rebuild();

    // -- Public API -------------------------------------------------------

    /// Returns the number of rows.
    [[nodiscard]] std::size_t size() const noexcept override { return rows_.size(); }

    /// Returns the row at the given index.
    [[nodiscard]] Row& operator[](std::size_t index) override;
    [[nodiscard]] const Row& operator[](std::size_t index) const override;

    /// Adds a row to the collection.
    Row& add(std::unique_ptr<Row> row);

    /// Clones the given template row and appends it to the end.
    std::vector<Row*> add_clone(const Row& templ, bool with_attached_rows) override;

    /// Clones the given template row and inserts it at the specified index.
    std::vector<Row*> insert_clone(std::size_t index, const Row& templ,
                                   bool with_attached_rows) override;

    /// Removes the row at the given index.
    /// @throws std::out_of_range if the index is out of bounds.
    void remove_at(std::size_t first_row_index, bool with_attached_rows) override;

    /// Removes the row at the given index (convenience overload).
    void remove_at(std::size_t index);

    /// Removes all rows.
    void clear() noexcept { rows_.clear(); }

    /// Returns a snapshot of the rows as raw pointers.
    [[nodiscard]] std::vector<Row*> as_i_collection() const override;

    /// Returns a snapshot of the rows as raw pointers (same as as_i_collection).
    [[nodiscard]] std::vector<Row*> as_i_enumerable() const override;

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<Row>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Row>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return rows_.begin(); }
    [[nodiscard]] iterator end() noexcept { return rows_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return rows_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return rows_.end(); }

private:
    /// Deep-clones a Row (height + cells).
    [[nodiscard]] static std::unique_ptr<Row> clone_row(const Row& src);

    /// Parses `<a:tr>` children from tbl_element_ and populates rows_.
    void parse_rows();

    std::vector<std::unique_ptr<Row>> rows_;
    pugi::xml_node tbl_element_;
    std::function<void()> save_callback_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;
    Table* table_ = nullptr;
};

} // namespace Aspose::Slides::Foss
