// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Determines blend mode.
enum class FillBlendMode {
    DARKEN,
    LIGHTEN,
    MULTIPLY,
    OVERLAY,
    SCREEN,
};

/// Returns the string representation of a FillBlendMode value.
constexpr std::string_view to_string_view(FillBlendMode value) {
    switch (value) {
        case FillBlendMode::DARKEN: return "Darken";
        case FillBlendMode::LIGHTEN: return "Lighten";
        case FillBlendMode::MULTIPLY: return "Multiply";
        case FillBlendMode::OVERLAY: return "Overlay";
        case FillBlendMode::SCREEN: return "Screen";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
