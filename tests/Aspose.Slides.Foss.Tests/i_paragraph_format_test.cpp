// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <cmath>
#include <limits>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/bullet_format.h>
#include <Aspose/Slides/Foss/font_alignment.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/text_alignment.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// IParagraphFormat interface tests exercised through ParagraphFormat.
// ---------------------------------------------------------------------------

class IParagraphFormatTest : public ::testing::Test {
protected:
    ParagraphFormat fmt;
};

TEST_F(IParagraphFormatTest, AlignmentDefaultIsNotDefined) {
    EXPECT_EQ(fmt.alignment(), TextAlignment::NOT_DEFINED);
}

TEST_F(IParagraphFormatTest, AlignmentSetCenter) {
    fmt.set_alignment(TextAlignment::CENTER);
    EXPECT_EQ(fmt.alignment(), TextAlignment::CENTER);
}

TEST_F(IParagraphFormatTest, AlignmentSetThroughInterface) {
    IParagraphFormat* ip = &fmt;
    ip->set_alignment(TextAlignment::RIGHT);
    EXPECT_EQ(ip->alignment(), TextAlignment::RIGHT);
}

TEST_F(IParagraphFormatTest, AlignmentAllValues) {
    for (auto a : {TextAlignment::LEFT, TextAlignment::CENTER,
                   TextAlignment::RIGHT, TextAlignment::JUSTIFY,
                   TextAlignment::JUSTIFY_LOW, TextAlignment::DISTRIBUTED}) {
        fmt.set_alignment(a);
        EXPECT_EQ(fmt.alignment(), a);
    }
}

TEST_F(IParagraphFormatTest, DepthDefaultIsZero) {
    EXPECT_EQ(fmt.depth(), 0);
}

TEST_F(IParagraphFormatTest, DepthSetAndGet) {
    fmt.set_depth(3);
    EXPECT_EQ(fmt.depth(), 3);
}

TEST_F(IParagraphFormatTest, DepthThroughInterface) {
    IParagraphFormat* ip = &fmt;
    ip->set_depth(5);
    EXPECT_EQ(ip->depth(), 5);
}

// Spacing properties
TEST_F(IParagraphFormatTest, SpaceWithinDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.space_within()));
}

TEST_F(IParagraphFormatTest, SpaceWithinSetPositivePercentage) {
    fmt.set_space_within(150.0);
    EXPECT_DOUBLE_EQ(fmt.space_within(), 150.0);
}

TEST_F(IParagraphFormatTest, SpaceWithinSetNegativePoints) {
    fmt.set_space_within(-12.0);
    EXPECT_DOUBLE_EQ(fmt.space_within(), -12.0);
}

TEST_F(IParagraphFormatTest, SpaceBeforeDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.space_before()));
}

TEST_F(IParagraphFormatTest, SpaceBeforeSetAndGet) {
    fmt.set_space_before(20.0);
    EXPECT_DOUBLE_EQ(fmt.space_before(), 20.0);
}

TEST_F(IParagraphFormatTest, SpaceAfterDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.space_after()));
}

TEST_F(IParagraphFormatTest, SpaceAfterSetAndGet) {
    fmt.set_space_after(-8.0);
    EXPECT_DOUBLE_EQ(fmt.space_after(), -8.0);
}

// NullableBool properties
TEST_F(IParagraphFormatTest, EastAsianLineBreakDefault) {
    EXPECT_EQ(fmt.east_asian_line_break(), NullableBool::NOT_DEFINED);
}

TEST_F(IParagraphFormatTest, EastAsianLineBreakSetTrue) {
    fmt.set_east_asian_line_break(NullableBool::TRUE);
    EXPECT_EQ(fmt.east_asian_line_break(), NullableBool::TRUE);
}

TEST_F(IParagraphFormatTest, RightToLeftDefault) {
    EXPECT_EQ(fmt.right_to_left(), NullableBool::NOT_DEFINED);
}

TEST_F(IParagraphFormatTest, RightToLeftSetTrue) {
    fmt.set_right_to_left(NullableBool::TRUE);
    EXPECT_EQ(fmt.right_to_left(), NullableBool::TRUE);
}

