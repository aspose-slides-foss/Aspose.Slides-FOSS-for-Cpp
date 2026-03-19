// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/i_line_format.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

/// Default-constructed LineFormat reports is_format_not_defined as true.
TEST(ILineFormatTest, IsFormatNotDefinedDefault) {
    LineFormat lf;
    EXPECT_TRUE(lf.is_format_not_defined());
}

/// Setting any property makes is_format_not_defined return false.
TEST(ILineFormatTest, IsFormatNotDefinedAfterWidthSet) {
    LineFormat lf;
    lf.set_width(2.0);
    EXPECT_FALSE(lf.is_format_not_defined());
}

/// All properties are accessible through the ILineFormat interface.
TEST(ILineFormatTest, InterfaceAccessAllProperties) {
    LineFormat concrete;
    ILineFormat& lf = concrete;

    lf.set_width(3.5);
    EXPECT_EQ(lf.width(), 3.5);

    lf.set_dash_style(LineDashStyle::DASH_DOT);
    EXPECT_EQ(lf.dash_style(), LineDashStyle::DASH_DOT);

    lf.set_custom_dash_pattern({2.0f, 1.0f, 0.5f});
    auto pattern = lf.custom_dash_pattern();
    ASSERT_EQ(pattern.size(), 3u);
    EXPECT_EQ(pattern[0], 2.0f);

    lf.set_cap_style(LineCapStyle::ROUND);
    EXPECT_EQ(lf.cap_style(), LineCapStyle::ROUND);

    lf.set_style(LineStyle::THIN_THICK);
    EXPECT_EQ(lf.style(), LineStyle::THIN_THICK);

    lf.set_alignment(LineAlignment::CENTER);
    EXPECT_EQ(lf.alignment(), LineAlignment::CENTER);

    lf.set_join_style(LineJoinStyle::BEVEL);
    EXPECT_EQ(lf.join_style(), LineJoinStyle::BEVEL);

    lf.set_miter_limit(8.0);
    EXPECT_EQ(lf.miter_limit(), 8.0);

    lf.set_begin_arrowhead_style(LineArrowheadStyle::TRIANGLE);
    EXPECT_EQ(lf.begin_arrowhead_style(), LineArrowheadStyle::TRIANGLE);

    lf.set_end_arrowhead_style(LineArrowheadStyle::STEALTH);
    EXPECT_EQ(lf.end_arrowhead_style(), LineArrowheadStyle::STEALTH);

    lf.set_begin_arrowhead_width(LineArrowheadWidth::WIDE);
    EXPECT_EQ(lf.begin_arrowhead_width(), LineArrowheadWidth::WIDE);

    lf.set_end_arrowhead_width(LineArrowheadWidth::NARROW);
    EXPECT_EQ(lf.end_arrowhead_width(), LineArrowheadWidth::NARROW);

    lf.set_begin_arrowhead_length(LineArrowheadLength::LONG);
    EXPECT_EQ(lf.begin_arrowhead_length(), LineArrowheadLength::LONG);

    lf.set_end_arrowhead_length(LineArrowheadLength::SHORT);
    EXPECT_EQ(lf.end_arrowhead_length(), LineArrowheadLength::SHORT);
}

/// Ports: test_reroute — connector line format accessible after reroute.
TEST(ILineFormatTest, ConnectorLineFormatAfterReroute) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& s1 = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 50, 100, 80, 80);
    auto& s2 = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 400, 100, 80, 80);
    auto& conn = slide.shapes().add_connector(ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);
    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);
    conn.reroute();

    // After reroute the connector should span between shapes.
    EXPECT_TRUE(conn.width() > 0 || conn.height() > 0);

    // Line format is accessible and modifiable on the connector.
    ILineFormat& lf = conn.line_format();
    lf.set_width(2.0);
    EXPECT_EQ(lf.width(), 2.0);
    EXPECT_FALSE(lf.is_format_not_defined());
}

/// Ports: test_solid_fill — solid fill via line fill format interface.
TEST(ILineFormatTest, LineFillSolid) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    ILineFormat& lf = shape.line_format();
    lf.fill_format().set_fill_type(FillType::SOLID);
    lf.fill_format().solid_fill_color().set_color(Drawing::Color::dark_red);

    EXPECT_EQ(lf.fill_format().fill_type(), FillType::SOLID);
    auto c = lf.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), Drawing::Color::dark_red.r());
}

/// Ports: test_gradient_fill — gradient fill via line fill format interface.
TEST(ILineFormatTest, LineFillGradient) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 300, 150);

    ILineFormat& lf = shape.line_format();
    lf.fill_format().set_fill_type(FillType::GRADIENT);
    lf.fill_format().gradient_format().set_gradient_shape(GradientShape::LINEAR);
    lf.fill_format().gradient_format().set_linear_gradient_angle(45);
    lf.fill_format().gradient_format().gradient_stops().add(0.0f, Drawing::Color::blue);
    lf.fill_format().gradient_format().gradient_stops().add(1.0f, Drawing::Color::red);

    EXPECT_EQ(lf.fill_format().fill_type(), FillType::GRADIENT);
    EXPECT_GE(lf.fill_format().gradient_format().gradient_stops().size(), 2u);
}

/// Ports: test_pattern_fill — pattern fill via line fill format interface.
TEST(ILineFormatTest, LineFillPattern) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    ILineFormat& lf = shape.line_format();
    lf.fill_format().set_fill_type(FillType::PATTERN);
    lf.fill_format().pattern_format().set_pattern_style(PatternStyle::PERCENT50);
    lf.fill_format().pattern_format().fore_color().set_color(Drawing::Color::dark_blue);
    lf.fill_format().pattern_format().back_color().set_color(Drawing::Color::light_yellow);

    EXPECT_EQ(lf.fill_format().fill_type(), FillType::PATTERN);
    EXPECT_EQ(lf.fill_format().pattern_format().pattern_style(), PatternStyle::PERCENT50);
}

/// Ports: test_no_fill — no-fill via line fill format interface.
TEST(ILineFormatTest, LineFillNoFill) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    ILineFormat& lf = shape.line_format();
    lf.fill_format().set_fill_type(FillType::NO_FILL);

    EXPECT_EQ(lf.fill_format().fill_type(), FillType::NO_FILL);
}
