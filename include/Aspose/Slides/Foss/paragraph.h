// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_paragraph.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/portion_collection.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Represents a text paragraph within a text frame.
class Paragraph final : public IParagraph {
public:
    /// Constructs an empty paragraph.
    Paragraph();
    /// Constructs a paragraph with the given text.
    explicit Paragraph(std::string text);
    Paragraph(const Paragraph&) = delete;
    Paragraph& operator=(const Paragraph&) = delete;
    ~Paragraph() override;
    Paragraph(Paragraph&&) noexcept;
    Paragraph& operator=(Paragraph&&) noexcept;

    /// Returns the text content of the paragraph.
    [[nodiscard]] std::string text() const override;

    /// Sets the text content of the paragraph.
    void set_text(std::string value) override;

    /// Returns the paragraph format.
    [[nodiscard]] ParagraphFormat& paragraph_format() override;
    [[nodiscard]] const ParagraphFormat& paragraph_format() const override;

    /// Returns the collection of text portions.
    [[nodiscard]] PortionCollection& portions() override;
    [[nodiscard]] const PortionCollection& portions() const override;

    /// Returns this as ISlideComponent.
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

    /// Initialize this paragraph from XML elements within a slide part.
    /// @param p_element The `<a:p>` pugixml node.
    /// @param txbody_element The `<a:txBody>` pugixml node that contains this paragraph.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node p_element,
                       pugi::xml_node txbody_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Returns the backing `<a:p>` XML element, if any.
    [[nodiscard]] pugi::xml_node p_element() const;

    /// Returns the backing `<a:txBody>` XML element, if any.
    [[nodiscard]] pugi::xml_node txbody_element() const;

    /// Returns the owning SlidePart, or nullptr.
    [[nodiscard]] Internal::pptx::SlidePart* slide_part() const;

    /// Sets the parent slide for this paragraph.
    void set_slide(IBaseSlide* slide);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace Aspose::Slides::Foss
