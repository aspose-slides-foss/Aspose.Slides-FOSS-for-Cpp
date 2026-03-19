// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/effects/soft_edge.h>
#include <Aspose/Slides/Foss/effects/i_soft_edge.h>
#include <Aspose/Slides/Foss/effects/i_image_transform_operation.h>
#include <Aspose/Slides/Foss/effect_format.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Effects;

// ---------------------------------------------------------------------------
// SoftEdge: default state
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, DefaultValues) {
    SoftEdge se;
    EXPECT_EQ(se.radius(), 0.0);
}

// ---------------------------------------------------------------------------
// SoftEdge: radius read/write
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, RadiusReadWrite) {
    SoftEdge se;
    se.set_radius(10.0);
    EXPECT_EQ(se.radius(), 10.0);

    se.set_radius(0.0);
    EXPECT_EQ(se.radius(), 0.0);
}

// ---------------------------------------------------------------------------
// SoftEdge: as_i_image_transform_operation returns self
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, AsIImageTransformOperation) {
    SoftEdge se;
    auto& op = se.as_i_image_transform_operation();
    EXPECT_EQ(&op, static_cast<IImageTransformOperation*>(&se));
}

// ---------------------------------------------------------------------------
// SoftEdge: ISoftEdge interface polymorphism
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, ISoftEdgeInterface) {
    SoftEdge se;
    ISoftEdge& ise = se;
    ise.set_radius(15.5);
    EXPECT_EQ(ise.radius(), 15.5);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, EnableSoftEdgeViaEffectFormat) {
    EffectFormat ef;
    EXPECT_EQ(ef.soft_edge_effect(), nullptr);

    ef.enable_soft_edge_effect();
    auto* se = ef.soft_edge_effect();
    ASSERT_NE(se, nullptr);
    se->set_radius(10.0);
    EXPECT_EQ(se->radius(), 10.0);
}

// ---------------------------------------------------------------------------
// SoftEdge: disable removes soft edge effect
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, DisableSoftEdgeEffect) {
    EffectFormat ef;
    ef.enable_soft_edge_effect();
    ef.soft_edge_effect()->set_radius(10.0);
    EXPECT_FALSE(ef.is_no_effects());

    ef.disable_soft_edge_effect();
    EXPECT_EQ(ef.soft_edge_effect(), nullptr);
    EXPECT_TRUE(ef.is_no_effects());
}

// ---------------------------------------------------------------------------
// SoftEdge: enable is idempotent (does not reset existing effect)
// ---------------------------------------------------------------------------
TEST(SoftEdgeTest, EnableIdempotent) {
    EffectFormat ef;
    ef.enable_soft_edge_effect();
    ef.soft_edge_effect()->set_radius(12.0);

    ef.enable_soft_edge_effect();
    EXPECT_EQ(ef.soft_edge_effect()->radius(), 12.0);
}
