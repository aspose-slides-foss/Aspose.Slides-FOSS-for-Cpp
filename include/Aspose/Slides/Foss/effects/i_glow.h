// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {
class IColorFormat;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing a glow effect, in which a color blurred outline
/// is added outside the edges of the object.
class IGlow {
public:
    virtual ~IGlow() = default;

    /// Returns the glow radius in points. Default 0.
    [[nodiscard]] virtual double radius() const = 0;
    /// Sets the glow radius in points.
    virtual void set_radius(double value) = 0;

    /// Returns the glow color format. Read-only.
    [[nodiscard]] virtual IColorFormat& color() = 0;
    /// Returns the glow color format (const). Read-only.
    [[nodiscard]] virtual const IColorFormat& color() const = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
