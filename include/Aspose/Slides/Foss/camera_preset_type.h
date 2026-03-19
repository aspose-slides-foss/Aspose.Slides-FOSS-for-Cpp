// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define camera preset type.
enum class CameraPresetType {
    NOT_DEFINED,
    ISOMETRIC_BOTTOM_DOWN,
    ISOMETRIC_BOTTOM_UP,
    ISOMETRIC_LEFT_DOWN,
    ISOMETRIC_LEFT_UP,
    ISOMETRIC_OFF_AXIS_1_LEFT,
    ISOMETRIC_OFF_AXIS_1_RIGHT,
    ISOMETRIC_OFF_AXIS_1_TOP,
    ISOMETRIC_OFF_AXIS_2_LEFT,
    ISOMETRIC_OFF_AXIS_2_RIGHT,
    ISOMETRIC_OFF_AXIS_2_TOP,
    ISOMETRIC_OFF_AXIS_3_BOTTOM,
    ISOMETRIC_OFF_AXIS_3_LEFT,
    ISOMETRIC_OFF_AXIS_3_RIGHT,
    ISOMETRIC_OFF_AXIS_4_BOTTOM,
    ISOMETRIC_OFF_AXIS_4_LEFT,
    ISOMETRIC_OFF_AXIS_4_RIGHT,
    ISOMETRIC_RIGHT_DOWN,
    ISOMETRIC_RIGHT_UP,
    ISOMETRIC_TOP_DOWN,
    ISOMETRIC_TOP_UP,
    LEGACY_OBLIQUE_BOTTOM,
    LEGACY_OBLIQUE_BOTTOM_LEFT,
    LEGACY_OBLIQUE_BOTTOM_RIGHT,
    LEGACY_OBLIQUE_FRONT,
    LEGACY_OBLIQUE_LEFT,
    LEGACY_OBLIQUE_RIGHT,
    LEGACY_OBLIQUE_TOP,
    LEGACY_OBLIQUE_TOP_LEFT,
    LEGACY_OBLIQUE_TOP_RIGHT,
    LEGACY_PERSPECTIVE_BOTTOM,
    LEGACY_PERSPECTIVE_BOTTOM_LEFT,
    LEGACY_PERSPECTIVE_BOTTOM_RIGHT,
    LEGACY_PERSPECTIVE_FRONT,
    LEGACY_PERSPECTIVE_LEFT,
    LEGACY_PERSPECTIVE_RIGHT,
    LEGACY_PERSPECTIVE_TOP,
    LEGACY_PERSPECTIVE_TOP_LEFT,
    LEGACY_PERSPECTIVE_TOP_RIGHT,
    OBLIQUE_BOTTOM,
    OBLIQUE_BOTTOM_LEFT,
    OBLIQUE_BOTTOM_RIGHT,
    OBLIQUE_LEFT,
    OBLIQUE_RIGHT,
    OBLIQUE_TOP,
    OBLIQUE_TOP_LEFT,
    OBLIQUE_TOP_RIGHT,
    ORTHOGRAPHIC_FRONT,
    PERSPECTIVE_ABOVE,
    PERSPECTIVE_ABOVE_LEFT_FACING,
    PERSPECTIVE_ABOVE_RIGHT_FACING,
    PERSPECTIVE_BELOW,
    PERSPECTIVE_CONTRASTING_LEFT_FACING,
    PERSPECTIVE_CONTRASTING_RIGHT_FACING,
    PERSPECTIVE_FRONT,
    PERSPECTIVE_HEROIC_EXTREME_LEFT_FACING,
    PERSPECTIVE_HEROIC_EXTREME_RIGHT_FACING,
    PERSPECTIVE_HEROIC_LEFT_FACING,
    PERSPECTIVE_HEROIC_RIGHT_FACING,
    PERSPECTIVE_LEFT,
    PERSPECTIVE_RELAXED,
    PERSPECTIVE_RELAXED_MODERATELY,
    PERSPECTIVE_RIGHT,
};

