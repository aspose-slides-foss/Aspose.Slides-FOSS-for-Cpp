// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/i_cell_collection.h>

namespace Aspose::Slides::Foss {

class IBaseSlide;
class IPresentation;

/// Represents a collection of table cells.
class CellCollection : public ICellCollection {
public:
    CellCollection() = default;
    ~CellCollection() override = default;

    /// Initializes the collection with cells and parent slide context.
    void init_internal(std::vector<std::unique_ptr<Cell>> cells,
                       IBaseSlide* parent_slide) {
        cells_ = std::move(cells);
        parent_slide_ = parent_slide;
    }

    /// Returns the number of cells.
    [[nodiscard]] std::size_t size() const noexcept override { return cells_.size(); }

    /// Returns the cell at the given index.
    [[nodiscard]] Cell& operator[](std::size_t index) override {
        if (index >= cells_.size()) {
            throw std::out_of_range("CellCollection index out of range");
        }
        return *cells_[index];
    }
    [[nodiscard]] const Cell& operator[](std::size_t index) const override {
        if (index >= cells_.size()) {
            throw std::out_of_range("CellCollection index out of range");
        }
        return *cells_[index];
    }

    /// Adds a cell to the collection.
    Cell& add(std::unique_ptr<Cell> cell) {
        cells_.push_back(std::move(cell));
        return *cells_.back();
    }

    /// Adds a default cell to the collection.
    Cell& add() { return add(std::make_unique<Cell>()); }

    /// Removes all cells.
    void clear() noexcept { cells_.clear(); }

    /// Returns the parent slide of this CellCollection. Read-only.
    [[nodiscard]] IBaseSlide* slide() override { return parent_slide_; }
    [[nodiscard]] const IBaseSlide* slide() const override { return parent_slide_; }

    /// Sets the parent slide.
    void set_slide(IBaseSlide* slide) noexcept { parent_slide_ = slide; }

    /// Returns the parent presentation of this CellCollection. Read-only.
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] ISlideComponent* as_i_slide_component() override { return this; }
    [[nodiscard]] const ISlideComponent* as_i_slide_component() const override { return this; }

    /// Allows to get base IPresentationComponent interface. Read-only.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override { return this; }
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override { return this; }

    /// Returns a snapshot of the cells as raw pointers.
    [[nodiscard]] std::vector<Cell*> as_i_collection() const override {
        std::vector<Cell*> result;
        result.reserve(cells_.size());
        for (const auto& c : cells_) {
            result.push_back(c.get());
        }
        return result;
    }

    /// Returns a snapshot of the cells as raw pointers (same as as_i_collection).
    [[nodiscard]] std::vector<Cell*> as_i_enumerable() const override { return as_i_collection(); }

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<Cell>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Cell>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return cells_.begin(); }
    [[nodiscard]] iterator end() noexcept { return cells_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return cells_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return cells_.end(); }

protected:
    std::vector<std::unique_ptr<Cell>>& cells() { return cells_; }

private:
    std::vector<std::unique_ptr<Cell>> cells_;
    IBaseSlide* parent_slide_ = nullptr;
};

} // namespace Aspose::Slides::Foss
