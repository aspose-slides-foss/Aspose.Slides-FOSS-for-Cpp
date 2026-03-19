// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/base_portion_format.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class BasePortionFormatTest : public ::testing::Test {
protected:
    BasePortionFormat fmt;
};

// ---------------------------------------------------------------------------
// Default state: all properties start "not defined"
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, DefaultsNotDefined) {
    EXPECT_EQ(fmt.font_bold(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_italic(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.kumimoji(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.normalise_height(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.proof_disabled(), NullableBool::NOT_DEFINED);

    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::NOT_DEFINED);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::NOT_DEFINED);

    EXPECT_EQ(fmt.is_hard_underline_line(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_hard_underline_fill(), NullableBool::NOT_DEFINED);

    EXPECT_TRUE(std::isnan(fmt.font_height()));
    EXPECT_TRUE(std::isnan(fmt.escapement()));
    EXPECT_TRUE(std::isnan(fmt.kerning_minimal_size()));
    EXPECT_TRUE(std::isnan(fmt.spacing()));

    EXPECT_FALSE(fmt.latin_font().has_value());
    EXPECT_FALSE(fmt.east_asian_font().has_value());
    EXPECT_FALSE(fmt.complex_script_font().has_value());
    EXPECT_FALSE(fmt.symbol_font().has_value());

    EXPECT_FALSE(fmt.language_id().has_value());
    EXPECT_FALSE(fmt.alternative_language_id().has_value());
}

// ---------------------------------------------------------------------------
// NullableBool properties: round-trip TRUE / FALSE / NOT_DEFINED
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, FontBoldRoundTrip) {
    fmt.set_font_bold(NullableBool::TRUE);
    EXPECT_EQ(fmt.font_bold(), NullableBool::TRUE);

    fmt.set_font_bold(NullableBool::FALSE);
    EXPECT_EQ(fmt.font_bold(), NullableBool::FALSE);

    fmt.set_font_bold(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_bold(), NullableBool::NOT_DEFINED);
}

TEST_F(BasePortionFormatTest, FontItalicRoundTrip) {
    fmt.set_font_italic(NullableBool::TRUE);
    EXPECT_EQ(fmt.font_italic(), NullableBool::TRUE);

    fmt.set_font_italic(NullableBool::FALSE);
    EXPECT_EQ(fmt.font_italic(), NullableBool::FALSE);
}

TEST_F(BasePortionFormatTest, KumimojiRoundTrip) {
    fmt.set_kumimoji(NullableBool::TRUE);
    EXPECT_EQ(fmt.kumimoji(), NullableBool::TRUE);
}

TEST_F(BasePortionFormatTest, NormaliseHeightRoundTrip) {
    fmt.set_normalise_height(NullableBool::TRUE);
    EXPECT_EQ(fmt.normalise_height(), NullableBool::TRUE);
}

TEST_F(BasePortionFormatTest, ProofDisabledRoundTrip) {
    fmt.set_proof_disabled(NullableBool::TRUE);
    EXPECT_EQ(fmt.proof_disabled(), NullableBool::TRUE);

    fmt.set_proof_disabled(NullableBool::FALSE);
    EXPECT_EQ(fmt.proof_disabled(), NullableBool::FALSE);
}

// ---------------------------------------------------------------------------
// Enum properties: round-trip all valid values
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, FontUnderlineRoundTrip) {
    fmt.set_font_underline(TextUnderlineType::SINGLE);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::SINGLE);

    fmt.set_font_underline(TextUnderlineType::DOUBLE);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::DOUBLE);

    fmt.set_font_underline(TextUnderlineType::WAVY);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::WAVY);

    fmt.set_font_underline(TextUnderlineType::NOT_DEFINED);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
}

TEST_F(BasePortionFormatTest, TextCapTypeRoundTrip) {
    fmt.set_text_cap_type(TextCapType::SMALL);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::SMALL);

    fmt.set_text_cap_type(TextCapType::ALL);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::ALL);

    fmt.set_text_cap_type(TextCapType::NONE);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::NONE);

    fmt.set_text_cap_type(TextCapType::NOT_DEFINED);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::NOT_DEFINED);
}