/// Returns the string representation of a CameraPresetType value.
constexpr std::string_view to_string_view(CameraPresetType value) {
    switch (value) {
        case CameraPresetType::NOT_DEFINED: return "NotDefined";
        case CameraPresetType::ISOMETRIC_BOTTOM_DOWN: return "IsometricBottomDown";
        case CameraPresetType::ISOMETRIC_BOTTOM_UP: return "IsometricBottomUp";
        case CameraPresetType::ISOMETRIC_LEFT_DOWN: return "IsometricLeftDown";
        case CameraPresetType::ISOMETRIC_LEFT_UP: return "IsometricLeftUp";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_LEFT: return "IsometricOffAxis1Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_RIGHT: return "IsometricOffAxis1Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_TOP: return "IsometricOffAxis1Top";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_LEFT: return "IsometricOffAxis2Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_RIGHT: return "IsometricOffAxis2Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_TOP: return "IsometricOffAxis2Top";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_BOTTOM: return "IsometricOffAxis3Bottom";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_LEFT: return "IsometricOffAxis3Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_RIGHT: return "IsometricOffAxis3Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_BOTTOM: return "IsometricOffAxis4Bottom";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_LEFT: return "IsometricOffAxis4Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_RIGHT: return "IsometricOffAxis4Right";
        case CameraPresetType::ISOMETRIC_RIGHT_DOWN: return "IsometricRightDown";
        case CameraPresetType::ISOMETRIC_RIGHT_UP: return "IsometricRightUp";
        case CameraPresetType::ISOMETRIC_TOP_DOWN: return "IsometricTopDown";
        case CameraPresetType::ISOMETRIC_TOP_UP: return "IsometricTopUp";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM: return "LegacyObliqueBottom";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM_LEFT: return "LegacyObliqueBottomLeft";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM_RIGHT: return "LegacyObliqueBottomRight";
        case CameraPresetType::LEGACY_OBLIQUE_FRONT: return "LegacyObliqueFront";
        case CameraPresetType::LEGACY_OBLIQUE_LEFT: return "LegacyObliqueLeft";
        case CameraPresetType::LEGACY_OBLIQUE_RIGHT: return "LegacyObliqueRight";
        case CameraPresetType::LEGACY_OBLIQUE_TOP: return "LegacyObliqueTop";
        case CameraPresetType::LEGACY_OBLIQUE_TOP_LEFT: return "LegacyObliqueTopLeft";
        case CameraPresetType::LEGACY_OBLIQUE_TOP_RIGHT: return "LegacyObliqueTopRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM: return "LegacyPerspectiveBottom";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_LEFT: return "LegacyPerspectiveBottomLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_RIGHT: return "LegacyPerspectiveBottomRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_FRONT: return "LegacyPerspectiveFront";
        case CameraPresetType::LEGACY_PERSPECTIVE_LEFT: return "LegacyPerspectiveLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_RIGHT: return "LegacyPerspectiveRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP: return "LegacyPerspectiveTop";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP_LEFT: return "LegacyPerspectiveTopLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP_RIGHT: return "LegacyPerspectiveTopRight";
        case CameraPresetType::OBLIQUE_BOTTOM: return "ObliqueBottom";
        case CameraPresetType::OBLIQUE_BOTTOM_LEFT: return "ObliqueBottomLeft";
        case CameraPresetType::OBLIQUE_BOTTOM_RIGHT: return "ObliqueBottomRight";
        case CameraPresetType::OBLIQUE_LEFT: return "ObliqueLeft";
        case CameraPresetType::OBLIQUE_RIGHT: return "ObliqueRight";
        case CameraPresetType::OBLIQUE_TOP: return "ObliqueTop";
        case CameraPresetType::OBLIQUE_TOP_LEFT: return "ObliqueTopLeft";
        case CameraPresetType::OBLIQUE_TOP_RIGHT: return "ObliqueTopRight";
        case CameraPresetType::ORTHOGRAPHIC_FRONT: return "OrthographicFront";
        case CameraPresetType::PERSPECTIVE_ABOVE: return "PerspectiveAbove";
        case CameraPresetType::PERSPECTIVE_ABOVE_LEFT_FACING: return "PerspectiveAboveLeftFacing";
        case CameraPresetType::PERSPECTIVE_ABOVE_RIGHT_FACING: return "PerspectiveAboveRightFacing";
        case CameraPresetType::PERSPECTIVE_BELOW: return "PerspectiveBelow";
        case CameraPresetType::PERSPECTIVE_CONTRASTING_LEFT_FACING: return "PerspectiveContrastingLeftFacing";
        case CameraPresetType::PERSPECTIVE_CONTRASTING_RIGHT_FACING: return "PerspectiveContrastingRightFacing";
        case CameraPresetType::PERSPECTIVE_FRONT: return "PerspectiveFront";
        case CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_LEFT_FACING: return "PerspectiveHeroicExtremeLeftFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_RIGHT_FACING: return "PerspectiveHeroicExtremeRightFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_LEFT_FACING: return "PerspectiveHeroicLeftFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_RIGHT_FACING: return "PerspectiveHeroicRightFacing";
        case CameraPresetType::PERSPECTIVE_LEFT: return "PerspectiveLeft";
        case CameraPresetType::PERSPECTIVE_RELAXED: return "PerspectiveRelaxed";
        case CameraPresetType::PERSPECTIVE_RELAXED_MODERATELY: return "PerspectiveRelaxedModerately";
        case CameraPresetType::PERSPECTIVE_RIGHT: return "PerspectiveRight";
    }
    return "Unknown";
}

