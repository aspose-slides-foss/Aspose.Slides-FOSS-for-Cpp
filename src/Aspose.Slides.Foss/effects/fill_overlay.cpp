// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/fill_overlay.h>

namespace Aspose::Slides::Foss::Effects {

void FillOverlay::init_internal(pugi::xml_node element,
                                std::function<void()> save_callback,
                                IBaseSlide* parent_slide) {
    element_ = element;
    save_callback_ = std::move(save_callback);
    set_parent_slide(parent_slide);
}

void FillOverlay::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss::Effects
