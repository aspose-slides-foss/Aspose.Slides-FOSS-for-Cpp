// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_format.h>
#include <Aspose/Slides/Foss/i_line_fill_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/pattern_format.h>
#include <Aspose/Slides/Foss/simple_color_format.h>

namespace Aspose::Slides::Foss {

/// Represents the fill properties of a line.
class LineFillFormat final : public ILineFillFormat {
public:
    LineFillFormat() = default;
    ~LineFillFormat() override = default;

    /// Returns the fill type.
    [[nodiscard]] FillType fill_type() const noexcept override { return fill_type_; }
    void set_fill_type(FillType value) noexcept override { fill_type_ = value; }

    /// Returns the solid fill color.
    [[nodiscard]] SimpleColorFormat& solid_fill_color() noexcept override { return solid_fill_color_; }
    [[nodiscard]] const SimpleColorFormat& solid_fill_color() const noexcept override { return solid_fill_color_; }

    /// Returns the gradient fill format.
    [[nodiscard]] GradientFormat& gradient_format() noexcept override { return gradient_format_; }
    [[nodiscard]] const GradientFormat& gradient_format() const noexcept override { return gradient_format_; }

    /// Returns the pattern fill format.
    [[nodiscard]] PatternFormat& pattern_format() noexcept override { return pattern_format_; }
    [[nodiscard]] const PatternFormat& pattern_format() const noexcept override { return pattern_format_; }

    /// Determines whether the fill should be rotated with a shape.
    [[nodiscard]] NullableBool rotate_with_shape() const noexcept override { return rotate_with_shape_; }
    void set_rotate_with_shape(NullableBool value) noexcept override { rotate_with_shape_ = value; }

private:
    FillType fill_type_ = FillType::NOT_DEFINED;
    SimpleColorFormat solid_fill_color_;
    GradientFormat gradient_format_;
    PatternFormat pattern_format_;
    NullableBool rotate_with_shape_ = NullableBool::NOT_DEFINED;
};

} // namespace Aspose::Slides::Foss
