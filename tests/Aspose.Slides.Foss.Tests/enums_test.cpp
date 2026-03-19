// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include "Aspose/Slides/Foss/bevel_preset_type.h"
#include "Aspose/Slides/Foss/bullet_type.h"
#include "Aspose/Slides/Foss/camera_preset_type.h"
#include "Aspose/Slides/Foss/color_type.h"
#include "Aspose/Slides/Foss/fill_blend_mode.h"
#include "Aspose/Slides/Foss/fill_type.h"
#include "Aspose/Slides/Foss/font_alignment.h"
#include "Aspose/Slides/Foss/gradient_direction.h"
#include "Aspose/Slides/Foss/gradient_shape.h"
#include "Aspose/Slides/Foss/light_rig_preset_type.h"
#include "Aspose/Slides/Foss/lighting_direction.h"
#include "Aspose/Slides/Foss/line_alignment.h"
#include "Aspose/Slides/Foss/line_arrowhead_length.h"
#include "Aspose/Slides/Foss/line_arrowhead_style.h"
#include "Aspose/Slides/Foss/line_arrowhead_width.h"
#include "Aspose/Slides/Foss/line_cap_style.h"
#include "Aspose/Slides/Foss/line_dash_style.h"
#include "Aspose/Slides/Foss/line_join_style.h"
#include "Aspose/Slides/Foss/line_style.h"
#include "Aspose/Slides/Foss/material_preset_type.h"
#include "Aspose/Slides/Foss/nullable_bool.h"
#include "Aspose/Slides/Foss/numbered_bullet_style.h"
#include "Aspose/Slides/Foss/pattern_style.h"
#include "Aspose/Slides/Foss/picture_fill_mode.h"
#include "Aspose/Slides/Foss/preset_color.h"
#include "Aspose/Slides/Foss/preset_shadow_type.h"
#include "Aspose/Slides/Foss/rectangle_alignment.h"
#include "Aspose/Slides/Foss/scheme_color.h"
#include "Aspose/Slides/Foss/slide_layout_type.h"
#include "Aspose/Slides/Foss/source_format.h"
#include "Aspose/Slides/Foss/table_style_preset.h"
#include "Aspose/Slides/Foss/text_alignment.h"
#include "Aspose/Slides/Foss/text_anchor_type.h"
#include "Aspose/Slides/Foss/text_autofit_type.h"
#include "Aspose/Slides/Foss/text_cap_type.h"
#include "Aspose/Slides/Foss/text_shape_type.h"
#include "Aspose/Slides/Foss/text_strikethrough_type.h"
#include "Aspose/Slides/Foss/text_underline_type.h"
#include "Aspose/Slides/Foss/text_vertical_type.h"
#include "Aspose/Slides/Foss/tile_flip.h"

using namespace Aspose::Slides::Foss;


TEST(FillTypeTest, SolidFillValue) {
    FillType ft = FillType::SOLID;
    EXPECT_EQ(ft, FillType::SOLID);
    EXPECT_NE(ft, FillType::NOT_DEFINED);
    EXPECT_EQ(to_string_view(ft), "Solid");
}

TEST(FillTypeTest, GradientFillValue) {
    FillType ft = FillType::GRADIENT;
    EXPECT_EQ(ft, FillType::GRADIENT);
    EXPECT_EQ(to_string_view(ft), "Gradient");
}

TEST(FillTypeTest, PatternFillValue) {
    FillType ft = FillType::PATTERN;
    EXPECT_EQ(ft, FillType::PATTERN);
    EXPECT_EQ(to_string_view(ft), "Pattern");
}

TEST(FillTypeTest, NoFillValue) {
    FillType ft = FillType::NO_FILL;
    EXPECT_EQ(ft, FillType::NO_FILL);
    EXPECT_EQ(to_string_view(ft), "NoFill");
}

TEST(FillTypeTest, PictureFillValue) {
    FillType ft = FillType::PICTURE;
    EXPECT_EQ(ft, FillType::PICTURE);
    EXPECT_EQ(to_string_view(ft), "Picture");
}

TEST(FillTypeTest, AllValuesDistinct) {
    EXPECT_NE(FillType::NOT_DEFINED, FillType::NO_FILL);
    EXPECT_NE(FillType::SOLID, FillType::GRADIENT);
    EXPECT_NE(FillType::PATTERN, FillType::PICTURE);
    EXPECT_NE(FillType::GROUP, FillType::SOLID);
}

// --- GradientShape tests (from test_gradient_fill) ---

TEST(GradientShapeTest, LinearValue) {
    EXPECT_EQ(to_string_view(GradientShape::LINEAR), "Linear");
}

TEST(GradientShapeTest, AllValues) {
    EXPECT_NE(GradientShape::NOT_DEFINED, GradientShape::LINEAR);
    EXPECT_NE(GradientShape::RECTANGLE, GradientShape::RADIAL);
    EXPECT_NE(GradientShape::PATH, GradientShape::LINEAR);
}

// --- PatternStyle tests (from test_pattern_fill) ---

