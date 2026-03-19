// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the lines join style.
enum class LineJoinStyle {
    NOT_DEFINED,
    ROUND,
    BEVEL,
    MITER,
};

/// Returns the string representation of a LineJoinStyle value.
constexpr std::string_view to_string_view(LineJoinStyle value) {
    switch (value) {
        case LineJoinStyle::NOT_DEFINED: return "NotDefined";
        case LineJoinStyle::ROUND: return "Round";
        case LineJoinStyle::BEVEL: return "Bevel";
        case LineJoinStyle::MITER: return "Miter";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
