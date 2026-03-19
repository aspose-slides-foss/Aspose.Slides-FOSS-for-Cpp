// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <ostream>
#include <string>

namespace Aspose::Slides::Foss::Drawing {

/// Represents a 2D size with integer dimensions, equivalent to System.Drawing.Size.
struct Size {
    int width = 0;
    int height = 0;

    constexpr Size() noexcept = default;
    constexpr Size(int width, int height) noexcept : width(width), height(height) {}

    constexpr bool operator==(const Size&) const noexcept = default;
    constexpr bool operator!=(const Size&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Size& s) {
        return os << "Size(width=" << s.width << ", height=" << s.height << ")";
    }
};

/// Returns a string representation of the size, e.g. "Size(width=100, height=200)".
std::string to_string(const Size& s);

} // namespace Aspose::Slides::Foss::Drawing
