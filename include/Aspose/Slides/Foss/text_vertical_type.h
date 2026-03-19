// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Determines vertical writing mode for a text.
enum class TextVerticalType {
    NOT_DEFINED,
    HORIZONTAL,
    VERTICAL,
    VERTICAL270,
    WORD_ART_VERTICAL,
    EAST_ASIAN_VERTICAL,
    MONGOLIAN_VERTICAL,
    WORD_ART_VERTICAL_RIGHT_TO_LEFT,
};

/// Returns the string representation of a TextVerticalType value.
constexpr std::string_view to_string_view(TextVerticalType value) {
    switch (value) {
        case TextVerticalType::NOT_DEFINED: return "NotDefined";
        case TextVerticalType::HORIZONTAL: return "Horizontal";
        case TextVerticalType::VERTICAL: return "Vertical";
        case TextVerticalType::VERTICAL270: return "Vertical270";
        case TextVerticalType::WORD_ART_VERTICAL: return "WordArtVertical";
        case TextVerticalType::EAST_ASIAN_VERTICAL: return "EastAsianVertical";
        case TextVerticalType::MONGOLIAN_VERTICAL: return "MongolianVertical";
        case TextVerticalType::WORD_ART_VERTICAL_RIGHT_TO_LEFT: return "WordArtVerticalRightToLeft";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
