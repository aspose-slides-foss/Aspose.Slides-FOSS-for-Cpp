// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file effect_format_test.cpp
/// Integration tests for EffectFormat: shadow, glow, soft edge, blur, reflection.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/effect_format.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/rectangle_alignment.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class EffectFormatIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("effect_format_integration_test_" +
                    std::to_string(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()));
        std::filesystem::create_directories(tmp_dir_);
    }

    void TearDown() override {
        std::filesystem::remove_all(tmp_dir_);
    }

    /// Saves a presentation to a temp file and reopens from that file.
    Presentation save_and_reopen(Presentation& pres) {
        auto path = (tmp_dir_ / "roundtrip.pptx").string();
        pres.save(path, static_cast<int>(SaveFormat::PPTX));
        return Presentation(path);
    }

    Slide& clear_slide(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        return pres.slides()[0];
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(EffectFormatIntegrationTest, OuterShadow) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();
    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(10);
    shadow->set_direction(315);
    shadow->set_distance(8);
    shadow->shadow_color().set_color(Color::from_argb(128, 0, 0, 0));

    auto pres2 = save_and_reopen(pres);
    auto& ef2 = pres2.slides()[0].shapes()[0].effect_format();
    auto* s2 = ef2.outer_shadow_effect();
    ASSERT_NE(s2, nullptr) << "outer_shadow_effect should not be None after reload";
    EXPECT_EQ(s2->blur_radius(), 10);
    EXPECT_EQ(s2->direction(), 315);
    EXPECT_EQ(s2->distance(), 8);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(EffectFormatIntegrationTest, Glow) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 100, 100, 200, 200);
    auto& ef = shape.effect_format();
    ef.enable_glow_effect();
    auto* glow = ef.glow_effect();
    ASSERT_NE(glow, nullptr);
    glow->set_radius(15);
    glow->color().set_color(Color::gold);

    auto pres2 = save_and_reopen(pres);
    auto* g2 = pres2.slides()[0].shapes()[0].effect_format().glow_effect();
    ASSERT_NE(g2, nullptr) << "glow_effect should not be None after reload";
    EXPECT_EQ(g2->radius(), 15);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(EffectFormatIntegrationTest, SoftEdge) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();
    ef.enable_soft_edge_effect();
    auto* se = ef.soft_edge_effect();
    ASSERT_NE(se, nullptr);
    se->set_radius(10);

    auto pres2 = save_and_reopen(pres);
    auto* se2 = pres2.slides()[0].shapes()[0].effect_format().soft_edge_effect();
    ASSERT_NE(se2, nullptr) << "soft_edge_effect should not be None after reload";
    EXPECT_EQ(se2->radius(), 10);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(EffectFormatIntegrationTest, Blur) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& ef = shape.effect_format();
    ef.set_blur_effect(8, true);

    auto pres2 = save_and_reopen(pres);
    auto* b2 = pres2.slides()[0].shapes()[0].effect_format().blur_effect();
    ASSERT_NE(b2, nullptr) << "blur_effect should not be None after reload";
    EXPECT_EQ(b2->radius(), 8);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(EffectFormatIntegrationTest, EnableDisableEffects) {
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

} // namespace
