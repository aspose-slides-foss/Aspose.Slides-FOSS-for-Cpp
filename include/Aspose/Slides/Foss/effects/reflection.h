// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_reflection.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents a reflection effect applied to a shape.
class Reflection final : public IReflection, public IImageTransformOperation {
public:
    Reflection() = default;
    ~Reflection() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:reflection>) with a persistence callback.
    /// @param element  The <a:reflection> XML node.
    /// @param save_callback  Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide  The owning slide (may be nullptr).
    void init_internal(pugi::xml_node element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Persist changes via the save callback provided at init time.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns the start position along the alpha gradient ramp (percents).
    [[nodiscard]] double start_pos_alpha() const noexcept override;
    /// Sets the start position along the alpha gradient ramp (percents).
    void set_start_pos_alpha(double value) noexcept override;

    /// Returns the end position along the alpha gradient ramp (percents).
    [[nodiscard]] double end_pos_alpha() const noexcept override;
    /// Sets the end position along the alpha gradient ramp (percents).
    void set_end_pos_alpha(double value) noexcept override;

    /// Returns the fade direction angle in degrees.
    [[nodiscard]] double fade_direction() const noexcept override;
    /// Sets the fade direction angle in degrees.
    void set_fade_direction(double value) noexcept override;

    /// Returns the starting reflection opacity (percents).
    [[nodiscard]] double start_reflection_opacity() const noexcept override;
    /// Sets the starting reflection opacity (percents).
    void set_start_reflection_opacity(double value) noexcept override;

    /// Returns the ending reflection opacity (percents).
    [[nodiscard]] double end_reflection_opacity() const noexcept override;
    /// Sets the ending reflection opacity (percents).
    void set_end_reflection_opacity(double value) noexcept override;

    /// Returns the blur radius in points.
    [[nodiscard]] double blur_radius() const noexcept override;
    /// Sets the blur radius in points.
    void set_blur_radius(double value) noexcept override;

    /// Returns the direction of reflection in degrees.
    [[nodiscard]] double direction() const noexcept override;
    /// Sets the direction of reflection in degrees.
    void set_direction(double value) noexcept override;

    /// Returns the distance of reflection in points.
    [[nodiscard]] double distance() const noexcept override;
    /// Sets the distance of reflection in points.
    void set_distance(double value) noexcept override;

    /// Returns the rectangle alignment.
    [[nodiscard]] RectangleAlignment rectangle_align() const noexcept override;
    /// Sets the rectangle alignment.
    void set_rectangle_align(RectangleAlignment value) noexcept override;

    /// Returns the horizontal skew angle in degrees.
    [[nodiscard]] double skew_horizontal() const noexcept override;
    /// Sets the horizontal skew angle in degrees.
    void set_skew_horizontal(double value) noexcept override;

    /// Returns the vertical skew angle in degrees.
    [[nodiscard]] double skew_vertical() const noexcept override;
    /// Sets the vertical skew angle in degrees.
    void set_skew_vertical(double value) noexcept override;

    /// Returns whether the reflection rotates with the shape.
    [[nodiscard]] bool rotate_shadow_with_shape() const noexcept override;
    /// Sets whether the reflection rotates with the shape.
    void set_rotate_shadow_with_shape(bool value) noexcept override;

    /// Returns the horizontal scaling factor in percent.
    [[nodiscard]] double scale_horizontal() const noexcept override;
    /// Sets the horizontal scaling factor in percent.
    void set_scale_horizontal(double value) noexcept override;

    /// Returns the vertical scaling factor in percent.
    [[nodiscard]] double scale_vertical() const noexcept override;
    /// Sets the vertical scaling factor in percent.
    void set_scale_vertical(double value) noexcept override;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] IImageTransformOperation& as_i_image_transform_operation() noexcept override { return *this; }

private:
    double start_pos_alpha_ = 0.0;
    double end_pos_alpha_ = 0.0;
    double fade_direction_ = 0.0;
    double start_reflection_opacity_ = 0.0;
    double end_reflection_opacity_ = 0.0;
    double blur_radius_ = 0.0;
    double direction_ = 0.0;
    double distance_ = 0.0;
    RectangleAlignment rectangle_align_ = RectangleAlignment::NOT_DEFINED;
    double skew_horizontal_ = 0.0;
    double skew_vertical_ = 0.0;
    bool rotate_shadow_with_shape_ = true;
    double scale_horizontal_ = 100.0;
    double scale_vertical_ = 100.0;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
