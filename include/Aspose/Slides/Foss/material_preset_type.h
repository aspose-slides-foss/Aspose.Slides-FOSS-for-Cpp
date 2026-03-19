// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define material of shape.
enum class MaterialPresetType {
    NOT_DEFINED,
    CLEAR,
    DK_EDGE,
    FLAT,
    LEGACY_MATTE,
    LEGACY_METAL,
    LEGACY_PLASTIC,
    LEGACY_WIREFRAME,
    MATTE,
    METAL,
    PLASTIC,
    POWDER,
    SOFT_EDGE,
    SOFTMETAL,
    TRANSLUCENT_POWDER,
    WARM_MATTE,
};

/// Returns the string representation of a MaterialPresetType value.
constexpr std::string_view to_string_view(MaterialPresetType value) {
    switch (value) {
        case MaterialPresetType::NOT_DEFINED: return "NotDefined";
        case MaterialPresetType::CLEAR: return "Clear";
        case MaterialPresetType::DK_EDGE: return "DkEdge";
        case MaterialPresetType::FLAT: return "Flat";
        case MaterialPresetType::LEGACY_MATTE: return "LegacyMatte";
        case MaterialPresetType::LEGACY_METAL: return "LegacyMetal";
        case MaterialPresetType::LEGACY_PLASTIC: return "LegacyPlastic";
        case MaterialPresetType::LEGACY_WIREFRAME: return "LegacyWireframe";
        case MaterialPresetType::MATTE: return "Matte";
        case MaterialPresetType::METAL: return "Metal";
        case MaterialPresetType::PLASTIC: return "Plastic";
        case MaterialPresetType::POWDER: return "Powder";
        case MaterialPresetType::SOFT_EDGE: return "SoftEdge";
        case MaterialPresetType::SOFTMETAL: return "Softmetal";
        case MaterialPresetType::TRANSLUCENT_POWDER: return "TranslucentPowder";
        case MaterialPresetType::WARM_MATTE: return "WarmMatte";
    }
    return "Unknown";
}

/// Converts an OOXML prstMaterial attribute value to MaterialPresetType.
constexpr MaterialPresetType material_preset_type_from_ooxml(std::string_view ooxml) {
    if (ooxml == "clear")             return MaterialPresetType::CLEAR;
    if (ooxml == "dkEdge")            return MaterialPresetType::DK_EDGE;
    if (ooxml == "flat")              return MaterialPresetType::FLAT;
    if (ooxml == "legacyMatte")       return MaterialPresetType::LEGACY_MATTE;
    if (ooxml == "legacyMetal")       return MaterialPresetType::LEGACY_METAL;
    if (ooxml == "legacyPlastic")     return MaterialPresetType::LEGACY_PLASTIC;
    if (ooxml == "legacyWireframe")   return MaterialPresetType::LEGACY_WIREFRAME;
    if (ooxml == "matte")             return MaterialPresetType::MATTE;
    if (ooxml == "metal")             return MaterialPresetType::METAL;
    if (ooxml == "plastic")           return MaterialPresetType::PLASTIC;
    if (ooxml == "powder")            return MaterialPresetType::POWDER;
    if (ooxml == "softEdge")          return MaterialPresetType::SOFT_EDGE;
    if (ooxml == "softmetal")         return MaterialPresetType::SOFTMETAL;
    if (ooxml == "translucentPowder") return MaterialPresetType::TRANSLUCENT_POWDER;
    if (ooxml == "warmMatte")         return MaterialPresetType::WARM_MATTE;
    return MaterialPresetType::NOT_DEFINED;
}

/// Converts a MaterialPresetType to its OOXML prstMaterial attribute value.
constexpr std::string_view material_preset_type_to_ooxml(MaterialPresetType value) {
    switch (value) {
        case MaterialPresetType::CLEAR:              return "clear";
        case MaterialPresetType::DK_EDGE:            return "dkEdge";
        case MaterialPresetType::FLAT:               return "flat";
        case MaterialPresetType::LEGACY_MATTE:       return "legacyMatte";
        case MaterialPresetType::LEGACY_METAL:       return "legacyMetal";
        case MaterialPresetType::LEGACY_PLASTIC:     return "legacyPlastic";
        case MaterialPresetType::LEGACY_WIREFRAME:   return "legacyWireframe";
        case MaterialPresetType::MATTE:              return "matte";
        case MaterialPresetType::METAL:              return "metal";
        case MaterialPresetType::PLASTIC:            return "plastic";
        case MaterialPresetType::POWDER:             return "powder";
        case MaterialPresetType::SOFT_EDGE:          return "softEdge";
        case MaterialPresetType::SOFTMETAL:          return "softmetal";
        case MaterialPresetType::TRANSLUCENT_POWDER: return "translucentPowder";
        case MaterialPresetType::WARM_MATTE:         return "warmMatte";
        case MaterialPresetType::NOT_DEFINED:        return "";
    }
    return "";
}

} // namespace Aspose::Slides::Foss
