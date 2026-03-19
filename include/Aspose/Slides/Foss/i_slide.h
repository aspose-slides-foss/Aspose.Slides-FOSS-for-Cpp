// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <vector>

namespace Aspose::Slides::Foss {

class Comment;
class CommentAuthor;
class ILayoutSlide;
class INotesSlideManager;
class ShapeCollection;

/// Interface for a slide in a presentation.
class ISlide {
public:
    virtual ~ISlide() = default;

    /// Returns the collection of shapes on this slide.
    [[nodiscard]] virtual ShapeCollection& shapes() = 0;
    [[nodiscard]] virtual const ShapeCollection& shapes() const = 0;

    /// Returns the number of the slide. Read/write.
    [[nodiscard]] virtual int slide_number() const = 0;
    /// Sets the number of the slide.
    virtual void set_slide_number(int value) = 0;

    /// Determines whether the specified slide is hidden during a slide show. Read/write.
    [[nodiscard]] virtual bool hidden() const = 0;
    /// Sets whether the slide is hidden.
    virtual void set_hidden(bool value) = 0;

    /// Returns the layout slide for the current slide. Read/write.
    [[nodiscard]] virtual ILayoutSlide* layout_slide() const = 0;
    /// Sets the layout slide for the current slide.
    virtual void set_layout_slide(ILayoutSlide* value) = 0;

    /// Returns the notes slide manager. Read-only.
    [[nodiscard]] virtual INotesSlideManager& notes_slide_manager() = 0;
    [[nodiscard]] virtual const INotesSlideManager& notes_slide_manager() const = 0;

    /// Returns comments on this slide, optionally filtered by author.
    /// If author is nullptr, returns all comments on this slide.
    [[nodiscard]] virtual std::vector<Comment*> get_slide_comments(
        CommentAuthor* author) const = 0;

    /// Removes this slide from the presentation.
    virtual void remove() = 0;

protected:
    ISlide() = default;
};

} // namespace Aspose::Slides::Foss
