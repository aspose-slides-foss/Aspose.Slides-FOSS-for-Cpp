// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <array>
#include <Aspose/Slides/Foss/camera_preset_type.h>

namespace Aspose::Slides::Foss {

/// Interface representing camera properties for 3D scene rendering.
class ICamera {
public:
    virtual ~ICamera() = default;

    /// Returns the camera preset type. Read/write.
    [[nodiscard]] virtual CameraPresetType camera_type() const = 0;
    /// Sets the camera preset type.
    virtual void set_camera_type(CameraPresetType value) = 0;

    /// Returns the field of view angle in degrees (0-180). Read/write.
    [[nodiscard]] virtual float field_of_view_angle() const = 0;
    /// Sets the field of view angle in degrees.
    virtual void set_field_of_view_angle(float value) = 0;

    /// Returns the zoom factor as a percentage. Read/write.
    [[nodiscard]] virtual float zoom() const = 0;
    /// Sets the zoom factor as a percentage.
    virtual void set_zoom(float value) = 0;

    /// Sets the rotation angles (latitude, longitude, revolution) in degrees.
    virtual void set_rotation(float latitude, float longitude, float revolution) = 0;

    /// Returns the rotation as {latitude, longitude, revolution} in degrees.
    [[nodiscard]] virtual std::array<float, 3> get_rotation() const = 0;

protected:
    ICamera() = default;
    ICamera(const ICamera&) = default;
    ICamera& operator=(const ICamera&) = default;
};

} // namespace Aspose::Slides::Foss
