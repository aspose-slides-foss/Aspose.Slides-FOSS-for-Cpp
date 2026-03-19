// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/gradient_direction.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/i_fill_param_source.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/tile_flip.h>

namespace Aspose::Slides::Foss {

class GradientStopCollection;

/// Represent a gradient format.
class IGradientFormat : public IFillParamSource {
public:
    ~IGradientFormat() override = default;

    /// Returns or sets the flipping mode for a gradient. Read/write.
    [[nodiscard]] virtual TileFlip tile_flip() const = 0;
    virtual void set_tile_flip(TileFlip value) = 0;

    /// Returns or sets the style of a gradient. Read/write.
    [[nodiscard]] virtual GradientDirection gradient_direction() const = 0;
    virtual void set_gradient_direction(GradientDirection value) = 0;

    /// Returns or sets the angle of a gradient. Read/write.
    [[nodiscard]] virtual float linear_gradient_angle() const = 0;
    virtual void set_linear_gradient_angle(float value) = 0;

    /// Determines whether a gradient is scaled. Read/write.
    [[nodiscard]] virtual NullableBool linear_gradient_scaled() const = 0;
    virtual void set_linear_gradient_scaled(NullableBool value) = 0;

    /// Returns or sets the shape of a gradient. Read/write.
    [[nodiscard]] virtual GradientShape gradient_shape() const = 0;
    virtual void set_gradient_shape(GradientShape value) = 0;

    /// Returns the collection of gradient stops. Read-only.
    [[nodiscard]] virtual GradientStopCollection& gradient_stops() = 0;
    [[nodiscard]] virtual const GradientStopCollection& gradient_stops() const = 0;
};

} // namespace Aspose::Slides::Foss
