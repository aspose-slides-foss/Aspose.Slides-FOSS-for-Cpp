// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/color_format.h>

namespace Aspose::Slides::Foss {

/// A simple concrete implementation of ColorFormat backed by an sRGB color.
class SimpleColorFormat final : public ColorFormat {
public:
    [[nodiscard]] ColorType color_type() const override { return color_type_; }
    void set_color_type(ColorType value) override { color_type_ = value; }

    [[nodiscard]] Drawing::Color color() const override { return color_; }
    void set_color(const Drawing::Color& value) override {
        color_ = value;
        color_type_ = ColorType::RGB;
    }

    [[nodiscard]] PresetColor preset_color() const override { return preset_color_; }
    void set_preset_color(PresetColor value) override { preset_color_ = value; }

    [[nodiscard]] SchemeColor scheme_color() const override { return scheme_color_; }
    void set_scheme_color(SchemeColor value) override { scheme_color_ = value; }

private:
    ColorType color_type_ = ColorType::NOT_DEFINED;
    Drawing::Color color_;
    PresetColor preset_color_ = PresetColor::NOT_DEFINED;
    SchemeColor scheme_color_ = SchemeColor::NOT_DEFINED;
};

} // namespace Aspose::Slides::Foss
