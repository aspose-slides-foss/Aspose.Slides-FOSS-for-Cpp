// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/preset_shadow_type.h>

namespace Aspose::Slides::Foss {
class IColorFormat;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing a preset shadow effect.
class IPresetShadow {
public:
    virtual ~IPresetShadow() = default;

    /// Returns the shadow direction in degrees. Default 0.
    [[nodiscard]] virtual double direction() const = 0;
    /// Sets the shadow direction in degrees.
    virtual void set_direction(double value) = 0;

    /// Returns the shadow distance in points. Default 0.
    [[nodiscard]] virtual double distance() const = 0;
    /// Sets the shadow distance in points.
    virtual void set_distance(double value) = 0;

    /// Returns the shadow color format. Read-only.
    [[nodiscard]] virtual IColorFormat& shadow_color() = 0;
    /// Returns the shadow color format (const). Read-only.
    [[nodiscard]] virtual const IColorFormat& shadow_color() const = 0;

    /// Returns the preset shadow type. Default TOP_LEFT_DROP_SHADOW.
    [[nodiscard]] virtual PresetShadowType preset() const = 0;
    /// Sets the preset shadow type.
    virtual void set_preset(PresetShadowType value) = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
