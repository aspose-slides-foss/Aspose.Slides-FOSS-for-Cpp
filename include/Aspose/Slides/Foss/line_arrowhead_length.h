// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the length of an arrowhead.
enum class LineArrowheadLength {
    NOT_DEFINED,
    SHORT,
    MEDIUM,
    LONG,
};

/// Returns the string representation of a LineArrowheadLength value.
constexpr std::string_view to_string_view(LineArrowheadLength value) {
    switch (value) {
        case LineArrowheadLength::NOT_DEFINED: return "NotDefined";
        case LineArrowheadLength::SHORT: return "Short";
        case LineArrowheadLength::MEDIUM: return "Medium";
        case LineArrowheadLength::LONG: return "Long";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
