// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>

#include <Aspose/Slides/Foss/color_type.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/i_fill_param_source.h>
#include <Aspose/Slides/Foss/preset_color.h>
#include <Aspose/Slides/Foss/scheme_color.h>

namespace Aspose::Slides::Foss {

/// Interface representing a color used in a presentation.
///
/// Provides access to different color representations (RGB, scheme, preset)
/// and individual R/G/B components in both integer (0-255) and float (0.0-1.0)
/// form.
class IColorFormat : public IFillParamSource {
public:
    ~IColorFormat() override = default;

    /// Returns the color definition method.
    [[nodiscard]] virtual ColorType color_type() const = 0;
    /// Sets the color definition method.
    virtual void set_color_type(ColorType value) = 0;

    /// Returns the resulting color (with all color transformations applied).
    [[nodiscard]] virtual Drawing::Color color() const = 0;
    /// Sets the RGB color and clears all color transformations.
    virtual void set_color(const Drawing::Color& value) = 0;

    /// Returns the color preset.
    [[nodiscard]] virtual PresetColor preset_color() const = 0;
    /// Sets the color preset.
    virtual void set_preset_color(PresetColor value) = 0;

    /// Returns the color identified by a color scheme.
    [[nodiscard]] virtual SchemeColor scheme_color() const = 0;
    /// Sets the color identified by a color scheme.
    virtual void set_scheme_color(SchemeColor value) = 0;

    /// Returns the red component of a color (0-255). Color transformations are ignored.
    [[nodiscard]] virtual uint8_t r() const = 0;
    /// Sets the red component of a color (0-255).
    virtual void set_r(uint8_t value) = 0;

    /// Returns the green component of a color (0-255). Color transformations are ignored.
    [[nodiscard]] virtual uint8_t g() const = 0;
    /// Sets the green component of a color (0-255).
    virtual void set_g(uint8_t value) = 0;

    /// Returns the blue component of a color (0-255). Color transformations are ignored.
    [[nodiscard]] virtual uint8_t b() const = 0;
    /// Sets the blue component of a color (0-255).
    virtual void set_b(uint8_t value) = 0;

    /// Returns the red component as a float (0.0-1.0). Color transformations are ignored.
    [[nodiscard]] virtual float float_r() const = 0;
    /// Sets the red component from a float (0.0-1.0).
    virtual void set_float_r(float value) = 0;

    /// Returns the green component as a float (0.0-1.0). Color transformations are ignored.
    [[nodiscard]] virtual float float_g() const = 0;
    /// Sets the green component from a float (0.0-1.0).
    virtual void set_float_g(float value) = 0;

    /// Returns the blue component as a float (0.0-1.0). Color transformations are ignored.
    [[nodiscard]] virtual float float_b() const = 0;
    /// Sets the blue component from a float (0.0-1.0).
    virtual void set_float_b(float value) = 0;
};

} // namespace Aspose::Slides::Foss
