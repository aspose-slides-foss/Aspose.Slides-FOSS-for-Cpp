// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the style of a line.
enum class LineStyle {
    NOT_DEFINED,
    SINGLE,
    THIN_THIN,
    THICK_THIN,
    THIN_THICK,
    THICK_BETWEEN_THIN,
};

/// Returns the string representation of a LineStyle value.
constexpr std::string_view to_string_view(LineStyle value) {
    switch (value) {
        case LineStyle::NOT_DEFINED: return "NotDefined";
        case LineStyle::SINGLE: return "Single";
        case LineStyle::THIN_THIN: return "ThinThin";
        case LineStyle::THICK_THIN: return "ThickThin";
        case LineStyle::THIN_THICK: return "ThinThick";
        case LineStyle::THICK_BETWEEN_THIN: return "ThickBetweenThin";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
