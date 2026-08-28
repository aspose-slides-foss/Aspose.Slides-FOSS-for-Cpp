// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/effect_color.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <string_view>

#include <Aspose/Slides/Foss/drawing/color.h>

namespace Aspose::Slides::Foss::Internal::pptx {

namespace {

/// EG_ColorChoice: the element names a colour may take.
constexpr std::array kColorChoice = {
    std::string_view{"a:scrgbClr"}, std::string_view{"a:srgbClr"},
    std::string_view{"a:hslClr"},   std::string_view{"a:sysClr"},
    std::string_view{"a:schemeClr"}, std::string_view{"a:prstClr"},
};

int hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

} // namespace

bool read_effect_color(pugi::xml_node element, SimpleColorFormat& format) {
    for (auto tag : kColorChoice) {
        auto node = element.child(std::string(tag).c_str());
        if (!node) continue;
        if (tag != "a:srgbClr") {
            // Only sRGB maps onto SimpleColorFormat; the others are left in
            // the file untouched rather than flattened into something else.
            return true;
        }
        std::string_view val{node.attribute("val").as_string("")};
        if (val.size() < 6) return true;
        auto byte_at = [&](std::size_t i) {
            return static_cast<std::uint8_t>(hex_digit(val[i]) * 16 +
                                             hex_digit(val[i + 1]));
        };
        std::uint8_t alpha = 255;
        if (auto a = node.child("a:alpha")) {
            alpha = static_cast<std::uint8_t>(std::lround(
                a.attribute("val").as_double(100000.0) / 100000.0 * 255.0));
        }
        format.set_color(Drawing::Color::from_argb(alpha, byte_at(0),
                                                   byte_at(2), byte_at(4)));
        return true;
    }
    return false;
}

void write_effect_color(pugi::xml_node element,
                        const SimpleColorFormat& format) {
    for (auto tag : kColorChoice) {
        std::string name{tag};
        while (auto existing = element.child(name.c_str())) {
            element.remove_child(existing);
        }
    }

    auto color = format.color();
    char hex[7];
    std::snprintf(hex, sizeof(hex), "%02X%02X%02X", static_cast<int>(color.r()),
                  static_cast<int>(color.g()), static_cast<int>(color.b()));
    auto srgb = element.append_child("a:srgbClr");
    srgb.append_attribute("val") = hex;
    if (color.a() < 255) {
        // ST_PositiveFixedPercentage: 100% is 100000.
        srgb.append_child("a:alpha").append_attribute("val") =
            static_cast<int>(std::lround(color.a() / 255.0 * 100000.0));
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
