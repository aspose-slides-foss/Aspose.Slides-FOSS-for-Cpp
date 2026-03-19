// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Defines 2-dimension alignment.
enum class RectangleAlignment {
    NOT_DEFINED,
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    CENTER,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT,
};

/// Returns the string representation of a RectangleAlignment value.
constexpr std::string_view to_string_view(RectangleAlignment value) {
    switch (value) {
        case RectangleAlignment::NOT_DEFINED: return "NotDefined";
        case RectangleAlignment::TOP_LEFT: return "TopLeft";
        case RectangleAlignment::TOP: return "Top";
        case RectangleAlignment::TOP_RIGHT: return "TopRight";
        case RectangleAlignment::LEFT: return "Left";
        case RectangleAlignment::CENTER: return "Center";
        case RectangleAlignment::RIGHT: return "Right";
        case RectangleAlignment::BOTTOM_LEFT: return "BottomLeft";
        case RectangleAlignment::BOTTOM: return "Bottom";
        case RectangleAlignment::BOTTOM_RIGHT: return "BottomRight";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
