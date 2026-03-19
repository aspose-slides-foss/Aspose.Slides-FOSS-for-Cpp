// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/effects/glow.h>
#include <Aspose/Slides/Foss/effects/i_glow.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/drawing/color.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Effects;

// ---------------------------------------------------------------------------
// Glow: default state
// ---------------------------------------------------------------------------
TEST(GlowTest, DefaultValues) {
    Glow glow;
    EXPECT_EQ(glow.radius(), 0.0);
    EXPECT_EQ(glow.color().color_type(), ColorType::NOT_DEFINED);
}

// ---------------------------------------------------------------------------
// Glow: radius read/write
// ---------------------------------------------------------------------------
TEST(GlowTest, RadiusReadWrite) {
    Glow glow;
    glow.set_radius(15.0);
    EXPECT_EQ(glow.radius(), 15.0);

    glow.set_radius(0.0);
    EXPECT_EQ(glow.radius(), 0.0);
}

// ---------------------------------------------------------------------------
// Glow: color read/write
// ---------------------------------------------------------------------------
TEST(GlowTest, ColorReadWrite) {
    Glow glow;
    glow.color().set_color(Drawing::Color::gold);
    EXPECT_EQ(glow.color().color(), Drawing::Color::gold);
}

// ---------------------------------------------------------------------------
// Glow: as_i_image_transform_operation returns self
// ---------------------------------------------------------------------------
TEST(GlowTest, AsIImageTransformOperation) {
    Glow glow;
    auto& op = glow.as_i_image_transform_operation();
    EXPECT_EQ(&op, static_cast<IImageTransformOperation*>(&glow));
}

// ---------------------------------------------------------------------------
// Glow: IGlow interface polymorphism
// ---------------------------------------------------------------------------
TEST(GlowTest, IGlowInterface) {
    Glow glow;
    IGlow& iglow = glow;
    iglow.set_radius(10.5);
    EXPECT_EQ(iglow.radius(), 10.5);
}
