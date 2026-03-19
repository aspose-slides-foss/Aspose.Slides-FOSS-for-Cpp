// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents different text alignment styles.
enum class TextAlignment {
    NOT_DEFINED,
    LEFT,
    CENTER,
    RIGHT,
    JUSTIFY,
    JUSTIFY_LOW,
    DISTRIBUTED,
};

/// Returns the string representation of a TextAlignment value.
constexpr std::string_view to_string_view(TextAlignment value) {
    switch (value) {
        case TextAlignment::NOT_DEFINED: return "NotDefined";
        case TextAlignment::LEFT: return "Left";
        case TextAlignment::CENTER: return "Center";
        case TextAlignment::RIGHT: return "Right";
        case TextAlignment::JUSTIFY: return "Justify";
        case TextAlignment::JUSTIFY_LOW: return "JustifyLow";
        case TextAlignment::DISTRIBUTED: return "Distributed";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
