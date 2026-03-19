// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents different color modes.
enum class ColorType {
    NOT_DEFINED,
    RGB,
    RGB_PERCENTAGE,
    HSL,
    SCHEME,
    SYSTEM,
    PRESET,
};

/// Returns the string representation of a ColorType value.
constexpr std::string_view to_string_view(ColorType value) {
    switch (value) {
        case ColorType::NOT_DEFINED: return "NotDefined";
        case ColorType::RGB: return "RGB";
        case ColorType::RGB_PERCENTAGE: return "RGBPercentage";
        case ColorType::HSL: return "HSL";
        case ColorType::SCHEME: return "Scheme";
        case ColorType::SYSTEM: return "System";
        case ColorType::PRESET: return "Preset";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
