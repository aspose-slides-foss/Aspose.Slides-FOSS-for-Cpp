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
// Intent: inner shadow blur_radius, direction, distance, shadow_color persist.
// ---------------------------------------------------------------------------
TEST(IInnerShadowTest, InnerShadowPropertiesPersist) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_inner_shadow_effect();
    auto* shadow = ef.inner_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(10);
    shadow->set_direction(315);
    shadow->set_distance(8);
    shadow->shadow_color().set_color(Drawing::Color::from_argb(128, 0, 0, 0));

    // Re-read to verify persistence
    auto* s2 = ef.inner_shadow_effect();
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(s2->blur_radius(), 10);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
    EXPECT_EQ(s2->shadow_color().color(), Drawing::Color::from_argb(128, 0, 0, 0));
}

// ---------------------------------------------------------------------------
// enable/disable mirrors the enable/disable pattern tested for other effects)
// Intent: inner shadow can be enabled then disabled; is_no_effects reflects state.
// ---------------------------------------------------------------------------
TEST(IInnerShadowTest, EnableDisableInnerShadow) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_TRUE(ef.is_no_effects());

    ef.enable_inner_shadow_effect();
    EXPECT_FALSE(ef.is_no_effects());
    ASSERT_NE(ef.inner_shadow_effect(), nullptr);

    ef.disable_inner_shadow_effect();
    EXPECT_TRUE(ef.is_no_effects());
    EXPECT_EQ(ef.inner_shadow_effect(), nullptr);
}

// ---------------------------------------------------------------------------
// Default values: newly enabled inner shadow should have sensible defaults.
// ---------------------------------------------------------------------------
TEST(IInnerShadowTest, DefaultValues) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_inner_shadow_effect();
    auto* shadow = ef.inner_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    EXPECT_EQ(shadow->blur_radius(), 0.0);
    EXPECT_EQ(shadow->direction(), 0.0);
    EXPECT_EQ(shadow->distance(), 0.0);
}
