// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_direction.h>
#include <Aspose/Slides/Foss/gradient_format.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/tile_flip.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: clear shapes from first slide and return a reference.
Slide& clear_slide(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    return pres.slides()[0];
}

} // namespace

/// Gradient stops and angle persist after set.
/// Ports: test_gradient_fill
TEST(GradientFormatTest, GradientStopsAndAnglePersist) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 150);

    shape.fill_format().set_fill_type(FillType::GRADIENT);
    auto& gf = shape.fill_format().gradient_format();
    gf.set_gradient_shape(GradientShape::LINEAR);
    gf.set_linear_gradient_angle(45);
    gf.gradient_stops().add(0.0f, Drawing::Color::blue);
    gf.gradient_stops().add(1.0f, Drawing::Color::red);

    EXPECT_EQ(shape.fill_format().fill_type(), FillType::GRADIENT);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::LINEAR);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 45.0f);
    ASSERT_GE(gf.gradient_stops().size(), 2u);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[1].position(), 1.0f);
}

/// tile_flip defaults to NOT_DEFINED and round-trips all values.
TEST(GradientFormatTest, TileFlipRoundTrip) {
    GradientFormat gf;
    EXPECT_EQ(gf.tile_flip(), TileFlip::NOT_DEFINED);

    gf.set_tile_flip(TileFlip::NO_FLIP);
    EXPECT_EQ(gf.tile_flip(), TileFlip::NO_FLIP);

    gf.set_tile_flip(TileFlip::FLIP_X);
    EXPECT_EQ(gf.tile_flip(), TileFlip::FLIP_X);

    gf.set_tile_flip(TileFlip::FLIP_Y);
    EXPECT_EQ(gf.tile_flip(), TileFlip::FLIP_Y);

    gf.set_tile_flip(TileFlip::FLIP_BOTH);
    EXPECT_EQ(gf.tile_flip(), TileFlip::FLIP_BOTH);

    gf.set_tile_flip(TileFlip::NOT_DEFINED);
    EXPECT_EQ(gf.tile_flip(), TileFlip::NOT_DEFINED);
}

/// gradient_direction defaults to NOT_DEFINED; setting NOT_DEFINED is a no-op.
TEST(GradientFormatTest, GradientDirectionRoundTrip) {
    GradientFormat gf;
    EXPECT_EQ(gf.gradient_direction(), GradientDirection::NOT_DEFINED);

    gf.set_gradient_direction(GradientDirection::FROM_CORNER1);
    EXPECT_EQ(gf.gradient_direction(), GradientDirection::FROM_CORNER1);

    gf.set_gradient_direction(GradientDirection::FROM_CENTER);
    EXPECT_EQ(gf.gradient_direction(), GradientDirection::FROM_CENTER);

    // Setting NOT_DEFINED is a no-op — value should remain FROM_CENTER.
    gf.set_gradient_direction(GradientDirection::NOT_DEFINED);
    EXPECT_EQ(gf.gradient_direction(), GradientDirection::FROM_CENTER);
}

/// gradient_shape defaults to NOT_DEFINED; setting NOT_DEFINED is a no-op.
TEST(GradientFormatTest, GradientShapeSetNotDefinedIsNoop) {
    GradientFormat gf;
    EXPECT_EQ(gf.gradient_shape(), GradientShape::NOT_DEFINED);

    gf.set_gradient_shape(GradientShape::RADIAL);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::RADIAL);

    // Setting NOT_DEFINED is a no-op.
    gf.set_gradient_shape(GradientShape::NOT_DEFINED);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::RADIAL);
}

/// All gradient shape values can be set and read back.
TEST(GradientFormatTest, GradientShapeAllValues) {
    GradientFormat gf;

    gf.set_gradient_shape(GradientShape::LINEAR);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::LINEAR);

    gf.set_gradient_shape(GradientShape::RECTANGLE);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::RECTANGLE);

    gf.set_gradient_shape(GradientShape::RADIAL);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::RADIAL);

    gf.set_gradient_shape(GradientShape::PATH);
    EXPECT_EQ(gf.gradient_shape(), GradientShape::PATH);
}

/// linear_gradient_angle defaults to 0.0 and round-trips.
TEST(GradientFormatTest, LinearGradientAngle) {
    GradientFormat gf;
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 0.0f);

    gf.set_linear_gradient_angle(90.0f);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 90.0f);

    gf.set_linear_gradient_angle(45.5f);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 45.5f);

    gf.set_linear_gradient_angle(0.0f);
    EXPECT_FLOAT_EQ(gf.linear_gradient_angle(), 0.0f);
}

/// linear_gradient_scaled defaults to NOT_DEFINED and round-trips NullableBool.
TEST(GradientFormatTest, LinearGradientScaled) {
    GradientFormat gf;
    EXPECT_EQ(gf.linear_gradient_scaled(), NullableBool::NOT_DEFINED);

    gf.set_linear_gradient_scaled(NullableBool::TRUE);
    EXPECT_EQ(gf.linear_gradient_scaled(), NullableBool::TRUE);

    gf.set_linear_gradient_scaled(NullableBool::FALSE);
    EXPECT_EQ(gf.linear_gradient_scaled(), NullableBool::FALSE);

    gf.set_linear_gradient_scaled(NullableBool::NOT_DEFINED);
    EXPECT_EQ(gf.linear_gradient_scaled(), NullableBool::NOT_DEFINED);
}

/// gradient_stops can be added and accessed by index.
TEST(GradientFormatTest, GradientStopsCollection) {
    GradientFormat gf;
    EXPECT_EQ(gf.gradient_stops().size(), 0u);

    gf.gradient_stops().add(0.0f, Drawing::Color::blue);
    gf.gradient_stops().add(0.5f, Drawing::Color::green);
    gf.gradient_stops().add(1.0f, Drawing::Color::red);

    ASSERT_EQ(gf.gradient_stops().size(), 3u);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[1].position(), 0.5f);
    EXPECT_FLOAT_EQ(gf.gradient_stops()[2].position(), 1.0f);

    EXPECT_EQ(gf.gradient_stops()[0].color().color(), Drawing::Color::blue);
    EXPECT_EQ(gf.gradient_stops()[2].color().color(), Drawing::Color::red);
}
