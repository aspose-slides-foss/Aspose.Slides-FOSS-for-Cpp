// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <ostream>
#include <string>

namespace Aspose::Slides::Foss::Drawing {

/// Represents a 2D point with float coordinates, equivalent to System.Drawing.PointF.
struct PointF {
    float x = 0.0f;
    float y = 0.0f;

    constexpr PointF() noexcept = default;
    constexpr PointF(float x, float y) noexcept : x(x), y(y) {}

    constexpr bool operator==(const PointF&) const noexcept = default;
    constexpr bool operator!=(const PointF&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const PointF& p) {
        return os << "PointF(x=" << p.x << ", y=" << p.y << ")";
    }
};

/// Returns a string representation of the point, e.g. "PointF(x=1.5, y=2.5)".
std::string to_string(const PointF& p);

} // namespace Aspose::Slides::Foss::Drawing
