// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
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
// Intent: reflection blur_radius, direction, distance persist after setting.
// ---------------------------------------------------------------------------
TEST(IReflectionTest, ReflectionPropertiesPersist) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_reflection_effect();
    auto* refl = ef.reflection_effect();
    ASSERT_NE(refl, nullptr);
    refl->set_blur_radius(10);
    refl->set_direction(315);
    refl->set_distance(8);

    // Re-read to verify persistence
    auto* r2 = ef.reflection_effect();
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->blur_radius(), 10);
    EXPECT_EQ(r2->direction(), 315);
    EXPECT_EQ(r2->distance(), 8);
}

// ---------------------------------------------------------------------------
// Intent: reflection can be enabled then disabled; is_no_effects reflects state.
// ---------------------------------------------------------------------------
TEST(IReflectionTest, EnableDisableReflection) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_TRUE(ef.is_no_effects());

    ef.enable_reflection_effect();
    EXPECT_FALSE(ef.is_no_effects());
    ASSERT_NE(ef.reflection_effect(), nullptr);

    ef.disable_reflection_effect();
    EXPECT_TRUE(ef.is_no_effects());
    EXPECT_EQ(ef.reflection_effect(), nullptr);
}

// ---------------------------------------------------------------------------
// Default values: newly enabled reflection should have expected defaults.
// ---------------------------------------------------------------------------
TEST(IReflectionTest, DefaultValues) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_reflection_effect();
    auto* refl = ef.reflection_effect();
    ASSERT_NE(refl, nullptr);
    EXPECT_EQ(refl->start_pos_alpha(), 0.0);
    EXPECT_EQ(refl->end_pos_alpha(), 0.0);
    EXPECT_EQ(refl->fade_direction(), 0.0);
    EXPECT_EQ(refl->start_reflection_opacity(), 0.0);
    EXPECT_EQ(refl->end_reflection_opacity(), 0.0);
    EXPECT_EQ(refl->blur_radius(), 0.0);
    EXPECT_EQ(refl->direction(), 0.0);
    EXPECT_EQ(refl->distance(), 0.0);
    EXPECT_EQ(refl->rectangle_align(), RectangleAlignment::NOT_DEFINED);
    EXPECT_EQ(refl->skew_horizontal(), 0.0);
    EXPECT_EQ(refl->skew_vertical(), 0.0);
    EXPECT_TRUE(refl->rotate_shadow_with_shape());
    EXPECT_EQ(refl->scale_horizontal(), 100.0);
    EXPECT_EQ(refl->scale_vertical(), 100.0);
}

// ---------------------------------------------------------------------------
// properties unique to reflection - alpha, opacity, fade, skew, scale)
// Intent: all reflection properties persist after setting.
// ---------------------------------------------------------------------------
TEST(IReflectionTest, AllPropertiesPersist) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_reflection_effect();
    auto* refl = ef.reflection_effect();
    ASSERT_NE(refl, nullptr);

    refl->set_start_pos_alpha(10.0);
    refl->set_end_pos_alpha(90.0);
    refl->set_fade_direction(45.0);
    refl->set_start_reflection_opacity(50.0);
    refl->set_end_reflection_opacity(0.0);
    refl->set_blur_radius(4.0);
    refl->set_direction(270.0);
    refl->set_distance(5.0);
    refl->set_rectangle_align(RectangleAlignment::BOTTOM);
    refl->set_skew_horizontal(20.0);
    refl->set_skew_vertical(-15.0);
    refl->set_rotate_shadow_with_shape(false);
    refl->set_scale_horizontal(150.0);
    refl->set_scale_vertical(75.0);

    EXPECT_EQ(refl->start_pos_alpha(), 10.0);
    EXPECT_EQ(refl->end_pos_alpha(), 90.0);
    EXPECT_EQ(refl->fade_direction(), 45.0);
    EXPECT_EQ(refl->start_reflection_opacity(), 50.0);
    EXPECT_EQ(refl->end_reflection_opacity(), 0.0);
    EXPECT_EQ(refl->blur_radius(), 4.0);
    EXPECT_EQ(refl->direction(), 270.0);
    EXPECT_EQ(refl->distance(), 5.0);
    EXPECT_EQ(refl->rectangle_align(), RectangleAlignment::BOTTOM);
    EXPECT_EQ(refl->skew_horizontal(), 20.0);
    EXPECT_EQ(refl->skew_vertical(), -15.0);
    EXPECT_FALSE(refl->rotate_shadow_with_shape());
    EXPECT_EQ(refl->scale_horizontal(), 150.0);
    EXPECT_EQ(refl->scale_vertical(), 75.0);
}

// ---------------------------------------------------------------------------
// as_i_image_transform_operation returns a valid reference.
// ---------------------------------------------------------------------------
TEST(IReflectionTest, AsImageTransformOperation) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_reflection_effect();
    auto* refl = ef.reflection_effect();
    ASSERT_NE(refl, nullptr);

    auto& transform = refl->as_i_image_transform_operation();
    // Verify it's a valid reference (non-null address)
    EXPECT_NE(&transform, nullptr);
}
