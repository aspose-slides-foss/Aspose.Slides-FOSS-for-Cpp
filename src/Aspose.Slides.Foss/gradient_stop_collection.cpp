// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/gradient_stop_collection.h>

namespace Aspose::Slides::Foss {

void GradientStopCollection::init_internal(pugi::xml_node gs_lst_element,
                                           std::function<void()> save_callback) {
    gs_lst_ = gs_lst_element;
    save_callback_ = std::move(save_callback);
}

void GradientStopCollection::save() {
    if (save_callback_) {
        save_callback_();
    }
}

void GradientStopCollection::set_color_from_arg(SimpleColorFormat& cf,
                                                 const Drawing::Color& color) {
    cf.set_color(color);
}

void GradientStopCollection::set_color_from_arg(SimpleColorFormat& cf,
                                                 PresetColor preset) {
    cf.set_preset_color(preset);
}

void GradientStopCollection::set_color_from_arg(SimpleColorFormat& cf,
                                                 SchemeColor scheme) {
    cf.set_scheme_color(scheme);
}

} // namespace Aspose::Slides::Foss
