// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/rectangle_alignment.h>

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing a reflection effect.
class IReflection {
public:
    virtual ~IReflection() = default;

    /// Returns the start position along the alpha gradient ramp (percents). Default 0.
    [[nodiscard]] virtual double start_pos_alpha() const = 0;
    /// Sets the start position along the alpha gradient ramp (percents).
    virtual void set_start_pos_alpha(double value) = 0;

    /// Returns the end position along the alpha gradient ramp (percents). Default 0.
    [[nodiscard]] virtual double end_pos_alpha() const = 0;
    /// Sets the end position along the alpha gradient ramp (percents).
    virtual void set_end_pos_alpha(double value) = 0;

    /// Returns the fade direction angle in degrees. Default 0.
    [[nodiscard]] virtual double fade_direction() const = 0;
    /// Sets the fade direction angle in degrees.
    virtual void set_fade_direction(double value) = 0;

    /// Returns the starting reflection opacity (percents). Default 0.
    [[nodiscard]] virtual double start_reflection_opacity() const = 0;
    /// Sets the starting reflection opacity (percents).
    virtual void set_start_reflection_opacity(double value) = 0;

    /// Returns the ending reflection opacity (percents). Default 0.
    [[nodiscard]] virtual double end_reflection_opacity() const = 0;
    /// Sets the ending reflection opacity (percents).
    virtual void set_end_reflection_opacity(double value) = 0;

    /// Returns the blur radius in points. Default 0.
    [[nodiscard]] virtual double blur_radius() const = 0;
    /// Sets the blur radius in points.
    virtual void set_blur_radius(double value) = 0;

    /// Returns the direction of reflection in degrees. Default 0.
    [[nodiscard]] virtual double direction() const = 0;
    /// Sets the direction of reflection in degrees.
    virtual void set_direction(double value) = 0;

    /// Returns the distance of reflection in points. Default 0.
    [[nodiscard]] virtual double distance() const = 0;
    /// Sets the distance of reflection in points.
    virtual void set_distance(double value) = 0;

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

    /// Returns whether the reflection rotates with the shape. Default true.
    [[nodiscard]] virtual bool rotate_shadow_with_shape() const = 0;
    /// Sets whether the reflection rotates with the shape.
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
