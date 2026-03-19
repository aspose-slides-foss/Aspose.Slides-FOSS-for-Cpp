// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/bullet_format.h>

#include <array>
#include <string_view>

namespace Aspose::Slides::Foss {

// Bullet type element tags (ECMA-376 group 6 in CT_TextParagraphProperties).
static constexpr std::array kBulletTypeTags = {
    std::string_view{"a:buNone"},
    std::string_view{"a:buAutoNum"},
    std::string_view{"a:buChar"},
    std::string_view{"a:buBlip"},
};

void BulletFormat::init_internal(pugi::xml_node ppr_element,
                                 std::function<void()> save_callback) {
    ppr_element_ = ppr_element;
    save_callback_ = std::move(save_callback);
}

void BulletFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

void BulletFormat::remove_bullet_type_elements() {
    if (!ppr_element_) {
        return;
    }
    for (auto tag : kBulletTypeTags) {
        auto el = ppr_element_.child(std::string(tag).c_str());
        if (el) {
            ppr_element_.remove_child(el);
        }
    }
}

} // namespace Aspose::Slides::Foss