TEST_F(BasePortionFormatTest, StrikethroughTypeRoundTrip) {
    fmt.set_strikethrough_type(TextStrikethroughType::SINGLE);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::SINGLE);

    fmt.set_strikethrough_type(TextStrikethroughType::DOUBLE);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::DOUBLE);

    fmt.set_strikethrough_type(TextStrikethroughType::NONE);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::NONE);

    fmt.set_strikethrough_type(TextStrikethroughType::NOT_DEFINED);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// Underline hard/soft properties
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, IsHardUnderlineLineRoundTrip) {
    fmt.set_is_hard_underline_line(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_hard_underline_line(), NullableBool::TRUE);

    fmt.set_is_hard_underline_line(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_hard_underline_line(), NullableBool::FALSE);

    fmt.set_is_hard_underline_line(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_hard_underline_line(), NullableBool::NOT_DEFINED);
}

TEST_F(BasePortionFormatTest, IsHardUnderlineFillRoundTrip) {
    fmt.set_is_hard_underline_fill(NullableBool::TRUE);
    EXPECT_EQ(fmt.is_hard_underline_fill(), NullableBool::TRUE);

    fmt.set_is_hard_underline_fill(NullableBool::FALSE);
    EXPECT_EQ(fmt.is_hard_underline_fill(), NullableBool::FALSE);

    fmt.set_is_hard_underline_fill(NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.is_hard_underline_fill(), NullableBool::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// Float properties: set, read back, clear with NaN
//   effect properties like blur_radius, distance use numeric values that
//   must round-trip; undefined is represented as NaN.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, FontHeightRoundTrip) {
    fmt.set_font_height(12.5);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 12.5);

    fmt.set_font_height(0.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 0.0);

    // Clear
    fmt.set_font_height(std::numeric_limits<double>::quiet_NaN());
    EXPECT_TRUE(std::isnan(fmt.font_height()));
}

TEST_F(BasePortionFormatTest, EscapementRoundTrip) {
    // 30% superscript
    fmt.set_escapement(30.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 30.0);

    // -20% subscript
    fmt.set_escapement(-20.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), -20.0);

    // Clear
    fmt.set_escapement(std::numeric_limits<double>::quiet_NaN());
    EXPECT_TRUE(std::isnan(fmt.escapement()));
}

TEST_F(BasePortionFormatTest, KerningMinimalSizeRoundTrip) {
    fmt.set_kerning_minimal_size(10.0);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 10.0);
}

TEST_F(BasePortionFormatTest, SpacingRoundTrip) {
    fmt.set_spacing(1.5);
    EXPECT_DOUBLE_EQ(fmt.spacing(), 1.5);

    fmt.set_spacing(-0.5);
    EXPECT_DOUBLE_EQ(fmt.spacing(), -0.5);
}

// ---------------------------------------------------------------------------
// Font properties: set, read back, clear
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, LatinFontRoundTrip) {
    fmt.set_latin_font(FontData("Arial"));
    ASSERT_TRUE(fmt.latin_font().has_value());
    EXPECT_EQ(fmt.latin_font()->font_name(), "Arial");

    // Clear
    fmt.set_latin_font(std::nullopt);
    EXPECT_FALSE(fmt.latin_font().has_value());
}

TEST_F(BasePortionFormatTest, EastAsianFontRoundTrip) {
    fmt.set_east_asian_font(FontData("MS Gothic"));
    ASSERT_TRUE(fmt.east_asian_font().has_value());
    EXPECT_EQ(fmt.east_asian_font()->font_name(), "MS Gothic");
}

TEST_F(BasePortionFormatTest, ComplexScriptFontRoundTrip) {
    fmt.set_complex_script_font(FontData("Arabic Typesetting"));
    ASSERT_TRUE(fmt.complex_script_font().has_value());
    EXPECT_EQ(fmt.complex_script_font()->font_name(), "Arabic Typesetting");
}

