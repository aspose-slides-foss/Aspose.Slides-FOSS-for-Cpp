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
// Intent: preset shadow direction, distance, shadow_color persist.
// ---------------------------------------------------------------------------
TEST(IPresetShadowTest, PresetShadowPropertiesPersist) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_preset_shadow_effect();
    auto* shadow = ef.preset_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_direction(315);
    shadow->set_distance(8);
    shadow->shadow_color().set_color(Drawing::Color::from_argb(128, 0, 0, 0));

    // Re-read to verify persistence
    auto* s2 = ef.preset_shadow_effect();
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
    EXPECT_EQ(s2->shadow_color().color(), Drawing::Color::from_argb(128, 0, 0, 0));
}

// ---------------------------------------------------------------------------
// enable/disable mirrors the enable/disable pattern tested for other effects)
// Intent: preset shadow can be enabled then disabled; is_no_effects reflects state.
// ---------------------------------------------------------------------------
TEST(IPresetShadowTest, EnableDisablePresetShadow) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_TRUE(ef.is_no_effects());

    ef.enable_preset_shadow_effect();
    EXPECT_FALSE(ef.is_no_effects());
    ASSERT_NE(ef.preset_shadow_effect(), nullptr);

    ef.disable_preset_shadow_effect();
    EXPECT_TRUE(ef.is_no_effects());
    EXPECT_EQ(ef.preset_shadow_effect(), nullptr);
}

// ---------------------------------------------------------------------------
// Default values: newly enabled preset shadow should have sensible defaults.
// ---------------------------------------------------------------------------
TEST(IPresetShadowTest, DefaultValues) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_preset_shadow_effect();
    auto* shadow = ef.preset_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    EXPECT_EQ(shadow->direction(), 0.0);
    EXPECT_EQ(shadow->distance(), 0.0);
    EXPECT_EQ(shadow->preset(), PresetShadowType::TOP_LEFT_DROP_SHADOW);
}

// ---------------------------------------------------------------------------
// Preset type can be set and retrieved.
// ---------------------------------------------------------------------------
TEST(IPresetShadowTest, PresetTypeReadWrite) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_preset_shadow_effect();
    auto* shadow = ef.preset_shadow_effect();
    ASSERT_NE(shadow, nullptr);

    shadow->set_preset(PresetShadowType::BOTTOM_RIGHT_DROP_SHADOW);
    EXPECT_EQ(shadow->preset(), PresetShadowType::BOTTOM_RIGHT_DROP_SHADOW);

    shadow->set_preset(PresetShadowType::OUTER_BOX_SHADOW3_D);
    EXPECT_EQ(shadow->preset(), PresetShadowType::OUTER_BOX_SHADOW3_D);
}

// ---------------------------------------------------------------------------
// as_i_image_transform_operation returns a valid reference.
// ---------------------------------------------------------------------------
TEST(IPresetShadowTest, AsImageTransformOperation) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_preset_shadow_effect();
    auto* shadow = ef.preset_shadow_effect();
    ASSERT_NE(shadow, nullptr);

    auto& op = shadow->as_i_image_transform_operation();
    // Verify it returns a reference to the same object (as IImageTransformOperation).
    EXPECT_EQ(&op, static_cast<Effects::IImageTransformOperation*>(shadow));
}
