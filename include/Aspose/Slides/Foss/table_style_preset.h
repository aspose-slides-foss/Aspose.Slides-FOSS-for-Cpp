// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents builtin table styles.
enum class TableStylePreset {
    CUSTOM,
    NONE,
    MEDIUM_STYLE2_ACCENT1,
    MEDIUM_STYLE2,
    NO_STYLE_NO_GRID,
    THEMED_STYLE1_ACCENT1,
    THEMED_STYLE1_ACCENT2,
    THEMED_STYLE1_ACCENT3,
    THEMED_STYLE1_ACCENT4,
    THEMED_STYLE1_ACCENT5,
    THEMED_STYLE1_ACCENT6,
    NO_STYLE_TABLE_GRID,
    THEMED_STYLE2_ACCENT1,
    THEMED_STYLE2_ACCENT2,
    THEMED_STYLE2_ACCENT3,
    THEMED_STYLE2_ACCENT4,
    THEMED_STYLE2_ACCENT5,
    THEMED_STYLE2_ACCENT6,
    LIGHT_STYLE1,
    LIGHT_STYLE1_ACCENT1,
    LIGHT_STYLE1_ACCENT2,
    LIGHT_STYLE1_ACCENT3,
    LIGHT_STYLE1_ACCENT4,
    LIGHT_STYLE2_ACCENT5,
    LIGHT_STYLE1_ACCENT6,
    LIGHT_STYLE2,
    LIGHT_STYLE2_ACCENT1,
    LIGHT_STYLE2_ACCENT2,
    LIGHT_STYLE2_ACCENT3,
    MEDIUM_STYLE2_ACCENT3,
    MEDIUM_STYLE2_ACCENT4,
    MEDIUM_STYLE2_ACCENT5,
    LIGHT_STYLE2_ACCENT6,
    LIGHT_STYLE2_ACCENT4,
    LIGHT_STYLE3,
    LIGHT_STYLE3_ACCENT1,
    MEDIUM_STYLE2_ACCENT2,
    LIGHT_STYLE3_ACCENT2,
    LIGHT_STYLE3_ACCENT3,
    LIGHT_STYLE3_ACCENT4,
    LIGHT_STYLE3_ACCENT5,
    LIGHT_STYLE3_ACCENT6,
    MEDIUM_STYLE1,
    MEDIUM_STYLE1_ACCENT1,
    MEDIUM_STYLE1_ACCENT2,
    MEDIUM_STYLE1_ACCENT3,
    MEDIUM_STYLE1_ACCENT4,
    MEDIUM_STYLE1_ACCENT5,
    MEDIUM_STYLE1_ACCENT6,
    MEDIUM_STYLE2_ACCENT6,
    MEDIUM_STYLE3,
    MEDIUM_STYLE3_ACCENT1,
    MEDIUM_STYLE3_ACCENT2,
    MEDIUM_STYLE3_ACCENT3,
    MEDIUM_STYLE3_ACCENT4,
    MEDIUM_STYLE3_ACCENT5,
    MEDIUM_STYLE3_ACCENT6,
    MEDIUM_STYLE4,
    MEDIUM_STYLE4_ACCENT1,
    MEDIUM_STYLE4_ACCENT2,
    MEDIUM_STYLE4_ACCENT3,
    MEDIUM_STYLE4_ACCENT4,
    MEDIUM_STYLE4_ACCENT5,
    MEDIUM_STYLE4_ACCENT6,
    DARK_STYLE1,
    DARK_STYLE1_ACCENT1,
    DARK_STYLE1_ACCENT2,
    DARK_STYLE1_ACCENT3,
    DARK_STYLE1_ACCENT4,
    DARK_STYLE1_ACCENT5,
    DARK_STYLE1_ACCENT6,
    DARK_STYLE2,
    DARK_STYLE2_ACCENT1_ACCENT2,
    DARK_STYLE2_ACCENT3_ACCENT4,
    DARK_STYLE2_ACCENT5_ACCENT6,
    LIGHT_STYLE1_ACCENT5,
};

