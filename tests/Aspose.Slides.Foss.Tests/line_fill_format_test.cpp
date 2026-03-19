// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/i_line_fill_format.h>
#include <Aspose/Slides/Foss/line_fill_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/pattern_style.h>

using namespace Aspose::Slides::Foss;

/// Solid fill colour can be set and read back on a LineFillFormat.
/// Ports: test_solid_fill (adapted for line fill)
TEST(LineFillFormatTest, SolidFill) {
    LineFillFormat lff;
    lff.set_fill_type(FillType::SOLID);
    lff.solid_fill_color().set_color(
        Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_EQ(lff.fill_type(), FillType::SOLID);
    auto c = lff.solid_fill_color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

/// Gradient stops and angle can be set and read back.
/// Ports: test_gradient_fill (adapted for line fill)
TEST(LineFillFormatTest, GradientFill) {
    LineFillFormat lff;
    lff.set_fill_type(FillType::GRADIENT);
    auto& gf = lff.gradient_format();
    gf.set_gradient_shape(GradientShape::LINEAR);
    gf.set_linear_gradient_angle(45);
    gf.gradient_stops().add(0.0f, Drawing::Color::blue);
    gf.gradient_stops().add(1.0f, Drawing::Color::red);

    EXPECT_EQ(lff.fill_type(), FillType::GRADIENT);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::LINEAR);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 45.0f);
    ASSERT_GE(gf.gradient_stops().size(), 2u);
}

/// Pattern style and colours can be set and read back.
/// Ports: test_pattern_fill (adapted for line fill)
TEST(LineFillFormatTest, PatternFill) {
    LineFillFormat lff;
    lff.set_fill_type(FillType::PATTERN);
    auto& pf = lff.pattern_format();
    pf.set_pattern_style(PatternStyle::PERCENT50);
    pf.fore_color().set_color(Drawing::Color::dark_blue);
    pf.back_color().set_color(Drawing::Color::light_yellow);

    EXPECT_EQ(lff.fill_type(), FillType::PATTERN);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::PERCENT50);
    EXPECT_EQ(pf.fore_color().color(), Drawing::Color::dark_blue);
    EXPECT_EQ(pf.back_color().color(), Drawing::Color::light_yellow);
}

/// NO_FILL type can be set and read back.
/// Ports: test_no_fill (adapted for line fill)
TEST(LineFillFormatTest, NoFill) {
    LineFillFormat lff;
    lff.set_fill_type(FillType::NO_FILL);
    EXPECT_EQ(lff.fill_type(), FillType::NO_FILL);
}

/// rotate_with_shape defaults to NOT_DEFINED and can be toggled.
TEST(LineFillFormatTest, RotateWithShape) {
    LineFillFormat lff;
    EXPECT_EQ(lff.rotate_with_shape(), NullableBool::NOT_DEFINED);

    lff.set_rotate_with_shape(NullableBool::TRUE);
    EXPECT_EQ(lff.rotate_with_shape(), NullableBool::TRUE);

    lff.set_rotate_with_shape(NullableBool::FALSE);
    EXPECT_EQ(lff.rotate_with_shape(), NullableBool::FALSE);

    lff.set_rotate_with_shape(NullableBool::NOT_DEFINED);
    EXPECT_EQ(lff.rotate_with_shape(), NullableBool::NOT_DEFINED);
}

/// LineFillFormat is usable through the ILineFillFormat interface.
/// Ports: test_line_color_and_width (fill portion, via interface pointer)
TEST(LineFillFormatTest, PolymorphicAccess) {
    LineFillFormat lff;
    ILineFillFormat* iface = &lff;

    iface->set_fill_type(FillType::SOLID);
    iface->solid_fill_color().set_color(Drawing::Color::dark_red);

    EXPECT_EQ(iface->fill_type(), FillType::SOLID);
    EXPECT_EQ(iface->solid_fill_color().color().r(), Drawing::Color::dark_red.r());
}

/// Default state: fill_type is NOT_DEFINED.
TEST(LineFillFormatTest, DefaultState) {
    LineFillFormat lff;
    EXPECT_EQ(lff.fill_type(), FillType::NOT_DEFINED);
    EXPECT_EQ(lff.rotate_with_shape(), NullableBool::NOT_DEFINED);
}