/// Converts an OOXML preset attribute value to CameraPresetType.
constexpr CameraPresetType camera_preset_type_from_ooxml(std::string_view ooxml) {
    if (ooxml == "isometricBottomDown")       return CameraPresetType::ISOMETRIC_BOTTOM_DOWN;
    if (ooxml == "isometricBottomUp")         return CameraPresetType::ISOMETRIC_BOTTOM_UP;
    if (ooxml == "isometricLeftDown")         return CameraPresetType::ISOMETRIC_LEFT_DOWN;
    if (ooxml == "isometricLeftUp")           return CameraPresetType::ISOMETRIC_LEFT_UP;
    if (ooxml == "isometricOffAxis1Left")     return CameraPresetType::ISOMETRIC_OFF_AXIS_1_LEFT;
    if (ooxml == "isometricOffAxis1Right")    return CameraPresetType::ISOMETRIC_OFF_AXIS_1_RIGHT;
    if (ooxml == "isometricOffAxis1Top")      return CameraPresetType::ISOMETRIC_OFF_AXIS_1_TOP;
    if (ooxml == "isometricOffAxis2Left")     return CameraPresetType::ISOMETRIC_OFF_AXIS_2_LEFT;
    if (ooxml == "isometricOffAxis2Right")    return CameraPresetType::ISOMETRIC_OFF_AXIS_2_RIGHT;
    if (ooxml == "isometricOffAxis2Top")      return CameraPresetType::ISOMETRIC_OFF_AXIS_2_TOP;
    if (ooxml == "isometricOffAxis3Bottom")   return CameraPresetType::ISOMETRIC_OFF_AXIS_3_BOTTOM;
    if (ooxml == "isometricOffAxis3Left")     return CameraPresetType::ISOMETRIC_OFF_AXIS_3_LEFT;
    if (ooxml == "isometricOffAxis3Right")    return CameraPresetType::ISOMETRIC_OFF_AXIS_3_RIGHT;
    if (ooxml == "isometricOffAxis4Bottom")   return CameraPresetType::ISOMETRIC_OFF_AXIS_4_BOTTOM;
    if (ooxml == "isometricOffAxis4Left")     return CameraPresetType::ISOMETRIC_OFF_AXIS_4_LEFT;
    if (ooxml == "isometricOffAxis4Right")    return CameraPresetType::ISOMETRIC_OFF_AXIS_4_RIGHT;
    if (ooxml == "isometricRightDown")        return CameraPresetType::ISOMETRIC_RIGHT_DOWN;
    if (ooxml == "isometricRightUp")          return CameraPresetType::ISOMETRIC_RIGHT_UP;
    if (ooxml == "isometricTopDown")          return CameraPresetType::ISOMETRIC_TOP_DOWN;
    if (ooxml == "isometricTopUp")            return CameraPresetType::ISOMETRIC_TOP_UP;
    if (ooxml == "legacyObliqueBottom")       return CameraPresetType::LEGACY_OBLIQUE_BOTTOM;
    if (ooxml == "legacyObliqueBottomLeft")   return CameraPresetType::LEGACY_OBLIQUE_BOTTOM_LEFT;
    if (ooxml == "legacyObliqueBottomRight")  return CameraPresetType::LEGACY_OBLIQUE_BOTTOM_RIGHT;
    if (ooxml == "legacyObliqueFront")        return CameraPresetType::LEGACY_OBLIQUE_FRONT;
    if (ooxml == "legacyObliqueLeft")         return CameraPresetType::LEGACY_OBLIQUE_LEFT;
    if (ooxml == "legacyObliqueRight")        return CameraPresetType::LEGACY_OBLIQUE_RIGHT;
    if (ooxml == "legacyObliqueTop")          return CameraPresetType::LEGACY_OBLIQUE_TOP;
    if (ooxml == "legacyObliqueTopLeft")      return CameraPresetType::LEGACY_OBLIQUE_TOP_LEFT;
    if (ooxml == "legacyObliqueTopRight")     return CameraPresetType::LEGACY_OBLIQUE_TOP_RIGHT;
    if (ooxml == "legacyPerspectiveBottom")      return CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM;
    if (ooxml == "legacyPerspectiveBottomLeft")  return CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_LEFT;
    if (ooxml == "legacyPerspectiveBottomRight") return CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_RIGHT;
    if (ooxml == "legacyPerspectiveFront")       return CameraPresetType::LEGACY_PERSPECTIVE_FRONT;
    if (ooxml == "legacyPerspectiveLeft")         return CameraPresetType::LEGACY_PERSPECTIVE_LEFT;
    if (ooxml == "legacyPerspectiveRight")        return CameraPresetType::LEGACY_PERSPECTIVE_RIGHT;
    if (ooxml == "legacyPerspectiveTop")          return CameraPresetType::LEGACY_PERSPECTIVE_TOP;
    if (ooxml == "legacyPerspectiveTopLeft")      return CameraPresetType::LEGACY_PERSPECTIVE_TOP_LEFT;
    if (ooxml == "legacyPerspectiveTopRight")     return CameraPresetType::LEGACY_PERSPECTIVE_TOP_RIGHT;
    if (ooxml == "obliqueBottom")             return CameraPresetType::OBLIQUE_BOTTOM;
    if (ooxml == "obliqueBottomLeft")         return CameraPresetType::OBLIQUE_BOTTOM_LEFT;
    if (ooxml == "obliqueBottomRight")        return CameraPresetType::OBLIQUE_BOTTOM_RIGHT;
    if (ooxml == "obliqueLeft")               return CameraPresetType::OBLIQUE_LEFT;
    if (ooxml == "obliqueRight")              return CameraPresetType::OBLIQUE_RIGHT;
    if (ooxml == "obliqueTop")                return CameraPresetType::OBLIQUE_TOP;
    if (ooxml == "obliqueTopLeft")            return CameraPresetType::OBLIQUE_TOP_LEFT;
    if (ooxml == "obliqueTopRight")           return CameraPresetType::OBLIQUE_TOP_RIGHT;
    if (ooxml == "orthographicFront")         return CameraPresetType::ORTHOGRAPHIC_FRONT;
    if (ooxml == "perspectiveAbove")          return CameraPresetType::PERSPECTIVE_ABOVE;
    if (ooxml == "perspectiveAboveLeftFacing")    return CameraPresetType::PERSPECTIVE_ABOVE_LEFT_FACING;
    if (ooxml == "perspectiveAboveRightFacing")   return CameraPresetType::PERSPECTIVE_ABOVE_RIGHT_FACING;
    if (ooxml == "perspectiveBelow")              return CameraPresetType::PERSPECTIVE_BELOW;
    if (ooxml == "perspectiveContrastingLeftFacing")  return CameraPresetType::PERSPECTIVE_CONTRASTING_LEFT_FACING;
    if (ooxml == "perspectiveContrastingRightFacing") return CameraPresetType::PERSPECTIVE_CONTRASTING_RIGHT_FACING;
    if (ooxml == "perspectiveFront")                  return CameraPresetType::PERSPECTIVE_FRONT;
    if (ooxml == "perspectiveHeroicExtremeLeftFacing")  return CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_LEFT_FACING;
    if (ooxml == "perspectiveHeroicExtremeRightFacing") return CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_RIGHT_FACING;
    if (ooxml == "perspectiveHeroicLeftFacing")    return CameraPresetType::PERSPECTIVE_HEROIC_LEFT_FACING;
    if (ooxml == "perspectiveHeroicRightFacing")   return CameraPresetType::PERSPECTIVE_HEROIC_RIGHT_FACING;
    if (ooxml == "perspectiveLeft")                return CameraPresetType::PERSPECTIVE_LEFT;
    if (ooxml == "perspectiveRelaxed")             return CameraPresetType::PERSPECTIVE_RELAXED;
    if (ooxml == "perspectiveRelaxedModerately")   return CameraPresetType::PERSPECTIVE_RELAXED_MODERATELY;
    if (ooxml == "perspectiveRight")               return CameraPresetType::PERSPECTIVE_RIGHT;
    return CameraPresetType::NOT_DEFINED;
}

