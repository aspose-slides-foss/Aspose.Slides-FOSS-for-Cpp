// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_outer_shadow.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents an outer shadow effect applied to a shape.
class OuterShadow final : public IOuterShadow, public IImageTransformOperation {
public:
    OuterShadow() = default;
    ~OuterShadow() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:outerShdw>) with a persistence callback.
    /// @param element  The <a:outerShdw> XML node.
    /// @param save_callback  Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide  The owning slide (may be nullptr).
    void init_internal(pugi::xml_node element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Persist changes via the save callback provided at init time.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns the blur radius in points.
    [[nodiscard]] double blur_radius() const noexcept override;
    /// Sets the blur radius in points.
    void set_blur_radius(double value) noexcept override;

    /// Returns the shadow direction in degrees.
    [[nodiscard]] double direction() const noexcept override;
    /// Sets the shadow direction in degrees.
    void set_direction(double value) noexcept override;

    /// Returns the shadow distance in points.
    [[nodiscard]] double distance() const noexcept override;
    /// Sets the shadow distance in points.
    void set_distance(double value) noexcept override;

    /// Returns the shadow color format.
    [[nodiscard]] SimpleColorFormat& shadow_color() noexcept override { return shadow_color_; }
    /// Returns the shadow color format (const).
    [[nodiscard]] const SimpleColorFormat& shadow_color() const noexcept override { return shadow_color_; }

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

    /// Returns whether the shadow rotates with the shape.
    [[nodiscard]] bool rotate_shadow_with_shape() const noexcept override;
    /// Sets whether the shadow rotates with the shape.
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
    double blur_radius_ = 0.0;
    double distance_ = 0.0;
    double direction_ = 0.0;
    SimpleColorFormat shadow_color_;
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
