// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_dash_style.h>

using namespace Aspose::Slides::Foss;

/// CellFormat fill_format accessor returns a modifiable FillFormat.
/// Ports: CellFormat.fill_format property
TEST(CellFormatTest, FillFormat) {
    CellFormat cf;

    cf.fill_format().set_fill_type(FillType::SOLID);
    cf.fill_format().solid_fill_color().set_color(
        Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_EQ(cf.fill_format().fill_type(), FillType::SOLID);
    auto c = cf.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

/// Each border accessor returns an independent LineFormat.
/// Ports: CellFormat.border_left, border_top, border_right, border_bottom
TEST(CellFormatTest, BorderAccessors) {
    CellFormat cf;

    cf.border_left().set_width(1.0);
    cf.border_top().set_width(2.0);
    cf.border_right().set_width(3.0);
    cf.border_bottom().set_width(4.0);

    EXPECT_EQ(cf.border_left().width(), 1.0);
    EXPECT_EQ(cf.border_top().width(), 2.0);
    EXPECT_EQ(cf.border_right().width(), 3.0);
    EXPECT_EQ(cf.border_bottom().width(), 4.0);
}

/// Diagonal border accessors return independent LineFormats.
/// Ports: CellFormat.border_diagonal_down, border_diagonal_up
TEST(CellFormatTest, DiagonalBorderAccessors) {
    CellFormat cf;

    cf.border_diagonal_down().set_width(1.5);
    cf.border_diagonal_down().set_dash_style(LineDashStyle::DASH);

    cf.border_diagonal_up().set_width(2.5);
    cf.border_diagonal_up().set_dash_style(LineDashStyle::DOT);

    EXPECT_EQ(cf.border_diagonal_down().width(), 1.5);
    EXPECT_EQ(cf.border_diagonal_down().dash_style(), LineDashStyle::DASH);
    EXPECT_EQ(cf.border_diagonal_up().width(), 2.5);
    EXPECT_EQ(cf.border_diagonal_up().dash_style(), LineDashStyle::DOT);
}

/// Border line fill format can be configured for color.
/// Ports: border line color via _get_border + LineFormat
TEST(CellFormatTest, BorderFillFormat) {
    CellFormat cf;

    cf.border_left().fill_format().set_fill_type(FillType::SOLID);
    cf.border_left().fill_format().solid_fill_color().set_color(
        Drawing::Color::dark_red);

    EXPECT_EQ(cf.border_left().fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(cf.border_left().fill_format().solid_fill_color().color().r(),
              Drawing::Color::dark_red.r());
}

/// Const accessors compile and return the same values.
TEST(CellFormatTest, ConstAccessors) {
    CellFormat cf;
    cf.fill_format().set_fill_type(FillType::NO_FILL);
    cf.border_left().set_width(5.0);

    const CellFormat& ccf = cf;
    EXPECT_EQ(ccf.fill_format().fill_type(), FillType::NO_FILL);
    EXPECT_EQ(ccf.border_left().width(), 5.0);
}

/// All borders default to zero width and NOT_DEFINED dash style.
TEST(CellFormatTest, DefaultValues) {
    CellFormat cf;

    EXPECT_EQ(cf.fill_format().fill_type(), FillType::NOT_DEFINED);
    EXPECT_EQ(cf.border_left().width(), 0.0);
    EXPECT_EQ(cf.border_top().width(), 0.0);
    EXPECT_EQ(cf.border_right().width(), 0.0);
    EXPECT_EQ(cf.border_bottom().width(), 0.0);
    EXPECT_EQ(cf.border_diagonal_down().width(), 0.0);
    EXPECT_EQ(cf.border_diagonal_up().width(), 0.0);
    EXPECT_EQ(cf.border_left().dash_style(), LineDashStyle::NOT_DEFINED);
}
