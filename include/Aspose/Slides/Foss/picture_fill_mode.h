// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Determines how picture will fill area.
enum class PictureFillMode {
    TILE,
    STRETCH,
};

/// Returns the string representation of a PictureFillMode value.
constexpr std::string_view to_string_view(PictureFillMode value) {
    switch (value) {
        case PictureFillMode::TILE: return "Tile";
        case PictureFillMode::STRETCH: return "Stretch";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
