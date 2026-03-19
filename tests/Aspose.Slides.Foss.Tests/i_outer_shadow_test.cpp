// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/rectangle_alignment.h>
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
// Intent: outer shadow blur_radius, direction, distance, shadow_color persist.
// ---------------------------------------------------------------------------
TEST(IOuterShadowTest, OuterShadowPropertiesPersist) {
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

    // Re-read to verify persistence
    auto* s2 = ef.outer_shadow_effect();
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(s2->blur_radius(), 10);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
    EXPECT_EQ(s2->shadow_color().color(), Drawing::Color::from_argb(128, 0, 0, 0));
}

// ---------------------------------------------------------------------------
// Intent: outer shadow can be enabled then disabled; is_no_effects reflects state.
// ---------------------------------------------------------------------------
TEST(IOuterShadowTest, EnableDisableOuterShadow) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_TRUE(ef.is_no_effects());

    ef.enable_outer_shadow_effect();
    EXPECT_FALSE(ef.is_no_effects());
    ASSERT_NE(ef.outer_shadow_effect(), nullptr);

    ef.disable_outer_shadow_effect();
    EXPECT_TRUE(ef.is_no_effects());
    EXPECT_EQ(ef.outer_shadow_effect(), nullptr);
}

// ---------------------------------------------------------------------------
// Default values: newly enabled outer shadow should have expected defaults.
// ---------------------------------------------------------------------------
TEST(IOuterShadowTest, DefaultValues) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    EXPECT_EQ(shadow->blur_radius(), 0.0);
    EXPECT_EQ(shadow->direction(), 0.0);
    EXPECT_EQ(shadow->distance(), 0.0);
    EXPECT_EQ(shadow->rectangle_align(), RectangleAlignment::NOT_DEFINED);
    EXPECT_EQ(shadow->skew_horizontal(), 0.0);
    EXPECT_EQ(shadow->skew_vertical(), 0.0);
    EXPECT_TRUE(shadow->rotate_shadow_with_shape());
    EXPECT_EQ(shadow->scale_horizontal(), 100.0);
    EXPECT_EQ(shadow->scale_vertical(), 100.0);
}

// ---------------------------------------------------------------------------
// properties unique to outer shadow - rectangle_align, skew, scale, rotation)
// Intent: all outer shadow properties persist after setting.
// ---------------------------------------------------------------------------
TEST(IOuterShadowTest, AdditionalPropertiesPersist) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);

    shadow->set_rectangle_align(RectangleAlignment::CENTER);
    shadow->set_skew_horizontal(20.0);
    shadow->set_skew_vertical(-15.0);
    shadow->set_rotate_shadow_with_shape(false);
    shadow->set_scale_horizontal(150.0);
    shadow->set_scale_vertical(75.0);

    EXPECT_EQ(shadow->rectangle_align(), RectangleAlignment::CENTER);
    EXPECT_EQ(shadow->skew_horizontal(), 20.0);
    EXPECT_EQ(shadow->skew_vertical(), -15.0);
    EXPECT_FALSE(shadow->rotate_shadow_with_shape());
    EXPECT_EQ(shadow->scale_horizontal(), 150.0);
    EXPECT_EQ(shadow->scale_vertical(), 75.0);
}

// ---------------------------------------------------------------------------
// as_i_image_transform_operation returns a valid reference.
// ---------------------------------------------------------------------------
TEST(IOuterShadowTest, AsImageTransformOperation) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);

    auto& transform = shadow->as_i_image_transform_operation();
    // Verify it's a valid reference (non-null address)
    EXPECT_NE(&transform, nullptr);
}
