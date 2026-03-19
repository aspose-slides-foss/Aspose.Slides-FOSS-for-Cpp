// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the shape of gradient fill.
enum class GradientShape {
    NOT_DEFINED,
    LINEAR,
    RECTANGLE,
    RADIAL,
    PATH,
};

/// Returns the string representation of a GradientShape value.
constexpr std::string_view to_string_view(GradientShape value) {
    switch (value) {
        case GradientShape::NOT_DEFINED: return "NotDefined";
        case GradientShape::LINEAR: return "Linear";
        case GradientShape::RECTANGLE: return "Rectangle";
        case GradientShape::RADIAL: return "Radial";
        case GradientShape::PATH: return "Path";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
