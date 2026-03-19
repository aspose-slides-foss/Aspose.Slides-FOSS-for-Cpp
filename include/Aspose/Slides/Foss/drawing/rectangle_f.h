// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <ostream>

namespace Aspose::Slides::Foss::Drawing {

/// Represents a rectangle with float coordinates, equivalent to System.Drawing.RectangleF.
struct RectangleF {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    constexpr RectangleF() noexcept = default;
    constexpr RectangleF(float x, float y, float width, float height) noexcept
        : x(x), y(y), width(width), height(height) {}

    constexpr bool operator==(const RectangleF&) const noexcept = default;
    constexpr bool operator!=(const RectangleF&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const RectangleF& r) {
        return os << "RectangleF(x=" << r.x << ", y=" << r.y
                  << ", width=" << r.width << ", height=" << r.height << ")";
    }
};

} // namespace Aspose::Slides::Foss::Drawing
