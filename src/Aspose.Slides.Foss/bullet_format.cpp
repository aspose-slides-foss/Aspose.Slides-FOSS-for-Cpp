// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/bullet_format.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <string_view>

#include <Aspose/Slides/Foss/_internal/pptx/text_serialization.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/i_bullet_format.h>
#include <Aspose/Slides/Foss/i_color_format.h>

namespace Aspose::Slides::Foss {

// Bullet type element tags (ECMA-376 group 6 in CT_TextParagraphProperties).
static constexpr std::array kBulletTypeTags = {
    std::string_view{"a:buNone"},
    std::string_view{"a:buAutoNum"},
    std::string_view{"a:buChar"},
    std::string_view{"a:buBlip"},
};

/// Everything in `<a:pPr>` that belongs to the bullet, in schema order.
///
/// These are the elements write_bullet() owns: it clears all of them and
/// writes back what the model says, so a bullet can be replaced without
/// leaving the previous one behind and without touching anything else on the
/// paragraph.
static constexpr std::array kBulletOwnedTags = {
    std::string_view{"a:buClrTx"},  std::string_view{"a:buClr"},
    std::string_view{"a:buSzTx"},   std::string_view{"a:buSzPct"},
    std::string_view{"a:buSzPts"},  std::string_view{"a:buFontTx"},
    std::string_view{"a:buFont"},   std::string_view{"a:buNone"},
    std::string_view{"a:buAutoNum"},std::string_view{"a:buChar"},
    std::string_view{"a:buBlip"},
};

namespace {

void append_srgb_color(pugi::xml_node parent, const IColorFormat& cf) {
    auto c = cf.color();
    char hex[7];
    std::snprintf(hex, sizeof(hex), "%02X%02X%02X", static_cast<int>(c.r()),
                  static_cast<int>(c.g()), static_cast<int>(c.b()));
    parent.append_child("a:srgbClr").append_attribute("val") = hex;
}

/// Read a colour from the first a:srgbClr under @p parent.
Drawing::Color read_srgb_color(pugi::xml_node parent) {
    auto srgb = parent.child("a:srgbClr");
    if (!srgb) return {};
    std::string_view hex = srgb.attribute("val").as_string("");
    if (hex.size() < 6) return {};
    auto digit = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return 0;
    };
    auto byte = [&](std::size_t i) {
        return static_cast<uint8_t>(digit(hex[i]) * 16 + digit(hex[i + 1]));
    };
    return Drawing::Color::from_argb(255, byte(0), byte(2), byte(4));
}

} // namespace

void Internal::pptx::write_bullet(pugi::xml_node ppr,
                                  const IBulletFormat& bullet) {
    if (!ppr) return;

    for (auto tag : kBulletOwnedTags) {
        std::string name{tag};
        while (auto child = ppr.child(name.c_str())) ppr.remove_child(child);
    }

    if (bullet.type() == BulletType::NOT_DEFINED) return;

    if (bullet.is_bullet_hard_color() == NullableBool::TRUE) {
        append_srgb_color(ppr_insert_child(ppr, "a:buClr"), bullet.color());
    }
    if (!std::isnan(bullet.height())) {
        ppr_insert_child(ppr, "a:buSzPct").append_attribute("val") =
            static_cast<int>(std::round(bullet.height() * 1000.0f));
    }
    if (!bullet.font_name().empty()) {
        ppr_insert_child(ppr, "a:buFont").append_attribute("typeface") =
            bullet.font_name().c_str();
    }

    switch (bullet.type()) {
        case BulletType::NONE:
            ppr_insert_child(ppr, "a:buNone");
            break;
        case BulletType::SYMBOL: {
            // @char is required by CT_TextCharBullet. A symbol bullet with no
            // character set falls back to the same glyph PowerPoint uses.
            auto node = ppr_insert_child(ppr, "a:buChar");
            node.append_attribute("char") =
                bullet.get_char().empty() ? "\xE2\x80\xA2"
                                          : bullet.get_char().c_str();
            break;
        }
        case BulletType::NUMBERED: {
            auto node = ppr_insert_child(ppr, "a:buAutoNum");
            // @type is required by CT_TextAutonumberBullet.
            const char* scheme =
                numbered_bullet_style_to_ooxml(bullet.numbered_bullet_style());
            node.append_attribute("type") = scheme ? scheme : "arabicPeriod";
            if (bullet.numbered_bullet_start_with() != 1) {
                node.append_attribute("startAt") =
                    bullet.numbered_bullet_start_with();
            }
            break;
        }
        case BulletType::PICTURE:
            // a:buBlip needs an r:embed to an image part, which this
            // serialiser has no relationship table to allocate one in. Writing
            // a:buBlip with no a:blip would produce a package that does not
            // validate, so the bullet is left to be inherited instead.
            break;
        case BulletType::NOT_DEFINED:
            break;
    }
}

