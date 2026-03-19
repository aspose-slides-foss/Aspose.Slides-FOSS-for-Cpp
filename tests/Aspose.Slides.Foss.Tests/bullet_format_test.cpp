// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/bullet_format.h>
#include <Aspose/Slides/Foss/drawing/color.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class BulletFormatTest : public ::testing::Test {
protected:
    BulletFormat fmt;
};

// ---------------------------------------------------------------------------
// Default state: all properties start "not defined" / default
//   type=NOT_DEFINED, char='', height=NaN, start_with=1,
//   numbered_style=NOT_DEFINED, hard_color/font=NOT_DEFINED
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, DefaultsNotDefined) {
    EXPECT_EQ(fmt.type(), BulletType::NOT_DEFINED);
    EXPECT_EQ(fmt.character(), "");
    EXPECT_EQ(fmt.font_name(), "");
    EXPECT_TRUE(std::isnan(fmt.height()));
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 1);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// type: round-trip all BulletType values
//   setting type changes the bullet kind; NOT_DEFINED = inherited
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, TypeRoundTrip) {
    fmt.set_type(BulletType::NONE);
    EXPECT_EQ(fmt.type(), BulletType::NONE);

    fmt.set_type(BulletType::SYMBOL);
    EXPECT_EQ(fmt.type(), BulletType::SYMBOL);

    fmt.set_type(BulletType::NUMBERED);
    EXPECT_EQ(fmt.type(), BulletType::NUMBERED);

    fmt.set_type(BulletType::PICTURE);
    EXPECT_EQ(fmt.type(), BulletType::PICTURE);

    fmt.set_type(BulletType::NOT_DEFINED);
    EXPECT_EQ(fmt.type(), BulletType::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// char: round-trip bullet character
//   default is '', can be set to any Unicode char (e.g. bullet U+2022)
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, CharacterRoundTrip) {
    fmt.set_character("\xe2\x80\xa2"); // U+2022 bullet
    EXPECT_EQ(fmt.character(), "\xe2\x80\xa2");

    fmt.set_character("-");
    EXPECT_EQ(fmt.character(), "-");

    fmt.set_character("");
    EXPECT_EQ(fmt.character(), "");
}

// ---------------------------------------------------------------------------
// font: round-trip font name
//   returns FontData(typeface) or None; setter accepts FontData or None
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, FontNameRoundTrip) {
    fmt.set_font_name("Arial");
    EXPECT_EQ(fmt.font_name(), "Arial");

    fmt.set_font_name("Wingdings");
    EXPECT_EQ(fmt.font_name(), "Wingdings");

    fmt.set_font_name("");
    EXPECT_EQ(fmt.font_name(), "");
}

// ---------------------------------------------------------------------------
// height: round-trip percentage height, NaN = inherited
//   NaN means inherited; otherwise percentage of first portion height
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, HeightRoundTrip) {
    fmt.set_height(75.0f);
    EXPECT_FLOAT_EQ(fmt.height(), 75.0f);

    fmt.set_height(120.0f);
    EXPECT_FLOAT_EQ(fmt.height(), 120.0f);

    // Reset to inherited
    fmt.set_height(std::numeric_limits<float>::quiet_NaN());
    EXPECT_TRUE(std::isnan(fmt.height()));
}

// ---------------------------------------------------------------------------
// color: sub-object access and modification
//   returns a ColorFormat sub-object for the bullet color
//   color properties persist after set
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, ColorRoundTrip) {
    EXPECT_EQ(fmt.color().color_type(), ColorType::NOT_DEFINED);

    fmt.color().set_color(Drawing::Color::red);
    EXPECT_EQ(fmt.color().color(), Drawing::Color::red);
    EXPECT_EQ(fmt.color().color_type(), ColorType::RGB);

    fmt.color().set_color(Drawing::Color::from_argb(255, 0, 128, 255));
    EXPECT_EQ(fmt.color().color().r(), 0);
    EXPECT_EQ(fmt.color().color().g(), 128);
    EXPECT_EQ(fmt.color().color().b(), 255);
}

// ---------------------------------------------------------------------------
// numbered_bullet_start_with: round-trip start value
//   default=1, values <= 1 treated as default, values > 1 persist
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, NumberedBulletStartWithRoundTrip) {
    fmt.set_numbered_bullet_start_with(5);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 5);

    fmt.set_numbered_bullet_start_with(1);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 1);

    fmt.set_numbered_bullet_start_with(0);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 0);
}

// ---------------------------------------------------------------------------
// numbered_bullet_style: round-trip style enum
//   maps to OOXML buAutoNum type attribute; NOT_DEFINED removes element
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, NumberedBulletStyleRoundTrip) {
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ARABIC_PERIOD);

    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD);

    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT);

    fmt.set_numbered_bullet_style(NumberedBulletStyle::NOT_DEFINED);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// is_bullet_hard_color: round-trip NullableBool
