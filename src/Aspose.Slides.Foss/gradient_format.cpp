// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/gradient_format.h>

namespace Aspose::Slides::Foss {

void GradientFormat::init_internal(pugi::xml_node grad_fill_element,
                                   std::function<void()> save_callback) {
    grad_fill_ = grad_fill_element;
    save_callback_ = std::move(save_callback);
}

void GradientFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
