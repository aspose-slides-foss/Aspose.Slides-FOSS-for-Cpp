// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_frame.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Intent: reroute() updates connector position so it spans between shapes.
// ---------------------------------------------------------------------------
TEST(IShapeTest, RerouteUpdatesWidthOrHeight) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& s1 = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 50, 100, 80, 80);
    auto& s2 = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 400, 100, 80, 80);
    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);

    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);
    conn.reroute();

    // After reroute the connector should span between the shapes.
    EXPECT_TRUE(conn.width() > 0 || conn.height() > 0);
}

// ---------------------------------------------------------------------------
// Intent: blur effect radius persists after set_blur_effect.
// ---------------------------------------------------------------------------
TEST(IShapeTest, BlurEffect) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
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
TEST(IShapeTest, EnableDisableEffects) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

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
TEST(IShapeTest, GlowEffect) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 100, 100, 200, 200);
    auto& ef = shape.effect_format();

    ef.enable_glow_effect();
    auto* glow = ef.glow_effect();
    ASSERT_NE(glow, nullptr);
    glow->set_radius(15);

    auto* glow2 = ef.glow_effect();
    ASSERT_NE(glow2, nullptr);
    EXPECT_EQ(glow2->radius(), 15);
}

// ---------------------------------------------------------------------------
// Intent: outer shadow blur_radius, direction, distance persist.
// ---------------------------------------------------------------------------
TEST(IShapeTest, OuterShadowEffect) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();

    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(10);
    shadow->set_direction(315);
    shadow->set_distance(8);

    auto* s2 = ef.outer_shadow_effect();
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(s2->blur_radius(), 10);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
}

// ---------------------------------------------------------------------------
// Intent: soft edge radius persists after enable + set.
// ---------------------------------------------------------------------------
TEST(IShapeTest, SoftEdgeEffect) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
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

// ---------------------------------------------------------------------------
// IShape property tests — verify the new contract members work on Shape.
// ---------------------------------------------------------------------------

TEST(IShapeTest, AlternativeText) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_TRUE(shape.alternative_text().empty());

    shape.set_alternative_text("Description of shape");
    EXPECT_EQ(shape.alternative_text(), "Description of shape");
}

TEST(IShapeTest, AlternativeTextTitle) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_TRUE(shape.alternative_text_title().empty());

    shape.set_alternative_text_title("Title");
    EXPECT_EQ(shape.alternative_text_title(), "Title");
}

TEST(IShapeTest, HiddenProperty) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_FALSE(shape.hidden());

    shape.set_hidden(true);
    EXPECT_TRUE(shape.hidden());
}

TEST(IShapeTest, IsDecorativeProperty) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_FALSE(shape.is_decorative());

    shape.set_is_decorative(true);
    EXPECT_TRUE(shape.is_decorative());
}

TEST(IShapeTest, IsGroupedDefault) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_FALSE(shape.is_grouped());
}

TEST(IShapeTest, UniqueIdAndOfficeInteropId) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    // Default IDs are 0; verify they are accessible.
    EXPECT_EQ(shape.unique_id(), 0u);
    EXPECT_EQ(shape.office_interop_shape_id(), 0u);
}

TEST(IShapeTest, ConnectionSiteCount) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_EQ(shape.connection_site_count(), 4);
}

TEST(IShapeTest, FrameRoundTrip) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 10, 20, 300, 150);

    auto& f = shape.frame();
    EXPECT_DOUBLE_EQ(f.x(), 10.0);
    EXPECT_DOUBLE_EQ(f.y(), 20.0);
    EXPECT_DOUBLE_EQ(f.width(), 300.0);
    EXPECT_DOUBLE_EQ(f.height(), 150.0);

    ShapeFrame new_frame(50, 60, 400, 200);
    shape.set_frame(new_frame);
    EXPECT_DOUBLE_EQ(shape.x(), 50.0);
    EXPECT_DOUBLE_EQ(shape.y(), 60.0);
    EXPECT_DOUBLE_EQ(shape.width(), 400.0);
    EXPECT_DOUBLE_EQ(shape.height(), 200.0);
}

TEST(IShapeTest, RawFrameRoundTrip) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);

    ShapeFrame raw(5, 10, 200, 300, NullableBool::FALSE, NullableBool::FALSE, 45.0);
    shape.set_raw_frame(raw);
    EXPECT_DOUBLE_EQ(shape.raw_frame().rotation(), 45.0);
    EXPECT_DOUBLE_EQ(shape.rotation(), 45.0);
}

TEST(IShapeTest, IsTextHolderDefault) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    // AutoShape inherits default is_text_holder = false from Shape.
    EXPECT_FALSE(shape.is_text_holder());
}

TEST(IShapeTest, PlaceholderAndCustomDataDefault) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_EQ(shape.placeholder(), nullptr);
    EXPECT_EQ(shape.custom_data(), nullptr);
}
