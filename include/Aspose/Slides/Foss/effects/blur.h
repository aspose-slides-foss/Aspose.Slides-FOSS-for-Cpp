// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_blur.h>
#include <Aspose/Slides/Foss/effects/image_transform_operation.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents a blur effect applied to the entire shape, including its fill.
/// All color channels, including alpha, are affected.
class Blur final : public ImageTransformOperation, public IBlur {
public:
    Blur() = default;
    ~Blur() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:blur>) with a persistence callback.
    /// @param element  The <a:blur> XML node.
    /// @param save_callback  Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide  The owning slide (may be nullptr).
    void init_internal(pugi::xml_node element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Persist changes via the save callback provided at init time.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] IImageTransformOperation& as_i_image_transform_operation() noexcept override { return *this; }

    /// Returns the blur radius in points.
    [[nodiscard]] double radius() const noexcept override { return radius_; }
    /// Sets the blur radius in points.
    void set_radius(double value) noexcept override;

    /// Returns whether the blur grows beyond the shape boundary.
    [[nodiscard]] bool grow() const noexcept override { return grow_; }
    /// Sets whether the blur grows beyond the shape boundary.
    void set_grow(bool value) noexcept override;

private:
    double radius_ = 0.0;
    bool grow_ = true;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
