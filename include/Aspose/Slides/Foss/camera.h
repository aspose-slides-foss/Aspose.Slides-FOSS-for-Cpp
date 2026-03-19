// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <array>
#include <functional>

#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents camera properties for 3D scene rendering.
class Camera final {
public:
    Camera() = default;
    virtual ~Camera() = default;

    /// Initialize XML-backed camera.
    /// @param scene3d_element The <a:scene3d> XML element that contains the camera.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node scene3d_element,
                       std::function<void()> save_callback);

    /// Get the <a:camera> element if it exists within the scene3d element.
    [[nodiscard]] pugi::xml_node get_camera() const;

    /// Get or create the <a:camera> element with default preset "orthographicFront".
    pugi::xml_node ensure_camera();

    /// Save changes via the save callback.
    void save();

    /// Returns true if this camera has been initialized with a parent XML element.
    [[nodiscard]] bool has_parent() const noexcept { return static_cast<bool>(scene3d_element_); }

    /// Returns the camera preset type.
    [[nodiscard]] CameraPresetType camera_type() const noexcept { return camera_type_; }
    /// Sets the camera preset type.
    void set_camera_type(CameraPresetType value) noexcept;

    /// Returns the field of view angle in degrees (0-180).
    [[nodiscard]] float field_of_view_angle() const noexcept { return fov_; }
    /// Sets the field of view angle in degrees.
    void set_field_of_view_angle(float value) noexcept { fov_ = value; }

    /// Returns the zoom factor as a percentage (default 100).
    [[nodiscard]] float zoom() const noexcept { return zoom_; }
    /// Sets the zoom factor as a percentage.
    void set_zoom(float value) noexcept { zoom_ = value; }

    /// Sets the rotation angles (latitude, longitude, revolution) in degrees.
    void set_rotation(float lat, float lon, float rev) noexcept {
        lat_ = lat;
        lon_ = lon;
        rev_ = rev;
    }

    /// Returns the rotation as {latitude, longitude, revolution} in degrees.
    [[nodiscard]] std::array<float, 3> get_rotation() const noexcept {
        return {lat_, lon_, rev_};
    }

    /// Returns the latitude component of the rotation.
    [[nodiscard]] float latitude() const noexcept { return lat_; }
    /// Returns the longitude component of the rotation.
    [[nodiscard]] float longitude() const noexcept { return lon_; }
    /// Returns the revolution component of the rotation.
    [[nodiscard]] float revolution() const noexcept { return rev_; }

private:
    CameraPresetType camera_type_ = CameraPresetType::NOT_DEFINED;
    float fov_ = 0.0f;
    float zoom_ = 100.0f;
    float lat_ = 0.0f;
    float lon_ = 0.0f;
    float rev_ = 0.0f;

    pugi::xml_node scene3d_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
