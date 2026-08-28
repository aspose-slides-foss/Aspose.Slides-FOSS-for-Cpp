// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/soft_edge.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/xml_attribute_utils.h>

#include <cmath>

namespace Aspose::Slides::Foss::Effects {

void SoftEdge::init_internal(pugi::xml_node element,
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

    // @rad is required by CT_SoftEdgesEffect; a freshly created element has
    // none, and PowerPoint refuses a file that leaves it off.
    if (element_) {
        Internal::pptx::set_attribute(
            element_, "rad",
            static_cast<long long>(
                std::round(radius_ * Internal::pptx::kEmuPerPoint)));
    }
}

void SoftEdge::save() {
    if (save_callback_) {
        save_callback_();
    }
}

double SoftEdge::radius() const noexcept {
    return radius_;
}

void SoftEdge::set_radius(double value) noexcept {
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
