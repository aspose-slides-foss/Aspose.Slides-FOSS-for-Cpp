// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>

#include <Aspose/Slides/Foss/i_shape_frame.h>
#include <Aspose/Slides/Foss/nullable_bool.h>

namespace Aspose::Slides::Foss {

/// Represents the geometric frame of a shape.
class ShapeFrame final : public IShapeFrame {
public:
    /// Constructs a shape frame with the given properties.
    ShapeFrame(double x, double y, double width, double height,
               NullableBool flip_h = NullableBool::FALSE,
               NullableBool flip_v = NullableBool::FALSE,
               double rotation = 0.0)
        : x_(x), y_(y), width_(width), height_(height),
          flip_h_(flip_h), flip_v_(flip_v), rotation_(rotation) {}

    ShapeFrame() = default;

    /// Returns the X coordinate of the upper-left corner.
    [[nodiscard]] double x() const override { return x_; }
    /// Returns the Y coordinate of the upper-left corner.
    [[nodiscard]] double y() const override { return y_; }
    /// Returns the width.
    [[nodiscard]] double width() const override { return width_; }
    /// Returns the height.
    [[nodiscard]] double height() const override { return height_; }
    /// Returns the rotation angle in degrees.
    [[nodiscard]] double rotation() const override { return rotation_; }

    /// Returns the X coordinate of the frame's center.
    [[nodiscard]] double center_x() const override { return x_ + width_ / 2.0; }
    /// Returns the Y coordinate of the frame's center.
    [[nodiscard]] double center_y() const override { return y_ + height_ / 2.0; }

    /// Returns horizontal flip state.
    [[nodiscard]] NullableBool flip_h() const override { return flip_h_; }
    /// Returns vertical flip state.
    [[nodiscard]] NullableBool flip_v() const override { return flip_v_; }

    /// Returns the coordinates of this frame as a rectangle.
    [[nodiscard]] Drawing::RectangleF rectangle() const override {
        return {static_cast<float>(x_), static_cast<float>(y_),
                static_cast<float>(width_), static_cast<float>(height_)};
    }

    /// Returns a deep copy of this shape frame.
    [[nodiscard]] std::unique_ptr<IShapeFrame> clone_t() const override {
        return std::make_unique<ShapeFrame>(*this);
    }

    /// Returns a copy of this frame (value-semantic clone).
    [[nodiscard]] ShapeFrame clone() const { return *this; }

    /// Compares with another ShapeFrame for equality.
    [[nodiscard]] bool equals(const ShapeFrame& other) const {
        return x_ == other.x_ && y_ == other.y_ &&
               width_ == other.width_ && height_ == other.height_ &&
               rotation_ == other.rotation_ &&
               flip_h_ == other.flip_h_ && flip_v_ == other.flip_v_;
    }

    bool operator==(const ShapeFrame& other) const { return equals(other); }
    bool operator!=(const ShapeFrame& other) const { return !equals(other); }

private:
    double x_ = 0.0;
    double y_ = 0.0;
    double width_ = 0.0;
    double height_ = 0.0;
    NullableBool flip_h_ = NullableBool::FALSE;
    NullableBool flip_v_ = NullableBool::FALSE;
    double rotation_ = 0.0;
};

} // namespace Aspose::Slides::Foss
