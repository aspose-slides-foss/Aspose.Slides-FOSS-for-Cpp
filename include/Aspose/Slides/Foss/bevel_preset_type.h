// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define 3D bevel of shape.
enum class BevelPresetType {
    NOT_DEFINED,
    ANGLE,
    ART_DECO,
    CIRCLE,
    CONVEX,
    COOL_SLANT,
    CROSS,
    DIVOT,
    HARD_EDGE,
    RELAXED_INSET,
    RIBLET,
    SLOPE,
    SOFT_ROUND,
};

/// Returns the string representation of a BevelPresetType value.
constexpr std::string_view to_string_view(BevelPresetType value) {
    switch (value) {
        case BevelPresetType::NOT_DEFINED: return "NotDefined";
        case BevelPresetType::ANGLE: return "Angle";
        case BevelPresetType::ART_DECO: return "ArtDeco";
        case BevelPresetType::CIRCLE: return "Circle";
        case BevelPresetType::CONVEX: return "Convex";
        case BevelPresetType::COOL_SLANT: return "CoolSlant";
        case BevelPresetType::CROSS: return "Cross";
        case BevelPresetType::DIVOT: return "Divot";
        case BevelPresetType::HARD_EDGE: return "HardEdge";
        case BevelPresetType::RELAXED_INSET: return "RelaxedInset";
        case BevelPresetType::RIBLET: return "Riblet";
        case BevelPresetType::SLOPE: return "Slope";
        case BevelPresetType::SOFT_ROUND: return "SoftRound";
    }
    return "Unknown";
}

/// Converts an OOXML preset attribute value to BevelPresetType.
constexpr BevelPresetType bevel_preset_type_from_ooxml(std::string_view ooxml) {
    if (ooxml == "angle")        return BevelPresetType::ANGLE;
    if (ooxml == "artDeco")      return BevelPresetType::ART_DECO;
    if (ooxml == "circle")       return BevelPresetType::CIRCLE;
    if (ooxml == "convex")       return BevelPresetType::CONVEX;
    if (ooxml == "coolSlant")    return BevelPresetType::COOL_SLANT;
    if (ooxml == "cross")        return BevelPresetType::CROSS;
    if (ooxml == "divot")        return BevelPresetType::DIVOT;
    if (ooxml == "hardEdge")     return BevelPresetType::HARD_EDGE;
    if (ooxml == "relaxedInset") return BevelPresetType::RELAXED_INSET;
    if (ooxml == "riblet")       return BevelPresetType::RIBLET;
    if (ooxml == "slope")        return BevelPresetType::SLOPE;
    if (ooxml == "softRound")    return BevelPresetType::SOFT_ROUND;
    return BevelPresetType::NOT_DEFINED;
}

/// Converts a BevelPresetType to its OOXML preset attribute value.
/// Returns an empty string_view for NOT_DEFINED.
constexpr std::string_view bevel_preset_type_to_ooxml(BevelPresetType value) {
    switch (value) {
        case BevelPresetType::ANGLE:         return "angle";
        case BevelPresetType::ART_DECO:      return "artDeco";
        case BevelPresetType::CIRCLE:        return "circle";
        case BevelPresetType::CONVEX:        return "convex";
        case BevelPresetType::COOL_SLANT:    return "coolSlant";
        case BevelPresetType::CROSS:         return "cross";
        case BevelPresetType::DIVOT:         return "divot";
        case BevelPresetType::HARD_EDGE:     return "hardEdge";
        case BevelPresetType::RELAXED_INSET: return "relaxedInset";
        case BevelPresetType::RIBLET:        return "riblet";
        case BevelPresetType::SLOPE:         return "slope";
        case BevelPresetType::SOFT_ROUND:    return "softRound";
        case BevelPresetType::NOT_DEFINED:   return "";
    }
    return "";
}

} // namespace Aspose::Slides::Foss
