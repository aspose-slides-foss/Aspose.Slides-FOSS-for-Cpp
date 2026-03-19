// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/gradient_direction.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/gradient_stop_collection.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/tile_flip.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents gradient fill formatting.
class GradientFormat final {
public:
    GradientFormat() = default;
    virtual ~GradientFormat() = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed gradient format.
    /// @param grad_fill_element The \<a:gradFill\> XML element.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node grad_fill_element,
                       std::function<void()> save_callback);

    /// Save changes via the save callback.
    void save();

    /// Returns the gradient shape type. Read/write.
    [[nodiscard]] GradientShape gradient_shape() const noexcept { return gradient_shape_; }
    /// Sets the gradient shape type. Setting NOT_DEFINED is a no-op.
    void set_gradient_shape(GradientShape value) noexcept {
        if (value != GradientShape::NOT_DEFINED)
            gradient_shape_ = value;
    }

    /// Returns the gradient direction. Read/write.
    [[nodiscard]] GradientDirection gradient_direction() const noexcept { return gradient_direction_; }
    /// Sets the gradient direction. Setting NOT_DEFINED is a no-op.
    void set_gradient_direction(GradientDirection value) noexcept {
        if (value != GradientDirection::NOT_DEFINED)
            gradient_direction_ = value;
    }

    /// Returns the angle of the linear gradient in degrees. Read/write.
    [[nodiscard]] float linear_gradient_angle() const noexcept { return linear_angle_; }
    void set_linear_gradient_angle(float value) noexcept { linear_angle_ = value; }

    /// Returns whether the linear gradient is scaled. Read/write.
    [[nodiscard]] NullableBool linear_gradient_scaled() const noexcept { return linear_scaled_; }
    void set_linear_gradient_scaled(NullableBool value) noexcept { linear_scaled_ = value; }

    /// Returns the tile flip mode. Read/write.
    [[nodiscard]] TileFlip tile_flip() const noexcept { return tile_flip_; }
    void set_tile_flip(TileFlip value) noexcept { tile_flip_ = value; }

    /// Returns the collection of gradient stops. Read-only.
    [[nodiscard]] GradientStopCollection& gradient_stops() noexcept { return gradient_stops_; }
    [[nodiscard]] const GradientStopCollection& gradient_stops() const noexcept { return gradient_stops_; }

private:
    GradientShape gradient_shape_ = GradientShape::NOT_DEFINED;
    GradientDirection gradient_direction_ = GradientDirection::NOT_DEFINED;
    float linear_angle_ = 0.0f;
    NullableBool linear_scaled_ = NullableBool::NOT_DEFINED;
    TileFlip tile_flip_ = TileFlip::NOT_DEFINED;
    GradientStopCollection gradient_stops_;

    pugi::xml_node grad_fill_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
