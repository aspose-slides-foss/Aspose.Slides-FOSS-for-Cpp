// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/gradient_stop.h>

using namespace Aspose::Slides::Foss;

/// Default-constructed gradient stop has zero position and default color.
TEST(GradientStopTest, DefaultConstruction) {
    GradientStop stop;
    EXPECT_FLOAT_EQ(stop.position(), 0.0f);
    EXPECT_EQ(stop.color().color_type(), ColorType::NOT_DEFINED);
}

/// Constructing with position only sets position, leaves color default.
TEST(GradientStopTest, ConstructWithPosition) {
    GradientStop stop(0.75f);
    EXPECT_FLOAT_EQ(stop.position(), 0.75f);
    EXPECT_EQ(stop.color().color_type(), ColorType::NOT_DEFINED);
}

/// Constructing with position and color sets both.
TEST(GradientStopTest, ConstructWithPositionAndColor) {
    GradientStop stop(0.5f, Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_FLOAT_EQ(stop.position(), 0.5f);
    auto c = stop.color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
    EXPECT_EQ(stop.color().color_type(), ColorType::RGB);
}

/// Position can be set and retrieved.
TEST(GradientStopTest, SetPosition) {
    GradientStop stop;
    stop.set_position(0.33f);
    EXPECT_FLOAT_EQ(stop.position(), 0.33f);

    stop.set_position(1.0f);
    EXPECT_FLOAT_EQ(stop.position(), 1.0f);

    stop.set_position(0.0f);
    EXPECT_FLOAT_EQ(stop.position(), 0.0f);
}

/// Color can be set via the mutable accessor.
TEST(GradientStopTest, SetColorViaAccessor) {
    GradientStop stop;
    stop.color().set_color(Drawing::Color::from_argb(255, 0, 128, 255));

    EXPECT_EQ(stop.color().color_type(), ColorType::RGB);
    auto c = stop.color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

/// Changing the color replaces previous value.
TEST(GradientStopTest, ColorCanBeChanged) {
    GradientStop stop(0.5f, Drawing::Color::blue);
    EXPECT_EQ(stop.color().color(), Drawing::Color::blue);

    stop.color().set_color(Drawing::Color::gold);
    EXPECT_EQ(stop.color().color(), Drawing::Color::gold);
}

/// Named color constants are preserved through gradient stop.
TEST(GradientStopTest, NamedColorConstants) {
    GradientStop stop_dark_blue(0.0f, Drawing::Color::dark_blue);
    EXPECT_EQ(stop_dark_blue.color().color(), Drawing::Color::dark_blue);

    GradientStop stop_dark_red(1.0f, Drawing::Color::dark_red);
    EXPECT_EQ(stop_dark_red.color().color(), Drawing::Color::dark_red);
}

/// Multiple properties can be set independently.
TEST(GradientStopTest, IndependentPropertyAssignment) {
    GradientStop stop;
    stop.set_position(0.5f);
    stop.color().set_color(Drawing::Color::black);

    EXPECT_FLOAT_EQ(stop.position(), 0.5f);
    EXPECT_EQ(stop.color().color(), Drawing::Color::black);

    // Changing position doesn't affect color
    stop.set_position(0.75f);
    EXPECT_EQ(stop.color().color(), Drawing::Color::black);

    // Changing color doesn't affect position
    stop.color().set_color(Drawing::Color::red);
    EXPECT_FLOAT_EQ(stop.position(), 0.75f);
}

/// Const access returns correct values.
TEST(GradientStopTest, ConstAccess) {
    const GradientStop stop(0.25f, Drawing::Color::green);
    EXPECT_FLOAT_EQ(stop.position(), 0.25f);
    EXPECT_EQ(stop.color().color(), Drawing::Color::green);
}

/// ARGB components survive round-trip through gradient stop color.
TEST(GradientStopTest, ArgbRoundTrip) {
    auto semi_transparent_black = Drawing::Color::from_argb(128, 0, 0, 0);
    GradientStop stop(0.0f, semi_transparent_black);

    auto c = stop.color().color();
    EXPECT_EQ(c.a(), 128);
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 0);
    EXPECT_EQ(c.b(), 0);
}

/// Boundary positions (0.0 and 1.0) work correctly.
TEST(GradientStopTest, BoundaryPositions) {
    GradientStop start(0.0f, Drawing::Color::blue);
    GradientStop end(1.0f, Drawing::Color::red);

    EXPECT_FLOAT_EQ(start.position(), 0.0f);
    EXPECT_FLOAT_EQ(end.position(), 1.0f);
    EXPECT_EQ(start.color().color(), Drawing::Color::blue);
    EXPECT_EQ(end.color().color(), Drawing::Color::red);
}