TEST_F(IParagraphFormatTest, LatinLineBreakDefault) {
    EXPECT_EQ(fmt.latin_line_break(), NullableBool::NOT_DEFINED);
}

TEST_F(IParagraphFormatTest, LatinLineBreakSetFalse) {
    fmt.set_latin_line_break(NullableBool::FALSE);
    EXPECT_EQ(fmt.latin_line_break(), NullableBool::FALSE);
}

TEST_F(IParagraphFormatTest, HangingPunctuationDefault) {
    EXPECT_EQ(fmt.hanging_punctuation(), NullableBool::NOT_DEFINED);
}

TEST_F(IParagraphFormatTest, HangingPunctuationSetTrue) {
    fmt.set_hanging_punctuation(NullableBool::TRUE);
    EXPECT_EQ(fmt.hanging_punctuation(), NullableBool::TRUE);
}

// Margin and indent properties
TEST_F(IParagraphFormatTest, MarginLeftDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.margin_left()));
}

TEST_F(IParagraphFormatTest, MarginLeftSetAndGet) {
    fmt.set_margin_left(36.0);
    EXPECT_DOUBLE_EQ(fmt.margin_left(), 36.0);
}

TEST_F(IParagraphFormatTest, MarginRightDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.margin_right()));
}

TEST_F(IParagraphFormatTest, MarginRightSetAndGet) {
    fmt.set_margin_right(24.0);
    EXPECT_DOUBLE_EQ(fmt.margin_right(), 24.0);
}

TEST_F(IParagraphFormatTest, IndentDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.indent()));
}

TEST_F(IParagraphFormatTest, IndentSetPositive) {
    fmt.set_indent(18.0);
    EXPECT_DOUBLE_EQ(fmt.indent(), 18.0);
}

TEST_F(IParagraphFormatTest, IndentSetNegativeHanging) {
    fmt.set_indent(-14.0);
    EXPECT_DOUBLE_EQ(fmt.indent(), -14.0);
}

TEST_F(IParagraphFormatTest, DefaultTabSizeDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.default_tab_size()));
}

TEST_F(IParagraphFormatTest, DefaultTabSizeSetAndGet) {
    fmt.set_default_tab_size(72.0);
    EXPECT_DOUBLE_EQ(fmt.default_tab_size(), 72.0);
}

// Font alignment
TEST_F(IParagraphFormatTest, FontAlignmentDefaultIsDefault) {
    EXPECT_EQ(fmt.font_alignment(), FontAlignment::DEFAULT);
}

TEST_F(IParagraphFormatTest, FontAlignmentSetBaseline) {
    fmt.set_font_alignment(FontAlignment::BASELINE);
    EXPECT_EQ(fmt.font_alignment(), FontAlignment::BASELINE);
}

// Bullet access (read-only sub-object)
TEST_F(IParagraphFormatTest, BulletAccessible) {
    IBulletFormat& b = fmt.bullet();
    b.set_type(BulletType::SYMBOL);
    EXPECT_EQ(fmt.bullet().type(), BulletType::SYMBOL);
}

TEST_F(IParagraphFormatTest, BulletAccessThroughInterface) {
    IParagraphFormat* ip = &fmt;
    ip->bullet().set_type(BulletType::NUMBERED);
    EXPECT_EQ(ip->bullet().type(), BulletType::NUMBERED);
}

TEST_F(IParagraphFormatTest, BulletConstAccess) {
    const IParagraphFormat* ip = &fmt;
    EXPECT_EQ(ip->bullet().type(), BulletType::NOT_DEFINED);
}

// Default portion format access (read-only sub-object)
TEST_F(IParagraphFormatTest, DefaultPortionFormatAccessible) {
    PortionFormat& pf = fmt.default_portion_format();
    (void)pf; // Should compile and not crash.
}

TEST_F(IParagraphFormatTest, DefaultPortionFormatThroughInterface) {
    IParagraphFormat* ip = &fmt;
    PortionFormat& pf = ip->default_portion_format();
    (void)pf;
}

TEST_F(IParagraphFormatTest, DefaultPortionFormatConstAccess) {
    const IParagraphFormat* ip = &fmt;
    const PortionFormat& pf = ip->default_portion_format();
    (void)pf;
}
