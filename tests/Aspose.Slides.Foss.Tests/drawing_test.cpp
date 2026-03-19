// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/drawing/size.h>
#include <Aspose/Slides/Foss/drawing/size_f.h>
#include <Aspose/Slides/Foss/color_format.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace Aspose::Slides::Foss::Drawing;
using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Color tests
// ---------------------------------------------------------------------------

TEST(ColorTest, DefaultConstructor) {
    Color c;
    EXPECT_EQ(c.a(), 255);
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 0);
    EXPECT_EQ(c.b(), 0);
}

TEST(ColorTest, ArgbConstructor) {
    Color c(128, 10, 20, 30);
    EXPECT_EQ(c.a(), 128);
    EXPECT_EQ(c.r(), 10);
    EXPECT_EQ(c.g(), 20);
    EXPECT_EQ(c.b(), 30);
}

TEST(ColorTest, FromArgb) {
    auto c = Color::from_argb(128, 0, 0, 0);
    EXPECT_EQ(c.a(), 128);
    EXPECT_EQ(c.r(), 0);
}

TEST(ColorTest, Equality) {
    Color a(255, 100, 150, 200);
    Color b(255, 100, 150, 200);
    Color c(255, 100, 150, 201);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(ColorTest, CopySemantics) {
    Color original(200, 10, 20, 30);
    Color copied = original;
    EXPECT_EQ(original, copied);
    Color assigned;
    assigned = original;
    EXPECT_EQ(original, assigned);
}

TEST(ColorTest, ToStringOpaque) {
    Color c(255, 10, 20, 30);
    EXPECT_EQ(c.to_string(), "Color(r=10, g=20, b=30)");
}

TEST(ColorTest, ToStringWithAlpha) {
    Color c(128, 10, 20, 30);
    EXPECT_EQ(c.to_string(), "Color(a=128, r=10, g=20, b=30)");
}

TEST(ColorTest, StreamOutput) {
    Color c(255, 255, 0, 0);
    std::ostringstream oss;
    oss << c;
    EXPECT_EQ(oss.str(), "Color(r=255, g=0, b=0)");
}

// which uses Color.gold as an effect color value.
TEST(ColorTest, GoldNamedConstant) {
    EXPECT_EQ(Color::gold.r(), 255);
    EXPECT_EQ(Color::gold.g(), 215);
    EXPECT_EQ(Color::gold.b(), 0);
    EXPECT_EQ(Color::gold.a(), 255);
}

TEST(ColorTest, SemiTransparentBlack) {
    auto c = Color::from_argb(128, 0, 0, 0);
    EXPECT_EQ(c.a(), 128);
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 0);
    EXPECT_EQ(c.b(), 0);
}

TEST(ColorTest, NamedColorBlack) {
    EXPECT_EQ(Color::black, Color(255, 0, 0, 0));
}

TEST(ColorTest, NamedColorWhite) {
    EXPECT_EQ(Color::white, Color(255, 255, 255, 255));
}

TEST(ColorTest, NamedColorTransparent) {
    EXPECT_EQ(Color::transparent.a(), 0);
}

TEST(ColorTest, NamedColorsAreDistinct) {
    EXPECT_NE(Color::red, Color::blue);
    EXPECT_NE(Color::green, Color::yellow);
}

// ---------------------------------------------------------------------------
// PointF tests
// ---------------------------------------------------------------------------

TEST(PointFTest, DefaultConstructor) {
    PointF p;
    EXPECT_FLOAT_EQ(p.x, 0.0f);
    EXPECT_FLOAT_EQ(p.y, 0.0f);
}

TEST(PointFTest, ValueConstructor) {
    PointF p(3.5f, 7.2f);
    EXPECT_FLOAT_EQ(p.x, 3.5f);
    EXPECT_FLOAT_EQ(p.y, 7.2f);
}

TEST(PointFTest, Equality) {
    EXPECT_EQ(PointF(1.0f, 2.0f), PointF(1.0f, 2.0f));
    EXPECT_NE(PointF(1.0f, 2.0f), PointF(1.0f, 3.0f));
}

TEST(PointFTest, CommentPosition) {
    PointF pos(2.0f, 3.0f);
    EXPECT_FLOAT_EQ(pos.x, 2.0f);
    EXPECT_FLOAT_EQ(pos.y, 3.0f);
}

TEST(PointFTest, MultiplePositions) {
    PointF p1(1.0f, 1.0f);
    PointF p2(2.0f, 2.0f);
    EXPECT_NE(p1, p2);
}

TEST(PointFTest, InsertCommentPositions) {
    PointF first(1.0f, 1.0f);
    PointF third(1.0f, 3.0f);
    PointF second(1.0f, 2.0f);
    EXPECT_EQ(first.x, second.x);
    EXPECT_NE(first.y, second.y);
    EXPECT_NE(second.y, third.y);
}

