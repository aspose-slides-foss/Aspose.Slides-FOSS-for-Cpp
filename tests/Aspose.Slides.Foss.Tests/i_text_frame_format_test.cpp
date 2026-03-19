// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <cmath>
#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/text_frame_format.h>
#include <Aspose/Slides/Foss/i_text_frame_format.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/material_preset_type.h>

using namespace Aspose::Slides::Foss;

class ITextFrameFormatTest : public ::testing::Test {
protected:
    TextFrameFormat fmt;
    ITextFrameFormat& iface = fmt;
};

// -- Margin properties --

TEST_F(ITextFrameFormatTest, MarginLeftDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(iface.margin_left()));
}

TEST_F(ITextFrameFormatTest, MarginLeftRoundTrips) {
    iface.set_margin_left(7.5);
    EXPECT_DOUBLE_EQ(iface.margin_left(), 7.5);
}

TEST_F(ITextFrameFormatTest, MarginRightDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(iface.margin_right()));
}

TEST_F(ITextFrameFormatTest, MarginRightRoundTrips) {
    iface.set_margin_right(3.0);
    EXPECT_DOUBLE_EQ(iface.margin_right(), 3.0);
}

TEST_F(ITextFrameFormatTest, MarginTopDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(iface.margin_top()));
}

TEST_F(ITextFrameFormatTest, MarginTopRoundTrips) {
    iface.set_margin_top(12.0);
    EXPECT_DOUBLE_EQ(iface.margin_top(), 12.0);
}

TEST_F(ITextFrameFormatTest, MarginBottomDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(iface.margin_bottom()));
}

TEST_F(ITextFrameFormatTest, MarginBottomRoundTrips) {
    iface.set_margin_bottom(1.5);
    EXPECT_DOUBLE_EQ(iface.margin_bottom(), 1.5);
}

// -- Enum properties --