TEST_F(BasePortionFormatTest, SymbolFontRoundTrip) {
    fmt.set_symbol_font(FontData("Wingdings"));
    ASSERT_TRUE(fmt.symbol_font().has_value());
    EXPECT_EQ(fmt.symbol_font()->font_name(), "Wingdings");
}

TEST_F(BasePortionFormatTest, FontDataEquality) {
    fmt.set_latin_font(FontData("Calibri"));
    EXPECT_EQ(fmt.latin_font().value(), FontData("Calibri"));
    EXPECT_NE(fmt.latin_font().value(), FontData("Arial"));
}

// ---------------------------------------------------------------------------
// String properties: language_id and alternative_language_id
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, LanguageIdRoundTrip) {
    fmt.set_language_id("en-US");
    ASSERT_TRUE(fmt.language_id().has_value());
    EXPECT_EQ(fmt.language_id().value(), "en-US");

    // Clear
    fmt.set_language_id(std::nullopt);
    EXPECT_FALSE(fmt.language_id().has_value());
}

TEST_F(BasePortionFormatTest, AlternativeLanguageIdRoundTrip) {
    fmt.set_alternative_language_id("ja-JP");
    ASSERT_TRUE(fmt.alternative_language_id().has_value());
    EXPECT_EQ(fmt.alternative_language_id().value(), "ja-JP");

    fmt.set_alternative_language_id(std::nullopt);
    EXPECT_FALSE(fmt.alternative_language_id().has_value());
}

// ---------------------------------------------------------------------------
// spell_check: inverse relationship with proof_disabled
//   spell_check=False -> noProof='1' (proof_disabled=TRUE)
//   spell_check=True  -> noProof removed (proof_disabled=NOT_DEFINED)
//   Reading: spell_check is True only when proof_disabled is FALSE.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, SpellCheckDefaultIsFalse) {
    // Default proof_disabled is NOT_DEFINED, spell_check requires FALSE
    EXPECT_FALSE(fmt.spell_check());
}

TEST_F(BasePortionFormatTest, SpellCheckSetFalseSetsProofDisabledTrue) {
    fmt.set_spell_check(false);
    EXPECT_EQ(fmt.proof_disabled(), NullableBool::TRUE);
    EXPECT_FALSE(fmt.spell_check());
}

TEST_F(BasePortionFormatTest, SpellCheckSetTrueClearsProofDisabled) {
    fmt.set_proof_disabled(NullableBool::TRUE);
    fmt.set_spell_check(true);
    EXPECT_EQ(fmt.proof_disabled(), NullableBool::NOT_DEFINED);
}

TEST_F(BasePortionFormatTest, SpellCheckTrueWhenProofDisabledFalse) {
    fmt.set_proof_disabled(NullableBool::FALSE);
    EXPECT_TRUE(fmt.spell_check());
}

// ---------------------------------------------------------------------------
// Behavioral intent: properties can be toggled between defined and undefined
// states, and cycling back to NOT_DEFINED restores initial state.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, TogglePropertiesReturnToDefault) {
    // Enable various properties
    fmt.set_font_bold(NullableBool::TRUE);
    fmt.set_font_underline(TextUnderlineType::HEAVY);
    fmt.set_text_cap_type(TextCapType::ALL);
    fmt.set_font_height(24.0);
    fmt.set_latin_font(FontData("Impact"));

    // Verify they are set
    EXPECT_EQ(fmt.font_bold(), NullableBool::TRUE);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::HEAVY);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::ALL);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 24.0);
    ASSERT_TRUE(fmt.latin_font().has_value());

    // Reset everything to undefined
    fmt.set_font_bold(NullableBool::NOT_DEFINED);
    fmt.set_font_underline(TextUnderlineType::NOT_DEFINED);
    fmt.set_text_cap_type(TextCapType::NOT_DEFINED);
    fmt.set_font_height(std::numeric_limits<double>::quiet_NaN());
    fmt.set_latin_font(std::nullopt);

    // Verify all back to defaults
    EXPECT_EQ(fmt.font_bold(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::NOT_DEFINED);
    EXPECT_TRUE(std::isnan(fmt.font_height()));
    EXPECT_FALSE(fmt.latin_font().has_value());
}

