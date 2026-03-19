// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define light directions.
enum class LightingDirection {
    NOT_DEFINED,
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
};

/// Returns the string representation of a LightingDirection value.
constexpr std::string_view to_string_view(LightingDirection value) {
    switch (value) {
        case LightingDirection::NOT_DEFINED: return "NotDefined";
        case LightingDirection::TOP_LEFT: return "TopLeft";
        case LightingDirection::TOP: return "Top";
        case LightingDirection::TOP_RIGHT: return "TopRight";
        case LightingDirection::RIGHT: return "Right";
        case LightingDirection::BOTTOM_RIGHT: return "BottomRight";
        case LightingDirection::BOTTOM: return "Bottom";
        case LightingDirection::BOTTOM_LEFT: return "BottomLeft";
        case LightingDirection::LEFT: return "Left";
    }
    return "Unknown";
}

/// Converts an OOXML dir attribute value to LightingDirection.
constexpr LightingDirection lighting_direction_from_ooxml(std::string_view ooxml) {
    if (ooxml == "tl") return LightingDirection::TOP_LEFT;
    if (ooxml == "t")  return LightingDirection::TOP;
    if (ooxml == "tr") return LightingDirection::TOP_RIGHT;
    if (ooxml == "r")  return LightingDirection::RIGHT;
    if (ooxml == "br") return LightingDirection::BOTTOM_RIGHT;
    if (ooxml == "b")  return LightingDirection::BOTTOM;
    if (ooxml == "bl") return LightingDirection::BOTTOM_LEFT;
    if (ooxml == "l")  return LightingDirection::LEFT;
    return LightingDirection::NOT_DEFINED;
}

/// Converts a LightingDirection to its OOXML dir attribute value.
constexpr std::string_view lighting_direction_to_ooxml(LightingDirection value) {
    switch (value) {
        case LightingDirection::TOP_LEFT:     return "tl";
        case LightingDirection::TOP:          return "t";
        case LightingDirection::TOP_RIGHT:    return "tr";
        case LightingDirection::RIGHT:        return "r";
        case LightingDirection::BOTTOM_RIGHT: return "br";
        case LightingDirection::BOTTOM:       return "b";
        case LightingDirection::BOTTOM_LEFT:  return "bl";
        case LightingDirection::LEFT:         return "l";
        case LightingDirection::NOT_DEFINED:  return "";
    }
    return "";
}

} // namespace Aspose::Slides::Foss
