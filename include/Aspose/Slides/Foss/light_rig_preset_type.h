// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define light preset types.
enum class LightRigPresetType {
    NOT_DEFINED,
    BALANCED,
    BRIGHT_ROOM,
    CHILLY,
    CONTRASTING,
    FLAT,
    FLOOD,
    FREEZING,
    GLOW,
    HARSH,
    LEGACY_FLAT1,
    LEGACY_FLAT2,
    LEGACY_FLAT3,
    LEGACY_FLAT4,
    LEGACY_HARSH1,
    LEGACY_HARSH2,
    LEGACY_HARSH3,
    LEGACY_HARSH4,
    LEGACY_NORMAL1,
    LEGACY_NORMAL2,
    LEGACY_NORMAL3,
    LEGACY_NORMAL4,
    MORNING,
    SOFT,
    SUNRISE,
    SUNSET,
    THREE_PT,
    TWO_PT,
};

/// Returns the string representation of a LightRigPresetType value.
constexpr std::string_view to_string_view(LightRigPresetType value) {
    switch (value) {
        case LightRigPresetType::NOT_DEFINED: return "NotDefined";
        case LightRigPresetType::BALANCED: return "Balanced";
        case LightRigPresetType::BRIGHT_ROOM: return "BrightRoom";
        case LightRigPresetType::CHILLY: return "Chilly";
        case LightRigPresetType::CONTRASTING: return "Contrasting";
        case LightRigPresetType::FLAT: return "Flat";
        case LightRigPresetType::FLOOD: return "Flood";
        case LightRigPresetType::FREEZING: return "Freezing";
        case LightRigPresetType::GLOW: return "Glow";
        case LightRigPresetType::HARSH: return "Harsh";
        case LightRigPresetType::LEGACY_FLAT1: return "LegacyFlat1";
        case LightRigPresetType::LEGACY_FLAT2: return "LegacyFlat2";
        case LightRigPresetType::LEGACY_FLAT3: return "LegacyFlat3";
        case LightRigPresetType::LEGACY_FLAT4: return "LegacyFlat4";
        case LightRigPresetType::LEGACY_HARSH1: return "LegacyHarsh1";
        case LightRigPresetType::LEGACY_HARSH2: return "LegacyHarsh2";
        case LightRigPresetType::LEGACY_HARSH3: return "LegacyHarsh3";
        case LightRigPresetType::LEGACY_HARSH4: return "LegacyHarsh4";
        case LightRigPresetType::LEGACY_NORMAL1: return "LegacyNormal1";
        case LightRigPresetType::LEGACY_NORMAL2: return "LegacyNormal2";
        case LightRigPresetType::LEGACY_NORMAL3: return "LegacyNormal3";
        case LightRigPresetType::LEGACY_NORMAL4: return "LegacyNormal4";
        case LightRigPresetType::MORNING: return "Morning";
        case LightRigPresetType::SOFT: return "Soft";
        case LightRigPresetType::SUNRISE: return "Sunrise";
        case LightRigPresetType::SUNSET: return "Sunset";
        case LightRigPresetType::THREE_PT: return "ThreePt";
        case LightRigPresetType::TWO_PT: return "TwoPt";
    }
    return "Unknown";
}

