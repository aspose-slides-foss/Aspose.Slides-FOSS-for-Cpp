// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/i_gradient_stop.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents a gradient stop within a gradient fill.
///
/// A gradient stop defines a color at a specific position (0.0 to 1.0)
/// within a gradient fill.
class GradientStop final : public IGradientStop {
public:
    GradientStop() = default;
    explicit GradientStop(float position) : position_(position) {}
    GradientStop(float position, const Drawing::Color& color)
        : position_(position) {
        color_.set_color(color);
    }

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML \<a:gs\> element.
    /// @param gs_element The \<a:gs\> XML element for this gradient stop.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node gs_element,
                       std::function<void()> save_callback);

    /// Persist changes via the save callback.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns the position of the gradient stop (0.0 to 1.0).
    [[nodiscard]] float position() const noexcept override { return position_; }

    /// Sets the position of the gradient stop (0.0 to 1.0).
    void set_position(float value) noexcept override { position_ = value; }

    /// Returns the color format for this gradient stop.
    [[nodiscard]] SimpleColorFormat& color() noexcept override { return color_; }

    /// Returns the color format for this gradient stop (const).
    [[nodiscard]] const SimpleColorFormat& color() const noexcept override { return color_; }

private:
    float position_ = 0.0f;
    SimpleColorFormat color_;
    pugi::xml_node gs_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