TEST(PatternStyleTest, Percent50Value) {
    EXPECT_EQ(to_string_view(PatternStyle::PERCENT50), "Percent50");
}

TEST(PatternStyleTest, AllPercentValues) {
    EXPECT_NE(PatternStyle::PERCENT05, PatternStyle::PERCENT10);
    EXPECT_NE(PatternStyle::PERCENT20, PatternStyle::PERCENT25);
    EXPECT_NE(PatternStyle::PERCENT50, PatternStyle::PERCENT75);
}

// --- PictureFillMode tests (from test_picture_fill) ---

TEST(PictureFillModeTest, StretchValue) {
    EXPECT_EQ(to_string_view(PictureFillMode::STRETCH), "Stretch");
}

TEST(PictureFillModeTest, TileValue) {
    EXPECT_EQ(to_string_view(PictureFillMode::TILE), "Tile");
    EXPECT_NE(PictureFillMode::TILE, PictureFillMode::STRETCH);
}

// --- LineDashStyle tests (from test_line_format.py) ---

TEST(LineDashStyleTest, LineColorAndWidthUsesEnums) {
    FillType line_fill = FillType::SOLID;
    EXPECT_EQ(line_fill, FillType::SOLID);
    EXPECT_EQ(to_string_view(line_fill), "Solid");
}

TEST(LineDashStyleTest, DashStyleValue) {
    LineDashStyle ds = LineDashStyle::DASH;
    EXPECT_EQ(ds, LineDashStyle::DASH);
    EXPECT_EQ(to_string_view(ds), "Dash");
}

TEST(LineDashStyleTest, MultipleDashStylesDistinct) {
    LineDashStyle styles[] = {
        LineDashStyle::SOLID,
        LineDashStyle::DASH,
        LineDashStyle::DOT,
        LineDashStyle::DASH_DOT,
    };
    for (auto style : styles) {
        LineDashStyle assigned = style;
        EXPECT_EQ(assigned, style);
    }
    // All are distinct
    EXPECT_NE(LineDashStyle::SOLID, LineDashStyle::DASH);
    EXPECT_NE(LineDashStyle::DOT, LineDashStyle::DASH_DOT);
}

// --- Cross-enum to_string_view tests for a representative sample ---

TEST(EnumToStringTest, CameraPresetType) {
    EXPECT_EQ(to_string_view(CameraPresetType::NOT_DEFINED), "NotDefined");
    EXPECT_EQ(to_string_view(CameraPresetType::PERSPECTIVE_ABOVE), "PerspectiveAbove");
    EXPECT_EQ(to_string_view(CameraPresetType::ISOMETRIC_OFF_AXIS_1_LEFT), "IsometricOffAxis1Left");
    EXPECT_EQ(to_string_view(CameraPresetType::LEGACY_OBLIQUE_FRONT), "LegacyObliqueFront");
    EXPECT_EQ(to_string_view(CameraPresetType::ORTHOGRAPHIC_FRONT), "OrthographicFront");
}

TEST(CameraPresetTypeTest, AllValuesDistinct) {
    EXPECT_NE(CameraPresetType::NOT_DEFINED, CameraPresetType::PERSPECTIVE_ABOVE);
    EXPECT_NE(CameraPresetType::ISOMETRIC_BOTTOM_DOWN, CameraPresetType::ISOMETRIC_BOTTOM_UP);
    EXPECT_NE(CameraPresetType::OBLIQUE_TOP, CameraPresetType::OBLIQUE_BOTTOM);
    EXPECT_NE(CameraPresetType::PERSPECTIVE_FRONT, CameraPresetType::PERSPECTIVE_LEFT);
}

TEST(EnumToStringTest, BevelPresetType) {
    EXPECT_EQ(to_string_view(BevelPresetType::NOT_DEFINED), "NotDefined");
    EXPECT_EQ(to_string_view(BevelPresetType::COOL_SLANT), "CoolSlant");
    EXPECT_EQ(to_string_view(BevelPresetType::SOFT_ROUND), "SoftRound");
}

TEST(EnumToStringTest, BulletType) {
    EXPECT_EQ(to_string_view(BulletType::SYMBOL), "Symbol");
    EXPECT_EQ(to_string_view(BulletType::NUMBERED), "Numbered");
}

TEST(EnumToStringTest, ColorType) {
    EXPECT_EQ(to_string_view(ColorType::RGB), "RGB");
    EXPECT_EQ(to_string_view(ColorType::RGB_PERCENTAGE), "RGBPercentage");
    EXPECT_EQ(to_string_view(ColorType::HSL), "HSL");
}

TEST(EnumToStringTest, FillBlendMode) {
    EXPECT_EQ(to_string_view(FillBlendMode::DARKEN), "Darken");
    EXPECT_EQ(to_string_view(FillBlendMode::MULTIPLY), "Multiply");
}

TEST(EnumToStringTest, FontAlignment) {
    EXPECT_EQ(to_string_view(FontAlignment::BASELINE), "Baseline");
}

