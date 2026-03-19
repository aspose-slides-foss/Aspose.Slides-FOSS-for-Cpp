// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <array>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>

namespace Aspose::Slides::Foss {

/// Interface for light rig properties.
class ILightRig {
public:
    virtual ~ILightRig() = default;

    /// Returns the light rig preset type. Read/write.
    [[nodiscard]] virtual LightRigPresetType light_type() const = 0;
    /// Sets the light rig preset type.
    virtual void set_light_type(LightRigPresetType value) = 0;

    /// Returns the lighting direction. Read/write.
    [[nodiscard]] virtual LightingDirection direction() const = 0;
    /// Sets the lighting direction.
    virtual void set_direction(LightingDirection value) = 0;

    /// Sets the rotation angles (latitude, longitude, revolution) in degrees.
    virtual void set_rotation(float latitude, float longitude, float revolution) = 0;

    /// Returns the rotation as {latitude, longitude, revolution} in degrees.
    [[nodiscard]] virtual std::array<float, 3> get_rotation() const = 0;

protected:
    ILightRig() = default;
};

} // namespace Aspose::Slides::Foss
