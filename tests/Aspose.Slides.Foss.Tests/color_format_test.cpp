// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/color_format.h>
#include <Aspose/Slides/Foss/drawing/color.h>

#include <gtest/gtest.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

// ---------------------------------------------------------------------------
// Concrete stub for testing the ColorFormat base-class default methods.
// ---------------------------------------------------------------------------

namespace {

class StubColorFormat : public ColorFormat {
public:
    ColorType color_type() const override { return type_; }
    void set_color_type(ColorType value) override { type_ = value; }

    Color color() const override { return color_; }
    void set_color(const Color& value) override { color_ = value; }

    PresetColor preset_color() const override { return preset_; }
    void set_preset_color(PresetColor value) override { preset_ = value; }

    SchemeColor scheme_color() const override { return scheme_; }
    void set_scheme_color(SchemeColor value) override { scheme_ = value; }

private:
    ColorType type_ = ColorType::NOT_DEFINED;
    Color color_;
    PresetColor preset_ = PresetColor::NOT_DEFINED;
    SchemeColor scheme_ = SchemeColor::NOT_DEFINED;
};

} // namespace

// ---------------------------------------------------------------------------
// Intent: shadow_color.color = Color.from_argb(128,0,0,0) preserves ARGB.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, SetColorSemiTransparentBlack) {
    StubColorFormat cf;
    cf.set_color(Color::from_argb(128, 0, 0, 0));

    EXPECT_EQ(cf.color().a(), 128);
    EXPECT_EQ(cf.color().r(), 0);
    EXPECT_EQ(cf.color().g(), 0);
    EXPECT_EQ(cf.color().b(), 0);

    // Component accessors also reflect the value
    EXPECT_EQ(cf.r(), 0);
    EXPECT_EQ(cf.g(), 0);
    EXPECT_EQ(cf.b(), 0);
}

// ---------------------------------------------------------------------------
// Intent: glow_effect.color.color = Color.gold — named color round-trips.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, SetColorGold) {
    StubColorFormat cf;
    cf.set_color(Color::gold);

    EXPECT_EQ(cf.color(), Color::gold);
    EXPECT_EQ(cf.r(), 255);
    EXPECT_EQ(cf.g(), 215);
    EXPECT_EQ(cf.b(), 0);
}

// ---------------------------------------------------------------------------
// Intent: solid_fill_color.color = Color.from_argb(255,0,128,255) then
//         verify c.r == 0 && c.g == 128 && c.b == 255.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, SolidFillColorComponents) {
    StubColorFormat cf;
    cf.set_color(Color::from_argb(255, 0, 128, 255));

    auto c = cf.color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

// ---------------------------------------------------------------------------
// Intent: fore_color.color = Color.dark_blue, back_color.color = Color.light_yellow
//         — two independent ColorFormat instances hold distinct named colors.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, PatternFillForeAndBackColors) {
    StubColorFormat fore;
    fore.set_color(Color::dark_blue);

    StubColorFormat back;
    back.set_color(Color::light_yellow);

    EXPECT_EQ(fore.color(), Color::dark_blue);
    EXPECT_EQ(back.color(), Color::light_yellow);
    EXPECT_NE(fore.color(), back.color());

    // dark_blue = (255, 0, 0, 139)
    EXPECT_EQ(fore.r(), 0);
    EXPECT_EQ(fore.g(), 0);
    EXPECT_EQ(fore.b(), 139);

    // light_yellow = (255, 255, 255, 224)
    EXPECT_EQ(back.r(), 255);
    EXPECT_EQ(back.g(), 255);
    EXPECT_EQ(back.b(), 224);
}

// ---------------------------------------------------------------------------
// Intent: solid_fill_color.color = Color.dark_red then c.r == Color.dark_red.r.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, LineColorDarkRed) {
    StubColorFormat cf;
    cf.set_color(Color::dark_red);

    EXPECT_EQ(cf.r(), Color::dark_red.r());
    EXPECT_EQ(cf.g(), Color::dark_red.g());
    EXPECT_EQ(cf.b(), Color::dark_red.b());
}

// ---------------------------------------------------------------------------
// Intent: solid_fill_color.color = Color.black — verify black round-trips.
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, LineColorBlack) {
    StubColorFormat cf;
    cf.set_color(Color::black);

    EXPECT_EQ(cf.color(), Color::black);
    EXPECT_EQ(cf.r(), 0);
    EXPECT_EQ(cf.g(), 0);
    EXPECT_EQ(cf.b(), 0);
}

