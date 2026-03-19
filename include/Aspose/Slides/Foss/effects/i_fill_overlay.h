// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/fill_blend_mode.h>

namespace Aspose::Slides::Foss {
class IFillFormat;
class IBaseSlide;
class IPresentationComponent;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface for a fill overlay image transform operation.
class IFillOverlay {
public:
    virtual ~IFillOverlay() = default;

    /// Returns the fill blend mode.
    [[nodiscard]] virtual FillBlendMode blend() const = 0;
    /// Sets the fill blend mode.
    virtual void set_blend(FillBlendMode value) = 0;

    /// Returns the fill format. Read-only.
    [[nodiscard]] virtual IFillFormat& fill_format() = 0;
    /// Returns the fill format (const). Read-only.
    [[nodiscard]] virtual const IFillFormat& fill_format() const = 0;

    /// Returns the parent slide, or nullptr if not set.
    [[nodiscard]] virtual IBaseSlide* slide() = 0;
    [[nodiscard]] virtual const IBaseSlide* slide() const = 0;

    /// Returns this object as IPresentationComponent, or nullptr.
    [[nodiscard]] virtual IPresentationComponent* as_i_presentation_component() = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
