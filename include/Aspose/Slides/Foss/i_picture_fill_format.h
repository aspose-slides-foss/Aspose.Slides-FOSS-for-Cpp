// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_fill_param_source.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/rectangle_alignment.h>
#include <Aspose/Slides/Foss/tile_flip.h>

namespace Aspose::Slides::Foss {

class ISlidesPicture;
class PPImage;

/// Represents a picture fill style.
class IPictureFillFormat : public IFillParamSource {
public:
    ~IPictureFillFormat() override = default;

    /// Returns or sets the dpi used to fill a picture. Read/write.
    [[nodiscard]] virtual int dpi() const = 0;
    virtual void set_dpi(int value) = 0;

    /// Returns or sets the picture fill mode. Read/write.
    [[nodiscard]] virtual PictureFillMode picture_fill_mode() const = 0;
    virtual void set_picture_fill_mode(PictureFillMode value) = 0;

    /// Returns the picture. Read-only.
    [[nodiscard]] virtual ISlidesPicture& picture() noexcept = 0;
    [[nodiscard]] virtual const ISlidesPicture& picture() const noexcept = 0;

    /// Returns or sets the number of percents of real image width cropped off the left. Read/write.
    [[nodiscard]] virtual float crop_left() const = 0;
    virtual void set_crop_left(float value) = 0;

    /// Returns or sets the number of percents of real image height cropped off the top. Read/write.
    [[nodiscard]] virtual float crop_top() const = 0;
    virtual void set_crop_top(float value) = 0;

    /// Returns or sets the number of percents of real image width cropped off the right. Read/write.
    [[nodiscard]] virtual float crop_right() const = 0;
    virtual void set_crop_right(float value) = 0;

    /// Returns or sets the number of percents of real image height cropped off the bottom. Read/write.
    [[nodiscard]] virtual float crop_bottom() const = 0;
    virtual void set_crop_bottom(float value) = 0;

    /// Returns or sets the left edge stretch offset as a percentage. Read/write.
    [[nodiscard]] virtual float stretch_offset_left() const = 0;
    virtual void set_stretch_offset_left(float value) = 0;

    /// Returns or sets the top edge stretch offset as a percentage. Read/write.
    [[nodiscard]] virtual float stretch_offset_top() const = 0;
    virtual void set_stretch_offset_top(float value) = 0;

    /// Returns or sets the right edge stretch offset as a percentage. Read/write.
    [[nodiscard]] virtual float stretch_offset_right() const = 0;
    virtual void set_stretch_offset_right(float value) = 0;

    /// Returns or sets the bottom edge stretch offset as a percentage. Read/write.
    [[nodiscard]] virtual float stretch_offset_bottom() const = 0;
    virtual void set_stretch_offset_bottom(float value) = 0;

    /// Returns or sets the horizontal offset of the texture in points. Read/write.
    [[nodiscard]] virtual float tile_offset_x() const = 0;
    virtual void set_tile_offset_x(float value) = 0;

    /// Returns or sets the vertical offset of the texture in points. Read/write.
    [[nodiscard]] virtual float tile_offset_y() const = 0;
    virtual void set_tile_offset_y(float value) = 0;

    /// Returns or sets the horizontal scale for the texture fill as a percentage. Read/write.
    [[nodiscard]] virtual float tile_scale_x() const = 0;
    virtual void set_tile_scale_x(float value) = 0;

    /// Returns or sets the vertical scale for the texture fill as a percentage. Read/write.
    [[nodiscard]] virtual float tile_scale_y() const = 0;
    virtual void set_tile_scale_y(float value) = 0;

    /// Returns or sets the texture tile alignment. Read/write.
    [[nodiscard]] virtual RectangleAlignment tile_alignment() const = 0;
    virtual void set_tile_alignment(RectangleAlignment value) = 0;

    /// Returns or sets the texture tile flip mode. Read/write.
    [[nodiscard]] virtual TileFlip tile_flip() const = 0;
    virtual void set_tile_flip(TileFlip value) = 0;

    /// Returns the image used for the picture fill.
    [[nodiscard]] virtual PPImage* image() const = 0;
    virtual void set_image(PPImage* img) = 0;

protected:
    IPictureFillFormat() = default;
};

} // namespace Aspose::Slides::Foss
