// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/glow.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/effect_color.h>
#include <Aspose/Slides/Foss/_internal/pptx/xml_attribute_utils.h>

#include <charconv>
#include <cmath>
#include <string>

namespace Aspose::Slides::Foss::Effects {

void Glow::init_internal(pugi::xml_node element,
                         std::function<void()> save_callback,
                         IBaseSlide* parent_slide) {
    element_ = element;
    save_callback_ = std::move(save_callback);
    set_parent_slide(parent_slide);

    // Read radius from 'rad' attribute (stored in EMUs, exposed in points).
    if (auto rad_attr = element_.attribute("rad"); rad_attr) {
        auto emu_value = rad_attr.as_llong(0);
        radius_ = static_cast<double>(emu_value) / Internal::pptx::kEmuPerPoint;
    }

    if (element_) {
        Internal::pptx::set_attribute(
            element_, "rad",
            static_cast<long long>(
                std::round(radius_ * Internal::pptx::kEmuPerPoint)));
        // CT_GlowEffect requires exactly one colour child.
        if (!Internal::pptx::read_effect_color(element_, color_)) {
            Internal::pptx::write_effect_color(element_, color_);
        }
        color_.set_on_changed([this] {
            Internal::pptx::write_effect_color(element_, color_);
            if (save_callback_) save_callback_();
        });
    }
}

void Glow::save() {
    if (save_callback_) {
        save_callback_();
    }
}

double Glow::radius() const noexcept {
    return radius_;
}

void Glow::set_radius(double value) noexcept {
    radius_ = value;

    // Write back to XML element as EMUs.
    if (element_) {
        auto emu_value = static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint));
        Internal::pptx::set_attribute(element_, "rad", emu_value);
    }

    // Persist changes.
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss::Effects
