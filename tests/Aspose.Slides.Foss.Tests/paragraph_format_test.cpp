// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <cmath>
#include <limits>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/font_alignment.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/text_alignment.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// ParagraphFormat concrete class tests.
//              test_depth_and_material  (test_threed_format.py)
// ---------------------------------------------------------------------------

class ParagraphFormatTest : public ::testing::Test {
protected:
    ParagraphFormat fmt;
};

// Verifies that paragraph alignment can be set to CENTER and read back.
TEST_F(ParagraphFormatTest, AlignmentPersistsAfterSet) {
    fmt.set_alignment(TextAlignment::CENTER);
    EXPECT_EQ(fmt.alignment(), TextAlignment::CENTER);
}

// Verifies round-trip for all defined alignment values.
TEST_F(ParagraphFormatTest, AlignmentRoundTripAllValues) {
    for (auto a : {TextAlignment::LEFT, TextAlignment::CENTER,
                   TextAlignment::RIGHT, TextAlignment::JUSTIFY,
                   TextAlignment::JUSTIFY_LOW, TextAlignment::DISTRIBUTED}) {
        fmt.set_alignment(a);
        EXPECT_EQ(fmt.alignment(), a);
    }
}

TEST_F(ParagraphFormatTest, AlignmentResetToNotDefined) {
    fmt.set_alignment(TextAlignment::CENTER);
    EXPECT_EQ(fmt.alignment(), TextAlignment::CENTER);
    fmt.set_alignment(TextAlignment::NOT_DEFINED);
    EXPECT_EQ(fmt.alignment(), TextAlignment::NOT_DEFINED);
}

// Verifies that depth can be set and read back.
TEST_F(ParagraphFormatTest, DepthPersistsAfterSet) {
    fmt.set_depth(20);
    EXPECT_EQ(fmt.depth(), 20);
}

TEST_F(ParagraphFormatTest, DepthDefaultIsZero) {
    EXPECT_EQ(fmt.depth(), 0);
}

TEST_F(ParagraphFormatTest, DepthResetToZero) {
    fmt.set_depth(5);
    EXPECT_EQ(fmt.depth(), 5);
    fmt.set_depth(0);
    EXPECT_EQ(fmt.depth(), 0);
}

// Additional ParagraphFormat property tests to verify all members initialize correctly
TEST_F(ParagraphFormatTest, SpacingDefaultsAreNaN) {
    EXPECT_TRUE(std::isnan(fmt.space_within()));
    EXPECT_TRUE(std::isnan(fmt.space_before()));
    EXPECT_TRUE(std::isnan(fmt.space_after()));
}

TEST_F(ParagraphFormatTest, NullableBoolDefaultsAreNotDefined) {
    EXPECT_EQ(fmt.east_asian_line_break(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.right_to_left(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.latin_line_break(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.hanging_punctuation(), NullableBool::NOT_DEFINED);
}

TEST_F(ParagraphFormatTest, MarginAndIndentDefaultsAreNaN) {
    EXPECT_TRUE(std::isnan(fmt.margin_left()));
    EXPECT_TRUE(std::isnan(fmt.margin_right()));
    EXPECT_TRUE(std::isnan(fmt.indent()));
    EXPECT_TRUE(std::isnan(fmt.default_tab_size()));
}

TEST_F(ParagraphFormatTest, FontAlignmentDefaultIsDefault) {
    EXPECT_EQ(fmt.font_alignment(), FontAlignment::DEFAULT);
}
