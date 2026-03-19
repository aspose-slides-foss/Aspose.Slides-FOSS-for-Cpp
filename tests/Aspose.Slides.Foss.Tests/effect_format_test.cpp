// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: return a slide with all shapes cleared.
Slide& blank_slide(Presentation& pres) {
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    return slide;
}

} // namespace

// ---------------------------------------------------------------------------
// Intent: blur effect radius and grow flag persist after set_blur_effect.
// ---------------------------------------------------------------------------
TEST(EffectFormatTest, Blur) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.set_blur_effect(8, true);

    auto* blur = ef.blur_effect();
    ASSERT_NE(blur, nullptr);
    EXPECT_EQ(blur->radius(), 8);
    EXPECT_TRUE(blur->grow());
}

// ---------------------------------------------------------------------------
// Intent: effects can be enabled then disabled; is_no_effects reflects state.
// ---------------------------------------------------------------------------
TEST(EffectFormatTest, EnableDisableEffects) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_TRUE(ef.is_no_effects());

    ef.enable_outer_shadow_effect();
    ef.enable_glow_effect();
    EXPECT_FALSE(ef.is_no_effects());

    ef.disable_outer_shadow_effect();
    ef.disable_glow_effect();
    EXPECT_TRUE(ef.is_no_effects());
}

// ---------------------------------------------------------------------------
// Intent: glow effect radius and color persist after enable + set.
// ---------------------------------------------------------------------------
TEST(EffectFormatTest, Glow) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 100, 100, 200, 200);
    auto& ef = shape.effect_format();

    ef.enable_glow_effect();
    auto* glow = ef.glow_effect();
    ASSERT_NE(glow, nullptr);
    glow->set_radius(15);
    glow->color().set_color(Drawing::Color::gold);

    // Re-read to verify persistence
    auto* glow2 = ef.glow_effect();
    ASSERT_NE(glow2, nullptr);
    EXPECT_EQ(glow2->radius(), 15);
    EXPECT_EQ(glow2->color().color(), Drawing::Color::gold);
}

// ---------------------------------------------------------------------------
// Intent: outer shadow blur_radius, direction, distance persist.
// ---------------------------------------------------------------------------
TEST(EffectFormatTest, OuterShadow) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(10);
    shadow->set_direction(315);
    shadow->set_distance(8);
    shadow->shadow_color().set_color(Drawing::Color::from_argb(128, 0, 0, 0));

    // Re-read to verify
    auto* s2 = ef.outer_shadow_effect();
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(s2->blur_radius(), 10);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
    EXPECT_EQ(s2->shadow_color().color(), Drawing::Color::from_argb(128, 0, 0, 0));
}

// ---------------------------------------------------------------------------
// Intent: soft edge radius persists after enable + set.
// ---------------------------------------------------------------------------
TEST(EffectFormatTest, SoftEdge) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_soft_edge_effect();
    auto* se = ef.soft_edge_effect();
    ASSERT_NE(se, nullptr);
    se->set_radius(10);

    auto* se2 = ef.soft_edge_effect();
    ASSERT_NE(se2, nullptr);
    EXPECT_EQ(se2->radius(), 10);
}
