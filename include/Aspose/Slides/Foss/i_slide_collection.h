// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Aspose::Slides::Foss {

class ILayoutSlide;
class IMasterSlide;
class ISlide;
class Slide;

/// Interface for a collection of slides.
class ISlideCollection {
public:
    virtual ~ISlideCollection() = default;

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] virtual ISlideCollection& as_i_collection() = 0;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] virtual ISlideCollection& as_i_enumerable() = 0;

    /// Returns the number of slides.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the slide at the given index.
    [[nodiscard]] virtual Slide& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const Slide& operator[](std::size_t index) const = 0;

    /// Adds a clone of the given slide to the end of the collection.
    virtual Slide& add_clone(const Slide& source_slide) = 0;

    /// Adds a clone of the given slide to the specified layout.
    virtual Slide& add_clone(const Slide& source_slide, ILayoutSlide* dest_layout) = 0;

    /// Adds a clone of the given slide to the specified master slide.
    virtual Slide& add_clone(const Slide& source_slide, IMasterSlide* dest_master,
                             bool allow_clone_missing_layout) = 0;

    /// Inserts a clone of the given slide at the specified index.
    virtual Slide& insert_clone(std::size_t index, const Slide& source_slide) = 0;

    /// Inserts a clone at the specified index with the given layout.
    virtual Slide& insert_clone(std::size_t index, const Slide& source_slide,
                                ILayoutSlide* dest_layout) = 0;

    /// Inserts a clone at the specified index with the given master slide.
    virtual Slide& insert_clone(std::size_t index, const Slide& source_slide,
                                IMasterSlide* dest_master,
                                bool allow_clone_missing_layout) = 0;

    /// Returns all slides as a vector of non-owning pointers.
    [[nodiscard]] virtual std::vector<Slide*> to_array() = 0;

    /// Returns slides in the specified range as non-owning pointers.
    [[nodiscard]] virtual std::vector<Slide*> to_array(std::size_t start_index,
                                                       std::size_t count) = 0;

    /// Adds an empty slide with the given layout to the end.
    virtual Slide& add_empty_slide(ILayoutSlide* layout) = 0;

    /// Inserts an empty slide with the given layout at the specified index.
    virtual Slide& insert_empty_slide(std::size_t index, ILayoutSlide* layout) = 0;

    /// Removes the given slide from the collection.
    virtual void remove(const Slide& slide) = 0;

    /// Removes the slide at the given index.
    virtual void remove_at(std::size_t index) = 0;

    /// Returns the zero-based index of a slide, or -1 if not found.
    [[nodiscard]] virtual std::ptrdiff_t index_of(const Slide& slide) const = 0;

protected:
    ISlideCollection() = default;
};

} // namespace Aspose::Slides::Foss
