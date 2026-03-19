// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the style of an arrowhead.
enum class LineArrowheadStyle {
    NOT_DEFINED,
    NONE,
    TRIANGLE,
    STEALTH,
    DIAMOND,
    OVAL,
    OPEN,
};

/// Returns the string representation of a LineArrowheadStyle value.
constexpr std::string_view to_string_view(LineArrowheadStyle value) {
    switch (value) {
        case LineArrowheadStyle::NOT_DEFINED: return "NotDefined";
        case LineArrowheadStyle::NONE: return "None";
        case LineArrowheadStyle::TRIANGLE: return "Triangle";
        case LineArrowheadStyle::STEALTH: return "Stealth";
        case LineArrowheadStyle::DIAMOND: return "Diamond";
        case LineArrowheadStyle::OVAL: return "Oval";
        case LineArrowheadStyle::OPEN: return "Open";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
