// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/pattern_format.h>

namespace Aspose::Slides::Foss {

void PatternFormat::init_internal(pugi::xml_node patt_fill_element,
                                  std::function<void()> save_callback) {
    patt_fill_element_ = patt_fill_element;
    save_callback_ = std::move(save_callback);
}

void PatternFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
