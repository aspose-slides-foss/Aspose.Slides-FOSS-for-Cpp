// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Specifies the interior fill type of various visual objects.
enum class FillType {
    NOT_DEFINED,
    NO_FILL,
    SOLID,
    GRADIENT,
    PATTERN,
    PICTURE,
    GROUP,
};

/// Returns the string representation of a FillType value.
constexpr std::string_view to_string_view(FillType value) {
    switch (value) {
        case FillType::NOT_DEFINED: return "NotDefined";
        case FillType::NO_FILL: return "NoFill";
        case FillType::SOLID: return "Solid";
        case FillType::GRADIENT: return "Gradient";
        case FillType::PATTERN: return "Pattern";
        case FillType::PICTURE: return "Picture";
        case FillType::GROUP: return "Group";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
