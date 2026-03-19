// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: create minimal valid PNG data for constructing a PPImage.
std::vector<std::uint8_t> create_test_png() {
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
        0xDE, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41,
        0x54, 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC,
        0x33, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E,
        0x44, 0xAE, 0x42, 0x60, 0x82};
}

/// Helper: return a slide with all shapes cleared.
Slide& blank_slide(Presentation& pres) {
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    return slide;
}

} // namespace

// ---------- PictureFrame properties ----------

TEST(PictureFrameTest, ShapeTypeDefaultsToConstructorValue) {
    PPImage img(create_test_png(), "image/png");
    PictureFrame pf(ShapeType::RECTANGLE, 10, 20, 300, 200, &img);
    EXPECT_EQ(pf.shape_type(), ShapeType::RECTANGLE);
}

TEST(PictureFrameTest, ShapeTypeCanBeChanged) {
    PPImage img(create_test_png(), "image/png");
    PictureFrame pf(ShapeType::RECTANGLE, 0, 0, 100, 100, &img);
    pf.set_shape_type(ShapeType::ELLIPSE);
    EXPECT_EQ(pf.shape_type(), ShapeType::ELLIPSE);
}

TEST(PictureFrameTest, RelativeScaleHeightDefaultsToOne) {
    PictureFrame pf;
    EXPECT_DOUBLE_EQ(pf.relative_scale_height(), 1.0);
}

TEST(PictureFrameTest, RelativeScaleHeightGetSet) {
    PictureFrame pf;
    pf.set_relative_scale_height(0.5);
    EXPECT_DOUBLE_EQ(pf.relative_scale_height(), 0.5);
    pf.set_relative_scale_height(2.0);
    EXPECT_DOUBLE_EQ(pf.relative_scale_height(), 2.0);
}

TEST(PictureFrameTest, RelativeScaleWidthDefaultsToOne) {
    PictureFrame pf;
    EXPECT_DOUBLE_EQ(pf.relative_scale_width(), 1.0);
}

TEST(PictureFrameTest, RelativeScaleWidthGetSet) {
    PictureFrame pf;
    pf.set_relative_scale_width(0.75);
    EXPECT_DOUBLE_EQ(pf.relative_scale_width(), 0.75);
}

TEST(PictureFrameTest, IsCameoAlwaysFalse) {
    PictureFrame pf;
    EXPECT_FALSE(pf.is_cameo());

    PPImage img(create_test_png(), "image/png");
    PictureFrame pf2(ShapeType::RECTANGLE, 0, 0, 100, 100, &img);
    EXPECT_FALSE(pf2.is_cameo());
}

TEST(PictureFrameTest, PictureFrameLockReturnsNullptr) {
    PictureFrame pf;
    EXPECT_EQ(pf.picture_frame_lock(), nullptr);
}

TEST(PictureFrameTest, PictureFormatNullByDefault) {
    PictureFrame pf;
    EXPECT_EQ(pf.picture_format(), nullptr);
}

TEST(PictureFrameTest, EnsurePictureFormatEnablesAccess) {
    PictureFrame pf;
    auto& fmt = pf.ensure_picture_format();
    EXPECT_NE(pf.picture_format(), nullptr);
    fmt.set_picture_fill_mode(PictureFillMode::STRETCH);
    EXPECT_EQ(pf.picture_format()->picture_fill_mode(), PictureFillMode::STRETCH);
}

TEST(PictureFrameTest, ImageGetSet) {
    PictureFrame pf;
    EXPECT_EQ(pf.pp_image(), nullptr);

    PPImage img(create_test_png(), "image/png");
    pf.set_pp_image(&img);
    EXPECT_EQ(pf.pp_image(), &img);
}


TEST(PictureFrameTest, AddAutoShapePreservesType) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    EXPECT_EQ(slide.shapes().size(), 1u);
    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
}

TEST(PictureFrameTest, MultipleShapeTypes) {
    ShapeType types[] = {ShapeType::RECTANGLE, ShapeType::ELLIPSE, ShapeType::TRIANGLE};
    Presentation pres;
    auto& slide = blank_slide(pres);
    for (auto st : types) {
        auto& s = slide.shapes().add_auto_shape(st, 10, 10, 100, 100);
        EXPECT_EQ(s.shape_type(), st);
    }
    EXPECT_EQ(slide.shapes().size(), 3u);
}

TEST(PictureFrameTest, ReorderShapes) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    auto& ellipse = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    slide.shapes().reorder(0, ellipse);
    EXPECT_EQ(slide.shapes()[0].shape_type(), ShapeType::ELLIPSE);
}

// Since there is no PPTX serialization yet, we verify properties are retained.
TEST(PictureFrameTest, ShapePersistsProperties) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(shape.x(), 50);
    EXPECT_EQ(shape.y(), 50);
    EXPECT_EQ(shape.width(), 200);
    EXPECT_EQ(shape.height(), 100);
    EXPECT_EQ(slide.shapes().size(), 1u);
}


TEST(PictureFrameTest, AddStraightConnectorPreservesType) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& conn = slide.shapes().add_connector(
        ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);
    EXPECT_EQ(conn.shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
}

TEST(PictureFrameTest, ConnectShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();

    auto& s1 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 100, 60);
    auto& s2 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 350, 200, 100, 60);
    auto& conn = slide.shapes().add_connector(ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);

    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);

    EXPECT_NE(conn.start_shape_connected_to(), nullptr);
    EXPECT_NE(conn.end_shape_connected_to(), nullptr);
    EXPECT_EQ(conn.start_shape_connection_site_index(), 3u);
    EXPECT_EQ(conn.end_shape_connection_site_index(), 1u);
}

// ---------- PictureFrame via ShapeCollection ----------

TEST(PictureFrameTest, AddPictureFrameViaCollection) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    PPImage img(create_test_png(), "image/png");
    auto& pf = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 100, 100, 200, 150, img);

    EXPECT_EQ(pf.shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(pf.pp_image(), &img);
    EXPECT_EQ(pf.x(), 100);
    EXPECT_EQ(pf.y(), 100);
    EXPECT_EQ(pf.width(), 200);
    EXPECT_EQ(pf.height(), 150);
    EXPECT_DOUBLE_EQ(pf.relative_scale_height(), 1.0);
    EXPECT_DOUBLE_EQ(pf.relative_scale_width(), 1.0);
    EXPECT_FALSE(pf.is_cameo());
}
