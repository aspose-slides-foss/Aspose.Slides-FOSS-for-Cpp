// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/bullet_format.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/i_bullet_format.h>

#include <cmath>
#include <memory>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture: access BulletFormat through the IBulletFormat interface pointer
// ---------------------------------------------------------------------------

class IBulletFormatTest : public ::testing::Test {
protected:
    std::unique_ptr<BulletFormat> concrete = std::make_unique<BulletFormat>();
    IBulletFormat& fmt = *concrete;
};

// ---------------------------------------------------------------------------
// type: round-trip through interface
// Ports: test_reroute — verifying a property is non-trivial after mutation
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, TypeRoundTrip) {
    fmt.set_type(BulletType::SYMBOL);
    EXPECT_EQ(fmt.type(), BulletType::SYMBOL);

    fmt.set_type(BulletType::NUMBERED);
    EXPECT_EQ(fmt.type(), BulletType::NUMBERED);

    fmt.set_type(BulletType::PICTURE);
    EXPECT_EQ(fmt.type(), BulletType::PICTURE);

    fmt.set_type(BulletType::NONE);
    EXPECT_EQ(fmt.type(), BulletType::NONE);
}

// ---------------------------------------------------------------------------
// char: round-trip through interface
// Ports: test_solid_fill — a single property persists after set
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, CharRoundTrip) {
    fmt.set_char("\xe2\x80\xa2"); // U+2022 bullet
    EXPECT_EQ(fmt.get_char(), "\xe2\x80\xa2");

    fmt.set_char("-");
    EXPECT_EQ(fmt.get_char(), "-");

    fmt.set_char("");
    EXPECT_EQ(fmt.get_char(), "");
}

// ---------------------------------------------------------------------------
// font_name: round-trip through interface
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, FontNameRoundTrip) {
    fmt.set_font_name("Arial");
    EXPECT_EQ(fmt.font_name(), "Arial");

    fmt.set_font_name("Wingdings");
    EXPECT_EQ(fmt.font_name(), "Wingdings");
}

// ---------------------------------------------------------------------------
// height: NaN = inherited, numeric = explicit
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, HeightDefaultIsNaN) {
    EXPECT_TRUE(std::isnan(fmt.height()));
}

TEST_F(IBulletFormatTest, HeightRoundTrip) {
    fmt.set_height(75.0f);
    EXPECT_FLOAT_EQ(fmt.height(), 75.0f);

    fmt.set_height(std::numeric_limits<float>::quiet_NaN());
    EXPECT_TRUE(std::isnan(fmt.height()));
}

// ---------------------------------------------------------------------------
// color: sub-object access through interface
// Ports: test_outer_shadow — color/sub-object properties persist after set
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, ColorSubObjectAccess) {
    IColorFormat& color = fmt.color();
    color.set_color(Drawing::Color::red);
    EXPECT_EQ(fmt.color().color(), Drawing::Color::red);

    color.set_color(Drawing::Color::from_argb(255, 0, 128, 255));
    EXPECT_EQ(fmt.color().color().r(), 0);
    EXPECT_EQ(fmt.color().color().g(), 128);
    EXPECT_EQ(fmt.color().color().b(), 255);
}

// ---------------------------------------------------------------------------
// picture: sub-object is accessible, default image is null
// Ports: test_picture_fill — picture sub-object is accessible
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, PictureSubObjectAccessible) {
    ISlidesPicture& pic = fmt.picture();
    EXPECT_EQ(pic.image(), nullptr);
}

// ---------------------------------------------------------------------------
// numbered_bullet_start_with: round-trip
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, NumberedBulletStartWithRoundTrip) {
    fmt.set_numbered_bullet_start_with(5);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 5);

    fmt.set_numbered_bullet_start_with(1);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 1);
}

// ---------------------------------------------------------------------------
// numbered_bullet_style: round-trip
// Ports: test_pattern_fill — style enum persists after set
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, NumberedBulletStyleRoundTrip) {
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ARABIC_PERIOD);

    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD);

    fmt.set_numbered_bullet_style(NumberedBulletStyle::NOT_DEFINED);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// is_bullet_hard_color: NullableBool round-trip
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, IsBulletHardColorRoundTrip) {
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::TRUE);

    fmt.set_is_bullet_hard_color(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::FALSE);

    fmt.set_is_bullet_hard_color(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// is_bullet_hard_font: NullableBool round-trip
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, IsBulletHardFontRoundTrip) {
    fmt.set_is_bullet_hard_font(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::TRUE);

    fmt.set_is_bullet_hard_font(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::FALSE);

    fmt.set_is_bullet_hard_font(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// All property channels are independent through interface
// Ports: test_glow — different formatting channels don't interfere
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, AllPropertyChannelsIndependent) {
    fmt.set_type(BulletType::SYMBOL);
    fmt.set_char("\xe2\x80\xa2");
    fmt.set_font_name("Wingdings");
    fmt.set_height(80.0f);
    fmt.color().set_color(Drawing::Color::blue);
    fmt.set_numbered_bullet_start_with(3);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    fmt.set_is_bullet_hard_font(NullableBool::FALSE);

    EXPECT_EQ(fmt.type(), BulletType::SYMBOL);
    EXPECT_EQ(fmt.get_char(), "\xe2\x80\xa2");
    EXPECT_EQ(fmt.font_name(), "Wingdings");
    EXPECT_FLOAT_EQ(fmt.height(), 80.0f);
    EXPECT_EQ(fmt.color().color(), Drawing::Color::blue);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 3);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::FALSE);
}

// ---------------------------------------------------------------------------
// Toggle properties back to defaults through interface
// Ports: test_enable_disable_effects — properties can be set then reset
// ---------------------------------------------------------------------------

TEST_F(IBulletFormatTest, TogglePropertiesReturnToDefault) {
    fmt.set_type(BulletType::NUMBERED);
    fmt.set_char("*");
    fmt.set_font_name("Arial");
    fmt.set_height(100.0f);
    fmt.set_numbered_bullet_start_with(10);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD);
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    fmt.set_is_bullet_hard_font(NullableBool::TRUE);

    // Reset to defaults
    fmt.set_type(BulletType::NOT_DEFINED);
    fmt.set_char("");
    fmt.set_font_name("");
    fmt.set_height(std::numeric_limits<float>::quiet_NaN());
    fmt.set_numbered_bullet_start_with(1);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::NOT_DEFINED);
    fmt.set_is_bullet_hard_color(NullableBool::NOT_DEFINED);
    fmt.set_is_bullet_hard_font(NullableBool::NOT_DEFINED);

    EXPECT_EQ(fmt.type(), BulletType::NOT_DEFINED);
    EXPECT_EQ(fmt.get_char(), "");
    EXPECT_EQ(fmt.font_name(), "");
    EXPECT_TRUE(std::isnan(fmt.height()));
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 1);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::NOT_DEFINED);
}
