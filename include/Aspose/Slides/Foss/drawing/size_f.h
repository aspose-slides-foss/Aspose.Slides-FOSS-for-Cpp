// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <ostream>
#include <string>

namespace Aspose::Slides::Foss::Drawing {

/// Represents a 2D size with float dimensions, equivalent to System.Drawing.SizeF.
struct SizeF {
    float width = 0.0f;
    float height = 0.0f;

    constexpr SizeF() noexcept = default;
    constexpr SizeF(float width, float height) noexcept : width(width), height(height) {}

    constexpr bool operator==(const SizeF&) const noexcept = default;
    constexpr bool operator!=(const SizeF&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const SizeF& s) {
        return os << "SizeF(width=" << s.width << ", height=" << s.height << ")";
    }
};

/// Returns a string representation of the size, e.g. "SizeF(width=1.5, height=2.5)".
std::string to_string(const SizeF& s);

} // namespace Aspose::Slides::Foss::Drawing
