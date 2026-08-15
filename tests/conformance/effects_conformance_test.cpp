// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file effects_conformance_test.cpp
/// Every shape effect, checked in the file rather than in the object that was
/// just told about it.
///
/// The in-memory effect objects report back whatever was set on them, so an
/// `enable_x(); set_y(); read y()` test passes whether or not the serialiser
/// knows the effect exists. Four of the eight effects are serialised; the
/// other four leave an empty `<a:effectLst/>` behind and the shape opens with
/// no effect on it.

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/effect_format.h>
#include <Aspose/Slides/Foss/effects/blur.h>
#include <Aspose/Slides/Foss/effects/fill_overlay.h>
#include <Aspose/Slides/Foss/effects/glow.h>
#include <Aspose/Slides/Foss/effects/inner_shadow.h>
#include <Aspose/Slides/Foss/effects/outer_shadow.h>
#include <Aspose/Slides/Foss/effects/preset_shadow.h>
#include <Aspose/Slides/Foss/effects/reflection.h>
#include <Aspose/Slides/Foss/effects/soft_edge.h>
#include <Aspose/Slides/Foss/fill_blend_mode.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/preset_shadow_type.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

constexpr const char* kSlide = "ppt/slides/slide1.xml";

class EffectsConformance : public conformance::SavedDeckTest {
protected:
    AutoShape& fresh_shape(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        return pres.slides()[0].shapes().add_auto_shape(ShapeType::RECTANGLE,
                                                        100, 100, 200, 100);
    }
};

// -- The four that are serialised today. Regression guards. -----------------

TEST_F(EffectsConformance, AnOuterShadowReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_outer_shadow_effect();
    auto* shadow = ef.outer_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(10);   // 10 pt -> 127000 EMU
    shadow->set_distance(5);       // 5 pt  -> 63500 EMU
    shadow->set_direction(45);     // 45 deg -> 2700000
    shadow->shadow_color().set_color(Color::black);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:effectLst/a:outerShdw",
        {{"blurRad", "127000"}, {"dist", "63500"}, {"dir", "2700000"}}));
}

TEST_F(EffectsConformance, AGlowReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_glow_effect();
    auto* glow = ef.glow_effect();
    ASSERT_NE(glow, nullptr);
    glow->set_radius(5); // 5 pt -> 63500 EMU
    glow->color().set_color(Color::gold);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:effectLst/a:glow",
                                           {{"rad", "63500"}}));
}

TEST_F(EffectsConformance, ASoftEdgeReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_soft_edge_effect();
    auto* edge = ef.soft_edge_effect();
    ASSERT_NE(edge, nullptr);
    edge->set_radius(5);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:softEdge",
                                           {{"rad", "63500"}}));
}

TEST_F(EffectsConformance, ABlurReachesTheFile) {
    Presentation pres;
    fresh_shape(pres).effect_format().set_blur_effect(8, true);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:effectLst/a:blur",
                                           {{"rad", "101600"}, {"grow", "1"}}));
}

// -- The four that are not. -------------------------------------------------

TEST_F(EffectsConformance, AnInnerShadowReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_inner_shadow_effect();
    auto* shadow = ef.inner_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(8);  // 8 pt -> 101600 EMU
    shadow->set_distance(5);     // 5 pt -> 63500 EMU
    shadow->set_direction(45);   // 45 deg -> 2700000
    shadow->shadow_color().set_color(Color::black);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:effectLst/a:innerShdw",
        {{"blurRad", "101600"}, {"dist", "63500"}, {"dir", "2700000"}}))
        << "the shape opens with no inner shadow on it";
}

TEST_F(EffectsConformance, APresetShadowReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_preset_shadow_effect();
    auto* shadow = ef.preset_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_preset(PresetShadowType::TOP_LEFT_DROP_SHADOW);
    shadow->set_distance(5); // 5 pt -> 63500 EMU
    shadow->set_direction(45);
    shadow->shadow_color().set_color(Color::black);

    auto pkg = save_and_inspect(pres);
    // @prst is required by CT_PresetShadowEffect.
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:prstShdw",
                                           {{"prst", "shdw1"},
                                            {"dist", "63500"},
                                            {"dir", "2700000"}}));
}

TEST_F(EffectsConformance, AReflectionReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_reflection_effect();
    auto* reflection = ef.reflection_effect();
    ASSERT_NE(reflection, nullptr);
    reflection->set_blur_radius(4); // 4 pt -> 50800 EMU
    reflection->set_distance(0);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:reflection",
                                           {{"blurRad", "50800"}}));
}

