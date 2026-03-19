// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/rectangle_alignment.h>

namespace Aspose::Slides::Foss {
class IColorFormat;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing an outer shadow effect.
class IOuterShadow {
public:
    virtual ~IOuterShadow() = default;

    /// Returns the blur radius in points. Default 0.
    [[nodiscard]] virtual double blur_radius() const = 0;
    /// Sets the blur radius in points.
    virtual void set_blur_radius(double value) = 0;

    /// Returns the shadow direction in degrees. Default 0.
    [[nodiscard]] virtual double direction() const = 0;
    /// Sets the shadow direction in degrees.
    virtual void set_direction(double value) = 0;

    /// Returns the shadow distance in points. Default 0.
    [[nodiscard]] virtual double distance() const = 0;
    /// Sets the shadow distance in points.
    virtual void set_distance(double value) = 0;

    /// Returns the shadow color format. Read-only.
    [[nodiscard]] virtual IColorFormat& shadow_color() = 0;
    /// Returns the shadow color format (const). Read-only.
    [[nodiscard]] virtual const IColorFormat& shadow_color() const = 0;

    /// Returns the rectangle alignment. Default NOT_DEFINED.
    [[nodiscard]] virtual RectangleAlignment rectangle_align() const = 0;
    /// Sets the rectangle alignment.
    virtual void set_rectangle_align(RectangleAlignment value) = 0;

    /// Returns the horizontal skew angle in degrees. Default 0.
    [[nodiscard]] virtual double skew_horizontal() const = 0;
    /// Sets the horizontal skew angle in degrees.
    virtual void set_skew_horizontal(double value) = 0;

    /// Returns the vertical skew angle in degrees. Default 0.
    [[nodiscard]] virtual double skew_vertical() const = 0;
    /// Sets the vertical skew angle in degrees.
    virtual void set_skew_vertical(double value) = 0;

    /// Returns whether the shadow rotates with the shape. Default true.
    [[nodiscard]] virtual bool rotate_shadow_with_shape() const = 0;
    /// Sets whether the shadow rotates with the shape.
    virtual void set_rotate_shadow_with_shape(bool value) = 0;

    /// Returns the horizontal scaling factor in percent. Default 100.
    [[nodiscard]] virtual double scale_horizontal() const = 0;
    /// Sets the horizontal scaling factor in percent.
    virtual void set_scale_horizontal(double value) = 0;

    /// Returns the vertical scaling factor in percent. Default 100.
    [[nodiscard]] virtual double scale_vertical() const = 0;
    /// Sets the vertical scaling factor in percent.
    virtual void set_scale_vertical(double value) = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
