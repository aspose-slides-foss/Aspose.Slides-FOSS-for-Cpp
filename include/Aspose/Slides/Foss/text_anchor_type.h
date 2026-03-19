// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Text box alignment within a text area.
enum class TextAnchorType {
    NOT_DEFINED,
    TOP,
    CENTER,
    BOTTOM,
    JUSTIFIED,
    DISTRIBUTED,
};

/// Returns the string representation of a TextAnchorType value.
constexpr std::string_view to_string_view(TextAnchorType value) {
    switch (value) {
        case TextAnchorType::NOT_DEFINED: return "NotDefined";
        case TextAnchorType::TOP: return "Top";
        case TextAnchorType::CENTER: return "Center";
        case TextAnchorType::BOTTOM: return "Bottom";
        case TextAnchorType::JUSTIFIED: return "Justified";
        case TextAnchorType::DISTRIBUTED: return "Distributed";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
