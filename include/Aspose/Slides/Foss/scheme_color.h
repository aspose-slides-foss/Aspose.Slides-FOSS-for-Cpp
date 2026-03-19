// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents colors in a color scheme.
enum class SchemeColor {
    NOT_DEFINED,
    BACKGROUND1,
    TEXT1,
    BACKGROUND2,
    TEXT2,
    ACCENT1,
    ACCENT2,
    ACCENT3,
    ACCENT4,
    ACCENT5,
    ACCENT6,
    HYPERLINK,
    FOLLOWED_HYPERLINK,
    STYLE_COLOR,
    DARK1,
    LIGHT1,
    DARK2,
    LIGHT2,
};

/// Returns the string representation of a SchemeColor value.
constexpr std::string_view to_string_view(SchemeColor value) {
    switch (value) {
        case SchemeColor::NOT_DEFINED: return "NotDefined";
        case SchemeColor::BACKGROUND1: return "Background1";
        case SchemeColor::TEXT1: return "Text1";
        case SchemeColor::BACKGROUND2: return "Background2";
        case SchemeColor::TEXT2: return "Text2";
        case SchemeColor::ACCENT1: return "Accent1";
        case SchemeColor::ACCENT2: return "Accent2";
        case SchemeColor::ACCENT3: return "Accent3";
        case SchemeColor::ACCENT4: return "Accent4";
        case SchemeColor::ACCENT5: return "Accent5";
        case SchemeColor::ACCENT6: return "Accent6";
        case SchemeColor::HYPERLINK: return "Hyperlink";
        case SchemeColor::FOLLOWED_HYPERLINK: return "FollowedHyperlink";
        case SchemeColor::STYLE_COLOR: return "StyleColor";
        case SchemeColor::DARK1: return "Dark1";
        case SchemeColor::LIGHT1: return "Light1";
        case SchemeColor::DARK2: return "Dark2";
        case SchemeColor::LIGHT2: return "Light2";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