// ---------------------------------------------------------------------------
// Behavioral intent: multiple numeric properties on the same object can be
// set independently without interfering with each other.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, MultipleFloatPropertiesIndependent) {
    fmt.set_font_height(18.0);
    fmt.set_escapement(30.0);
    fmt.set_kerning_minimal_size(12.0);
    fmt.set_spacing(2.0);

    EXPECT_DOUBLE_EQ(fmt.font_height(), 18.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 30.0);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 12.0);
    EXPECT_DOUBLE_EQ(fmt.spacing(), 2.0);

    // Changing one doesn't affect others
    fmt.set_font_height(36.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 36.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 30.0);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 12.0);
    EXPECT_DOUBLE_EQ(fmt.spacing(), 2.0);
}

// ---------------------------------------------------------------------------
// Behavioral intent: different formatting "channels" on the same object
// (bold + italic + underline + fonts + languages) are independent.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, AllPropertyChannelsIndependent) {
    fmt.set_font_bold(NullableBool::TRUE);
    fmt.set_font_italic(NullableBool::FALSE);
    fmt.set_font_underline(TextUnderlineType::DOTTED);
    fmt.set_text_cap_type(TextCapType::SMALL);
    fmt.set_strikethrough_type(TextStrikethroughType::SINGLE);
    fmt.set_is_hard_underline_line(NullableBool::TRUE);
    fmt.set_is_hard_underline_fill(NullableBool::FALSE);
    fmt.set_font_height(14.0);
    fmt.set_latin_font(FontData("Times New Roman"));
    fmt.set_language_id("en-GB");

    EXPECT_EQ(fmt.font_bold(), NullableBool::TRUE);
    EXPECT_EQ(fmt.font_italic(), NullableBool::FALSE);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::DOTTED);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::SMALL);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::SINGLE);
    EXPECT_EQ(fmt.is_hard_underline_line(), NullableBool::TRUE);
    EXPECT_EQ(fmt.is_hard_underline_fill(), NullableBool::FALSE);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 14.0);
    EXPECT_EQ(fmt.latin_font()->font_name(), "Times New Roman");
    EXPECT_EQ(fmt.language_id().value(), "en-GB");
}

// ---------------------------------------------------------------------------
// Behavioral intent: numeric properties persist exact values after set.
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, FontHeightPersistsExactValues) {
    // Like soft_edge_effect.radius = 10 persisting after save/reload
    fmt.set_font_height(10.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 10.0);

    // Like blur_effect.radius = 8
    fmt.set_font_height(8.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 8.0);

    // Fractional values
    fmt.set_font_height(11.5);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 11.5);
}

// ---------------------------------------------------------------------------
// Multiple font slots are independent
// ---------------------------------------------------------------------------

TEST_F(BasePortionFormatTest, MultipleFontSlotsIndependent) {
    fmt.set_latin_font(FontData("Calibri"));
    fmt.set_east_asian_font(FontData("MS Gothic"));
    fmt.set_complex_script_font(FontData("Arial"));
    fmt.set_symbol_font(FontData("Wingdings"));

    EXPECT_EQ(fmt.latin_font()->font_name(), "Calibri");
    EXPECT_EQ(fmt.east_asian_font()->font_name(), "MS Gothic");
    EXPECT_EQ(fmt.complex_script_font()->font_name(), "Arial");
    EXPECT_EQ(fmt.symbol_font()->font_name(), "Wingdings");

    // Clear one, others unaffected
    fmt.set_latin_font(std::nullopt);
    EXPECT_FALSE(fmt.latin_font().has_value());
    EXPECT_TRUE(fmt.east_asian_font().has_value());
    EXPECT_TRUE(fmt.complex_script_font().has_value());
    EXPECT_TRUE(fmt.symbol_font().has_value());
}