//   TRUE = bullet has own color (buClr present)
//   FALSE = inherits from first portion (buClrTx present)
//   NOT_DEFINED = neither present
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, IsBulletHardColorRoundTrip) {
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::TRUE);

    fmt.set_is_bullet_hard_color(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::FALSE);

    fmt.set_is_bullet_hard_color(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// is_bullet_hard_font: round-trip NullableBool
//   TRUE = bullet has own font (buFont present)
//   FALSE = inherits from first portion (buFontTx present)
//   NOT_DEFINED = neither present
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, IsBulletHardFontRoundTrip) {
    fmt.set_is_bullet_hard_font(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::TRUE);

    fmt.set_is_bullet_hard_font(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::FALSE);

    fmt.set_is_bullet_hard_font(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// picture: sub-object access
//   returns a Picture sub-object for the bullet image
//   picture object is accessible and image can be set/read
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, PictureDefaultIsNull) {
    EXPECT_EQ(fmt.picture().image(), nullptr);
}

// ---------------------------------------------------------------------------
// All property channels are independent
//   different formatting "channels" on the same object don't interfere
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, AllPropertyChannelsIndependent) {
    fmt.set_type(BulletType::SYMBOL);
    fmt.set_character("\xe2\x80\xa2");
    fmt.set_font_name("Wingdings");
    fmt.set_height(80.0f);
    fmt.color().set_color(Drawing::Color::blue);
    fmt.set_numbered_bullet_start_with(3);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    fmt.set_is_bullet_hard_font(NullableBool::FALSE);

    EXPECT_EQ(fmt.type(), BulletType::SYMBOL);
    EXPECT_EQ(fmt.character(), "\xe2\x80\xa2");
    EXPECT_EQ(fmt.font_name(), "Wingdings");
    EXPECT_FLOAT_EQ(fmt.height(), 80.0f);
    EXPECT_EQ(fmt.color().color(), Drawing::Color::blue);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 3);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ARABIC_PERIOD);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::TRUE);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::FALSE);
}

// ---------------------------------------------------------------------------
// Toggle properties back to defaults
//   properties can be enabled then disabled, restoring initial state
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, TogglePropertiesReturnToDefault) {
    fmt.set_type(BulletType::NUMBERED);
    fmt.set_character("*");
    fmt.set_font_name("Arial");
    fmt.set_height(100.0f);
    fmt.set_numbered_bullet_start_with(10);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD);
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    fmt.set_is_bullet_hard_font(NullableBool::TRUE);

    // Reset to defaults
    fmt.set_type(BulletType::NOT_DEFINED);
    fmt.set_character("");
    fmt.set_font_name("");
    fmt.set_height(std::numeric_limits<float>::quiet_NaN());
    fmt.set_numbered_bullet_start_with(1);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::NOT_DEFINED);
    fmt.set_is_bullet_hard_color(NullableBool::NOT_DEFINED);
    fmt.set_is_bullet_hard_font(NullableBool::NOT_DEFINED);

    EXPECT_EQ(fmt.type(), BulletType::NOT_DEFINED);
    EXPECT_EQ(fmt.character(), "");
    EXPECT_EQ(fmt.font_name(), "");
    EXPECT_TRUE(std::isnan(fmt.height()));
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 1);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
//   pattern style + colors persist; analogous to bullet type + style + color
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, NumberedBulletFullConfiguration) {
    fmt.set_type(BulletType::NUMBERED);
    fmt.set_numbered_bullet_style(NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD);
    fmt.set_numbered_bullet_start_with(5);
    fmt.set_is_bullet_hard_color(NullableBool::TRUE);
    fmt.color().set_color(Drawing::Color::dark_blue);

    EXPECT_EQ(fmt.type(), BulletType::NUMBERED);
    EXPECT_EQ(fmt.numbered_bullet_style(), NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD);
    EXPECT_EQ(fmt.numbered_bullet_start_with(), 5);
    EXPECT_EQ(fmt.is_bullet_hard_color(), NullableBool::TRUE);
    EXPECT_EQ(fmt.color().color(), Drawing::Color::dark_blue);
}

// ---------------------------------------------------------------------------
// Changing one property does not affect others
//   independent properties don't interfere with each other
// ---------------------------------------------------------------------------

TEST_F(BulletFormatTest, ChangingTypeDoesNotAffectOtherProperties) {
    fmt.set_character(">");
    fmt.set_font_name("Courier New");
    fmt.set_height(90.0f);
    fmt.set_is_bullet_hard_font(NullableBool::TRUE);

    // Change type
    fmt.set_type(BulletType::NUMBERED);

    // Other properties unchanged
    EXPECT_EQ(fmt.character(), ">");
    EXPECT_EQ(fmt.font_name(), "Courier New");
    EXPECT_FLOAT_EQ(fmt.height(), 90.0f);
    EXPECT_EQ(fmt.is_bullet_hard_font(), NullableBool::TRUE);
}
