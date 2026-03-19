// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/rectangle_alignment.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/tile_flip.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: create a shape with picture fill and return its PictureFillFormat.
PictureFillFormat& make_picture_fill(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 200);
    shape.fill_format().set_fill_type(FillType::PICTURE);
    return shape.fill_format().picture_fill_format();
}

} // namespace

/// Picture fill with an image persists.
/// Ports: test_picture_fill
TEST(IPictureFillFormatTest, PictureFillWithImage) {
    // Minimal 1x1 green PNG.
    std::vector<std::uint8_t> png_data = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
        0xDE, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41,
        0x54, 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC,
        0x33, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E,
        0x44, 0xAE, 0x42, 0x60, 0x82};

    Presentation pres;
    auto& pff = make_picture_fill(pres);
    pff.set_picture_fill_mode(PictureFillMode::STRETCH);

    auto& img = pres.images().add_image(png_data);
    pff.picture().set_image(&img);

    EXPECT_EQ(pres.slides()[0].shapes()[0].fill_format().fill_type(),
              FillType::PICTURE);
    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::STRETCH);
    EXPECT_EQ(pff.picture().image(), &img);
}

/// DPI defaults to 0 and can be set.
TEST(IPictureFillFormatTest, Dpi) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_EQ(pff.dpi(), 0);
    pff.set_dpi(150);
    EXPECT_EQ(pff.dpi(), 150);
}

/// Crop properties default to 0 and can be set.
TEST(IPictureFillFormatTest, CropProperties) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_FLOAT_EQ(pff.crop_left(), 0.0f);
    EXPECT_FLOAT_EQ(pff.crop_top(), 0.0f);
    EXPECT_FLOAT_EQ(pff.crop_right(), 0.0f);
    EXPECT_FLOAT_EQ(pff.crop_bottom(), 0.0f);

    pff.set_crop_left(10.0f);
    pff.set_crop_top(20.0f);
    pff.set_crop_right(30.0f);
    pff.set_crop_bottom(40.0f);

    EXPECT_FLOAT_EQ(pff.crop_left(), 10.0f);
    EXPECT_FLOAT_EQ(pff.crop_top(), 20.0f);
    EXPECT_FLOAT_EQ(pff.crop_right(), 30.0f);
    EXPECT_FLOAT_EQ(pff.crop_bottom(), 40.0f);
}

/// Stretch offset properties default to 0 and can be set.
TEST(IPictureFillFormatTest, StretchOffsetProperties) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_FLOAT_EQ(pff.stretch_offset_left(), 0.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_top(), 0.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_right(), 0.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_bottom(), 0.0f);

    pff.set_stretch_offset_left(5.0f);
    pff.set_stretch_offset_top(-10.0f);
    pff.set_stretch_offset_right(15.0f);
    pff.set_stretch_offset_bottom(-20.0f);

    EXPECT_FLOAT_EQ(pff.stretch_offset_left(), 5.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_top(), -10.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_right(), 15.0f);
    EXPECT_FLOAT_EQ(pff.stretch_offset_bottom(), -20.0f);
}

/// Tile offset properties default to 0 and can be set.
TEST(IPictureFillFormatTest, TileOffsetProperties) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_FLOAT_EQ(pff.tile_offset_x(), 0.0f);
    EXPECT_FLOAT_EQ(pff.tile_offset_y(), 0.0f);

    pff.set_tile_offset_x(25.5f);
    pff.set_tile_offset_y(-30.0f);

    EXPECT_FLOAT_EQ(pff.tile_offset_x(), 25.5f);
    EXPECT_FLOAT_EQ(pff.tile_offset_y(), -30.0f);
}

/// Tile scale properties default to 0 and can be set.
TEST(IPictureFillFormatTest, TileScaleProperties) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_FLOAT_EQ(pff.tile_scale_x(), 0.0f);
    EXPECT_FLOAT_EQ(pff.tile_scale_y(), 0.0f);

    pff.set_tile_scale_x(150.0f);
    pff.set_tile_scale_y(75.0f);

    EXPECT_FLOAT_EQ(pff.tile_scale_x(), 150.0f);
    EXPECT_FLOAT_EQ(pff.tile_scale_y(), 75.0f);
}

/// Tile alignment defaults to NOT_DEFINED and can be set.
TEST(IPictureFillFormatTest, TileAlignment) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_EQ(pff.tile_alignment(), RectangleAlignment::NOT_DEFINED);

    pff.set_tile_alignment(RectangleAlignment::CENTER);
    EXPECT_EQ(pff.tile_alignment(), RectangleAlignment::CENTER);

    pff.set_tile_alignment(RectangleAlignment::TOP_LEFT);
    EXPECT_EQ(pff.tile_alignment(), RectangleAlignment::TOP_LEFT);
}

/// Tile flip defaults to NOT_DEFINED and can be set.
TEST(IPictureFillFormatTest, TileFlip) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_EQ(pff.tile_flip(), TileFlip::NOT_DEFINED);

    pff.set_tile_flip(TileFlip::FLIP_X);
    EXPECT_EQ(pff.tile_flip(), TileFlip::FLIP_X);

    pff.set_tile_flip(TileFlip::FLIP_BOTH);
    EXPECT_EQ(pff.tile_flip(), TileFlip::FLIP_BOTH);
}

/// Picture fill mode defaults to TILE and can be toggled.
TEST(IPictureFillFormatTest, PictureFillMode) {
    Presentation pres;
    auto& pff = make_picture_fill(pres);

    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::TILE);

    pff.set_picture_fill_mode(PictureFillMode::STRETCH);
    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::STRETCH);

    pff.set_picture_fill_mode(PictureFillMode::TILE);
    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::TILE);
}
