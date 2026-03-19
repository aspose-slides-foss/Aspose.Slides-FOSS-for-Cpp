// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/light_rig.h>

#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// Tag constants (prefixed names for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kLightRig = "a:lightRig";

// ---------------------------------------------------------------------------
// LightRig – XML-backed internal methods
// ---------------------------------------------------------------------------

void LightRig::init_internal(pugi::xml_node scene3d_element,
                             std::function<void()> save_callback) {
    scene3d_element_ = scene3d_element;
    save_callback_ = std::move(save_callback);

    // Read existing light rig element.
    auto lr = get_light_rig();
    if (lr) {
        auto rig = lr.attribute("rig");
        if (rig) {
            light_type_ = light_rig_preset_type_from_ooxml(rig.as_string());
        }
        auto dir = lr.attribute("dir");
        if (dir) {
            direction_ = lighting_direction_from_ooxml(dir.as_string());
        }
    }
}

pugi::xml_node LightRig::get_light_rig() const {
    return scene3d_element_.child(std::string(kLightRig).c_str());
}

pugi::xml_node LightRig::ensure_light_rig() {
    auto lr = get_light_rig();
    if (lr) return lr;

    auto node = scene3d_element_.append_child(std::string(kLightRig).c_str());
    node.append_attribute("rig") = "threePt";
    node.append_attribute("dir") = "t";
    return node;
}

void LightRig::set_light_type(LightRigPresetType value) noexcept {
    light_type_ = value;
    if (scene3d_element_) {
        auto lr = ensure_light_rig();
        auto ooxml = light_rig_preset_type_to_ooxml(value);
        auto attr = lr.attribute("rig");
        if (attr) {
            attr.set_value(std::string(ooxml).c_str());
        } else if (!ooxml.empty()) {
            lr.append_attribute("rig") = std::string(ooxml).c_str();
        }
        save();
    }
}

void LightRig::set_direction(LightingDirection value) noexcept {
    direction_ = value;
    if (scene3d_element_) {
        auto lr = ensure_light_rig();
        auto ooxml = lighting_direction_to_ooxml(value);
        auto attr = lr.attribute("dir");
        if (attr) {
            attr.set_value(std::string(ooxml).c_str());
        } else if (!ooxml.empty()) {
            lr.append_attribute("dir") = std::string(ooxml).c_str();
        }
        save();
    }
}

void LightRig::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
