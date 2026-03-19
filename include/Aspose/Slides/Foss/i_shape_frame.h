// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>

#include <Aspose/Slides/Foss/drawing/rectangle_f.h>
#include <Aspose/Slides/Foss/nullable_bool.h>

namespace Aspose::Slides::Foss {

/// Interface representing shape frame's properties.
class IShapeFrame {
public:
    virtual ~IShapeFrame() = default;

    /// Returns the X coordinate of the upper-left corner of a frame.
    [[nodiscard]] virtual double x() const = 0;

    /// Returns the Y coordinate of the upper-left corner of a frame.
    [[nodiscard]] virtual double y() const = 0;

    /// Returns the width of a frame.
    [[nodiscard]] virtual double width() const = 0;

    /// Returns the height of a frame.
    [[nodiscard]] virtual double height() const = 0;

    /// Returns the number of degrees a frame is rotated around the z-axis.
    /// A positive value indicates clockwise rotation; a negative value
    /// indicates counterclockwise rotation.
    [[nodiscard]] virtual double rotation() const = 0;

    /// Returns the X coordinate of a frame's center.
    [[nodiscard]] virtual double center_x() const = 0;

    /// Returns the Y coordinate of a frame's center.
    [[nodiscard]] virtual double center_y() const = 0;

    /// Determines whether a frame is flipped horizontally.
    [[nodiscard]] virtual NullableBool flip_h() const = 0;

    /// Determines whether a frame is flipped vertically.
    [[nodiscard]] virtual NullableBool flip_v() const = 0;

    /// Returns the coordinates of a frame as a rectangle.
    [[nodiscard]] virtual Drawing::RectangleF rectangle() const = 0;

    /// Returns a deep copy of this shape frame.
    [[nodiscard]] virtual std::unique_ptr<IShapeFrame> clone_t() const = 0;

protected:
    IShapeFrame() = default;
};

} // namespace Aspose::Slides::Foss
