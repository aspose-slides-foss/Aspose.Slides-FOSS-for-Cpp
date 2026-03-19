// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Defines tile flipping mode.
enum class TileFlip {
    NOT_DEFINED,
    NO_FLIP,
    FLIP_X,
    FLIP_Y,
    FLIP_BOTH,
};

/// Returns the string representation of a TileFlip value.
constexpr std::string_view to_string_view(TileFlip value) {
    switch (value) {
        case TileFlip::NOT_DEFINED: return "NotDefined";
        case TileFlip::NO_FLIP: return "NoFlip";
        case TileFlip::FLIP_X: return "FlipX";
        case TileFlip::FLIP_Y: return "FlipY";
        case TileFlip::FLIP_BOTH: return "FlipBoth";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