TEST_F(ITextFrameFormatTest, WrapTextDefaultIsNotDefined) {
    EXPECT_EQ(iface.wrap_text(), NullableBool::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, WrapTextRoundTrips) {
    iface.set_wrap_text(NullableBool::TRUE);
    EXPECT_EQ(iface.wrap_text(), NullableBool::TRUE);
}

TEST_F(ITextFrameFormatTest, AnchoringTypeDefaultIsNotDefined) {
    EXPECT_EQ(iface.anchoring_type(), TextAnchorType::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, AnchoringTypeRoundTrips) {
    iface.set_anchoring_type(TextAnchorType::CENTER);
    EXPECT_EQ(iface.anchoring_type(), TextAnchorType::CENTER);
}

TEST_F(ITextFrameFormatTest, CenterTextDefaultIsNotDefined) {
    EXPECT_EQ(iface.center_text(), NullableBool::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, CenterTextRoundTrips) {
    iface.set_center_text(NullableBool::TRUE);
    EXPECT_EQ(iface.center_text(), NullableBool::TRUE);
}

TEST_F(ITextFrameFormatTest, TextVerticalTypeDefaultIsNotDefined) {
    EXPECT_EQ(iface.text_vertical_type(), TextVerticalType::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, TextVerticalTypeRoundTrips) {
    iface.set_text_vertical_type(TextVerticalType::VERTICAL);
    EXPECT_EQ(iface.text_vertical_type(), TextVerticalType::VERTICAL);
}

TEST_F(ITextFrameFormatTest, AutofitTypeDefaultIsNotDefined) {
    EXPECT_EQ(iface.autofit_type(), TextAutofitType::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, AutofitTypeRoundTrips) {
    iface.set_autofit_type(TextAutofitType::NORMAL);
    EXPECT_EQ(iface.autofit_type(), TextAutofitType::NORMAL);
}

// -- Column properties --

TEST_F(ITextFrameFormatTest, ColumnCountDefaultIsOne) {
    EXPECT_EQ(iface.column_count(), 1);
}

TEST_F(ITextFrameFormatTest, ColumnCountRoundTrips) {
    iface.set_column_count(3);
    EXPECT_EQ(iface.column_count(), 3);
}

TEST_F(ITextFrameFormatTest, ColumnSpacingDefaultIsZero) {
    EXPECT_DOUBLE_EQ(iface.column_spacing(), 0.0);
}

TEST_F(ITextFrameFormatTest, ColumnSpacingRoundTrips) {
    iface.set_column_spacing(15.5);
    EXPECT_DOUBLE_EQ(iface.column_spacing(), 15.5);
}

// -- 3D format (read-only accessor) --

TEST_F(ITextFrameFormatTest, ThreeDFormatAccessible) {
    ThreeDFormat& tdf = iface.three_d_format();
    EXPECT_DOUBLE_EQ(tdf.depth(), 0.0);
}

TEST_F(ITextFrameFormatTest, ThreeDFormatConstAccessible) {
    const ITextFrameFormat& ciface = iface;
    const ThreeDFormat& tdf = ciface.three_d_format();
    EXPECT_DOUBLE_EQ(tdf.depth(), 0.0);
}

// -- keep_text_flat --

TEST_F(ITextFrameFormatTest, KeepTextFlatDefaultIsTrue) {
    EXPECT_TRUE(iface.keep_text_flat());
}

TEST_F(ITextFrameFormatTest, KeepTextFlatRoundTrips) {
    iface.set_keep_text_flat(false);
    EXPECT_FALSE(iface.keep_text_flat());
}

// -- rotation_angle --

TEST_F(ITextFrameFormatTest, RotationAngleDefaultIsZero) {
    EXPECT_DOUBLE_EQ(iface.rotation_angle(), 0.0);
}

TEST_F(ITextFrameFormatTest, RotationAngleRoundTrips) {
    iface.set_rotation_angle(45.0);
    EXPECT_DOUBLE_EQ(iface.rotation_angle(), 45.0);
}

// -- transform --

TEST_F(ITextFrameFormatTest, TransformDefaultIsNotDefined) {
    EXPECT_EQ(iface.transform(), TextShapeType::NOT_DEFINED);
}

TEST_F(ITextFrameFormatTest, TransformRoundTrips) {
    iface.set_transform(TextShapeType::WAVE1);
    EXPECT_EQ(iface.transform(), TextShapeType::WAVE1);
}


TEST(ThreeDFormatViaTextFrame, BevelTop) {
    TextFrameFormat fmt;
    ThreeDFormat& tdf = fmt.three_d_format();
    tdf.bevel_top().set_bevel_type(BevelPresetType::CIRCLE);
    tdf.bevel_top().set_width(10);
    tdf.bevel_top().set_height(5);

    EXPECT_EQ(tdf.bevel_top().bevel_type(), BevelPresetType::CIRCLE);
    EXPECT_DOUBLE_EQ(tdf.bevel_top().width(), 10.0);
    EXPECT_DOUBLE_EQ(tdf.bevel_top().height(), 5.0);
}

TEST(ThreeDFormatViaTextFrame, Camera) {
    TextFrameFormat fmt;
    ThreeDFormat& tdf = fmt.three_d_format();
    tdf.camera().set_camera_type(CameraPresetType::PERSPECTIVE_ABOVE);

    EXPECT_EQ(tdf.camera().camera_type(), CameraPresetType::PERSPECTIVE_ABOVE);
}

TEST(ThreeDFormatViaTextFrame, LightRig) {
    TextFrameFormat fmt;
    ThreeDFormat& tdf = fmt.three_d_format();
    tdf.light_rig().set_light_type(LightRigPresetType::BALANCED);
    tdf.light_rig().set_direction(LightingDirection::TOP);

    EXPECT_EQ(tdf.light_rig().light_type(), LightRigPresetType::BALANCED);
    EXPECT_EQ(tdf.light_rig().direction(), LightingDirection::TOP);
}

TEST(ThreeDFormatViaTextFrame, DepthAndMaterial) {
    TextFrameFormat fmt;
    ThreeDFormat& tdf = fmt.three_d_format();
    tdf.set_depth(20);
    tdf.set_material(MaterialPresetType::METAL);

    EXPECT_DOUBLE_EQ(tdf.depth(), 20.0);
    EXPECT_EQ(tdf.material(), MaterialPresetType::METAL);
}
