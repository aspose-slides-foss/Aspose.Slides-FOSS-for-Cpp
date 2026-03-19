// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/effects/blur.h>
#include <Aspose/Slides/Foss/effects/i_blur.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/effect_format.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Effects;

// ---------------------------------------------------------------------------
// Blur: default state
// ---------------------------------------------------------------------------
TEST(BlurTest, DefaultValues) {
    Blur blur;
    EXPECT_EQ(blur.radius(), 0.0);
    EXPECT_TRUE(blur.grow());
}

// ---------------------------------------------------------------------------
// Blur: radius read/write
// ---------------------------------------------------------------------------
TEST(BlurTest, RadiusReadWrite) {
    Blur blur;
    blur.set_radius(8.0);
    EXPECT_EQ(blur.radius(), 8.0);

    blur.set_radius(0.0);
    EXPECT_EQ(blur.radius(), 0.0);
}

// ---------------------------------------------------------------------------
// Blur: grow read/write
// ---------------------------------------------------------------------------
TEST(BlurTest, GrowReadWrite) {
    Blur blur;
    EXPECT_TRUE(blur.grow());

    blur.set_grow(false);
    EXPECT_FALSE(blur.grow());

    blur.set_grow(true);
    EXPECT_TRUE(blur.grow());
}

// ---------------------------------------------------------------------------
// Blur: as_i_image_transform_operation returns self
// ---------------------------------------------------------------------------
TEST(BlurTest, AsIImageTransformOperation) {
    Blur blur;
    auto& op = blur.as_i_image_transform_operation();
    EXPECT_EQ(&op, static_cast<IImageTransformOperation*>(&blur));
}

// ---------------------------------------------------------------------------
// Blur: IBlur interface polymorphism
// ---------------------------------------------------------------------------
TEST(BlurTest, IBlurInterface) {
    Blur blur;
    IBlur& iblur = blur;
    iblur.set_radius(10.5);
    EXPECT_EQ(iblur.radius(), 10.5);
    iblur.set_grow(false);
    EXPECT_FALSE(iblur.grow());
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
TEST(BlurTest, SetBlurEffectViaEffectFormat) {
    EffectFormat ef;
    EXPECT_EQ(ef.blur_effect(), nullptr);

    ef.set_blur_effect(8.0, true);
    auto* b = ef.blur_effect();
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(b->radius(), 8.0);
    EXPECT_TRUE(b->grow());
}

// ---------------------------------------------------------------------------
// Blur: disable removes blur effect
// ---------------------------------------------------------------------------
TEST(BlurTest, DisableBlurEffect) {
    EffectFormat ef;
    ef.set_blur_effect(5.0, false);
    EXPECT_FALSE(ef.is_no_effects());

    ef.disable_blur_effect();
    EXPECT_EQ(ef.blur_effect(), nullptr);
    EXPECT_TRUE(ef.is_no_effects());
}
