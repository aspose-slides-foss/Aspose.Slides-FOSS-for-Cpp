// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/effects/fill_overlay.h>
#include <Aspose/Slides/Foss/fill_blend_mode.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Effects;

// ---------------------------------------------------------------------------
// Test: Default blend mode is OVERLAY
// Intent: A freshly-created FillOverlay defaults to FillBlendMode::OVERLAY.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, DefaultBlendIsOverlay) {
    FillOverlay fo;
    EXPECT_EQ(fo.blend(), FillBlendMode::OVERLAY);
}

// ---------------------------------------------------------------------------
// Test: Blend mode round-trip
// Intent: Setting blend mode persists for all valid enum values.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, BlendRoundTrip) {
    FillOverlay fo;

    fo.set_blend(FillBlendMode::MULTIPLY);
    EXPECT_EQ(fo.blend(), FillBlendMode::MULTIPLY);

    fo.set_blend(FillBlendMode::SCREEN);
    EXPECT_EQ(fo.blend(), FillBlendMode::SCREEN);

    fo.set_blend(FillBlendMode::DARKEN);
    EXPECT_EQ(fo.blend(), FillBlendMode::DARKEN);

    fo.set_blend(FillBlendMode::LIGHTEN);
    EXPECT_EQ(fo.blend(), FillBlendMode::LIGHTEN);

    fo.set_blend(FillBlendMode::OVERLAY);
    EXPECT_EQ(fo.blend(), FillBlendMode::OVERLAY);
}

// ---------------------------------------------------------------------------
// Test: fill_format is accessible and mutable
// Intent: The fill_format property returns a usable FillFormat that can be
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, FillFormatAccessible) {
    FillOverlay fo;

    auto& ff = fo.fill_format();
    EXPECT_EQ(ff.fill_type(), FillType::NOT_DEFINED);

    ff.set_fill_type(FillType::SOLID);
    EXPECT_EQ(fo.fill_format().fill_type(), FillType::SOLID);
}

// ---------------------------------------------------------------------------
// Test: fill_format solid color round-trip
// Intent: The overlay's fill format supports solid fill color configuration.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, FillFormatSolidColor) {
    FillOverlay fo;
    fo.fill_format().set_fill_type(FillType::SOLID);
    fo.fill_format().solid_fill_color().set_color(Drawing::Color::red);

    EXPECT_EQ(fo.fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(fo.fill_format().solid_fill_color().color(), Drawing::Color::red);
}

// ---------------------------------------------------------------------------
// Test: slide defaults to nullptr
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, SlideDefaultsToNull) {
    FillOverlay fo;
    EXPECT_EQ(fo.slide(), nullptr);
}

// ---------------------------------------------------------------------------
// Test: as_i_image_transform_operation returns self
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, AsImageTransformOperationReturnsSelf) {
    FillOverlay fo;
    IImageTransformOperation& op = fo.as_i_image_transform_operation();
    EXPECT_EQ(&op, static_cast<IImageTransformOperation*>(&fo));
}

// ---------------------------------------------------------------------------
// Test: as_i_presentation_component returns nullptr for standalone FillOverlay
// Intent: A standalone FillOverlay (not attached to a shape hierarchy) does
// not implement IPresentationComponent directly.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, AsPresentationComponentIsNull) {
    FillOverlay fo;
    EXPECT_EQ(fo.as_i_presentation_component(), nullptr);
}

// ---------------------------------------------------------------------------
// Test: FillOverlay via EffectFormat enable/disable
// Intent: Matches test_effect_format.py pattern — enable fill overlay through
// EffectFormat, configure blend mode, then verify persistence.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, EnableViaEffectFormat) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    EXPECT_EQ(ef.fill_overlay_effect(), nullptr);

    ef.enable_fill_overlay_effect();
    auto* fo = ef.fill_overlay_effect();
    ASSERT_NE(fo, nullptr);

    fo->set_blend(FillBlendMode::MULTIPLY);
    EXPECT_EQ(ef.fill_overlay_effect()->blend(), FillBlendMode::MULTIPLY);
}

// ---------------------------------------------------------------------------
// Test: Disable fill overlay clears it
// Intent: After disabling, fill_overlay_effect returns nullptr and
// is_no_effects reflects the change.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, DisableClearsEffect) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_fill_overlay_effect();
    EXPECT_FALSE(ef.is_no_effects());

    ef.disable_fill_overlay_effect();
    EXPECT_EQ(ef.fill_overlay_effect(), nullptr);
    EXPECT_TRUE(ef.is_no_effects());
}

// ---------------------------------------------------------------------------
// Test: Const access
// Intent: The const overloads of fill_format and blend compile and return
// consistent values.
// ---------------------------------------------------------------------------
TEST(FillOverlayTest, ConstAccess) {
    FillOverlay fo;
    fo.set_blend(FillBlendMode::SCREEN);
    fo.fill_format().set_fill_type(FillType::SOLID);

    const auto& cfo = fo;
    EXPECT_EQ(cfo.blend(), FillBlendMode::SCREEN);
    EXPECT_EQ(cfo.fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(cfo.slide(), nullptr);
}