void BulletFormat::init_internal(pugi::xml_node ppr_element,
                                 std::function<void()> save_callback,
                                 pugi::xml_node p_element) {
    ppr_element_ = ppr_element;
    p_element_ = p_element;
    save_callback_ = std::move(save_callback);

    if (!ppr_element_) {
        // The colour is handed out by reference and mutated in place, so there
        // is no setter call for this object to notice; the callback is the
        // only moment at which the new value can be written.
        color_.set_on_changed([this] { persist(); });
        return;
    }

    // Read the bullet the paragraph already carries. A setter rewrites every
    // element the bullet owns from this model, so anything left unread here is
    // deleted from the file the first time any single bullet property is set.
    if (auto clr = ppr_element_.child("a:buClr")) {
        color_.set_color(read_srgb_color(clr));
        hard_color_ = NullableBool::TRUE;
    } else if (ppr_element_.child("a:buClrTx")) {
        hard_color_ = NullableBool::FALSE;
    }
    if (auto sz = ppr_element_.child("a:buSzPct")) {
        height_ = static_cast<float>(sz.attribute("val").as_int(0) / 1000.0);
    }
    if (auto font = ppr_element_.child("a:buFont")) {
        font_name_ = font.attribute("typeface").as_string("");
        hard_font_ = NullableBool::TRUE;
    } else if (ppr_element_.child("a:buFontTx")) {
        hard_font_ = NullableBool::FALSE;
    }

    if (ppr_element_.child("a:buNone")) {
        type_ = BulletType::NONE;
    } else if (auto ch = ppr_element_.child("a:buChar")) {
        type_ = BulletType::SYMBOL;
        char_ = ch.attribute("char").as_string("");
    } else if (auto num = ppr_element_.child("a:buAutoNum")) {
        type_ = BulletType::NUMBERED;
        numbered_style_ =
            numbered_bullet_style_from_ooxml(num.attribute("type").as_string(""));
        numbered_start_ = num.attribute("startAt").as_int(1);
    } else if (ppr_element_.child("a:buBlip")) {
        type_ = BulletType::PICTURE;
    }

    // Installed after the read-back, so that reading the file does not write
    // it straight back out again.
    color_.set_on_changed([this] { persist(); });
}

void BulletFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

pugi::xml_node BulletFormat::ensure_ppr() {
    if (ppr_element_) return ppr_element_;
    if (!p_element_) return {};
    // CT_TextParagraph is (pPr?, (r|br|fld)*, endParaRPr?).
    ppr_element_ = p_element_.prepend_child("a:pPr");
    return ppr_element_;
}

void BulletFormat::persist() {
    // A paragraph with no bullet and no `<a:pPr>` has nothing to say, and
    // creating an empty element to say it would rewrite files nobody edited.
    if (!ppr_element_ && type_ == BulletType::NOT_DEFINED) return;
    auto ppr = ensure_ppr();
    if (!ppr) return;
    Internal::pptx::write_bullet(ppr, *this);
    save();
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