/// Converts an OOXML rig attribute value to LightRigPresetType.
constexpr LightRigPresetType light_rig_preset_type_from_ooxml(std::string_view ooxml) {
    if (ooxml == "balanced")      return LightRigPresetType::BALANCED;
    if (ooxml == "brightRoom")    return LightRigPresetType::BRIGHT_ROOM;
    if (ooxml == "chilly")        return LightRigPresetType::CHILLY;
    if (ooxml == "contrasting")   return LightRigPresetType::CONTRASTING;
    if (ooxml == "flat")          return LightRigPresetType::FLAT;
    if (ooxml == "flood")         return LightRigPresetType::FLOOD;
    if (ooxml == "freezing")      return LightRigPresetType::FREEZING;
    if (ooxml == "glow")          return LightRigPresetType::GLOW;
    if (ooxml == "harsh")         return LightRigPresetType::HARSH;
    if (ooxml == "legacyFlat1")   return LightRigPresetType::LEGACY_FLAT1;
    if (ooxml == "legacyFlat2")   return LightRigPresetType::LEGACY_FLAT2;
    if (ooxml == "legacyFlat3")   return LightRigPresetType::LEGACY_FLAT3;
    if (ooxml == "legacyFlat4")   return LightRigPresetType::LEGACY_FLAT4;
    if (ooxml == "legacyHarsh1")  return LightRigPresetType::LEGACY_HARSH1;
    if (ooxml == "legacyHarsh2")  return LightRigPresetType::LEGACY_HARSH2;
    if (ooxml == "legacyHarsh3")  return LightRigPresetType::LEGACY_HARSH3;
    if (ooxml == "legacyHarsh4")  return LightRigPresetType::LEGACY_HARSH4;
    if (ooxml == "legacyNormal1") return LightRigPresetType::LEGACY_NORMAL1;
    if (ooxml == "legacyNormal2") return LightRigPresetType::LEGACY_NORMAL2;
    if (ooxml == "legacyNormal3") return LightRigPresetType::LEGACY_NORMAL3;
    if (ooxml == "legacyNormal4") return LightRigPresetType::LEGACY_NORMAL4;
    if (ooxml == "morning")       return LightRigPresetType::MORNING;
    if (ooxml == "soft")          return LightRigPresetType::SOFT;
    if (ooxml == "sunrise")       return LightRigPresetType::SUNRISE;
    if (ooxml == "sunset")        return LightRigPresetType::SUNSET;
    if (ooxml == "threePt")       return LightRigPresetType::THREE_PT;
    if (ooxml == "twoPt")         return LightRigPresetType::TWO_PT;
    return LightRigPresetType::NOT_DEFINED;
}

/// Converts a LightRigPresetType to its OOXML rig attribute value.
constexpr std::string_view light_rig_preset_type_to_ooxml(LightRigPresetType value) {
    switch (value) {
        case LightRigPresetType::BALANCED:       return "balanced";
        case LightRigPresetType::BRIGHT_ROOM:    return "brightRoom";
        case LightRigPresetType::CHILLY:         return "chilly";
        case LightRigPresetType::CONTRASTING:    return "contrasting";
        case LightRigPresetType::FLAT:           return "flat";
        case LightRigPresetType::FLOOD:          return "flood";
        case LightRigPresetType::FREEZING:       return "freezing";
        case LightRigPresetType::GLOW:           return "glow";
        case LightRigPresetType::HARSH:          return "harsh";
        case LightRigPresetType::LEGACY_FLAT1:   return "legacyFlat1";
        case LightRigPresetType::LEGACY_FLAT2:   return "legacyFlat2";
        case LightRigPresetType::LEGACY_FLAT3:   return "legacyFlat3";
        case LightRigPresetType::LEGACY_FLAT4:   return "legacyFlat4";
        case LightRigPresetType::LEGACY_HARSH1:  return "legacyHarsh1";
        case LightRigPresetType::LEGACY_HARSH2:  return "legacyHarsh2";
        case LightRigPresetType::LEGACY_HARSH3:  return "legacyHarsh3";
        case LightRigPresetType::LEGACY_HARSH4:  return "legacyHarsh4";
        case LightRigPresetType::LEGACY_NORMAL1: return "legacyNormal1";
        case LightRigPresetType::LEGACY_NORMAL2: return "legacyNormal2";
        case LightRigPresetType::LEGACY_NORMAL3: return "legacyNormal3";
        case LightRigPresetType::LEGACY_NORMAL4: return "legacyNormal4";
        case LightRigPresetType::MORNING:        return "morning";
        case LightRigPresetType::SOFT:           return "soft";
        case LightRigPresetType::SUNRISE:        return "sunrise";
        case LightRigPresetType::SUNSET:         return "sunset";
        case LightRigPresetType::THREE_PT:       return "threePt";
        case LightRigPresetType::TWO_PT:         return "twoPt";
        case LightRigPresetType::NOT_DEFINED:    return "";
    }
    return "";
}

} // namespace Aspose::Slides::Foss