TEST(PointFTest, RemoveCommentPositions) {
    std::vector<PointF> positions = {
        {1.0f, 1.0f}, {2.0f, 2.0f}, {3.0f, 3.0f}
    };
    ASSERT_EQ(positions.size(), 3u);
    positions.erase(positions.begin() + 1);
    ASSERT_EQ(positions.size(), 2u);
    EXPECT_EQ(positions[0], PointF(1.0f, 1.0f));
    EXPECT_EQ(positions[1], PointF(3.0f, 3.0f));
}

TEST(PointFTest, ClearPositions) {
    std::vector<PointF> positions = {{1.0f, 1.0f}, {2.0f, 2.0f}};
    positions.clear();
    EXPECT_TRUE(positions.empty());
}

TEST(PointFTest, StreamOutput) {
    PointF p(1.5f, 2.5f);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "PointF(x=1.5, y=2.5)");
}

// ---------------------------------------------------------------------------
// Size tests
// ---------------------------------------------------------------------------

TEST(SizeTest, DefaultConstructor) {
    Size s;
    EXPECT_EQ(s.width, 0);
    EXPECT_EQ(s.height, 0);
}

TEST(SizeTest, ValueConstructor) {
    Size s(1920, 1080);
    EXPECT_EQ(s.width, 1920);
    EXPECT_EQ(s.height, 1080);
}

TEST(SizeTest, Equality) {
    EXPECT_EQ(Size(10, 20), Size(10, 20));
    EXPECT_NE(Size(10, 20), Size(10, 21));
}

TEST(SizeTest, StreamOutput) {
    Size s(640, 480);
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "Size(width=640, height=480)");
}

// ---------------------------------------------------------------------------
// SizeF tests
// ---------------------------------------------------------------------------

TEST(SizeFTest, DefaultConstructor) {
    SizeF s;
    EXPECT_FLOAT_EQ(s.width, 0.0f);
    EXPECT_FLOAT_EQ(s.height, 0.0f);
}

TEST(SizeFTest, ValueConstructor) {
    SizeF s(12.5f, 9.75f);
    EXPECT_FLOAT_EQ(s.width, 12.5f);
    EXPECT_FLOAT_EQ(s.height, 9.75f);
}

TEST(SizeFTest, Equality) {
    EXPECT_EQ(SizeF(1.0f, 2.0f), SizeF(1.0f, 2.0f));
    EXPECT_NE(SizeF(1.0f, 2.0f), SizeF(1.0f, 3.0f));
}

TEST(SizeFTest, StreamOutput) {
    SizeF s(10.5f, 20.5f);
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "SizeF(width=10.5, height=20.5)");
}

// ---------------------------------------------------------------------------
// ColorFormat interface tests (via concrete test implementation)
// ---------------------------------------------------------------------------

namespace {

/// Minimal concrete ColorFormat for testing the base class default methods.
class TestColorFormat : public ColorFormat {
public:
    ColorType color_type() const override { return type_; }
    void set_color_type(ColorType value) override { type_ = value; }

    Drawing::Color color() const override { return color_; }
    void set_color(const Drawing::Color& value) override { color_ = value; }

    PresetColor preset_color() const override { return preset_; }
    void set_preset_color(PresetColor value) override { preset_ = value; }

    SchemeColor scheme_color() const override { return scheme_; }
    void set_scheme_color(SchemeColor value) override { scheme_ = value; }

private:
    ColorType type_ = ColorType::NOT_DEFINED;
    Drawing::Color color_;
    PresetColor preset_ = PresetColor::NOT_DEFINED;
    SchemeColor scheme_ = SchemeColor::NOT_DEFINED;
};

} // namespace

TEST(ColorFormatTest, RComponentAccessor) {
    TestColorFormat cf;
    cf.set_color(Drawing::Color(255, 100, 150, 200));
    EXPECT_EQ(cf.r(), 100);
    cf.set_r(50);
    EXPECT_EQ(cf.r(), 50);
    EXPECT_EQ(cf.g(), 150);
    EXPECT_EQ(cf.b(), 200);
}

TEST(ColorFormatTest, GComponentAccessor) {
    TestColorFormat cf;
    cf.set_color(Drawing::Color(255, 100, 150, 200));
    cf.set_g(75);
    EXPECT_EQ(cf.g(), 75);
    EXPECT_EQ(cf.r(), 100);
}

TEST(ColorFormatTest, BComponentAccessor) {
    TestColorFormat cf;
    cf.set_color(Drawing::Color(255, 100, 150, 200));
    cf.set_b(25);
    EXPECT_EQ(cf.b(), 25);
    EXPECT_EQ(cf.r(), 100);
}

TEST(ColorFormatTest, FloatAccessors) {
    TestColorFormat cf;
    cf.set_color(Drawing::Color(255, 255, 0, 128));
    EXPECT_FLOAT_EQ(cf.float_r(), 1.0f);
    EXPECT_FLOAT_EQ(cf.float_g(), 0.0f);

    cf.set_float_r(0.5f);
    EXPECT_EQ(cf.r(), 128);

    cf.set_float_g(1.0f);
    EXPECT_EQ(cf.g(), 255);

    cf.set_float_b(0.0f);
    EXPECT_EQ(cf.b(), 0);
}
