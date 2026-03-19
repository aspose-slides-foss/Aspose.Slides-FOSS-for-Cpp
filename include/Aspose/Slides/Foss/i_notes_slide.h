// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IBaseSlide;
class INotesSlideHeaderFooterManager;
class ISlide;
class ITextFrame;
class ShapeCollection;
class TextFrame;

/// Interface for a notes slide in a presentation.
class INotesSlide {
public:
    virtual ~INotesSlide() = default;

    /// Returns the collection of shapes on the notes slide.
    [[nodiscard]] virtual ShapeCollection& shapes() = 0;
    [[nodiscard]] virtual const ShapeCollection& shapes() const = 0;

    /// Returns the HeaderFooter manager of the notes slide. Read-only.
    [[nodiscard]] virtual INotesSlideHeaderFooterManager& header_footer_manager() = 0;
    [[nodiscard]] virtual const INotesSlideHeaderFooterManager& header_footer_manager() const = 0;

    /// Returns the TextFrame with notes text. Read-only.
    [[nodiscard]] virtual TextFrame& notes_text_frame() = 0;
    [[nodiscard]] virtual const TextFrame& notes_text_frame() const = 0;

    /// Returns the parent slide. Read-only.
    [[nodiscard]] virtual ISlide* parent_slide() = 0;
    [[nodiscard]] virtual const ISlide* parent_slide() const = 0;

    /// Returns this as IBaseSlide. Read-only.
    [[nodiscard]] virtual IBaseSlide& as_i_base_slide() = 0;
    [[nodiscard]] virtual const IBaseSlide& as_i_base_slide() const = 0;

protected:
    INotesSlide() = default;
};

} // namespace Aspose::Slides::Foss
