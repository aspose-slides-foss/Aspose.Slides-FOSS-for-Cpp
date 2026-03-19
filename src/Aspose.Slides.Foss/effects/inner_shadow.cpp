// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/inner_shadow.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

#include <cmath>

namespace Aspose::Slides::Foss::Effects {

void InnerShadow::init_internal(pugi::xml_node element,
                                std::function<void()> save_callback,
                                IBaseSlide* /*parent_slide*/) {
    element_ = element;
    save_callback_ = std::move(save_callback);

    // Read blur radius from 'blurRad' attribute (stored in EMUs, exposed in points).
    if (auto attr = element_.attribute("blurRad"); attr) {
        blur_radius_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }

    // Read direction from 'dir' attribute (stored in 60000ths of a degree, exposed in degrees).
    if (auto attr = element_.attribute("dir"); attr) {
        direction_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kRotationUnit;
    }

    // Read distance from 'dist' attribute (stored in EMUs, exposed in points).
    if (auto attr = element_.attribute("dist"); attr) {
        distance_ = static_cast<double>(attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }
}

void InnerShadow::save() {
    if (save_callback_) {
        save_callback_();
    }
}

double InnerShadow::blur_radius() const noexcept {
    return blur_radius_;
}

void InnerShadow::set_blur_radius(double value) noexcept {
    blur_radius_ = value;

    if (element_) {
        auto emu = static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint));
        element_.attribute("blurRad").set_value(emu);
    }

    if (save_callback_) {
        save_callback_();
    }
}

double InnerShadow::direction() const noexcept {
    return direction_;
}

void InnerShadow::set_direction(double value) noexcept {
    direction_ = value;

    if (element_) {
        auto units = static_cast<long long>(std::round(value * Internal::pptx::kRotationUnit));
        element_.attribute("dir").set_value(units);
    }

    if (save_callback_) {
        save_callback_();
    }
}

double InnerShadow::distance() const noexcept {
    return distance_;
}

void InnerShadow::set_distance(double value) noexcept {
    distance_ = value;

    if (element_) {
        auto emu = static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint));
        element_.attribute("dist").set_value(emu);
    }

    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss::Effects
