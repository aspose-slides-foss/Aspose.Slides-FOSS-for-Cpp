// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/three_d_format.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <Aspose/Slides/Foss/color_type.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/material_preset_type.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::kEmuPerPoint;

// ---------------------------------------------------------------------------
// Tag constants (prefix notation for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kScene3d = "a:scene3d";
static constexpr std::string_view kSp3d    = "a:sp3d";
static constexpr std::string_view kExtLst  = "a:extLst";

/// Tags that must appear after <a:scene3d> in OOXML spPr ordering.
static constexpr std::array kPostScene3dTags = {
    std::string_view{"a:sp3d"},
    std::string_view{"a:extLst"},
};

/// Tags that must appear after <a:sp3d> in OOXML spPr ordering.
static constexpr std::array kPostSp3dTags = {
    std::string_view{"a:extLst"},
};

namespace {

/// Set an attribute, adding it if the element does not already carry it.
void set_or_add_attribute(pugi::xml_node node, const char* name,
                          const std::string& value) {
    if (auto attr = node.attribute(name)) {
        attr.set_value(value.c_str());
    } else {
        node.append_attribute(name) = value.c_str();
    }
}

/// Write an <a:srgbClr val="RRGGBB"/> child under the given colour element.
void write_srgb_color(pugi::xml_node parent, const Drawing::Color& c) {
    char hex[7];
    std::snprintf(hex, sizeof(hex), "%02X%02X%02X",
                  static_cast<int>(c.r()), static_cast<int>(c.g()),
                  static_cast<int>(c.b()));
    parent.append_child("a:srgbClr").append_attribute("val") = hex;
}

} // namespace

// ---------------------------------------------------------------------------
// ThreeDFormat – XML-backed internal methods
// ---------------------------------------------------------------------------

void ThreeDFormat::init_internal(pugi::xml_node parent_element,
                                 std::function<void()> save_callback) {
    parent_element_ = parent_element;
    save_callback_ = std::move(save_callback);

    // Read existing sp3d attributes.
    auto sp3d = get_sp3d();
    if (sp3d) {
        auto ext_h = sp3d.attribute("extrusionH");
        if (ext_h) {
            depth_ = static_cast<double>(ext_h.as_llong(0)) / kEmuPerPoint;
        }
        auto mat = sp3d.attribute("prstMaterial");
        if (mat) {
            material_ = material_preset_type_from_ooxml(mat.as_string());
        }

        // Initialize bevel sub-components from sp3d.
        bevel_top_.init_internal(sp3d, save_callback_);
        bevel_bottom_.init_internal(sp3d, save_callback_);
    }

    // Read existing scene3d sub-components.
    auto scene3d = get_scene3d();
    if (scene3d) {
        camera_.init_internal(scene3d, save_callback_);
        light_rig_.init_internal(scene3d, save_callback_);
    }
}

pugi::xml_node ThreeDFormat::get_sp3d() const {
    return parent_element_.child(std::string(kSp3d).c_str());
}

pugi::xml_node ThreeDFormat::ensure_sp3d() {
    auto el = get_sp3d();
    if (el) return el;

    // Insert before the first post-sp3d tag to maintain OOXML order.
    for (auto child : parent_element_.children()) {
        std::string_view name{child.name()};
        for (auto tag : kPostSp3dTags) {
            if (name == tag) {
                el = parent_element_.insert_child_before(
                    std::string(kSp3d).c_str(), child);
                // Init bevel sub-components on the new sp3d node.
                bevel_top_.init_internal(el, save_callback_);
                bevel_bottom_.init_internal(el, save_callback_);
                return el;
            }
        }
    }
    el = parent_element_.append_child(std::string(kSp3d).c_str());
    bevel_top_.init_internal(el, save_callback_);
    bevel_bottom_.init_internal(el, save_callback_);
    return el;
}

pugi::xml_node ThreeDFormat::get_scene3d() const {
    return parent_element_.child(std::string(kScene3d).c_str());
}

pugi::xml_node ThreeDFormat::ensure_scene3d() {
    auto el = get_scene3d();
    if (el) return el;

    // Insert before the first post-scene3d tag to maintain OOXML order.
    for (auto child : parent_element_.children()) {
        std::string_view name{child.name()};
        for (auto tag : kPostScene3dTags) {
            if (name == tag) {
                el = parent_element_.insert_child_before(
                    std::string(kScene3d).c_str(), child);
                camera_.init_internal(el, save_callback_);
                light_rig_.init_internal(el, save_callback_);
                return el;
            }
        }
    }
    el = parent_element_.append_child(std::string(kScene3d).c_str());
    camera_.init_internal(el, save_callback_);
    light_rig_.init_internal(el, save_callback_);
    return el;
}

