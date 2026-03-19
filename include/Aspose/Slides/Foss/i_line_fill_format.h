// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/i_fill_param_source.h>
#include <Aspose/Slides/Foss/nullable_bool.h>

namespace Aspose::Slides::Foss {

class SimpleColorFormat;
class GradientFormat;
class PatternFormat;

/// Represents properties for lines filling.
class ILineFillFormat : public IFillParamSource {
public:
    ~ILineFillFormat() override = default;

    /// Returns the fill type. Read/write.
    [[nodiscard]] virtual FillType fill_type() const = 0;
    /// Sets the fill type.
    virtual void set_fill_type(FillType value) = 0;

    /// Returns the color of a solid fill. Read-only.
    [[nodiscard]] virtual SimpleColorFormat& solid_fill_color() = 0;
    /// Returns the color of a solid fill (const). Read-only.
    [[nodiscard]] virtual const SimpleColorFormat& solid_fill_color() const = 0;

    /// Returns the gradient fill format. Read-only.
    [[nodiscard]] virtual GradientFormat& gradient_format() = 0;
    /// Returns the gradient fill format (const). Read-only.
    [[nodiscard]] virtual const GradientFormat& gradient_format() const = 0;

    /// Returns the pattern fill format. Read-only.
    [[nodiscard]] virtual PatternFormat& pattern_format() = 0;
    /// Returns the pattern fill format (const). Read-only.
    [[nodiscard]] virtual const PatternFormat& pattern_format() const = 0;

    /// Determines whether the fill should be rotated with a shape. Read/write.
    [[nodiscard]] virtual NullableBool rotate_with_shape() const = 0;
    /// Sets whether the fill should be rotated with a shape.
    virtual void set_rotate_with_shape(NullableBool value) = 0;

protected:
    ILineFillFormat() = default;
};

} // namespace Aspose::Slides::Foss
