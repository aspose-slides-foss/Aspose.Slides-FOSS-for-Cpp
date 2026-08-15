// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/preset_shadow.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/effect_color.h>
#include <Aspose/Slides/Foss/_internal/pptx/xml_attribute_utils.h>

#include <cmath>
#include <string_view>
#include <unordered_map>

namespace Aspose::Slides::Foss::Effects {

namespace {

// OOXML preset shadow attribute value -> PresetShadowType enum.
PresetShadowType preset_from_ooxml(std::string_view val) {
    static const std::unordered_map<std::string_view, PresetShadowType> map = {
        {"shdw1",  PresetShadowType::TOP_LEFT_DROP_SHADOW},
        {"shdw2",  PresetShadowType::TOP_LEFT_LARGE_DROP_SHADOW},
        {"shdw3",  PresetShadowType::BACK_LEFT_LONG_PERSPECTIVE_SHADOW},
        {"shdw4",  PresetShadowType::BACK_RIGHT_LONG_PERSPECTIVE_SHADOW},
        {"shdw5",  PresetShadowType::TOP_LEFT_DOUBLE_DROP_SHADOW},
        {"shdw6",  PresetShadowType::BOTTOM_RIGHT_SMALL_DROP_SHADOW},
        {"shdw7",  PresetShadowType::FRONT_LEFT_LONG_PERSPECTIVE_SHADOW},
        {"shdw8",  PresetShadowType::FRONT_RIGHT_LONG_PERSPECTIVE_SHADOW},
        {"shdw9",  PresetShadowType::OUTER_BOX_SHADOW3_D},
        {"shdw10", PresetShadowType::INNER_BOX_SHADOW3_D},
        {"shdw11", PresetShadowType::BACK_CENTER_PERSPECTIVE_SHADOW},
        {"shdw12", PresetShadowType::TOP_RIGHT_DROP_SHADOW},
        {"shdw13", PresetShadowType::FRONT_BOTTOM_SHADOW},
        {"shdw14", PresetShadowType::BACK_LEFT_PERSPECTIVE_SHADOW},
        {"shdw15", PresetShadowType::BACK_RIGHT_PERSPECTIVE_SHADOW},
        {"shdw16", PresetShadowType::BOTTOM_LEFT_DROP_SHADOW},
        {"shdw17", PresetShadowType::BOTTOM_RIGHT_DROP_SHADOW},
        {"shdw18", PresetShadowType::FRONT_LEFT_PERSPECTIVE_SHADOW},
        {"shdw19", PresetShadowType::FRONT_RIGHT_PERSPECTIVE_SHADOW},
        {"shdw20", PresetShadowType::TOP_LEFT_SMALL_DROP_SHADOW},
    };
    auto it = map.find(val);
    return it != map.end() ? it->second : PresetShadowType::TOP_LEFT_DROP_SHADOW;
}

// PresetShadowType enum -> OOXML preset shadow attribute value.
const char* preset_to_ooxml(PresetShadowType val) {
    switch (val) {
        case PresetShadowType::TOP_LEFT_DROP_SHADOW:                return "shdw1";
        case PresetShadowType::TOP_LEFT_LARGE_DROP_SHADOW:          return "shdw2";
        case PresetShadowType::BACK_LEFT_LONG_PERSPECTIVE_SHADOW:   return "shdw3";
        case PresetShadowType::BACK_RIGHT_LONG_PERSPECTIVE_SHADOW:  return "shdw4";
        case PresetShadowType::TOP_LEFT_DOUBLE_DROP_SHADOW:         return "shdw5";
        case PresetShadowType::BOTTOM_RIGHT_SMALL_DROP_SHADOW:      return "shdw6";
        case PresetShadowType::FRONT_LEFT_LONG_PERSPECTIVE_SHADOW:  return "shdw7";
        case PresetShadowType::FRONT_RIGHT_LONG_PERSPECTIVE_SHADOW: return "shdw8";
        case PresetShadowType::OUTER_BOX_SHADOW3_D:                 return "shdw9";
        case PresetShadowType::INNER_BOX_SHADOW3_D:                 return "shdw10";
        case PresetShadowType::BACK_CENTER_PERSPECTIVE_SHADOW:      return "shdw11";
        case PresetShadowType::TOP_RIGHT_DROP_SHADOW:               return "shdw12";
        case PresetShadowType::FRONT_BOTTOM_SHADOW:                 return "shdw13";
        case PresetShadowType::BACK_LEFT_PERSPECTIVE_SHADOW:        return "shdw14";
        case PresetShadowType::BACK_RIGHT_PERSPECTIVE_SHADOW:       return "shdw15";
        case PresetShadowType::BOTTOM_LEFT_DROP_SHADOW:             return "shdw16";
        case PresetShadowType::BOTTOM_RIGHT_DROP_SHADOW:            return "shdw17";
        case PresetShadowType::FRONT_LEFT_PERSPECTIVE_SHADOW:       return "shdw18";
        case PresetShadowType::FRONT_RIGHT_PERSPECTIVE_SHADOW:      return "shdw19";
        case PresetShadowType::TOP_LEFT_SMALL_DROP_SHADOW:          return "shdw20";
    }
    return "shdw1";
}

} // namespace

const char* preset_shadow_type_to_ooxml(PresetShadowType value) {
    return preset_to_ooxml(value);
}

void PresetShadow::init_internal(pugi::xml_node element,
                                 std::function<void()> save_callback,
                                 IBaseSlide* /*parent_slide*/) {
    element_ = element;
    save_callback_ = std::move(save_callback);

    // Direction: 'dir' in 60000ths of degree -> degrees.
    if (auto attr = element_.attribute("dir"); attr) {
        direction_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kRotationUnit;
    }

    // Distance: 'dist' in EMUs -> points.
    if (auto attr = element_.attribute("dist"); attr) {
        distance_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }

    // Preset type: 'prst' string -> PresetShadowType enum.
    if (auto attr = element_.attribute("prst"); attr) {
        preset_ = preset_from_ooxml(attr.as_string());
    }
    // CT_PresetShadowEffect requires @prst and exactly one colour child; a
    // freshly created element has neither, and PowerPoint refuses a file that
    // leaves either off.
    if (element_) {
        Internal::pptx::set_attribute(element_, "prst",
                                      preset_to_ooxml(preset_));
        if (!Internal::pptx::read_effect_color(element_, shadow_color_)) {
            Internal::pptx::write_effect_color(element_, shadow_color_);
        }
        shadow_color_.set_on_changed([this] {
            Internal::pptx::write_effect_color(element_, shadow_color_);
            if (save_callback_) save_callback_();
        });
    }
}

void PresetShadow::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// -- Property getters -----------------------------------------------------

double PresetShadow::direction() const noexcept { return direction_; }
double PresetShadow::distance() const noexcept { return distance_; }
PresetShadowType PresetShadow::preset() const noexcept { return preset_; }

// -- Property setters -----------------------------------------------------

void PresetShadow::set_direction(double value) noexcept {
    direction_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "dir", 
            static_cast<long long>(std::round(value * Internal::pptx::kRotationUnit)));
    }
    if (save_callback_) save_callback_();
}

void PresetShadow::set_distance(double value) noexcept {
    distance_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "dist", 
            static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint)));
    }
    if (save_callback_) save_callback_();
}

void PresetShadow::set_preset(PresetShadowType value) noexcept {
    preset_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "prst", preset_to_ooxml(value));
    }
    if (save_callback_) save_callback_();
}

} // namespace Aspose::Slides::Foss::Effects
