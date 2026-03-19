// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the width of an arrowhead.
enum class LineArrowheadWidth {
    NOT_DEFINED,
    NARROW,
    MEDIUM,
    WIDE,
};

/// Returns the string representation of a LineArrowheadWidth value.
constexpr std::string_view to_string_view(LineArrowheadWidth value) {
    switch (value) {
        case LineArrowheadWidth::NOT_DEFINED: return "NotDefined";
        case LineArrowheadWidth::NARROW: return "Narrow";
        case LineArrowheadWidth::MEDIUM: return "Medium";
        case LineArrowheadWidth::WIDE: return "Wide";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
