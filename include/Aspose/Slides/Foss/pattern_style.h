// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the pattern style.
enum class PatternStyle {
    NOT_DEFINED,
    UNKNOWN,
    PERCENT05,
    PERCENT10,
    PERCENT20,
    PERCENT25,
    PERCENT30,
    PERCENT40,
    PERCENT50,
    PERCENT60,
    PERCENT70,
    PERCENT75,
    PERCENT80,
    PERCENT90,
    DARK_HORIZONTAL,
    DARK_VERTICAL,
    DARK_DOWNWARD_DIAGONAL,
    DARK_UPWARD_DIAGONAL,
    SMALL_CHECKER_BOARD,
    TRELLIS,
    LIGHT_HORIZONTAL,
    LIGHT_VERTICAL,
    LIGHT_DOWNWARD_DIAGONAL,
    LIGHT_UPWARD_DIAGONAL,
    SMALL_GRID,
    DOTTED_DIAMOND,
    WIDE_DOWNWARD_DIAGONAL,
    WIDE_UPWARD_DIAGONAL,
    DASHED_DOWNWARD_DIAGONAL,
    DASHED_UPWARD_DIAGONAL,
    NARROW_VERTICAL,
    NARROW_HORIZONTAL,
    DASHED_VERTICAL,
    DASHED_HORIZONTAL,
    LARGE_CONFETTI,
    LARGE_GRID,
    HORIZONTAL_BRICK,
    LARGE_CHECKER_BOARD,
    SMALL_CONFETTI,
    ZIGZAG,
    SOLID_DIAMOND,
    DIAGONAL_BRICK,
    OUTLINED_DIAMOND,
    PLAID,
    SPHERE,
    WEAVE,
    DOTTED_GRID,
    DIVOT,
    SHINGLE,
    WAVE,
    HORIZONTAL,
    VERTICAL,
    CROSS,
    DOWNWARD_DIAGONAL,
    UPWARD_DIAGONAL,
    DIAGONAL_CROSS,
};

/// Returns the string representation of a PatternStyle value.
constexpr std::string_view to_string_view(PatternStyle value) {
    switch (value) {
        case PatternStyle::NOT_DEFINED: return "NotDefined";
        case PatternStyle::UNKNOWN: return "Unknown";
        case PatternStyle::PERCENT05: return "Percent05";
        case PatternStyle::PERCENT10: return "Percent10";
        case PatternStyle::PERCENT20: return "Percent20";
        case PatternStyle::PERCENT25: return "Percent25";
        case PatternStyle::PERCENT30: return "Percent30";
        case PatternStyle::PERCENT40: return "Percent40";
        case PatternStyle::PERCENT50: return "Percent50";
        case PatternStyle::PERCENT60: return "Percent60";
        case PatternStyle::PERCENT70: return "Percent70";
        case PatternStyle::PERCENT75: return "Percent75";
        case PatternStyle::PERCENT80: return "Percent80";
        case PatternStyle::PERCENT90: return "Percent90";
        case PatternStyle::DARK_HORIZONTAL: return "DarkHorizontal";
        case PatternStyle::DARK_VERTICAL: return "DarkVertical";
        case PatternStyle::DARK_DOWNWARD_DIAGONAL: return "DarkDownwardDiagonal";
        case PatternStyle::DARK_UPWARD_DIAGONAL: return "DarkUpwardDiagonal";
        case PatternStyle::SMALL_CHECKER_BOARD: return "SmallCheckerBoard";
        case PatternStyle::TRELLIS: return "Trellis";
        case PatternStyle::LIGHT_HORIZONTAL: return "LightHorizontal";
        case PatternStyle::LIGHT_VERTICAL: return "LightVertical";
        case PatternStyle::LIGHT_DOWNWARD_DIAGONAL: return "LightDownwardDiagonal";
        case PatternStyle::LIGHT_UPWARD_DIAGONAL: return "LightUpwardDiagonal";
        case PatternStyle::SMALL_GRID: return "SmallGrid";
        case PatternStyle::DOTTED_DIAMOND: return "DottedDiamond";
        case PatternStyle::WIDE_DOWNWARD_DIAGONAL: return "WideDownwardDiagonal";
        case PatternStyle::WIDE_UPWARD_DIAGONAL: return "WideUpwardDiagonal";
        case PatternStyle::DASHED_DOWNWARD_DIAGONAL: return "DashedDownwardDiagonal";
        case PatternStyle::DASHED_UPWARD_DIAGONAL: return "DashedUpwardDiagonal";
        case PatternStyle::NARROW_VERTICAL: return "NarrowVertical";
        case PatternStyle::NARROW_HORIZONTAL: return "NarrowHorizontal";
        case PatternStyle::DASHED_VERTICAL: return "DashedVertical";
        case PatternStyle::DASHED_HORIZONTAL: return "DashedHorizontal";
        case PatternStyle::LARGE_CONFETTI: return "LargeConfetti";
        case PatternStyle::LARGE_GRID: return "LargeGrid";
        case PatternStyle::HORIZONTAL_BRICK: return "HorizontalBrick";
        case PatternStyle::LARGE_CHECKER_BOARD: return "LargeCheckerBoard";
        case PatternStyle::SMALL_CONFETTI: return "SmallConfetti";
        case PatternStyle::ZIGZAG: return "Zigzag";
        case PatternStyle::SOLID_DIAMOND: return "SolidDiamond";
        case PatternStyle::DIAGONAL_BRICK: return "DiagonalBrick";
        case PatternStyle::OUTLINED_DIAMOND: return "OutlinedDiamond";
        case PatternStyle::PLAID: return "Plaid";
        case PatternStyle::SPHERE: return "Sphere";
        case PatternStyle::WEAVE: return "Weave";
        case PatternStyle::DOTTED_GRID: return "DottedGrid";
        case PatternStyle::DIVOT: return "Divot";
        case PatternStyle::SHINGLE: return "Shingle";
        case PatternStyle::WAVE: return "Wave";
        case PatternStyle::HORIZONTAL: return "Horizontal";
        case PatternStyle::VERTICAL: return "Vertical";
        case PatternStyle::CROSS: return "Cross";
        case PatternStyle::DOWNWARD_DIAGONAL: return "DownwardDiagonal";
        case PatternStyle::UPWARD_DIAGONAL: return "UpwardDiagonal";
        case PatternStyle::DIAGONAL_CROSS: return "DiagonalCross";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
