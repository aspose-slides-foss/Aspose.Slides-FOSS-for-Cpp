// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/blur.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

#include <cmath>

namespace Aspose::Slides::Foss::Effects {

void Blur::init_internal(pugi::xml_node element,
                         std::function<void()> save_callback,
                         IBaseSlide* parent_slide) {
    element_ = element;
    save_callback_ = std::move(save_callback);
    set_parent_slide(parent_slide);

    // Read radius from 'rad' attribute (stored in EMUs, exposed in points).
    if (auto rad_attr = element_.attribute("rad"); rad_attr) {
        radius_ = static_cast<double>(rad_attr.as_llong(0)) / Internal::pptx::kEmuPerPoint;
    }

    // Read grow from 'grow' attribute (defaults to true).
    if (auto grow_attr = element_.attribute("grow"); grow_attr) {
        grow_ = grow_attr.as_bool(true);
    }
}

void Blur::set_radius(double value) noexcept {
    radius_ = value;
    if (element_) {
        auto emu = static_cast<long long>(std::round(value * Internal::pptx::kEmuPerPoint));
        element_.attribute("rad").set_value(emu);
        save();
    }
}

void Blur::set_grow(bool value) noexcept {
    grow_ = value;
    if (element_) {
        element_.attribute("grow").set_value(value);
        save();
    }
}

void Blur::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss::Effects
