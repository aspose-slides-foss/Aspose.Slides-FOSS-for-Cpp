// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_color_format.h>

#include <cmath>
#include <cstdint>

namespace Aspose::Slides::Foss {

/// Represents a color used in a presentation.
///
/// ColorFormat wraps different color representations (RGB, scheme, preset, etc.)
/// and provides uniform access to the underlying color value. It also supports
/// reading and writing individual R/G/B components and float-normalized variants.
///
/// Subclasses must implement color_type/set_color_type, color/set_color,
/// preset_color/set_preset_color, and scheme_color/set_scheme_color.
/// Default implementations of the R/G/B and float accessors delegate to color().
class ColorFormat : public IColorFormat {
public:
    ~ColorFormat() override = default;

    /// Returns the red component (0-255).
    [[nodiscard]] uint8_t r() const override { return color().r(); }
    /// Sets the red component (0-255).
    void set_r(uint8_t value) override {
        auto c = color();
        set_color(Drawing::Color(c.a(), value, c.g(), c.b()));
    }

    /// Returns the green component (0-255).
    [[nodiscard]] uint8_t g() const override { return color().g(); }
    /// Sets the green component (0-255).
    void set_g(uint8_t value) override {
        auto c = color();
        set_color(Drawing::Color(c.a(), c.r(), value, c.b()));
    }

    /// Returns the blue component (0-255).
    [[nodiscard]] uint8_t b() const override { return color().b(); }
    /// Sets the blue component (0-255).
    void set_b(uint8_t value) override {
        auto c = color();
        set_color(Drawing::Color(c.a(), c.r(), c.g(), value));
    }

    /// Returns the red component as a float (0.0-1.0).
    [[nodiscard]] float float_r() const override { return r() / 255.0f; }
    /// Sets the red component from a float (0.0-1.0).
    void set_float_r(float value) override {
        set_r(static_cast<uint8_t>(std::lround(value * 255)));
    }

    /// Returns the green component as a float (0.0-1.0).
    [[nodiscard]] float float_g() const override { return g() / 255.0f; }
    /// Sets the green component from a float (0.0-1.0).
    void set_float_g(float value) override {
        set_g(static_cast<uint8_t>(std::lround(value * 255)));
    }

    /// Returns the blue component as a float (0.0-1.0).
    [[nodiscard]] float float_b() const override { return b() / 255.0f; }
    /// Sets the blue component from a float (0.0-1.0).
    void set_float_b(float value) override {
        set_b(static_cast<uint8_t>(std::lround(value * 255)));
    }
};

} // namespace Aspose::Slides::Foss
