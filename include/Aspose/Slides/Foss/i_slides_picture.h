// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

namespace Aspose::Slides::Foss {

class IPPImage;
class IBaseSlide;
class IPresentation;
class ISlideComponent;

/// Interface for a picture in a presentation.
class ISlidesPicture {
public:
    virtual ~ISlidesPicture() = default;

    /// Returns the embedded image. Read-only.
    [[nodiscard]] virtual IPPImage* image() const noexcept = 0;

    /// Sets the embedded image.
    virtual void set_image(IPPImage* value) = 0;

    /// Returns the linked image's URL. Read-only.
    [[nodiscard]] virtual const std::string& link_path_long() const noexcept = 0;

    /// Sets the linked image's URL.
    virtual void set_link_path_long(std::string value) = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent& as_i_slide_component() noexcept = 0;
    [[nodiscard]] virtual const ISlideComponent& as_i_slide_component() const noexcept = 0;

protected:
    ISlidesPicture() = default;
};

} // namespace Aspose::Slides::Foss