// ---------------------------------------------------------------------------
// Non-const accessors that ensure parent XML elements exist
// ---------------------------------------------------------------------------

ShapeBevel& ThreeDFormat::bevel_top() {
    if (parent_element_ && !bevel_top_.has_parent()) {
        ensure_sp3d();
    }
    return bevel_top_;
}

ShapeBevel& ThreeDFormat::bevel_bottom() {
    if (parent_element_ && !bevel_bottom_.has_parent()) {
        ensure_sp3d();
    }
    return bevel_bottom_;
}

Camera& ThreeDFormat::camera() {
    if (parent_element_ && !camera_.has_parent()) {
        ensure_scene3d();
    }
    return camera_;
}

LightRig& ThreeDFormat::light_rig() {
    if (parent_element_ && !light_rig_.has_parent()) {
        ensure_scene3d();
    }
    return light_rig_;
}

// ---------------------------------------------------------------------------
// Property setters with XML persistence
// ---------------------------------------------------------------------------

void ThreeDFormat::set_depth(double value) noexcept {
    depth_ = value;
    if (parent_element_) {
        auto sp3d = ensure_sp3d();
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        auto attr = sp3d.attribute("extrusionH");
        if (attr) {
            attr.set_value(std::to_string(emu).c_str());
        } else {
            sp3d.append_attribute("extrusionH") = std::to_string(emu).c_str();
        }
        save();
    }
}

void ThreeDFormat::set_extrusion_height(double value) noexcept {
    extrusion_height_ = value;
    if (parent_element_) {
        auto sp3d = ensure_sp3d();
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        set_or_add_attribute(sp3d, "extrusionH", std::to_string(emu));
        save();
    }
}

void ThreeDFormat::set_contour_width(double value) noexcept {
    contour_width_ = value;
    if (parent_element_) {
        auto sp3d = ensure_sp3d();
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        set_or_add_attribute(sp3d, "contourW", std::to_string(emu));
        save();
    }
}

void ThreeDFormat::set_material(MaterialPresetType value) noexcept {
    material_ = value;
    if (parent_element_) {
        auto sp3d = ensure_sp3d();
        auto ooxml = material_preset_type_to_ooxml(value);
        auto attr = sp3d.attribute("prstMaterial");
        if (attr) {
            if (ooxml.empty()) {
                sp3d.remove_attribute(attr);
            } else {
                attr.set_value(std::string(ooxml).c_str());
            }
        } else if (!ooxml.empty()) {
            sp3d.append_attribute("prstMaterial") = std::string(ooxml).c_str();
        }
        save();
    }
}

void ThreeDFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// ---------------------------------------------------------------------------
// has_data / serialize_to_xml — for from-scratch presentation save
// ---------------------------------------------------------------------------

bool ThreeDFormat::has_data() const noexcept {
    return depth_ != 0.0
        || extrusion_height_ != 0.0
        || contour_width_ != 0.0
        || extrusion_color_.color_type() != ColorType::NOT_DEFINED
        || contour_color_.color_type() != ColorType::NOT_DEFINED
        || material_ != MaterialPresetType::NOT_DEFINED
        || bevel_top_.bevel_type() != BevelPresetType::NOT_DEFINED
        || bevel_bottom_.bevel_type() != BevelPresetType::NOT_DEFINED
        || camera_.camera_type() != CameraPresetType::NOT_DEFINED
        || light_rig_.light_type() != LightRigPresetType::NOT_DEFINED
        || light_rig_.direction() != LightingDirection::NOT_DEFINED;
}

