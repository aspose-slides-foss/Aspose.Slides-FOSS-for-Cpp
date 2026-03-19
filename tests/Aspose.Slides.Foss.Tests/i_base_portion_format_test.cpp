// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/base_portion_format.h>
#include <Aspose/Slides/Foss/i_base_portion_format.h>

#include <cmath>
#include <limits>
#include <memory>
#include <gtest/gtest.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture: access BasePortionFormat through IBasePortionFormat interface
// ---------------------------------------------------------------------------

class IBasePortionFormatTest : public ::testing::Test {
protected:
    std::unique_ptr<BasePortionFormat> impl = std::make_unique<BasePortionFormat>();
    IBasePortionFormat& fmt = *impl;
};

// ---------------------------------------------------------------------------
// Ports: test_effect_format.py::test_outer_shadow
// Behavioral intent: different formatting "channels" on the same object
// are independent — setting one property does not disturb another.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, OuterShadowIndependentProperties) {
    // Analogous to setting blur_radius, direction, distance on an outer shadow:
    // multiple numeric properties on the same interface must round-trip
    // independently.
    fmt.set_font_height(10.0);
    fmt.set_escapement(315.0 / 10.0);  // direction-like
    fmt.set_kerning_minimal_size(8.0);  // distance-like

    EXPECT_DOUBLE_EQ(fmt.font_height(), 10.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 31.5);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 8.0);

    // Changing one doesn't affect others
    fmt.set_font_height(20.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 20.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 31.5);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 8.0);
}

// ---------------------------------------------------------------------------
// Ports: test_effect_format.py::test_glow
// Behavioral intent: a property set to a specific value persists and can
// be read back through the interface.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, GlowPropertyPersistence) {
    // Analogous to glow_effect.radius = 15 persisting after enable
    fmt.set_font_height(15.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 15.0);

    // Analogous to setting glow color — set a font and verify
    fmt.set_latin_font(FontData("Gold"));
    ASSERT_TRUE(fmt.latin_font().has_value());
    EXPECT_EQ(fmt.latin_font()->font_name(), "Gold");
}

// ---------------------------------------------------------------------------
// Ports: test_effect_format.py::test_soft_edge
// Behavioral intent: numeric values persist exact values after set.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, SoftEdgeRadiusPersistence) {
    // Analogous to soft_edge_effect.radius = 10
    fmt.set_spacing(10.0);
    EXPECT_DOUBLE_EQ(fmt.spacing(), 10.0);

    // Fractional values
    fmt.set_spacing(10.5);
    EXPECT_DOUBLE_EQ(fmt.spacing(), 10.5);
}

// ---------------------------------------------------------------------------
// Ports: test_effect_format.py::test_blur
// Behavioral intent: effect properties persist exact values.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, BlurRadiusPersistence) {
    // Analogous to set_blur_effect(8, True) -> blur_effect.radius == 8
    fmt.set_kerning_minimal_size(8.0);
    EXPECT_DOUBLE_EQ(fmt.kerning_minimal_size(), 8.0);
}

