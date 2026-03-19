// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <vector>

#include <Aspose/Slides/Foss/slide_layout_type.h>

namespace Aspose::Slides::Foss {

class ILayoutSlide;

/// Interface for a collection of layout slides.
class ILayoutSlideCollection {
public:
    virtual ~ILayoutSlideCollection() = default;

    /// Returns the number of layout slides.
    [[nodiscard]] virtual std::size_t size() const noexcept = 0;

    /// Returns the layout slide at the given index.
    [[nodiscard]] virtual ILayoutSlide& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const ILayoutSlide& operator[](std::size_t index) const = 0;

    /// Returns a non-owning snapshot of all layout slides as a vector.
    [[nodiscard]] virtual std::vector<ILayoutSlide*> as_i_collection() = 0;

    /// Returns a non-owning snapshot of all layout slides (const) as a vector.
    [[nodiscard]] virtual std::vector<const ILayoutSlide*> as_i_enumerable() const = 0;

    /// Finds the first layout slide matching the given type, or nullptr if none.
    [[nodiscard]] virtual ILayoutSlide* get_by_type(SlideLayoutType type) = 0;

protected:
    ILayoutSlideCollection() = default;
};

} // namespace Aspose::Slides::Foss
