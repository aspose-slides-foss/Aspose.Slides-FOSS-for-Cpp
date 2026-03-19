// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents vertical font alignment.
enum class FontAlignment {
    DEFAULT,
    AUTOMATIC,
    TOP,
    CENTER,
    BOTTOM,
    BASELINE,
};

/// Returns the string representation of a FontAlignment value.
constexpr std::string_view to_string_view(FontAlignment value) {
    switch (value) {
        case FontAlignment::DEFAULT: return "Default";
        case FontAlignment::AUTOMATIC: return "Automatic";
        case FontAlignment::TOP: return "Top";
        case FontAlignment::CENTER: return "Center";
        case FontAlignment::BOTTOM: return "Bottom";
        case FontAlignment::BASELINE: return "Baseline";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
