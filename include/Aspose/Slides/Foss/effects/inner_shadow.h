// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_inner_shadow.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents an inner shadow effect applied to a shape.
class InnerShadow final : public IInnerShadow, public IImageTransformOperation {
public:
    InnerShadow() = default;
    ~InnerShadow() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:innerShdw>) with a persistence callback.
    /// @param element  The <a:innerShdw> XML node.
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

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] IImageTransformOperation& as_i_image_transform_operation() noexcept override { return *this; }

private:
    double blur_radius_ = 0.0;
    double distance_ = 0.0;
    double direction_ = 0.0;
    SimpleColorFormat shadow_color_;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
