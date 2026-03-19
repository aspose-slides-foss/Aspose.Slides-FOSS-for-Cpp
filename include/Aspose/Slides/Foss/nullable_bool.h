// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents triple boolean values.
enum class NullableBool {
    NOT_DEFINED,
    FALSE,
    TRUE,
};

/// Returns the string representation of a NullableBool value.
constexpr std::string_view to_string_view(NullableBool value) {
    switch (value) {
        case NullableBool::NOT_DEFINED: return "NotDefined";
        case NullableBool::FALSE: return "False";
        case NullableBool::TRUE: return "True";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
