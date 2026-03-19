// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents a preset for a shadow effect.
enum class PresetShadowType {
    TOP_LEFT_DROP_SHADOW,
    TOP_LEFT_LARGE_DROP_SHADOW,
    BACK_LEFT_LONG_PERSPECTIVE_SHADOW,
    BACK_RIGHT_LONG_PERSPECTIVE_SHADOW,
    TOP_LEFT_DOUBLE_DROP_SHADOW,
    BOTTOM_RIGHT_SMALL_DROP_SHADOW,
    FRONT_LEFT_LONG_PERSPECTIVE_SHADOW,
    FRONT_RIGHT_LONG_PERSPECTIVE_SHADOW,
    OUTER_BOX_SHADOW3_D,
    INNER_BOX_SHADOW3_D,
    BACK_CENTER_PERSPECTIVE_SHADOW,
    TOP_RIGHT_DROP_SHADOW,
    FRONT_BOTTOM_SHADOW,
    BACK_LEFT_PERSPECTIVE_SHADOW,
    BACK_RIGHT_PERSPECTIVE_SHADOW,
    BOTTOM_LEFT_DROP_SHADOW,
    BOTTOM_RIGHT_DROP_SHADOW,
    FRONT_LEFT_PERSPECTIVE_SHADOW,
    FRONT_RIGHT_PERSPECTIVE_SHADOW,
    TOP_LEFT_SMALL_DROP_SHADOW,
};

/// Returns the string representation of a PresetShadowType value.
constexpr std::string_view to_string_view(PresetShadowType value) {
    switch (value) {
        case PresetShadowType::TOP_LEFT_DROP_SHADOW: return "TopLeftDropShadow";
        case PresetShadowType::TOP_LEFT_LARGE_DROP_SHADOW: return "TopLeftLargeDropShadow";
        case PresetShadowType::BACK_LEFT_LONG_PERSPECTIVE_SHADOW: return "BackLeftLongPerspectiveShadow";
        case PresetShadowType::BACK_RIGHT_LONG_PERSPECTIVE_SHADOW: return "BackRightLongPerspectiveShadow";
        case PresetShadowType::TOP_LEFT_DOUBLE_DROP_SHADOW: return "TopLeftDoubleDropShadow";
        case PresetShadowType::BOTTOM_RIGHT_SMALL_DROP_SHADOW: return "BottomRightSmallDropShadow";
        case PresetShadowType::FRONT_LEFT_LONG_PERSPECTIVE_SHADOW: return "FrontLeftLongPerspectiveShadow";
        case PresetShadowType::FRONT_RIGHT_LONG_PERSPECTIVE_SHADOW: return "FrontRightLongPerspectiveShadow";
        case PresetShadowType::OUTER_BOX_SHADOW3_D: return "OuterBoxShadow3D";
        case PresetShadowType::INNER_BOX_SHADOW3_D: return "InnerBoxShadow3D";
        case PresetShadowType::BACK_CENTER_PERSPECTIVE_SHADOW: return "BackCenterPerspectiveShadow";
        case PresetShadowType::TOP_RIGHT_DROP_SHADOW: return "TopRightDropShadow";
        case PresetShadowType::FRONT_BOTTOM_SHADOW: return "FrontBottomShadow";
        case PresetShadowType::BACK_LEFT_PERSPECTIVE_SHADOW: return "BackLeftPerspectiveShadow";
        case PresetShadowType::BACK_RIGHT_PERSPECTIVE_SHADOW: return "BackRightPerspectiveShadow";
        case PresetShadowType::BOTTOM_LEFT_DROP_SHADOW: return "BottomLeftDropShadow";
        case PresetShadowType::BOTTOM_RIGHT_DROP_SHADOW: return "BottomRightDropShadow";
        case PresetShadowType::FRONT_LEFT_PERSPECTIVE_SHADOW: return "FrontLeftPerspectiveShadow";
        case PresetShadowType::FRONT_RIGHT_PERSPECTIVE_SHADOW: return "FrontRightPerspectiveShadow";
        case PresetShadowType::TOP_LEFT_SMALL_DROP_SHADOW: return "TopLeftSmallDropShadow";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
