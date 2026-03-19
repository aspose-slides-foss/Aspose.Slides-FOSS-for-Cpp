// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the type of text strikethrough.
enum class TextStrikethroughType {
    NOT_DEFINED,
    NONE,
    SINGLE,
    DOUBLE,
};

/// Returns the string representation of a TextStrikethroughType value.
constexpr std::string_view to_string_view(TextStrikethroughType value) {
    switch (value) {
        case TextStrikethroughType::NOT_DEFINED: return "NotDefined";
        case TextStrikethroughType::NONE: return "None";
        case TextStrikethroughType::SINGLE: return "Single";
        case TextStrikethroughType::DOUBLE: return "Double";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
