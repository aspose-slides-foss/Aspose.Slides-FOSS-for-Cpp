// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <string_view>

#include <Aspose/Slides/Foss/picture.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/rectangle_alignment.h>
#include <Aspose/Slides/Foss/tile_flip.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

class PPImage;

/// Represents a picture fill within a fill format.
class PictureFillFormat final {
public:
    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed picture fill format.
    /// @param blip_fill_element The <a:blipFill> XML element.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node blip_fill_element,
                       std::function<void()> save_callback);

    /// Get the <a:blip> child element.
    [[nodiscard]] pugi::xml_node get_blip() const;

    /// Get or create the <a:srcRect> element for crop values.
    pugi::xml_node get_or_create_src_rect();

    /// Get the <a:stretch> child element.
    [[nodiscard]] pugi::xml_node get_stretch() const;

    /// Get or create the <a:fillRect> element under <a:stretch>.
    pugi::xml_node get_or_create_fill_rect();

    /// Get a crop value from <a:srcRect>.
    /// @param attr Attribute name ("l", "t", "r", or "b").
    /// @return Percentage value (e.g., 10.0 for 10%).
    [[nodiscard]] float get_crop_value(std::string_view attr) const;

    /// Set a crop value on <a:srcRect>.
    /// @param attr Attribute name ("l", "t", "r", or "b").
    /// @param value Percentage value (e.g., 10.0 for 10%).
    void set_crop_value(std::string_view attr, float value);

    /// Get a stretch offset value from <a:fillRect> under <a:stretch>.
    /// @param attr Attribute name ("l", "t", "r", or "b").
    /// @return Percentage value.
    [[nodiscard]] float get_stretch_offset(std::string_view attr) const;

    /// Set a stretch offset value on <a:fillRect> under <a:stretch>.
    /// @param attr Attribute name ("l", "t", "r", or "b").
    /// @param value Percentage value.
    void set_stretch_offset(std::string_view attr, float value);

    /// Get the <a:tile> element, or empty node if absent.
    [[nodiscard]] pugi::xml_node get_tile() const;

    /// Get or create the <a:tile> element, removing <a:stretch> if present.
    pugi::xml_node ensure_tile();

    /// Save changes via the save callback.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns or sets the dpi used to fill a picture.
    [[nodiscard]] int dpi() const noexcept { return dpi_; }
    void set_dpi(int value) noexcept { dpi_ = value; }

    /// Returns the picture fill mode.
    [[nodiscard]] PictureFillMode picture_fill_mode() const noexcept { return mode_; }
    void set_picture_fill_mode(PictureFillMode value) noexcept { mode_ = value; }

    /// Returns the picture associated with the fill.
    [[nodiscard]] Picture& picture() noexcept { return picture_; }
    [[nodiscard]] const Picture& picture() const noexcept { return picture_; }

    /// Returns or sets the number of percents of real image width cropped off the left.
    [[nodiscard]] float crop_left() const noexcept { return crop_left_; }
    void set_crop_left(float value) noexcept { crop_left_ = value; }

    /// Returns or sets the number of percents of real image height cropped off the top.
    [[nodiscard]] float crop_top() const noexcept { return crop_top_; }
    void set_crop_top(float value) noexcept { crop_top_ = value; }

    /// Returns or sets the number of percents of real image width cropped off the right.
    [[nodiscard]] float crop_right() const noexcept { return crop_right_; }
    void set_crop_right(float value) noexcept { crop_right_ = value; }

    /// Returns or sets the number of percents of real image height cropped off the bottom.
    [[nodiscard]] float crop_bottom() const noexcept { return crop_bottom_; }
    void set_crop_bottom(float value) noexcept { crop_bottom_ = value; }

    /// Returns or sets the left edge stretch offset as a percentage.
    [[nodiscard]] float stretch_offset_left() const noexcept { return stretch_offset_left_; }
    void set_stretch_offset_left(float value) noexcept { stretch_offset_left_ = value; }

    /// Returns or sets the top edge stretch offset as a percentage.
    [[nodiscard]] float stretch_offset_top() const noexcept { return stretch_offset_top_; }
    void set_stretch_offset_top(float value) noexcept { stretch_offset_top_ = value; }

    /// Returns or sets the right edge stretch offset as a percentage.
    [[nodiscard]] float stretch_offset_right() const noexcept { return stretch_offset_right_; }
    void set_stretch_offset_right(float value) noexcept { stretch_offset_right_ = value; }

    /// Returns or sets the bottom edge stretch offset as a percentage.
    [[nodiscard]] float stretch_offset_bottom() const noexcept { return stretch_offset_bottom_; }
    void set_stretch_offset_bottom(float value) noexcept { stretch_offset_bottom_ = value; }

    /// Returns or sets the horizontal offset of the texture in points.
    [[nodiscard]] float tile_offset_x() const noexcept { return tile_offset_x_; }
    void set_tile_offset_x(float value) noexcept { tile_offset_x_ = value; }

    /// Returns or sets the vertical offset of the texture in points.
    [[nodiscard]] float tile_offset_y() const noexcept { return tile_offset_y_; }
    void set_tile_offset_y(float value) noexcept { tile_offset_y_ = value; }

    /// Returns or sets the horizontal scale for the texture fill as a percentage.
    [[nodiscard]] float tile_scale_x() const noexcept { return tile_scale_x_; }
    void set_tile_scale_x(float value) noexcept { tile_scale_x_ = value; }

    /// Returns or sets the vertical scale for the texture fill as a percentage.
    [[nodiscard]] float tile_scale_y() const noexcept { return tile_scale_y_; }
    void set_tile_scale_y(float value) noexcept { tile_scale_y_ = value; }

    /// Returns or sets the texture tile alignment.
    [[nodiscard]] RectangleAlignment tile_alignment() const noexcept { return tile_alignment_; }
    void set_tile_alignment(RectangleAlignment value) noexcept { tile_alignment_ = value; }

    /// Returns or sets the texture tile flip mode.
    [[nodiscard]] TileFlip tile_flip() const noexcept { return tile_flip_; }
    void set_tile_flip(TileFlip value) noexcept { tile_flip_ = value; }

    /// Returns the image used for the picture fill.
    [[nodiscard]] PPImage* image() const noexcept { return image_; }
    void set_image(PPImage* img) noexcept { image_ = img; }

private:
    int dpi_ = 0;
    PictureFillMode mode_ = PictureFillMode::TILE;
    Picture picture_{nullptr};
    float crop_left_ = 0.0f;
    float crop_top_ = 0.0f;
    float crop_right_ = 0.0f;
    float crop_bottom_ = 0.0f;
    float stretch_offset_left_ = 0.0f;
    float stretch_offset_top_ = 0.0f;
    float stretch_offset_right_ = 0.0f;
    float stretch_offset_bottom_ = 0.0f;
    float tile_offset_x_ = 0.0f;
    float tile_offset_y_ = 0.0f;
    float tile_scale_x_ = 0.0f;
    float tile_scale_y_ = 0.0f;
    RectangleAlignment tile_alignment_ = RectangleAlignment::NOT_DEFINED;
    TileFlip tile_flip_ = TileFlip::NOT_DEFINED;
    PPImage* image_ = nullptr;

    pugi::xml_node blip_fill_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