void ThreeDFormat::serialize_to_xml(pugi::xml_node sp_pr) const {
    if (!has_data()) return;

    bool need_scene3d = camera_.camera_type() != CameraPresetType::NOT_DEFINED
                     || light_rig_.light_type() != LightRigPresetType::NOT_DEFINED
                     || light_rig_.direction() != LightingDirection::NOT_DEFINED;

    bool need_sp3d = depth_ != 0.0
                  || extrusion_height_ != 0.0
                  || contour_width_ != 0.0
                  || extrusion_color_.color_type() != ColorType::NOT_DEFINED
                  || contour_color_.color_type() != ColorType::NOT_DEFINED
                  || material_ != MaterialPresetType::NOT_DEFINED
                  || bevel_top_.bevel_type() != BevelPresetType::NOT_DEFINED
                  || bevel_bottom_.bevel_type() != BevelPresetType::NOT_DEFINED;

    // scene3d must come before sp3d in OOXML order.
    if (need_scene3d) {
        auto scene3d = sp_pr.append_child("a:scene3d");

        // Camera.
        if (camera_.camera_type() != CameraPresetType::NOT_DEFINED) {
            auto cam = scene3d.append_child("a:camera");
            cam.append_attribute("prst") =
                std::string(camera_preset_type_to_ooxml(camera_.camera_type())).c_str();
        }

        // Light rig.
        if (light_rig_.light_type() != LightRigPresetType::NOT_DEFINED
            || light_rig_.direction() != LightingDirection::NOT_DEFINED) {
            auto lr = scene3d.append_child("a:lightRig");
            if (light_rig_.light_type() != LightRigPresetType::NOT_DEFINED) {
                lr.append_attribute("rig") =
                    std::string(light_rig_preset_type_to_ooxml(light_rig_.light_type())).c_str();
            }
            // CT_LightRig requires dir. The API lets a caller set the rig
            // without a direction, and an a:lightRig with no dir is a file
            // PowerPoint refuses to open, so a direction is always written.
            if (light_rig_.direction() != LightingDirection::NOT_DEFINED) {
                lr.append_attribute("dir") =
                    std::string(lighting_direction_to_ooxml(light_rig_.direction())).c_str();
            } else {
                lr.append_attribute("dir") = "t";
            }
        }
    }

    if (need_sp3d) {
        auto sp3d = sp_pr.append_child("a:sp3d");

        // extrusionH is the extrusion height. depth() and extrusion_height()
        // are two names for it in this API; an explicitly set extrusion height
        // wins, otherwise the depth is used.
        double extrusion = extrusion_height_ != 0.0 ? extrusion_height_ : depth_;
        if (extrusion != 0.0) {
            auto emu = static_cast<long long>(std::round(extrusion * kEmuPerPoint));
            sp3d.append_attribute("extrusionH") = std::to_string(emu).c_str();
        }
        if (contour_width_ != 0.0) {
            auto emu = static_cast<long long>(
                std::round(contour_width_ * kEmuPerPoint));
            sp3d.append_attribute("contourW") = std::to_string(emu).c_str();
        }
        if (material_ != MaterialPresetType::NOT_DEFINED) {
            sp3d.append_attribute("prstMaterial") =
                std::string(material_preset_type_to_ooxml(material_)).c_str();
        }

        // Bevel top.
        if (bevel_top_.bevel_type() != BevelPresetType::NOT_DEFINED) {
            auto bt = sp3d.append_child("a:bevelT");
            bt.append_attribute("prst") =
                std::string(bevel_preset_type_to_ooxml(bevel_top_.bevel_type())).c_str();
            if (bevel_top_.width() != 0.0) {
                auto emu = static_cast<long long>(std::round(bevel_top_.width() * kEmuPerPoint));
                bt.append_attribute("w") = std::to_string(emu).c_str();
            }
            if (bevel_top_.height() != 0.0) {
                auto emu = static_cast<long long>(std::round(bevel_top_.height() * kEmuPerPoint));
                bt.append_attribute("h") = std::to_string(emu).c_str();
            }
        }

        // Bevel bottom.
        if (bevel_bottom_.bevel_type() != BevelPresetType::NOT_DEFINED) {
            auto bb = sp3d.append_child("a:bevelB");
            bb.append_attribute("prst") =
                std::string(bevel_preset_type_to_ooxml(bevel_bottom_.bevel_type())).c_str();
            if (bevel_bottom_.width() != 0.0) {
                auto emu = static_cast<long long>(std::round(bevel_bottom_.width() * kEmuPerPoint));
                bb.append_attribute("w") = std::to_string(emu).c_str();
            }
            if (bevel_bottom_.height() != 0.0) {
                auto emu = static_cast<long long>(std::round(bevel_bottom_.height() * kEmuPerPoint));
                bb.append_attribute("h") = std::to_string(emu).c_str();
            }
        }

        // CT_Shape3D orders its children bevelT, bevelB, extrusionClr,
        // contourClr.
        if (extrusion_color_.color_type() != ColorType::NOT_DEFINED) {
            write_srgb_color(sp3d.append_child("a:extrusionClr"),
                             extrusion_color_.color());
        }
        if (contour_color_.color_type() != ColorType::NOT_DEFINED) {
            write_srgb_color(sp3d.append_child("a:contourClr"),
                             contour_color_.color());
        }
    }
}

} // namespace Aspose::Slides::Foss