/// Converts a CameraPresetType to its OOXML preset attribute value.
constexpr std::string_view camera_preset_type_to_ooxml(CameraPresetType value) {
    switch (value) {
        case CameraPresetType::ISOMETRIC_BOTTOM_DOWN:       return "isometricBottomDown";
        case CameraPresetType::ISOMETRIC_BOTTOM_UP:         return "isometricBottomUp";
        case CameraPresetType::ISOMETRIC_LEFT_DOWN:         return "isometricLeftDown";
        case CameraPresetType::ISOMETRIC_LEFT_UP:           return "isometricLeftUp";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_LEFT:   return "isometricOffAxis1Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_RIGHT:  return "isometricOffAxis1Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_1_TOP:    return "isometricOffAxis1Top";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_LEFT:   return "isometricOffAxis2Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_RIGHT:  return "isometricOffAxis2Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_2_TOP:    return "isometricOffAxis2Top";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_BOTTOM: return "isometricOffAxis3Bottom";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_LEFT:   return "isometricOffAxis3Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_3_RIGHT:  return "isometricOffAxis3Right";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_BOTTOM: return "isometricOffAxis4Bottom";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_LEFT:   return "isometricOffAxis4Left";
        case CameraPresetType::ISOMETRIC_OFF_AXIS_4_RIGHT:  return "isometricOffAxis4Right";
        case CameraPresetType::ISOMETRIC_RIGHT_DOWN:        return "isometricRightDown";
        case CameraPresetType::ISOMETRIC_RIGHT_UP:          return "isometricRightUp";
        case CameraPresetType::ISOMETRIC_TOP_DOWN:          return "isometricTopDown";
        case CameraPresetType::ISOMETRIC_TOP_UP:            return "isometricTopUp";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM:       return "legacyObliqueBottom";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM_LEFT:  return "legacyObliqueBottomLeft";
        case CameraPresetType::LEGACY_OBLIQUE_BOTTOM_RIGHT: return "legacyObliqueBottomRight";
        case CameraPresetType::LEGACY_OBLIQUE_FRONT:        return "legacyObliqueFront";
        case CameraPresetType::LEGACY_OBLIQUE_LEFT:         return "legacyObliqueLeft";
        case CameraPresetType::LEGACY_OBLIQUE_RIGHT:        return "legacyObliqueRight";
        case CameraPresetType::LEGACY_OBLIQUE_TOP:          return "legacyObliqueTop";
        case CameraPresetType::LEGACY_OBLIQUE_TOP_LEFT:     return "legacyObliqueTopLeft";
        case CameraPresetType::LEGACY_OBLIQUE_TOP_RIGHT:    return "legacyObliqueTopRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM:       return "legacyPerspectiveBottom";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_LEFT:  return "legacyPerspectiveBottomLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_BOTTOM_RIGHT: return "legacyPerspectiveBottomRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_FRONT:        return "legacyPerspectiveFront";
        case CameraPresetType::LEGACY_PERSPECTIVE_LEFT:         return "legacyPerspectiveLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_RIGHT:        return "legacyPerspectiveRight";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP:          return "legacyPerspectiveTop";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP_LEFT:     return "legacyPerspectiveTopLeft";
        case CameraPresetType::LEGACY_PERSPECTIVE_TOP_RIGHT:    return "legacyPerspectiveTopRight";
        case CameraPresetType::OBLIQUE_BOTTOM:              return "obliqueBottom";
        case CameraPresetType::OBLIQUE_BOTTOM_LEFT:         return "obliqueBottomLeft";
        case CameraPresetType::OBLIQUE_BOTTOM_RIGHT:        return "obliqueBottomRight";
        case CameraPresetType::OBLIQUE_LEFT:                return "obliqueLeft";
        case CameraPresetType::OBLIQUE_RIGHT:               return "obliqueRight";
        case CameraPresetType::OBLIQUE_TOP:                 return "obliqueTop";
        case CameraPresetType::OBLIQUE_TOP_LEFT:            return "obliqueTopLeft";
        case CameraPresetType::OBLIQUE_TOP_RIGHT:           return "obliqueTopRight";
        case CameraPresetType::ORTHOGRAPHIC_FRONT:          return "orthographicFront";
        case CameraPresetType::PERSPECTIVE_ABOVE:               return "perspectiveAbove";
        case CameraPresetType::PERSPECTIVE_ABOVE_LEFT_FACING:   return "perspectiveAboveLeftFacing";
        case CameraPresetType::PERSPECTIVE_ABOVE_RIGHT_FACING:  return "perspectiveAboveRightFacing";
        case CameraPresetType::PERSPECTIVE_BELOW:               return "perspectiveBelow";
        case CameraPresetType::PERSPECTIVE_CONTRASTING_LEFT_FACING:  return "perspectiveContrastingLeftFacing";
        case CameraPresetType::PERSPECTIVE_CONTRASTING_RIGHT_FACING: return "perspectiveContrastingRightFacing";
        case CameraPresetType::PERSPECTIVE_FRONT:                    return "perspectiveFront";
        case CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_LEFT_FACING:  return "perspectiveHeroicExtremeLeftFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_EXTREME_RIGHT_FACING: return "perspectiveHeroicExtremeRightFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_LEFT_FACING:  return "perspectiveHeroicLeftFacing";
        case CameraPresetType::PERSPECTIVE_HEROIC_RIGHT_FACING: return "perspectiveHeroicRightFacing";
        case CameraPresetType::PERSPECTIVE_LEFT:                return "perspectiveLeft";
        case CameraPresetType::PERSPECTIVE_RELAXED:             return "perspectiveRelaxed";
        case CameraPresetType::PERSPECTIVE_RELAXED_MODERATELY:  return "perspectiveRelaxedModerately";
        case CameraPresetType::PERSPECTIVE_RIGHT:               return "perspectiveRight";
        case CameraPresetType::NOT_DEFINED:                     return "";
    }
    return "";
}

} // namespace Aspose::Slides::Foss
