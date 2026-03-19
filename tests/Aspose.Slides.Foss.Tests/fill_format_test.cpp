// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: clear shapes from first slide and return a reference.
Slide& clear_slide(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    return pres.slides()[0];
}

} // namespace

/// Solid fill colour can be set and read back.
/// Ports: test_solid_fill
TEST(FillFormatTest, SolidFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    shape.fill_format().set_fill_type(FillType::SOLID);
    shape.fill_format().solid_fill_color().set_color(
        Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::SOLID);
    auto c = shape.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

/// Gradient stops and angle can be set and read back.
/// Ports: test_gradient_fill
TEST(FillFormatTest, GradientFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 150);

    shape.fill_format().set_fill_type(FillType::GRADIENT);
    auto& gf = shape.fill_format().gradient_format();
    gf.set_gradient_shape(GradientShape::LINEAR);
    gf.set_linear_gradient_angle(45);
    gf.gradient_stops().add(0.0f, Drawing::Color::blue);
    gf.gradient_stops().add(1.0f, Drawing::Color::red);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::GRADIENT);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::LINEAR);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 45.0f);
    ASSERT_GE(gf.gradient_stops().size(), 2u);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[1].position(), 1.0f);
}

/// Pattern style and colours can be set and read back.
/// Ports: test_pattern_fill
TEST(FillFormatTest, PatternFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    shape.fill_format().set_fill_type(FillType::PATTERN);
    auto& pf = shape.fill_format().pattern_format();
    pf.set_pattern_style(PatternStyle::PERCENT50);
    pf.fore_color().set_color(Drawing::Color::dark_blue);
    pf.back_color().set_color(Drawing::Color::light_yellow);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::PATTERN);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::PERCENT50);
    EXPECT_EQ(pf.fore_color().color(), Drawing::Color::dark_blue);
    EXPECT_EQ(pf.back_color().color(), Drawing::Color::light_yellow);
}

/// NO_FILL type can be set and read back.
/// Ports: test_no_fill
TEST(FillFormatTest, NoFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    shape.fill_format().set_fill_type(FillType::NO_FILL);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::NO_FILL);
}

/// Picture fill with mode can be set and read back via shape.
/// Ports: test_picture_fill
TEST(FillFormatTest, PictureFillViaShape) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 200);

    shape.fill_format().set_fill_type(FillType::PICTURE);
    shape.fill_format().picture_fill_format().set_picture_fill_mode(
        PictureFillMode::STRETCH);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::PICTURE);
    EXPECT_EQ(shape.fill_format().picture_fill_format().picture_fill_mode(),
              PictureFillMode::STRETCH);
}

/// rotate_with_shape defaults to NOT_DEFINED and can be toggled.
/// Ports: rotate_with_shape property
TEST(FillFormatTest, RotateWithShape) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    EXPECT_EQ(shape.fill_format().rotate_with_shape(), NullableBool::NOT_DEFINED);

    shape.fill_format().set_fill_type(FillType::SOLID);
    shape.fill_format().set_rotate_with_shape(NullableBool::TRUE);
    EXPECT_EQ(shape.fill_format().rotate_with_shape(), NullableBool::TRUE);

    shape.fill_format().set_rotate_with_shape(NullableBool::FALSE);
    EXPECT_EQ(shape.fill_format().rotate_with_shape(), NullableBool::FALSE);

    shape.fill_format().set_rotate_with_shape(NullableBool::NOT_DEFINED);
    EXPECT_EQ(shape.fill_format().rotate_with_shape(), NullableBool::NOT_DEFINED);
}

/// Picture fill with an image set via picture().set_image() persists.
/// Ports: test_picture_fill (image assignment path)
TEST(FillFormatTest, PictureFillWithImage) {
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
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 200);

    shape.fill_format().set_fill_type(FillType::PICTURE);
    auto& pff = shape.fill_format().picture_fill_format();
    pff.set_picture_fill_mode(PictureFillMode::STRETCH);

    auto& img = pres.images().add_image(png_data);
    pff.picture().set_image(&img);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::PICTURE);
    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::STRETCH);
    EXPECT_EQ(pff.picture().image(), &img);
}
