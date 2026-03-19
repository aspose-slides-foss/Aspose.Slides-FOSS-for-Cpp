// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/gradient_stop.h>

namespace Aspose::Slides::Foss {

void GradientStop::init_internal(pugi::xml_node gs_element,
                                 std::function<void()> save_callback) {
    gs_element_ = gs_element;
    save_callback_ = std::move(save_callback);
}

void GradientStop::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
