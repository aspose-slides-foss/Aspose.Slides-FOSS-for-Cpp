// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents predefined color presets.
enum class PresetColor {
    NOT_DEFINED,
    ALICE_BLUE,
    ANTIQUE_WHITE,
    AQUA,
    AQUAMARINE,
    AZURE,
    BEIGE,
    BISQUE,
    BLACK,
    BLANCHED_ALMOND,
    BLUE,
    BLUE_VIOLET,
    BROWN,
    BURLY_WOOD,
    CADET_BLUE,
    CHARTREUSE,
    CHOCOLATE,
    CORAL,
    CORNFLOWER_BLUE,
    CORNSILK,
    CRIMSON,
    CYAN,
    DARK_BLUE,
    DARK_CYAN,
    DARK_GOLDENROD,
    DARK_GRAY,
    DARK_GREEN,
    DARK_KHAKI,
    DARK_MAGENTA,
    DARK_OLIVE_GREEN,
    DARK_ORANGE,
    DARK_ORCHID,
    DARK_RED,
    DARK_SALMON,
    DARK_SEA_GREEN,
    DARK_SLATE_BLUE,
    DARK_SLATE_GRAY,
    DARK_TURQUOISE,
    DARK_VIOLET,
    DEEP_PINK,
    DEEP_SKY_BLUE,
    DIM_GRAY,
    DODGER_BLUE,
    FIREBRICK,
    FLORAL_WHITE,
    FOREST_GREEN,
    FUCHSIA,
    GAINSBORO,
    GHOST_WHITE,
    GOLD,
    GOLDENROD,
    GRAY,
    GREEN,
    GREEN_YELLOW,
    HONEYDEW,
    HOT_PINK,
    INDIAN_RED,
    INDIGO,
    IVORY,
    KHAKI,
    LAVENDER,
    LAVENDER_BLUSH,
    LAWN_GREEN,
    LEMON_CHIFFON,
    LIGHT_BLUE,
    LIGHT_CORAL,
    LIGHT_CYAN,
    LIGHT_GOLDENROD_YELLOW,
    LIGHT_GRAY,
    LIGHT_GREEN,
    LIGHT_PINK,
    LIGHT_SALMON,
    LIGHT_SEA_GREEN,
    LIGHT_SKY_BLUE,
    LIGHT_SLATE_GRAY,
    LIGHT_STEEL_BLUE,
    LIGHT_YELLOW,
    LIME,
    LIME_GREEN,
    LINEN,
    MAGENTA,
    MAROON,
    MEDIUM_AQUAMARINE,
    MEDIUM_BLUE,
    MEDIUM_ORCHID,
    MEDIUM_PURPLE,
    MEDIUM_SEA_GREEN,
    MEDIUM_SLATE_BLUE,
    MEDIUM_SPRING_GREEN,
    MEDIUM_TURQUOISE,
    MEDIUM_VIOLET_RED,
    MIDNIGHT_BLUE,
    MINT_CREAM,
    MISTY_ROSE,
    MOCCASIN,
    NAVAJO_WHITE,
    NAVY,
    OLD_LACE,
    OLIVE,
    OLIVE_DRAB,
    ORANGE,
    ORANGE_RED,
    ORCHID,
    PALE_GOLDENROD,
    PALE_GREEN,
    PALE_TURQUOISE,
    PALE_VIOLET_RED,
    PAPAYA_WHIP,
    PEACH_PUFF,
    PERU,
    PINK,
    PLUM,
    POWDER_BLUE,
    PURPLE,
    RED,
    ROSY_BROWN,
    ROYAL_BLUE,
    SADDLE_BROWN,
    SALMON,
    SANDY_BROWN,
    SEA_GREEN,
    SEA_SHELL,
    SIENNA,
    SILVER,
    SKY_BLUE,
    SLATE_BLUE,
    SLATE_GRAY,
    SNOW,
    SPRING_GREEN,
    STEEL_BLUE,
    TAN,
    TEAL,
    THISTLE,
    TOMATO,
    TURQUOISE,
    VIOLET,
    WHEAT,
    WHITE,
    WHITE_SMOKE,
    YELLOW,
    YELLOW_GREEN,
};

