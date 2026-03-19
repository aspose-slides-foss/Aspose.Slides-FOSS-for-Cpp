// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the line cap style.
enum class LineCapStyle {
    NOT_DEFINED,
    ROUND,
    SQUARE,
    FLAT,
};

/// Returns the string representation of a LineCapStyle value.
constexpr std::string_view to_string_view(LineCapStyle value) {
    switch (value) {
        case LineCapStyle::NOT_DEFINED: return "NotDefined";
        case LineCapStyle::ROUND: return "Round";
        case LineCapStyle::SQUARE: return "Square";
        case LineCapStyle::FLAT: return "Flat";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
