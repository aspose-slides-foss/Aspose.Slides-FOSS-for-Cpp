// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/camera.h>

#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/camera_preset_type.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// Tag constants (prefixed names for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kCamera = "a:camera";

// ---------------------------------------------------------------------------
// Camera – XML-backed internal methods
// ---------------------------------------------------------------------------

void Camera::init_internal(pugi::xml_node scene3d_element,
                           std::function<void()> save_callback) {
    scene3d_element_ = scene3d_element;
    save_callback_ = std::move(save_callback);

    // Read existing camera element.
    auto cam = get_camera();
    if (cam) {
        auto prst = cam.attribute("prst");
        if (prst) {
            camera_type_ = camera_preset_type_from_ooxml(prst.as_string());
        }
    }
}

pugi::xml_node Camera::get_camera() const {
    return scene3d_element_.child(std::string(kCamera).c_str());
}

pugi::xml_node Camera::ensure_camera() {
    auto cam = get_camera();
    if (cam) return cam;

    auto node = scene3d_element_.append_child(std::string(kCamera).c_str());
    node.append_attribute("prst") = "orthographicFront";
    return node;
}

void Camera::set_camera_type(CameraPresetType value) noexcept {
    camera_type_ = value;
    if (scene3d_element_) {
        auto cam = ensure_camera();
        auto ooxml = camera_preset_type_to_ooxml(value);
        auto attr = cam.attribute("prst");
        if (attr) {
            attr.set_value(std::string(ooxml).c_str());
        } else if (!ooxml.empty()) {
            cam.append_attribute("prst") = std::string(ooxml).c_str();
        }
        save();
    }
}

void Camera::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
