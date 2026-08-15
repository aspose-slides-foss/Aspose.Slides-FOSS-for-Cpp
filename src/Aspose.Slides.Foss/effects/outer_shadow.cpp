// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/outer_shadow.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/effect_color.h>
#include <Aspose/Slides/Foss/_internal/pptx/xml_attribute_utils.h>

#include <cmath>
#include <string_view>
#include <unordered_map>

namespace Aspose::Slides::Foss::Effects {

namespace {

// OOXML alignment attribute value -> RectangleAlignment enum.
RectangleAlignment alignment_from_ooxml(std::string_view val) {
    static const std::unordered_map<std::string_view, RectangleAlignment> map = {
        {"tl",  RectangleAlignment::TOP_LEFT},
        {"t",   RectangleAlignment::TOP},
        {"tr",  RectangleAlignment::TOP_RIGHT},
        {"l",   RectangleAlignment::LEFT},
        {"ctr", RectangleAlignment::CENTER},
        {"r",   RectangleAlignment::RIGHT},
        {"bl",  RectangleAlignment::BOTTOM_LEFT},
        {"b",   RectangleAlignment::BOTTOM},
        {"br",  RectangleAlignment::BOTTOM_RIGHT},
    };
    auto it = map.find(val);
    return it != map.end() ? it->second : RectangleAlignment::NOT_DEFINED;
}

// RectangleAlignment enum -> OOXML alignment attribute value.
const char* alignment_to_ooxml(RectangleAlignment val) {
    switch (val) {
        case RectangleAlignment::TOP_LEFT:     return "tl";
        case RectangleAlignment::TOP:          return "t";
        case RectangleAlignment::TOP_RIGHT:    return "tr";
        case RectangleAlignment::LEFT:         return "l";
        case RectangleAlignment::CENTER:       return "ctr";
        case RectangleAlignment::RIGHT:        return "r";
        case RectangleAlignment::BOTTOM_LEFT:  return "bl";
        case RectangleAlignment::BOTTOM:       return "b";
        case RectangleAlignment::BOTTOM_RIGHT: return "br";
        default:                               return nullptr;
    }
}

// OOXML stores percentages as value * 1000 (e.g. 100% = 100000).
constexpr int kPercentUnit = 1000;

} // namespace

void OuterShadow::init_internal(pugi::xml_node element,
                                std::function<void()> save_callback,
                                IBaseSlide* /*parent_slide*/) {
    element_ = element;
    save_callback_ = std::move(save_callback);

    // Blur radius: 'blurRad' in EMUs -> points.
    if (auto attr = element_.attribute("blurRad"); attr) {
        blur_radius_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }

    // Direction: 'dir' in 60000ths of degree -> degrees.
    if (auto attr = element_.attribute("dir"); attr) {
        direction_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kRotationUnit;
    }

    // Distance: 'dist' in EMUs -> points.
    if (auto attr = element_.attribute("dist"); attr) {
        distance_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }

    // Alignment: 'algn' string -> RectangleAlignment enum.
    if (auto attr = element_.attribute("algn"); attr) {
        rectangle_align_ = alignment_from_ooxml(attr.as_string());
    }

    // Skew horizontal: 'kx' in 60000ths of degree -> degrees.
    if (auto attr = element_.attribute("kx"); attr) {
        skew_horizontal_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kRotationUnit;
    }

    // Skew vertical: 'ky' in 60000ths of degree -> degrees.
    if (auto attr = element_.attribute("ky"); attr) {
        skew_vertical_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kRotationUnit;
    }

    // Rotate with shape: 'rotWithShape' boolean (defaults to true).
    if (auto attr = element_.attribute("rotWithShape"); attr) {
        rotate_shadow_with_shape_ = attr.as_bool(true);
    }

    // Scale horizontal: 'sx' percentage * 1000 -> percent.
    if (auto attr = element_.attribute("sx"); attr) {
        scale_horizontal_ = static_cast<double>(attr.as_llong(100000)) / kPercentUnit;
    }

    // Scale vertical: 'sy' percentage * 1000 -> percent.
    if (auto attr = element_.attribute("sy"); attr) {
        scale_vertical_ = static_cast<double>(attr.as_llong(100000)) / kPercentUnit;
    }
    // CT_OuterShadowEffect requires exactly one colour child; a freshly created
    // element has none, and PowerPoint refuses a file that leaves it off.
    if (element_) {
        if (!Internal::pptx::read_effect_color(element_, shadow_color_)) {
            Internal::pptx::write_effect_color(element_, shadow_color_);
        }
        shadow_color_.set_on_changed([this] {
            Internal::pptx::write_effect_color(element_, shadow_color_);
            if (save_callback_) save_callback_();
        });
    }
}

void OuterShadow::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// -- Property getters -----------------------------------------------------

double OuterShadow::blur_radius() const noexcept { return blur_radius_; }
double OuterShadow::direction() const noexcept { return direction_; }
double OuterShadow::distance() const noexcept { return distance_; }
RectangleAlignment OuterShadow::rectangle_align() const noexcept { return rectangle_align_; }
double OuterShadow::skew_horizontal() const noexcept { return skew_horizontal_; }
double OuterShadow::skew_vertical() const noexcept { return skew_vertical_; }
bool OuterShadow::rotate_shadow_with_shape() const noexcept { return rotate_shadow_with_shape_; }
double OuterShadow::scale_horizontal() const noexcept { return scale_horizontal_; }
double OuterShadow::scale_vertical() const noexcept { return scale_vertical_; }

// -- Property setters -----------------------------------------------------

void OuterShadow::set_blur_radius(double value) noexcept {
    blur_radius_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "blurRad", 
            static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_direction(double value) noexcept {
    direction_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "dir", 
            static_cast<long long>(std::round(value * Internal::pptx::kRotationUnit)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_distance(double value) noexcept {
    distance_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "dist", 
            static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_rectangle_align(RectangleAlignment value) noexcept {
    rectangle_align_ = value;
    if (element_) {
        if (auto* ooxml_val = alignment_to_ooxml(value); ooxml_val) {
            Internal::pptx::set_attribute(element_, "algn", ooxml_val);
        }
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_skew_horizontal(double value) noexcept {
    skew_horizontal_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "kx", 
            static_cast<long long>(std::round(value * Internal::pptx::kRotationUnit)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_skew_vertical(double value) noexcept {
    skew_vertical_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "ky", 
            static_cast<long long>(std::round(value * Internal::pptx::kRotationUnit)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_rotate_shadow_with_shape(bool value) noexcept {
    rotate_shadow_with_shape_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "rotWithShape", value ? "1" : "0");
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_scale_horizontal(double value) noexcept {
    scale_horizontal_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "sx", 
            static_cast<long long>(std::round(value * kPercentUnit)));
    }
    if (save_callback_) save_callback_();
}

void OuterShadow::set_scale_vertical(double value) noexcept {
    scale_vertical_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "sy", 
            static_cast<long long>(std::round(value * kPercentUnit)));
    }
    if (save_callback_) save_callback_();
}

} // namespace Aspose::Slides::Foss::Effects
