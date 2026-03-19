// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the lines alignment type.
enum class LineAlignment {
    NOT_DEFINED,
    CENTER,
    INSET,
};

/// Returns the string representation of a LineAlignment value.
constexpr std::string_view to_string_view(LineAlignment value) {
    switch (value) {
        case LineAlignment::NOT_DEFINED: return "NotDefined";
        case LineAlignment::CENTER: return "Center";
        case LineAlignment::INSET: return "Inset";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