/// Returns the string representation of a PresetColor value.
constexpr std::string_view to_string_view(PresetColor value) {
    switch (value) {
        case PresetColor::NOT_DEFINED: return "NotDefined";
        case PresetColor::ALICE_BLUE: return "AliceBlue";
        case PresetColor::ANTIQUE_WHITE: return "AntiqueWhite";
        case PresetColor::AQUA: return "Aqua";
        case PresetColor::AQUAMARINE: return "Aquamarine";
        case PresetColor::AZURE: return "Azure";
        case PresetColor::BEIGE: return "Beige";
        case PresetColor::BISQUE: return "Bisque";
        case PresetColor::BLACK: return "Black";
        case PresetColor::BLANCHED_ALMOND: return "BlanchedAlmond";
        case PresetColor::BLUE: return "Blue";
        case PresetColor::BLUE_VIOLET: return "BlueViolet";
        case PresetColor::BROWN: return "Brown";
        case PresetColor::BURLY_WOOD: return "BurlyWood";
        case PresetColor::CADET_BLUE: return "CadetBlue";
        case PresetColor::CHARTREUSE: return "Chartreuse";
        case PresetColor::CHOCOLATE: return "Chocolate";
        case PresetColor::CORAL: return "Coral";
        case PresetColor::CORNFLOWER_BLUE: return "CornflowerBlue";
        case PresetColor::CORNSILK: return "Cornsilk";
        case PresetColor::CRIMSON: return "Crimson";
        case PresetColor::CYAN: return "Cyan";
        case PresetColor::DARK_BLUE: return "DarkBlue";
        case PresetColor::DARK_CYAN: return "DarkCyan";
        case PresetColor::DARK_GOLDENROD: return "DarkGoldenrod";
        case PresetColor::DARK_GRAY: return "DarkGray";
        case PresetColor::DARK_GREEN: return "DarkGreen";
        case PresetColor::DARK_KHAKI: return "DarkKhaki";
        case PresetColor::DARK_MAGENTA: return "DarkMagenta";
        case PresetColor::DARK_OLIVE_GREEN: return "DarkOliveGreen";
        case PresetColor::DARK_ORANGE: return "DarkOrange";
        case PresetColor::DARK_ORCHID: return "DarkOrchid";
        case PresetColor::DARK_RED: return "DarkRed";
        case PresetColor::DARK_SALMON: return "DarkSalmon";
        case PresetColor::DARK_SEA_GREEN: return "DarkSeaGreen";
        case PresetColor::DARK_SLATE_BLUE: return "DarkSlateBlue";
        case PresetColor::DARK_SLATE_GRAY: return "DarkSlateGray";
        case PresetColor::DARK_TURQUOISE: return "DarkTurquoise";
        case PresetColor::DARK_VIOLET: return "DarkViolet";
        case PresetColor::DEEP_PINK: return "DeepPink";
        case PresetColor::DEEP_SKY_BLUE: return "DeepSkyBlue";
        case PresetColor::DIM_GRAY: return "DimGray";
        case PresetColor::DODGER_BLUE: return "DodgerBlue";
        case PresetColor::FIREBRICK: return "Firebrick";
        case PresetColor::FLORAL_WHITE: return "FloralWhite";
        case PresetColor::FOREST_GREEN: return "ForestGreen";
        case PresetColor::FUCHSIA: return "Fuchsia";
        case PresetColor::GAINSBORO: return "Gainsboro";
        case PresetColor::GHOST_WHITE: return "GhostWhite";
        case PresetColor::GOLD: return "Gold";
        case PresetColor::GOLDENROD: return "Goldenrod";
        case PresetColor::GRAY: return "Gray";
        case PresetColor::GREEN: return "Green";
        case PresetColor::GREEN_YELLOW: return "GreenYellow";
        case PresetColor::HONEYDEW: return "Honeydew";
        case PresetColor::HOT_PINK: return "HotPink";
        case PresetColor::INDIAN_RED: return "IndianRed";
        case PresetColor::INDIGO: return "Indigo";
        case PresetColor::IVORY: return "Ivory";
        case PresetColor::KHAKI: return "Khaki";
        case PresetColor::LAVENDER: return "Lavender";
        case PresetColor::LAVENDER_BLUSH: return "LavenderBlush";
        case PresetColor::LAWN_GREEN: return "LawnGreen";
        case PresetColor::LEMON_CHIFFON: return "LemonChiffon";
        case PresetColor::LIGHT_BLUE: return "LightBlue";
        case PresetColor::LIGHT_CORAL: return "LightCoral";
        case PresetColor::LIGHT_CYAN: return "LightCyan";
        case PresetColor::LIGHT_GOLDENROD_YELLOW: return "LightGoldenrodYellow";
        case PresetColor::LIGHT_GRAY: return "LightGray";
        case PresetColor::LIGHT_GREEN: return "LightGreen";
        case PresetColor::LIGHT_PINK: return "LightPink";
        case PresetColor::LIGHT_SALMON: return "LightSalmon";
        case PresetColor::LIGHT_SEA_GREEN: return "LightSeaGreen";
        case PresetColor::LIGHT_SKY_BLUE: return "LightSkyBlue";
        case PresetColor::LIGHT_SLATE_GRAY: return "LightSlateGray";
        case PresetColor::LIGHT_STEEL_BLUE: return "LightSteelBlue";
        case PresetColor::LIGHT_YELLOW: return "LightYellow";
        case PresetColor::LIME: return "Lime";
        case PresetColor::LIME_GREEN: return "LimeGreen";
        case PresetColor::LINEN: return "Linen";
        case PresetColor::MAGENTA: return "Magenta";
        case PresetColor::MAROON: return "Maroon";
        case PresetColor::MEDIUM_AQUAMARINE: return "MediumAquamarine";
        case PresetColor::MEDIUM_BLUE: return "MediumBlue";
        case PresetColor::MEDIUM_ORCHID: return "MediumOrchid";
        case PresetColor::MEDIUM_PURPLE: return "MediumPurple";
        case PresetColor::MEDIUM_SEA_GREEN: return "MediumSeaGreen";
        case PresetColor::MEDIUM_SLATE_BLUE: return "MediumSlateBlue";
        case PresetColor::MEDIUM_SPRING_GREEN: return "MediumSpringGreen";
        case PresetColor::MEDIUM_TURQUOISE: return "MediumTurquoise";
        case PresetColor::MEDIUM_VIOLET_RED: return "MediumVioletRed";
        case PresetColor::MIDNIGHT_BLUE: return "MidnightBlue";
        case PresetColor::MINT_CREAM: return "MintCream";
        case PresetColor::MISTY_ROSE: return "MistyRose";
        case PresetColor::MOCCASIN: return "Moccasin";
        case PresetColor::NAVAJO_WHITE: return "NavajoWhite";
        case PresetColor::NAVY: return "Navy";
        case PresetColor::OLD_LACE: return "OldLace";
        case PresetColor::OLIVE: return "Olive";
        case PresetColor::OLIVE_DRAB: return "OliveDrab";
        case PresetColor::ORANGE: return "Orange";
        case PresetColor::ORANGE_RED: return "OrangeRed";
        case PresetColor::ORCHID: return "Orchid";
        case PresetColor::PALE_GOLDENROD: return "PaleGoldenrod";
        case PresetColor::PALE_GREEN: return "PaleGreen";
        case PresetColor::PALE_TURQUOISE: return "PaleTurquoise";
        case PresetColor::PALE_VIOLET_RED: return "PaleVioletRed";
        case PresetColor::PAPAYA_WHIP: return "PapayaWhip";
        case PresetColor::PEACH_PUFF: return "PeachPuff";
        case PresetColor::PERU: return "Peru";
        case PresetColor::PINK: return "Pink";
        case PresetColor::PLUM: return "Plum";
        case PresetColor::POWDER_BLUE: return "PowderBlue";
        case PresetColor::PURPLE: return "Purple";
        case PresetColor::RED: return "Red";
        case PresetColor::ROSY_BROWN: return "RosyBrown";
        case PresetColor::ROYAL_BLUE: return "RoyalBlue";
        case PresetColor::SADDLE_BROWN: return "SaddleBrown";
        case PresetColor::SALMON: return "Salmon";
        case PresetColor::SANDY_BROWN: return "SandyBrown";
        case PresetColor::SEA_GREEN: return "SeaGreen";
        case PresetColor::SEA_SHELL: return "SeaShell";
        case PresetColor::SIENNA: return "Sienna";
        case PresetColor::SILVER: return "Silver";
        case PresetColor::SKY_BLUE: return "SkyBlue";
        case PresetColor::SLATE_BLUE: return "SlateBlue";
        case PresetColor::SLATE_GRAY: return "SlateGray";
        case PresetColor::SNOW: return "Snow";
        case PresetColor::SPRING_GREEN: return "SpringGreen";
        case PresetColor::STEEL_BLUE: return "SteelBlue";
        case PresetColor::TAN: return "Tan";
        case PresetColor::TEAL: return "Teal";
        case PresetColor::THISTLE: return "Thistle";
        case PresetColor::TOMATO: return "Tomato";
        case PresetColor::TURQUOISE: return "Turquoise";
        case PresetColor::VIOLET: return "Violet";
        case PresetColor::WHEAT: return "Wheat";
        case PresetColor::WHITE: return "White";
        case PresetColor::WHITE_SMOKE: return "WhiteSmoke";
        case PresetColor::YELLOW: return "Yellow";
        case PresetColor::YELLOW_GREEN: return "YellowGreen";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
