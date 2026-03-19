// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the gradient style.
enum class GradientDirection {
    NOT_DEFINED,
    FROM_CORNER1,
    FROM_CORNER2,
    FROM_CORNER3,
    FROM_CORNER4,
    FROM_CENTER,
};

/// Returns the string representation of a GradientDirection value.
constexpr std::string_view to_string_view(GradientDirection value) {
    switch (value) {
        case GradientDirection::NOT_DEFINED: return "NotDefined";
        case GradientDirection::FROM_CORNER1: return "FromCorner1";
        case GradientDirection::FROM_CORNER2: return "FromCorner2";
        case GradientDirection::FROM_CORNER3: return "FromCorner3";
        case GradientDirection::FROM_CORNER4: return "FromCorner4";
        case GradientDirection::FROM_CENTER: return "FromCenter";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
