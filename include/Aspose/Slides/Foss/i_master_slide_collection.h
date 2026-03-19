// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>

namespace Aspose::Slides::Foss {

class IMasterSlide;
class MasterSlide;

/// Interface for a collection of master slides.
class IMasterSlideCollection {
public:
    virtual ~IMasterSlideCollection() = default;

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] virtual IMasterSlideCollection& as_i_collection() = 0;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] virtual IMasterSlideCollection& as_i_enumerable() = 0;

    /// Returns the number of master slides.
    [[nodiscard]] virtual std::size_t size() const noexcept = 0;

    /// Returns the master slide at the given index.
    [[nodiscard]] virtual MasterSlide& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const MasterSlide& operator[](std::size_t index) const = 0;

    /// Adds a clone of the given source master slide to the collection.
    virtual MasterSlide& add_clone(const IMasterSlide& source_master) = 0;

protected:
    IMasterSlideCollection() = default;
};

} // namespace Aspose::Slides::Foss
