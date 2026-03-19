// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_glow.h>
#include <Aspose/Slides/Foss/effects/image_transform_operation.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents a glow effect, in which a color blurred outline
/// is added outside the edges of the object.
class Glow final : public ImageTransformOperation, public IGlow {
public:
    Glow() = default;
    ~Glow() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:glow>) with a persistence callback.
    /// @param element  The <a:glow> XML node.
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

    /// Returns the glow radius in points.
    [[nodiscard]] double radius() const noexcept override;
    /// Sets the glow radius in points.
    void set_radius(double value) noexcept override;

    /// Returns the glow color format.
    [[nodiscard]] SimpleColorFormat& color() noexcept override { return color_; }
    /// Returns the glow color format (const).
    [[nodiscard]] const SimpleColorFormat& color() const noexcept override { return color_; }

private:
    double radius_ = 0.0;
    SimpleColorFormat color_;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
