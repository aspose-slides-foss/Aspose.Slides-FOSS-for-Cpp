// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <optional>

#include <Aspose/Slides/Foss/i_slide_component.h>

namespace Aspose::Slides::Foss {

class Paragraph;

/// Interface for a collection of paragraphs.
class IParagraphCollection : public virtual ISlideComponent {
public:
    ~IParagraphCollection() override = default;

    /// Returns the number of paragraphs.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the paragraph at the given index.
    [[nodiscard]] virtual Paragraph& operator[](std::size_t index) = 0;

    /// Returns the paragraph at the given index (const).
    [[nodiscard]] virtual const Paragraph& operator[](std::size_t index) const = 0;

    /// Adds a paragraph to the end of the collection.
    virtual Paragraph& add(Paragraph paragraph) = 0;

    /// Inserts a paragraph at the given index.
    virtual Paragraph& insert(std::size_t index, Paragraph paragraph) = 0;

    /// Removes the paragraph at the given index.
    virtual void remove_at(std::size_t index) = 0;

    /// Removes the given paragraph from the collection.
    /// @return true if the paragraph was found and removed.
    virtual bool remove(const Paragraph& item) = 0;

    /// Removes all paragraphs.
    virtual void clear() = 0;

    /// Returns whether the collection is read-only.
    [[nodiscard]] virtual bool is_read_only() const noexcept = 0;

    /// Returns the index of the given paragraph, or std::nullopt if not found.
    [[nodiscard]] virtual std::optional<std::size_t> index_of(const Paragraph& item) const = 0;

    /// Returns whether the collection contains the given paragraph.
    [[nodiscard]] virtual bool contains(const Paragraph& item) const = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;
    [[nodiscard]] virtual const ISlideComponent* as_i_slide_component() const = 0;

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] virtual IParagraphCollection& as_i_enumerable() = 0;
    [[nodiscard]] virtual const IParagraphCollection& as_i_enumerable() const = 0;

protected:
    IParagraphCollection() = default;
};

} // namespace Aspose::Slides::Foss
