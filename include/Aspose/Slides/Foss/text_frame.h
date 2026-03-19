// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_text_frame.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/text_frame_format.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class IBaseSlide;
class ICell;
class IPresentation;
class IShape;

/// Represents a TextFrame containing paragraphs of text.
class TextFrame final : public ITextFrame {
public:
    TextFrame();
    TextFrame(const TextFrame&) = delete;
    TextFrame& operator=(const TextFrame&) = delete;
    ~TextFrame() override;
    TextFrame(TextFrame&&) noexcept;
    TextFrame& operator=(TextFrame&&) noexcept;

    /// Returns the list of all paragraphs in a frame. Read-only.
    [[nodiscard]] IParagraphCollection& paragraphs() override;
    [[nodiscard]] const IParagraphCollection& paragraphs() const override;

    /// Returns the plain text for a TextFrame (paragraphs joined by newlines).
    [[nodiscard]] std::string text() const override;

    /// Sets the plain text, splitting on line breaks into separate paragraphs.
    void set_text(const std::string& value) override;

    /// Returns the formatting object for this TextFrame. Read-only.
    [[nodiscard]] ITextFrameFormat& text_frame_format() override;
    [[nodiscard]] const ITextFrameFormat& text_frame_format() const override;

    /// Returns the parent shape, or nullptr. Read-only.
    [[nodiscard]] IShape* parent_shape() override;
    [[nodiscard]] const IShape* parent_shape() const override;

    /// Returns the parent cell, or nullptr. Read-only.
    [[nodiscard]] ICell* parent_cell() override;
    [[nodiscard]] const ICell* parent_cell() const override;

    /// Returns this as ISlideComponent. Read-only.
    [[nodiscard]] ISlideComponent* as_i_slide_component() override;
    [[nodiscard]] const ISlideComponent* as_i_slide_component() const override;

    // -- ISlideComponent --
    [[nodiscard]] IBaseSlide* slide() override;
    [[nodiscard]] const IBaseSlide* slide() const override;
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    // -- IPresentationComponent --
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    /// Sets the parent slide for this text frame.
    void set_slide(IBaseSlide* slide);

    /// Sets the parent shape for this text frame.
    void set_parent_shape(IShape* shape);

    /// Sets the parent cell for this text frame.
    void set_parent_cell(ICell* cell);

    /// Initializes internal XML-backed state for this text frame.
    /// @param txbody_element The txBody XML element backing this frame.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    /// @param parent_shape The parent shape object. May be nullptr.
    void init_internal(pugi::xml_node txbody_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide,
                       IShape* parent_shape = nullptr);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace Aspose::Slides::Foss
