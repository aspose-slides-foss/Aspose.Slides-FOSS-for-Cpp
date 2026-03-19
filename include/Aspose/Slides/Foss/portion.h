// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_portion.h>
#include <Aspose/Slides/Foss/portion_format.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Represents a text portion (run) within a paragraph.
class Portion final : public IPortion {
public:
    /// Constructs an empty portion.
    Portion();
    /// Constructs a portion with the given text.
    explicit Portion(std::string text);
    Portion(const Portion&) = delete;
    Portion& operator=(const Portion&) = delete;
    ~Portion() override;
    Portion(Portion&&) noexcept;
    Portion& operator=(Portion&&) noexcept;

    /// Returns the text content of the portion.
    [[nodiscard]] const std::string& text() const override;

    /// Sets the text content of the portion.
    void set_text(std::string value) override;

    /// Returns the portion format.
    [[nodiscard]] PortionFormat& portion_format() override;
    [[nodiscard]] const PortionFormat& portion_format() const override;

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

    /// Initialize this portion from XML elements within a slide part.
    /// @param r_element The `<a:r>` pugixml node (the run element).
    /// @param p_element The `<a:p>` pugixml node containing this run.
    /// @param txbody_element The `<a:txBody>` pugixml node that contains the paragraph.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node r_element,
                       pugi::xml_node p_element,
                       pugi::xml_node txbody_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Returns the backing `<a:r>` XML element, if any.
    [[nodiscard]] pugi::xml_node r_element() const;

    /// Returns the backing `<a:p>` XML element, if any.
    [[nodiscard]] pugi::xml_node p_element() const;

    /// Returns the backing `<a:txBody>` XML element, if any.
    [[nodiscard]] pugi::xml_node txbody_element() const;

    /// Returns the owning SlidePart, or nullptr.
    [[nodiscard]] Internal::pptx::SlidePart* slide_part() const;

    /// Sets the parent slide for this portion.
    void set_slide(IBaseSlide* slide);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace Aspose::Slides::Foss
