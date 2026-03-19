// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>

namespace Aspose::Slides::Foss {

class ICell;
class IParagraphCollection;
class IShape;
class ITextFrameFormat;

/// Represents a TextFrame.
class ITextFrame : public virtual ISlideComponent,
                   public virtual IPresentationComponent {
public:
    ~ITextFrame() override = default;

    /// Returns the list of all paragraphs in a frame. Read-only.
    [[nodiscard]] virtual IParagraphCollection& paragraphs() = 0;
    [[nodiscard]] virtual const IParagraphCollection& paragraphs() const = 0;

    /// Returns the plain text for a TextFrame. Read-only.
    [[nodiscard]] virtual std::string text() const = 0;

    /// Sets the plain text for a TextFrame.
    virtual void set_text(const std::string& value) = 0;

    /// Returns the formatting object for this TextFrame object. Read-only.
    [[nodiscard]] virtual ITextFrameFormat& text_frame_format() = 0;
    [[nodiscard]] virtual const ITextFrameFormat& text_frame_format() const = 0;

    /// Returns the parent shape, or nullptr if the parent does not implement IShape. Read-only.
    [[nodiscard]] virtual IShape* parent_shape() = 0;
    [[nodiscard]] virtual const IShape* parent_shape() const = 0;

    /// Returns the parent cell, or nullptr if the parent does not implement ICell. Read-only.
    [[nodiscard]] virtual ICell* parent_cell() = 0;
    [[nodiscard]] virtual const ICell* parent_cell() const = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;
    [[nodiscard]] virtual const ISlideComponent* as_i_slide_component() const = 0;

protected:
    ITextFrame() = default;
};

} // namespace Aspose::Slides::Foss
