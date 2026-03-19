// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IColorFormat;

/// Interface representing a gradient stop.
///
/// A gradient stop defines a color at a specific position (0.0 to 1.0)
/// within a gradient fill.
class IGradientStop {
public:
    virtual ~IGradientStop() = default;

    /// Returns the position (0.0 to 1.0) of the gradient stop.
    [[nodiscard]] virtual float position() const = 0;

    /// Sets the position (0.0 to 1.0) of the gradient stop. Read/write.
    virtual void set_position(float value) = 0;

    /// Returns the color of the gradient stop. Read-only.
    [[nodiscard]] virtual IColorFormat& color() = 0;

    /// Returns the color of the gradient stop (const). Read-only.
    [[nodiscard]] virtual const IColorFormat& color() const = 0;
};

} // namespace Aspose::Slides::Foss
