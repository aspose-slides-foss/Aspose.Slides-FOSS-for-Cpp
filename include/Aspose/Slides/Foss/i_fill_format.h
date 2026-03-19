// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/i_fill_param_source.h>
#include <Aspose/Slides/Foss/nullable_bool.h>

namespace Aspose::Slides::Foss {

class IColorFormat;
class IGradientFormat;
class IPatternFormat;
class IPictureFillFormat;
class SimpleColorFormat;
class GradientFormat;
class PatternFormat;
class PictureFillFormat;

/// Represents fill formatting options.
///
/// Provides access to fill type, solid color, gradient, pattern, and picture
/// fill sub-formats, as well as the rotate-with-shape flag.
class IFillFormat : public IFillParamSource {
public:
    ~IFillFormat() override = default;

    /// Returns the type of filling.
    [[nodiscard]] virtual FillType fill_type() const = 0;
    /// Sets the type of filling.
    virtual void set_fill_type(FillType value) = 0;

    /// Returns the solid fill color format. Read-only.
    [[nodiscard]] virtual SimpleColorFormat& solid_fill_color() = 0;
    /// Returns the solid fill color format (const). Read-only.
    [[nodiscard]] virtual const SimpleColorFormat& solid_fill_color() const = 0;

    /// Returns the gradient fill format. Read-only.
    [[nodiscard]] virtual GradientFormat& gradient_format() = 0;
    /// Returns the gradient fill format (const). Read-only.
    [[nodiscard]] virtual const GradientFormat& gradient_format() const = 0;

    /// Returns the pattern fill format. Read-only.
    [[nodiscard]] virtual PatternFormat& pattern_format() = 0;
    /// Returns the pattern fill format (const). Read-only.
    [[nodiscard]] virtual const PatternFormat& pattern_format() const = 0;

    /// Returns the picture fill format. Read-only.
    [[nodiscard]] virtual PictureFillFormat& picture_fill_format() = 0;
    /// Returns the picture fill format (const). Read-only.
    [[nodiscard]] virtual const PictureFillFormat& picture_fill_format() const = 0;

    /// Determines whether the fill should be rotated with shape.
    [[nodiscard]] virtual NullableBool rotate_with_shape() const = 0;
    /// Sets whether the fill should be rotated with shape.
    virtual void set_rotate_with_shape(NullableBool value) = 0;
};

} // namespace Aspose::Slides::Foss