// ---------------------------------------------------------------------------
// Additional ColorFormat utility tests: component setters preserve others
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, SetRPreservesOtherChannels) {
    StubColorFormat cf;
    cf.set_color(Color::from_argb(200, 10, 20, 30));

    cf.set_r(99);

    EXPECT_EQ(cf.r(), 99);
    EXPECT_EQ(cf.g(), 20);
    EXPECT_EQ(cf.b(), 30);
    EXPECT_EQ(cf.color().a(), 200);
}

TEST(ColorFormatUtilTest, SetGPreservesOtherChannels) {
    StubColorFormat cf;
    cf.set_color(Color::from_argb(200, 10, 20, 30));

    cf.set_g(99);

    EXPECT_EQ(cf.r(), 10);
    EXPECT_EQ(cf.g(), 99);
    EXPECT_EQ(cf.b(), 30);
    EXPECT_EQ(cf.color().a(), 200);
}

TEST(ColorFormatUtilTest, SetBPreservesOtherChannels) {
    StubColorFormat cf;
    cf.set_color(Color::from_argb(200, 10, 20, 30));

    cf.set_b(99);

    EXPECT_EQ(cf.r(), 10);
    EXPECT_EQ(cf.g(), 20);
    EXPECT_EQ(cf.b(), 99);
    EXPECT_EQ(cf.color().a(), 200);
}

// ---------------------------------------------------------------------------
// Float accessors: round-trip and boundary values
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, FloatAccessorsRoundTrip) {
    StubColorFormat cf;
    cf.set_color(Color(255, 255, 0, 128));

    EXPECT_FLOAT_EQ(cf.float_r(), 1.0f);
    EXPECT_FLOAT_EQ(cf.float_g(), 0.0f);
    EXPECT_NEAR(cf.float_b(), 128.0f / 255.0f, 1e-5f);

    cf.set_float_r(0.5f);
    EXPECT_EQ(cf.r(), 128);

    cf.set_float_g(1.0f);
    EXPECT_EQ(cf.g(), 255);

    cf.set_float_b(0.0f);
    EXPECT_EQ(cf.b(), 0);
}

TEST(ColorFormatUtilTest, FloatAccessorsBoundary) {
    StubColorFormat cf;

    cf.set_float_r(0.0f);
    cf.set_float_g(0.0f);
    cf.set_float_b(0.0f);
    EXPECT_EQ(cf.r(), 0);
    EXPECT_EQ(cf.g(), 0);
    EXPECT_EQ(cf.b(), 0);

    cf.set_float_r(1.0f);
    cf.set_float_g(1.0f);
    cf.set_float_b(1.0f);
    EXPECT_EQ(cf.r(), 255);
    EXPECT_EQ(cf.g(), 255);
    EXPECT_EQ(cf.b(), 255);
}

// ---------------------------------------------------------------------------
// Preset and scheme color accessors
// ---------------------------------------------------------------------------

TEST(ColorFormatUtilTest, PresetColorAccessor) {
    StubColorFormat cf;
    EXPECT_EQ(cf.preset_color(), PresetColor::NOT_DEFINED);

    cf.set_preset_color(PresetColor::ALICE_BLUE);
    EXPECT_EQ(cf.preset_color(), PresetColor::ALICE_BLUE);
}

TEST(ColorFormatUtilTest, SchemeColorAccessor) {
    StubColorFormat cf;
    EXPECT_EQ(cf.scheme_color(), SchemeColor::NOT_DEFINED);

    cf.set_scheme_color(SchemeColor::ACCENT1);
    EXPECT_EQ(cf.scheme_color(), SchemeColor::ACCENT1);
}

TEST(ColorFormatUtilTest, ColorTypeAccessor) {
    StubColorFormat cf;
    EXPECT_EQ(cf.color_type(), ColorType::NOT_DEFINED);

    cf.set_color_type(ColorType::RGB);
    EXPECT_EQ(cf.color_type(), ColorType::RGB);

    cf.set_color_type(ColorType::SCHEME);
    EXPECT_EQ(cf.color_type(), ColorType::SCHEME);

    cf.set_color_type(ColorType::PRESET);
    EXPECT_EQ(cf.color_type(), ColorType::PRESET);
}
