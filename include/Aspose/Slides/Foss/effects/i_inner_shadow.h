// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {
class IColorFormat;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing an inner shadow effect.
class IInnerShadow {
public:
    virtual ~IInnerShadow() = default;

    /// Returns the blur radius in points.
    [[nodiscard]] virtual double blur_radius() const = 0;
    /// Sets the blur radius in points.
    virtual void set_blur_radius(double value) = 0;

    /// Returns the shadow direction in degrees.
    [[nodiscard]] virtual double direction() const = 0;
    /// Sets the shadow direction in degrees.
    virtual void set_direction(double value) = 0;

    /// Returns the shadow distance in points.
    [[nodiscard]] virtual double distance() const = 0;
    /// Sets the shadow distance in points.
    virtual void set_distance(double value) = 0;

    /// Returns the shadow color format. Read-only.
    [[nodiscard]] virtual IColorFormat& shadow_color() = 0;
    /// Returns the shadow color format (const). Read-only.
    [[nodiscard]] virtual const IColorFormat& shadow_color() const = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
