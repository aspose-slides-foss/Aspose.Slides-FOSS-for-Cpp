// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/i_table_format.h>
#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/table_format.h>

using namespace Aspose::Slides::Foss;

/// fill_format() returns a mutable FillFormat whose fill_type defaults to NOT_DEFINED.
/// Ports: ITableFormat.fill_format property (read-only accessor)
TEST(TableFormatTest, FillFormatDefaultIsNotDefined) {
    TableFormat tf;
    EXPECT_EQ(tf.fill_format().fill_type(), FillType::NOT_DEFINED);
}

/// fill_format() is accessible through the ITableFormat interface.
/// Ports: ITableFormat.fill_format property (polymorphic access)
TEST(TableFormatTest, FillFormatViaInterface) {
    TableFormat tf;
    ITableFormat& itf = tf;

    itf.fill_format().set_fill_type(FillType::SOLID);
    itf.fill_format().solid_fill_color().set_color(
        Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_EQ(itf.fill_format().fill_type(), FillType::SOLID);
    auto c = itf.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

/// const fill_format() is accessible through a const ITableFormat reference.
/// Ports: ITableFormat.fill_format property (const access)
TEST(TableFormatTest, ConstFillFormatAccess) {
    TableFormat tf;
    tf.fill_format().set_fill_type(FillType::NO_FILL);

    const ITableFormat& citf = tf;
    EXPECT_EQ(citf.fill_format().fill_type(), FillType::NO_FILL);
}

/// Gradient fill can be configured through ITableFormat.fill_format().
/// Ports: test_gradient_fill (via table format path)
TEST(TableFormatTest, GradientFillViaTableFormat) {
    TableFormat tf;
    tf.fill_format().set_fill_type(FillType::GRADIENT);

    auto& gf = tf.fill_format().gradient_format();
    gf.set_gradient_shape(GradientShape::LINEAR);
    gf.set_linear_gradient_angle(45);
    gf.gradient_stops().add(0.0f, Drawing::Color::blue);
    gf.gradient_stops().add(1.0f, Drawing::Color::red);

    EXPECT_EQ(tf.fill_format().fill_type(), FillType::GRADIENT);
    EXPECT_GE(gf.gradient_stops().size(), 2u);
}

/// Pattern fill can be configured through ITableFormat.fill_format().
/// Ports: test_pattern_fill (via table format path)
TEST(TableFormatTest, PatternFillViaTableFormat) {
    TableFormat tf;
    tf.fill_format().set_fill_type(FillType::PATTERN);

    auto& pf = tf.fill_format().pattern_format();
    pf.set_pattern_style(PatternStyle::PERCENT50);
    pf.fore_color().set_color(Drawing::Color::dark_blue);
    pf.back_color().set_color(Drawing::Color::light_yellow);

    EXPECT_EQ(tf.fill_format().fill_type(), FillType::PATTERN);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::PERCENT50);
}

/// NO_FILL type can be set through ITableFormat.fill_format().
/// Ports: test_no_fill (via table format path)
TEST(TableFormatTest, NoFillViaTableFormat) {
    TableFormat tf;
    ITableFormat& itf = tf;
    itf.fill_format().set_fill_type(FillType::NO_FILL);

    EXPECT_EQ(itf.fill_format().fill_type(), FillType::NO_FILL);
}