/// Returns the string representation of a TableStylePreset value.
constexpr std::string_view to_string_view(TableStylePreset value) {
    switch (value) {
        case TableStylePreset::CUSTOM: return "Custom";
        case TableStylePreset::NONE: return "None";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT1: return "MediumStyle2Accent1";
        case TableStylePreset::MEDIUM_STYLE2: return "MediumStyle2";
        case TableStylePreset::NO_STYLE_NO_GRID: return "NoStyleNoGrid";
        case TableStylePreset::THEMED_STYLE1_ACCENT1: return "ThemedStyle1Accent1";
        case TableStylePreset::THEMED_STYLE1_ACCENT2: return "ThemedStyle1Accent2";
        case TableStylePreset::THEMED_STYLE1_ACCENT3: return "ThemedStyle1Accent3";
        case TableStylePreset::THEMED_STYLE1_ACCENT4: return "ThemedStyle1Accent4";
        case TableStylePreset::THEMED_STYLE1_ACCENT5: return "ThemedStyle1Accent5";
        case TableStylePreset::THEMED_STYLE1_ACCENT6: return "ThemedStyle1Accent6";
        case TableStylePreset::NO_STYLE_TABLE_GRID: return "NoStyleTableGrid";
        case TableStylePreset::THEMED_STYLE2_ACCENT1: return "ThemedStyle2Accent1";
        case TableStylePreset::THEMED_STYLE2_ACCENT2: return "ThemedStyle2Accent2";
        case TableStylePreset::THEMED_STYLE2_ACCENT3: return "ThemedStyle2Accent3";
        case TableStylePreset::THEMED_STYLE2_ACCENT4: return "ThemedStyle2Accent4";
        case TableStylePreset::THEMED_STYLE2_ACCENT5: return "ThemedStyle2Accent5";
        case TableStylePreset::THEMED_STYLE2_ACCENT6: return "ThemedStyle2Accent6";
        case TableStylePreset::LIGHT_STYLE1: return "LightStyle1";
        case TableStylePreset::LIGHT_STYLE1_ACCENT1: return "LightStyle1Accent1";
        case TableStylePreset::LIGHT_STYLE1_ACCENT2: return "LightStyle1Accent2";
        case TableStylePreset::LIGHT_STYLE1_ACCENT3: return "LightStyle1Accent3";
        case TableStylePreset::LIGHT_STYLE1_ACCENT4: return "LightStyle1Accent4";
        case TableStylePreset::LIGHT_STYLE2_ACCENT5: return "LightStyle2Accent5";
        case TableStylePreset::LIGHT_STYLE1_ACCENT6: return "LightStyle1Accent6";
        case TableStylePreset::LIGHT_STYLE2: return "LightStyle2";
        case TableStylePreset::LIGHT_STYLE2_ACCENT1: return "LightStyle2Accent1";
        case TableStylePreset::LIGHT_STYLE2_ACCENT2: return "LightStyle2Accent2";
        case TableStylePreset::LIGHT_STYLE2_ACCENT3: return "LightStyle2Accent3";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT3: return "MediumStyle2Accent3";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT4: return "MediumStyle2Accent4";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT5: return "MediumStyle2Accent5";
        case TableStylePreset::LIGHT_STYLE2_ACCENT6: return "LightStyle2Accent6";
        case TableStylePreset::LIGHT_STYLE2_ACCENT4: return "LightStyle2Accent4";
        case TableStylePreset::LIGHT_STYLE3: return "LightStyle3";
        case TableStylePreset::LIGHT_STYLE3_ACCENT1: return "LightStyle3Accent1";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT2: return "MediumStyle2Accent2";
        case TableStylePreset::LIGHT_STYLE3_ACCENT2: return "LightStyle3Accent2";
        case TableStylePreset::LIGHT_STYLE3_ACCENT3: return "LightStyle3Accent3";
        case TableStylePreset::LIGHT_STYLE3_ACCENT4: return "LightStyle3Accent4";
        case TableStylePreset::LIGHT_STYLE3_ACCENT5: return "LightStyle3Accent5";
        case TableStylePreset::LIGHT_STYLE3_ACCENT6: return "LightStyle3Accent6";
        case TableStylePreset::MEDIUM_STYLE1: return "MediumStyle1";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT1: return "MediumStyle1Accent1";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT2: return "MediumStyle1Accent2";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT3: return "MediumStyle1Accent3";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT4: return "MediumStyle1Accent4";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT5: return "MediumStyle1Accent5";
        case TableStylePreset::MEDIUM_STYLE1_ACCENT6: return "MediumStyle1Accent6";
        case TableStylePreset::MEDIUM_STYLE2_ACCENT6: return "MediumStyle2Accent6";
        case TableStylePreset::MEDIUM_STYLE3: return "MediumStyle3";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT1: return "MediumStyle3Accent1";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT2: return "MediumStyle3Accent2";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT3: return "MediumStyle3Accent3";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT4: return "MediumStyle3Accent4";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT5: return "MediumStyle3Accent5";
        case TableStylePreset::MEDIUM_STYLE3_ACCENT6: return "MediumStyle3Accent6";
        case TableStylePreset::MEDIUM_STYLE4: return "MediumStyle4";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT1: return "MediumStyle4Accent1";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT2: return "MediumStyle4Accent2";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT3: return "MediumStyle4Accent3";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT4: return "MediumStyle4Accent4";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT5: return "MediumStyle4Accent5";
        case TableStylePreset::MEDIUM_STYLE4_ACCENT6: return "MediumStyle4Accent6";
        case TableStylePreset::DARK_STYLE1: return "DarkStyle1";
        case TableStylePreset::DARK_STYLE1_ACCENT1: return "DarkStyle1Accent1";
        case TableStylePreset::DARK_STYLE1_ACCENT2: return "DarkStyle1Accent2";
        case TableStylePreset::DARK_STYLE1_ACCENT3: return "DarkStyle1Accent3";
        case TableStylePreset::DARK_STYLE1_ACCENT4: return "DarkStyle1Accent4";
        case TableStylePreset::DARK_STYLE1_ACCENT5: return "DarkStyle1Accent5";
        case TableStylePreset::DARK_STYLE1_ACCENT6: return "DarkStyle1Accent6";
        case TableStylePreset::DARK_STYLE2: return "DarkStyle2";
        case TableStylePreset::DARK_STYLE2_ACCENT1_ACCENT2: return "DarkStyle2Accent1Accent2";
        case TableStylePreset::DARK_STYLE2_ACCENT3_ACCENT4: return "DarkStyle2Accent3Accent4";
        case TableStylePreset::DARK_STYLE2_ACCENT5_ACCENT6: return "DarkStyle2Accent5Accent6";
        case TableStylePreset::LIGHT_STYLE1_ACCENT5: return "LightStyle1Accent5";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
