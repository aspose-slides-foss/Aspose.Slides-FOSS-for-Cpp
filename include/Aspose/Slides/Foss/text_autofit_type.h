// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents text autofit mode.
enum class TextAutofitType {
    NOT_DEFINED,
    NONE,
    NORMAL,
    SHAPE,
};

/// Returns the string representation of a TextAutofitType value.
constexpr std::string_view to_string_view(TextAutofitType value) {
    switch (value) {
        case TextAutofitType::NOT_DEFINED: return "NotDefined";
        case TextAutofitType::NONE: return "None";
        case TextAutofitType::NORMAL: return "Normal";
        case TextAutofitType::SHAPE: return "Shape";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
