// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_dash_style.h>
#include <Aspose/Slides/Foss/line_format.h>
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

/// Line colour and width can be set and read back.
/// Ports: test_line_color_and_width
TEST(LineFormatTest, LineColorAndWidth) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    auto& lf = shape.line_format();
    lf.set_width(5);
    lf.fill_format().set_fill_type(FillType::SOLID);
    lf.fill_format().solid_fill_color().set_color(Drawing::Color::dark_red);

    EXPECT_EQ(lf.width(), 5);
    EXPECT_EQ(lf.fill_format().fill_type(), FillType::SOLID);
    auto c = lf.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), Drawing::Color::dark_red.r());
}

/// Dash style persists in memory.
/// Ports: test_line_dash_style
TEST(LineFormatTest, LineDashStyle) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);

    auto& lf = shape.line_format();
    lf.set_width(3);
    lf.set_dash_style(LineDashStyle::DASH);
    lf.fill_format().set_fill_type(FillType::SOLID);
    lf.fill_format().solid_fill_color().set_color(Drawing::Color::black);

    EXPECT_EQ(lf.dash_style(), LineDashStyle::DASH);
    EXPECT_EQ(lf.width(), 3);
    EXPECT_EQ(lf.fill_format().fill_type(), FillType::SOLID);
}

/// Various dash styles can be set in-memory.
/// Ports: test_multiple_dash_styles
TEST(LineFormatTest, MultipleDashStyles) {
    LineDashStyle styles[] = {
        LineDashStyle::SOLID,
        LineDashStyle::DASH,
        LineDashStyle::DOT,
        LineDashStyle::DASH_DOT,
    };

    Presentation pres;
    auto& slide = pres.slides()[0];
    for (auto style : styles) {
        auto& shape = slide.shapes().add_auto_shape(
            ShapeType::RECTANGLE, 50, 50, 200, 50);
        shape.line_format().set_dash_style(style);
        EXPECT_EQ(shape.line_format().dash_style(), style);
    }
}