TEST_F(EffectsConformance, AFillOverlayReachesTheFile) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_fill_overlay_effect();
    auto* overlay = ef.fill_overlay_effect();
    ASSERT_NE(overlay, nullptr);
    overlay->set_blend(FillBlendMode::MULTIPLY);

    auto pkg = save_and_inspect(pres);
    // @blend is required by CT_FillOverlayEffect, and the element also needs
    // exactly one fill child.
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:fillOverlay",
                                           {{"blend", "mult"}}));
}

/// Enabling an effect and writing nothing for it leaves an empty container
/// behind. An empty `<a:effectLst/>` is the signature of exactly that, and it
/// is worth catching on its own: it is a file that opens, validates and does
/// not do what the caller asked.
TEST_F(EffectsConformance, AnEnabledEffectNeverLeavesAnEmptyEffectList) {
    Presentation pres;
    auto& ef = fresh_shape(pres).effect_format();
    ef.enable_inner_shadow_effect();

    auto pkg = save_and_inspect(pres);
    auto node = pkg.xml(kSlide).select_node("//a:effectLst").node();
    ASSERT_TRUE(node) << "no a:effectLst was written at all";
    EXPECT_FALSE(conformance::ChildNames(node).empty())
        << "an effect was enabled and the effect list is empty";
}

/// A deck opened from a file takes the XML-backed path, where every effect
/// setter writes straight into the slide part. `xml_node::attribute(name)`
/// returns a null attribute when the element does not carry `name`, and
/// `set_value` on a null attribute is a silent no-op — so on a freshly enabled
/// effect, whose element has no attributes yet, every setter wrote nothing and
/// reported success.
TEST_F(EffectsConformance, EffectPropertiesSetOnALoadedDeckReachTheFile) {
    Presentation pres;
    fresh_shape(pres);
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto& ef = loaded.slides()[0].shapes()[0].effect_format();
    ef.enable_inner_shadow_effect();
    auto* shadow = ef.inner_shadow_effect();
    ASSERT_NE(shadow, nullptr);
    shadow->set_blur_radius(8);  // 8 pt -> 101600 EMU
    shadow->set_distance(5);     // 5 pt -> 63500 EMU
    shadow->set_direction(45);   // 45 deg -> 2700000

    conformance::Package pkg(save_to(loaded, path_for("shadowed.pptx")));
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:effectLst/a:innerShdw",
        {{"blurRad", "101600"}, {"dist", "63500"}, {"dir", "2700000"}}));
}

/// Every effect element the schema requires a colour child or an attribute on
/// carries it, whichever path created the element.
///
/// `CT_OuterShadowEffect`, `CT_InnerShadowEffect`, `CT_PresetShadowEffect` and
/// `CT_GlowEffect` each declare exactly one `EG_ColorChoice` child and it is
/// not optional; `CT_SoftEdgesEffect` requires `@rad` and
/// `CT_PresetShadowEffect` requires `@prst`. Enabling an effect creates an
/// empty element, so without this every one of them is a file PowerPoint
/// refuses outright.
TEST_F(EffectsConformance, EveryEffectEnabledOnALoadedDeckIsSchemaComplete) {
    Presentation pres;
    fresh_shape(pres);
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto& ef = loaded.slides()[0].shapes()[0].effect_format();
    ef.set_blur_effect(8, true);
    ef.enable_fill_overlay_effect();
    ef.enable_glow_effect();
    ef.enable_inner_shadow_effect();
    ef.enable_outer_shadow_effect();
    ef.enable_preset_shadow_effect();
    ef.enable_reflection_effect();
    ef.enable_soft_edge_effect();

    conformance::Package pkg(save_to(loaded, path_for("all_effects.pptx")));
    for (const char* tag : {"a:glow", "a:innerShdw", "a:outerShdw",
                            "a:prstShdw"}) {
        auto node = pkg.xml(kSlide)
                        .select_node(("//a:effectLst/" + std::string(tag)).c_str())
                        .node();
        ASSERT_TRUE(node) << tag << " was not written at all";
        EXPECT_FALSE(conformance::ChildNames(node).empty())
            << tag << " has no colour child, which its type requires";
    }
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:softEdge",
                                           {{"rad", "0"}}));
    auto prst = pkg.xml(kSlide).select_node("//a:effectLst/a:prstShdw").node();
    ASSERT_TRUE(prst);
    EXPECT_TRUE(prst.attribute("prst")) << "prstShdw has no prst attribute";
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:effectLst/a:fillOverlay",
                                           {{"blend", "over"}}));
}

} // namespace