TEST(EnumToStringTest, LightRigPresetType) {
    EXPECT_EQ(to_string_view(LightRigPresetType::THREE_PT), "ThreePt");
    EXPECT_EQ(to_string_view(LightRigPresetType::LEGACY_FLAT1), "LegacyFlat1");
}

TEST(EnumToStringTest, LineStyle) {
    EXPECT_EQ(to_string_view(LineStyle::THICK_BETWEEN_THIN), "ThickBetweenThin");
}

TEST(EnumToStringTest, MaterialPresetType) {
    EXPECT_EQ(to_string_view(MaterialPresetType::DK_EDGE), "DkEdge");
    EXPECT_EQ(to_string_view(MaterialPresetType::TRANSLUCENT_POWDER), "TranslucentPowder");
}

TEST(EnumToStringTest, NullableBool) {
    EXPECT_EQ(to_string_view(NullableBool::NOT_DEFINED), "NotDefined");
    EXPECT_EQ(to_string_view(NullableBool::TRUE), "True");
    EXPECT_EQ(to_string_view(NullableBool::FALSE), "False");
}

TEST(EnumToStringTest, NumberedBulletStyle) {
    EXPECT_EQ(to_string_view(NumberedBulletStyle::BULLET_ALPHA_LC_PERIOD), "BulletAlphaLCPeriod");
    EXPECT_EQ(to_string_view(NumberedBulletStyle::BULLET_HINDI_ALPHA1_PERIOD), "BulletHindiAlpha1Period");
}

TEST(EnumToStringTest, PresetColor) {
    EXPECT_EQ(to_string_view(PresetColor::ALICE_BLUE), "AliceBlue");
    EXPECT_EQ(to_string_view(PresetColor::YELLOW_GREEN), "YellowGreen");
}

TEST(EnumToStringTest, PresetShadowType) {
    EXPECT_EQ(to_string_view(PresetShadowType::OUTER_BOX_SHADOW3_D), "OuterBoxShadow3D");
}

TEST(EnumToStringTest, SchemeColor) {
    EXPECT_EQ(to_string_view(SchemeColor::FOLLOWED_HYPERLINK), "FollowedHyperlink");
}

TEST(EnumToStringTest, SlideLayoutType) {
    EXPECT_EQ(to_string_view(SlideLayoutType::TITLE_AND_OBJECT), "TitleAndObject");
    EXPECT_EQ(to_string_view(SlideLayoutType::BLANK), "Blank");
}

TEST(EnumToStringTest, SourceFormat) {
    EXPECT_EQ(to_string_view(SourceFormat::PPT), "Ppt");
    EXPECT_EQ(to_string_view(SourceFormat::PPTX), "Pptx");
    EXPECT_EQ(to_string_view(SourceFormat::ODP), "Odp");
}

TEST(EnumToStringTest, TableStylePreset) {
    EXPECT_EQ(to_string_view(TableStylePreset::DARK_STYLE2_ACCENT1_ACCENT2), "DarkStyle2Accent1Accent2");
}

TEST(EnumToStringTest, TextAlignment) {
    EXPECT_EQ(to_string_view(TextAlignment::JUSTIFY_LOW), "JustifyLow");
}

TEST(EnumToStringTest, TextShapeType) {
    EXPECT_EQ(to_string_view(TextShapeType::DEFLATE_INFLATE_DEFLATE), "DeflateInflateDeflate");
    EXPECT_EQ(to_string_view(TextShapeType::CASCADE_DOWN), "CascadeDown");
}

TEST(EnumToStringTest, TextUnderlineType) {
    EXPECT_EQ(to_string_view(TextUnderlineType::HEAVY_DOT_DOT_DASH), "HeavyDotDotDash");
    EXPECT_EQ(to_string_view(TextUnderlineType::DOUBLE_WAVY), "DoubleWavy");
}

TEST(EnumToStringTest, TextVerticalType) {
    EXPECT_EQ(to_string_view(TextVerticalType::WORD_ART_VERTICAL_RIGHT_TO_LEFT), "WordArtVerticalRightToLeft");
}

TEST(EnumToStringTest, TileFlip) {
    EXPECT_EQ(to_string_view(TileFlip::FLIP_BOTH), "FlipBoth");
    EXPECT_EQ(to_string_view(TileFlip::NO_FLIP), "NoFlip");
}

// --- Enum equality / copy semantics ---

TEST(EnumSemanticsTest, CopyAssignment) {
    FillType a = FillType::SOLID;
    FillType b = a;
    EXPECT_EQ(a, b);
}

TEST(EnumSemanticsTest, SwitchCoverage) {
    // Verifies switch-based to_string_view works for all FillType values
    FillType all[] = {
        FillType::NOT_DEFINED, FillType::NO_FILL, FillType::SOLID,
        FillType::GRADIENT, FillType::PATTERN, FillType::PICTURE, FillType::GROUP,
    };
    for (auto v : all) {
        EXPECT_NE(to_string_view(v), "Unknown");
    }
}
