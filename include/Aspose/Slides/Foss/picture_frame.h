// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/geometry_shape.h>
#include <Aspose/Slides/Foss/picture_fill_format.h>

namespace Aspose::Slides::Foss {

class PPImage;

/// Represents a picture frame shape containing an image.
class PictureFrame final : public GeometryShape {
public:
    PictureFrame() = default;
    PictureFrame(ShapeType type, double x, double y, double w, double h,
                 PPImage* image)
        : GeometryShape(type, x, y, w, h), image_(image) {}

    /// Returns the image associated with this picture frame.
    [[nodiscard]] PPImage* pp_image() const noexcept { return image_; }

    /// Sets the image associated with this picture frame.
    void set_pp_image(PPImage* image) noexcept { image_ = image; }

    /// Returns the PictureFillFormat for this picture frame, or nullptr.
    [[nodiscard]] PictureFillFormat* picture_format() noexcept {
        return has_picture_format_ ? &picture_format_ : nullptr;
    }
    [[nodiscard]] const PictureFillFormat* picture_format() const noexcept {
        return has_picture_format_ ? &picture_format_ : nullptr;
    }

    /// Enables and returns the picture format for editing.
    PictureFillFormat& ensure_picture_format() noexcept {
        has_picture_format_ = true;
        return picture_format_;
    }

    /// Returns the shape's picture frame lock. Not yet implemented.
    [[nodiscard]] std::nullptr_t picture_frame_lock() const noexcept { return nullptr; }

    /// Returns the scale of height relative to original picture size.
    /// Value 1.0 corresponds to 100%.
    [[nodiscard]] double relative_scale_height() const noexcept {
        return relative_scale_height_;
    }

    /// Sets the scale of height relative to original picture size.
    void set_relative_scale_height(double value) noexcept {
        relative_scale_height_ = value;
    }

    /// Returns the scale of width relative to original picture size.
    /// Value 1.0 corresponds to 100%.
    [[nodiscard]] double relative_scale_width() const noexcept {
        return relative_scale_width_;
    }

    /// Sets the scale of width relative to original picture size.
    void set_relative_scale_width(double value) noexcept {
        relative_scale_width_ = value;
    }

    /// Determines whether this PictureFrame is a Cameo object. Always false.
    [[nodiscard]] bool is_cameo() const noexcept { return false; }

    /// Returns the pending part name for deferred image resolution.
    [[nodiscard]] const std::string& pending_part_name() const noexcept {
        return pending_part_name_;
    }

    /// Sets a pending part name for deferred image resolution.
    void set_pending_part_name(std::string value) noexcept {
        pending_part_name_ = std::move(value);
    }

    /// Clears the pending part name.
    void clear_pending_part_name() noexcept { pending_part_name_.clear(); }

private:
    PPImage* image_ = nullptr;
    PictureFillFormat picture_format_;
    std::string pending_part_name_;
    bool has_picture_format_ = false;
    double relative_scale_height_ = 1.0;
    double relative_scale_width_ = 1.0;
};

} // namespace Aspose::Slides::Foss
