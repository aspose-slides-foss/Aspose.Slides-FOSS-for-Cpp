// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the type of text capitalisation.
enum class TextCapType {
    NOT_DEFINED,
    NONE,
    SMALL,
    ALL,
};

/// Returns the string representation of a TextCapType value.
constexpr std::string_view to_string_view(TextCapType value) {
    switch (value) {
        case TextCapType::NOT_DEFINED: return "NotDefined";
        case TextCapType::NONE: return "None";
        case TextCapType::SMALL: return "Small";
        case TextCapType::ALL: return "All";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
