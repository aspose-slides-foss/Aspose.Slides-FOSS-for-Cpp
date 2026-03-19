// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <array>
#include <functional>

#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents light rig properties for 3D scene rendering.
class LightRig final {
public:
    LightRig() = default;
    virtual ~LightRig() = default;

    /// Initialize XML-backed light rig.
    /// @param scene3d_element The <a:scene3d> XML element that contains the light rig.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node scene3d_element,
                       std::function<void()> save_callback);

    /// Get the <a:lightRig> element if it exists within the scene3d element.
    [[nodiscard]] pugi::xml_node get_light_rig() const;

    /// Get or create the <a:lightRig> element with defaults rig="threePt" dir="t".
    pugi::xml_node ensure_light_rig();

    /// Save changes via the save callback.
    void save();

    /// Returns true if this light rig has been initialized with a parent XML element.
    [[nodiscard]] bool has_parent() const noexcept { return static_cast<bool>(scene3d_element_); }

    /// Returns the light rig preset type.
    [[nodiscard]] LightRigPresetType light_type() const noexcept { return light_type_; }
    /// Sets the light rig preset type.
    void set_light_type(LightRigPresetType value) noexcept;

    /// Returns the lighting direction.
    [[nodiscard]] LightingDirection direction() const noexcept { return direction_; }
    /// Sets the lighting direction.
    void set_direction(LightingDirection value) noexcept;

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
    LightRigPresetType light_type_ = LightRigPresetType::NOT_DEFINED;
    LightingDirection direction_ = LightingDirection::NOT_DEFINED;
    float lat_ = 0.0f;
    float lon_ = 0.0f;
    float rev_ = 0.0f;

    pugi::xml_node scene3d_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
