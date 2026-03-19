// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/pattern_format.h>
#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: create a shape with pattern fill and return its PatternFormat.
PatternFormat& make_pattern_fill(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);
    shape.fill_format().set_fill_type(FillType::PATTERN);
    return shape.fill_format().pattern_format();
}

} // namespace

/// Pattern style and colours persist.
/// Ports: test_pattern_fill
TEST(IPatternFormatTest, PatternStyleAndColors) {
    Presentation pres;
    auto& pf = make_pattern_fill(pres);
    pf.set_pattern_style(PatternStyle::PERCENT50);
    pf.fore_color().set_color(Drawing::Color::dark_blue);
    pf.back_color().set_color(Drawing::Color::light_yellow);

    EXPECT_EQ(pres.slides()[0].shapes()[0].fill_format().fill_type(),
              FillType::PATTERN);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::PERCENT50);
    EXPECT_EQ(pf.fore_color().color(), Drawing::Color::dark_blue);
    EXPECT_EQ(pf.back_color().color(), Drawing::Color::light_yellow);
}

/// Pattern style defaults to NOT_DEFINED.
TEST(IPatternFormatTest, DefaultPatternStyle) {
    Presentation pres;
    auto& pf = make_pattern_fill(pres);

    EXPECT_EQ(pf.pattern_style(), PatternStyle::NOT_DEFINED);
}

/// Pattern style can be changed after initial assignment.
TEST(IPatternFormatTest, ChangePatternStyle) {
    Presentation pres;
    auto& pf = make_pattern_fill(pres);

    pf.set_pattern_style(PatternStyle::PERCENT50);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::PERCENT50);

    pf.set_pattern_style(PatternStyle::DIAGONAL_CROSS);
    EXPECT_EQ(pf.pattern_style(), PatternStyle::DIAGONAL_CROSS);
}

/// Foreground and background colors are independent.
TEST(IPatternFormatTest, ForeAndBackColorIndependent) {
    Presentation pres;
    auto& pf = make_pattern_fill(pres);

    pf.fore_color().set_color(Drawing::Color::red);
    pf.back_color().set_color(Drawing::Color::green);

    EXPECT_EQ(pf.fore_color().color(), Drawing::Color::red);
    EXPECT_EQ(pf.back_color().color(), Drawing::Color::green);
    EXPECT_NE(pf.fore_color().color(), pf.back_color().color());
}
