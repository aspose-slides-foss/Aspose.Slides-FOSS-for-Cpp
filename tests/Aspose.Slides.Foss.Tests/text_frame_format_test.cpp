// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <cmath>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/text_frame_format.h>

using namespace Aspose::Slides::Foss;

// --- Default construction ---

TEST(TextFrameFormatTest, DefaultConstruction) {
    TextFrameFormat fmt;
    EXPECT_EQ(fmt.anchoring_type(), TextAnchorType::NOT_DEFINED);
    EXPECT_EQ(fmt.autofit_type(), TextAutofitType::NOT_DEFINED);
    EXPECT_EQ(fmt.text_vertical_type(), TextVerticalType::NOT_DEFINED);
    EXPECT_EQ(fmt.wrap_text(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.center_text(), NullableBool::NOT_DEFINED);
    EXPECT_TRUE(std::isnan(fmt.margin_left()));
    EXPECT_TRUE(std::isnan(fmt.margin_right()));
    EXPECT_TRUE(std::isnan(fmt.margin_top()));
    EXPECT_TRUE(std::isnan(fmt.margin_bottom()));
    EXPECT_EQ(fmt.column_count(), 1);
    EXPECT_DOUBLE_EQ(fmt.column_spacing(), 0.0);
    EXPECT_DOUBLE_EQ(fmt.rotation_angle(), 0.0);
    EXPECT_EQ(fmt.transform(), TextShapeType::NOT_DEFINED);
    EXPECT_TRUE(fmt.keep_text_flat());
}

// --- Margin properties ---

TEST(TextFrameFormatTest, MarginLeft) {
    TextFrameFormat fmt;
    fmt.set_margin_left(7.2);
    EXPECT_DOUBLE_EQ(fmt.margin_left(), 7.2);
}

TEST(TextFrameFormatTest, MarginRight) {
    TextFrameFormat fmt;
    fmt.set_margin_right(3.6);
    EXPECT_DOUBLE_EQ(fmt.margin_right(), 3.6);
}

TEST(TextFrameFormatTest, MarginTop) {
    TextFrameFormat fmt;
    fmt.set_margin_top(1.5);
    EXPECT_DOUBLE_EQ(fmt.margin_top(), 1.5);
}

TEST(TextFrameFormatTest, MarginBottom) {
    TextFrameFormat fmt;
    fmt.set_margin_bottom(2.0);
    EXPECT_DOUBLE_EQ(fmt.margin_bottom(), 2.0);
}

// --- wrap_text ---

TEST(TextFrameFormatTest, WrapText) {
    TextFrameFormat fmt;
    fmt.set_wrap_text(NullableBool::TRUE);
    EXPECT_EQ(fmt.wrap_text(), NullableBool::TRUE);

    fmt.set_wrap_text(NullableBool::FALSE);
    EXPECT_EQ(fmt.wrap_text(), NullableBool::FALSE);

    fmt.set_wrap_text(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.wrap_text(), NullableBool::NOT_DEFINED);
}

// --- anchoring_type ---

TEST(TextFrameFormatTest, AnchoringType) {
    TextFrameFormat fmt;
    fmt.set_anchoring_type(TextAnchorType::TOP);
    EXPECT_EQ(fmt.anchoring_type(), TextAnchorType::TOP);

    fmt.set_anchoring_type(TextAnchorType::CENTER);
    EXPECT_EQ(fmt.anchoring_type(), TextAnchorType::CENTER);

    fmt.set_anchoring_type(TextAnchorType::BOTTOM);
    EXPECT_EQ(fmt.anchoring_type(), TextAnchorType::BOTTOM);

    fmt.set_anchoring_type(TextAnchorType::NOT_DEFINED);
    EXPECT_EQ(fmt.anchoring_type(), TextAnchorType::NOT_DEFINED);
}

// --- center_text ---

TEST(TextFrameFormatTest, CenterText) {
    TextFrameFormat fmt;
    fmt.set_center_text(NullableBool::TRUE);
    EXPECT_EQ(fmt.center_text(), NullableBool::TRUE);

    fmt.set_center_text(NullableBool::FALSE);
    EXPECT_EQ(fmt.center_text(), NullableBool::FALSE);
}

// --- text_vertical_type ---

TEST(TextFrameFormatTest, TextVerticalType) {
    TextFrameFormat fmt;
    fmt.set_text_vertical_type(TextVerticalType::VERTICAL);
    EXPECT_EQ(fmt.text_vertical_type(), TextVerticalType::VERTICAL);

    fmt.set_text_vertical_type(TextVerticalType::HORIZONTAL);
    EXPECT_EQ(fmt.text_vertical_type(), TextVerticalType::HORIZONTAL);

    fmt.set_text_vertical_type(TextVerticalType::VERTICAL270);
    EXPECT_EQ(fmt.text_vertical_type(), TextVerticalType::VERTICAL270);
}

// --- autofit_type ---

TEST(TextFrameFormatTest, AutofitType) {
    TextFrameFormat fmt;
    fmt.set_autofit_type(TextAutofitType::NONE);
    EXPECT_EQ(fmt.autofit_type(), TextAutofitType::NONE);

    fmt.set_autofit_type(TextAutofitType::NORMAL);
    EXPECT_EQ(fmt.autofit_type(), TextAutofitType::NORMAL);

    fmt.set_autofit_type(TextAutofitType::SHAPE);
    EXPECT_EQ(fmt.autofit_type(), TextAutofitType::SHAPE);
}

// --- column_count ---

TEST(TextFrameFormatTest, ColumnCount) {
    TextFrameFormat fmt;
    fmt.set_column_count(3);
    EXPECT_EQ(fmt.column_count(), 3);

    fmt.set_column_count(0);
    EXPECT_EQ(fmt.column_count(), 0);
}

// --- column_spacing ---

TEST(TextFrameFormatTest, ColumnSpacing) {
    TextFrameFormat fmt;
    fmt.set_column_spacing(10.5);
    EXPECT_DOUBLE_EQ(fmt.column_spacing(), 10.5);
}

// --- rotation_angle ---

TEST(TextFrameFormatTest, RotationAngle) {
    TextFrameFormat fmt;
    fmt.set_rotation_angle(45.0);
    EXPECT_DOUBLE_EQ(fmt.rotation_angle(), 45.0);

    fmt.set_rotation_angle(-90.0);
    EXPECT_DOUBLE_EQ(fmt.rotation_angle(), -90.0);
}

// --- transform ---

TEST(TextFrameFormatTest, Transform) {
    TextFrameFormat fmt;
    fmt.set_transform(TextShapeType::PLAIN);
    EXPECT_EQ(fmt.transform(), TextShapeType::PLAIN);

    fmt.set_transform(TextShapeType::WAVE1);
    EXPECT_EQ(fmt.transform(), TextShapeType::WAVE1);

    fmt.set_transform(TextShapeType::NOT_DEFINED);
    EXPECT_EQ(fmt.transform(), TextShapeType::NOT_DEFINED);
}

// --- keep_text_flat ---

TEST(TextFrameFormatTest, KeepTextFlat) {
    TextFrameFormat fmt;
    EXPECT_TRUE(fmt.keep_text_flat());

    fmt.set_keep_text_flat(false);
    EXPECT_FALSE(fmt.keep_text_flat());

    fmt.set_keep_text_flat(true);
    EXPECT_TRUE(fmt.keep_text_flat());
}

// --- three_d_format ---

TEST(TextFrameFormatTest, ThreeDFormat) {
    TextFrameFormat fmt;
    auto& tdf = fmt.three_d_format();
    EXPECT_DOUBLE_EQ(tdf.depth(), 0.0);

    tdf.set_depth(10.0);
    EXPECT_DOUBLE_EQ(fmt.three_d_format().depth(), 10.0);
}

TEST(TextFrameFormatTest, ThreeDFormatConst) {
    TextFrameFormat fmt;
    fmt.three_d_format().set_depth(5.0);

    const auto& cfmt = fmt;
    EXPECT_DOUBLE_EQ(cfmt.three_d_format().depth(), 5.0);
}
