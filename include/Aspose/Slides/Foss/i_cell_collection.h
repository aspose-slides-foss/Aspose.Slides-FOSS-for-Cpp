// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <vector>

#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>

namespace Aspose::Slides::Foss {

class Cell;
class ISlideComponent;

/// Represents a collection of cells.
class ICellCollection : public ISlideComponent, public virtual IPresentationComponent {
public:
    ~ICellCollection() override = default;

    /// Returns the number of cells in the collection.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the cell at the given index.
    [[nodiscard]] virtual Cell& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const Cell& operator[](std::size_t index) const = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;
    [[nodiscard]] virtual const ISlideComponent* as_i_slide_component() const = 0;

    /// Returns a snapshot of the cells as raw pointers.
    [[nodiscard]] virtual std::vector<Cell*> as_i_collection() const = 0;

    /// Returns a snapshot of the cells as raw pointers (same as as_i_collection).
    [[nodiscard]] virtual std::vector<Cell*> as_i_enumerable() const = 0;
};

} // namespace Aspose::Slides::Foss