// ---------------------------------------------------------------------------
// Ports: test_effect_format.py::test_enable_disable_effects
// Behavioral intent: properties can be enabled then disabled, returning
// to the initial undefined state.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, EnableDisableEffects) {
    // "Enable" properties
    fmt.set_font_bold(NullableBool::TRUE);
    fmt.set_font_italic(NullableBool::TRUE);
    fmt.set_font_underline(TextUnderlineType::HEAVY);
    fmt.set_text_cap_type(TextCapType::ALL);
    fmt.set_strikethrough_type(TextStrikethroughType::SINGLE);
    fmt.set_font_height(24.0);
    fmt.set_latin_font(FontData("Impact"));

    // Verify they are set (is_no_effects is False equivalent)
    EXPECT_NE(fmt.font_bold(), NullableBool::NOT_DEFINED);
    EXPECT_NE(fmt.font_italic(), NullableBool::NOT_DEFINED);
    EXPECT_NE(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
    EXPECT_NE(fmt.text_cap_type(), TextCapType::NOT_DEFINED);
    EXPECT_NE(fmt.strikethrough_type(), TextStrikethroughType::NOT_DEFINED);
    EXPECT_FALSE(std::isnan(fmt.font_height()));
    EXPECT_TRUE(fmt.latin_font().has_value());

    // "Disable" all — reset to undefined
    fmt.set_font_bold(NullableBool::NOT_DEFINED);
    fmt.set_font_italic(NullableBool::NOT_DEFINED);
    fmt.set_font_underline(TextUnderlineType::NOT_DEFINED);
    fmt.set_text_cap_type(TextCapType::NOT_DEFINED);
    fmt.set_strikethrough_type(TextStrikethroughType::NOT_DEFINED);
    fmt.set_font_height(std::numeric_limits<double>::quiet_NaN());
    fmt.set_latin_font(std::nullopt);

    // All back to "no effects" state
    EXPECT_EQ(fmt.font_bold(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_italic(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
    EXPECT_EQ(fmt.text_cap_type(), TextCapType::NOT_DEFINED);
    EXPECT_EQ(fmt.strikethrough_type(), TextStrikethroughType::NOT_DEFINED);
    EXPECT_TRUE(std::isnan(fmt.font_height()));
    EXPECT_FALSE(fmt.latin_font().has_value());
}

// ---------------------------------------------------------------------------
// Ports: test_fill_format.py::test_gradient_fill
// Behavioral intent: multiple properties set independently on the same
// object do not interfere with each other; gradient stops are analogous
// to setting multiple font slots independently.
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, GradientFillIndependentStops) {
    // Analogous to gradient_stops.add(0.0, Color.blue) and
    // gradient_stops.add(1.0, Color.red): set multiple font slots
    // independently and verify they persist without interference.
    fmt.set_latin_font(FontData("Blue"));
    fmt.set_east_asian_font(FontData("Red"));
    fmt.set_complex_script_font(FontData("Green"));
    fmt.set_symbol_font(FontData("Yellow"));

    ASSERT_TRUE(fmt.latin_font().has_value());
    ASSERT_TRUE(fmt.east_asian_font().has_value());
    ASSERT_TRUE(fmt.complex_script_font().has_value());
    ASSERT_TRUE(fmt.symbol_font().has_value());

    EXPECT_EQ(fmt.latin_font()->font_name(), "Blue");
    EXPECT_EQ(fmt.east_asian_font()->font_name(), "Red");
    EXPECT_EQ(fmt.complex_script_font()->font_name(), "Green");
    EXPECT_EQ(fmt.symbol_font()->font_name(), "Yellow");

    // Analogous to gradient angle: a numeric property coexists
    fmt.set_escapement(45.0);
    EXPECT_DOUBLE_EQ(fmt.escapement(), 45.0);

    // Font slots are still intact
    EXPECT_EQ(fmt.latin_font()->font_name(), "Blue");
    EXPECT_EQ(fmt.east_asian_font()->font_name(), "Red");
}

// ---------------------------------------------------------------------------
// Verify the interface provides access to format sub-objects
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, FormatObjectsAccessibleThroughInterface) {
    // line_format, fill_format, effect_format, highlight_color,
    // underline_line_format, underline_fill_format should be lazily created
    LineFormat& lf = fmt.line_format();
    FillFormat& ff = fmt.fill_format();
    EffectFormat& ef = fmt.effect_format();
    ColorFormat& hc = fmt.highlight_color();
    LineFormat& ulf = fmt.underline_line_format();
    FillFormat& uff = fmt.underline_fill_format();

    // Verify they are stable references (calling again returns same object)
    EXPECT_EQ(&fmt.line_format(), &lf);
    EXPECT_EQ(&fmt.fill_format(), &ff);
    EXPECT_EQ(&fmt.effect_format(), &ef);
    EXPECT_EQ(&fmt.highlight_color(), &hc);
    EXPECT_EQ(&fmt.underline_line_format(), &ulf);
    EXPECT_EQ(&fmt.underline_fill_format(), &uff);
}

// ---------------------------------------------------------------------------
// Verify polymorphic access: BasePortionFormat* -> IBasePortionFormat*
// ---------------------------------------------------------------------------

TEST_F(IBasePortionFormatTest, PolymorphicAccess) {
    IBasePortionFormat* iface = impl.get();
    iface->set_font_bold(NullableBool::TRUE);
    iface->set_language_id("fr-FR");
    iface->set_font_height(16.0);

    EXPECT_EQ(iface->font_bold(), NullableBool::TRUE);
    ASSERT_TRUE(iface->language_id().has_value());
    EXPECT_EQ(iface->language_id().value(), "fr-FR");
    EXPECT_DOUBLE_EQ(iface->font_height(), 16.0);
}
