// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_slides_picture.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class IPPImage;
class IPresentation;
class Slide;

/// Represents a picture in a presentation.
class Picture final : public ISlidesPicture,
                public ISlideComponent {
public:
    /// Constructs a Picture associated with a parent slide.
    explicit Picture(Slide* parent_slide) noexcept;

    /// Internal initialization with the a:blip XML element.
    /// @param blip_element The a:blip element containing r:embed reference.
    /// @param slide_part The SlidePart for relationship resolution.
    /// @param parent_slide The parent Slide object.
    void init_internal(pugi::xml_node blip_element,
                       Internal::pptx::SlidePart* slide_part,
                       Slide* parent_slide);

    /// Returns the stored blip XML node.
    [[nodiscard]] pugi::xml_node blip_element() const noexcept { return blip_; }

    /// Returns the associated slide part, or nullptr.
    [[nodiscard]] Internal::pptx::SlidePart* slide_part() const noexcept { return slide_part_; }

    // -- ISlidesPicture --

    /// Returns the embedded image.
    [[nodiscard]] IPPImage* image() const noexcept override;

    /// Sets the embedded image.
    void set_image(IPPImage* value) override;

    /// Returns the linked image's URL.
    [[nodiscard]] const std::string& link_path_long() const noexcept override;

    /// Sets the linked image's URL.
    void set_link_path_long(std::string value) override;

    // -- IPresentationComponent --

    /// Returns the parent presentation.
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    // -- ISlideComponent --

    /// Returns the parent slide.
    [[nodiscard]] IBaseSlide* slide() override;
    [[nodiscard]] const IBaseSlide* slide() const override;

    /// Returns this as IPresentationComponent.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    /// Returns this as ISlideComponent.
    [[nodiscard]] ISlideComponent& as_i_slide_component() noexcept override;
    [[nodiscard]] const ISlideComponent& as_i_slide_component() const noexcept override;

private:
    Slide* parent_slide_;
    IPPImage* image_ = nullptr;
    std::string link_path_long_;
    pugi::xml_node blip_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
};

} // namespace Aspose::Slides::Foss
