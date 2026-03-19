// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the type of text underline.
enum class TextUnderlineType {
    NOT_DEFINED,
    NONE,
    WORDS,
    SINGLE,
    DOUBLE,
    HEAVY,
    DOTTED,
    HEAVY_DOTTED,
    DASHED,
    HEAVY_DASHED,
    LONG_DASHED,
    HEAVY_LONG_DASHED,
    DOT_DASH,
    HEAVY_DOT_DASH,
    DOT_DOT_DASH,
    HEAVY_DOT_DOT_DASH,
    WAVY,
    HEAVY_WAVY,
    DOUBLE_WAVY,
};

/// Returns the string representation of a TextUnderlineType value.
constexpr std::string_view to_string_view(TextUnderlineType value) {
    switch (value) {
        case TextUnderlineType::NOT_DEFINED: return "NotDefined";
        case TextUnderlineType::NONE: return "None";
        case TextUnderlineType::WORDS: return "Words";
        case TextUnderlineType::SINGLE: return "Single";
        case TextUnderlineType::DOUBLE: return "Double";
        case TextUnderlineType::HEAVY: return "Heavy";
        case TextUnderlineType::DOTTED: return "Dotted";
        case TextUnderlineType::HEAVY_DOTTED: return "HeavyDotted";
        case TextUnderlineType::DASHED: return "Dashed";
        case TextUnderlineType::HEAVY_DASHED: return "HeavyDashed";
        case TextUnderlineType::LONG_DASHED: return "LongDashed";
        case TextUnderlineType::HEAVY_LONG_DASHED: return "HeavyLongDashed";
        case TextUnderlineType::DOT_DASH: return "DotDash";
        case TextUnderlineType::HEAVY_DOT_DASH: return "HeavyDotDash";
        case TextUnderlineType::DOT_DOT_DASH: return "DotDotDash";
        case TextUnderlineType::HEAVY_DOT_DOT_DASH: return "HeavyDotDotDash";
        case TextUnderlineType::WAVY: return "Wavy";
        case TextUnderlineType::HEAVY_WAVY: return "HeavyWavy";
        case TextUnderlineType::DOUBLE_WAVY: return "DoubleWavy";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
