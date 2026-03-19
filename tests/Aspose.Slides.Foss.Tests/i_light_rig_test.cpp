// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/light_rig.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/three_d_format.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: clear shapes from first slide and return a reference.
Slide& clear_slide(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    return pres.slides()[0];
}

} // namespace

/// Light rig preset and direction persist via shape's ThreeDFormat.
/// Ports: test_threed_format.py::test_light_rig
TEST(ILightRigTest, LightTypeAndDirection) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    auto& lr = shape.three_d_format().light_rig();
    lr.set_light_type(LightRigPresetType::BALANCED);
    lr.set_direction(LightingDirection::TOP);

    EXPECT_EQ(shape.three_d_format().light_rig().light_type(),
              LightRigPresetType::BALANCED);
    EXPECT_EQ(shape.three_d_format().light_rig().direction(),
              LightingDirection::TOP);
}

/// Rotation angles persist after set_rotation / get_rotation.
TEST(ILightRigTest, SetAndGetRotation) {
    LightRig lr;
    lr.set_rotation(30.0f, 60.0f, 90.0f);

    auto rot = lr.get_rotation();
    EXPECT_FLOAT_EQ(rot[0], 30.0f);
    EXPECT_FLOAT_EQ(rot[1], 60.0f);
    EXPECT_FLOAT_EQ(rot[2], 90.0f);
}

/// Default values: NOT_DEFINED type and direction, zero rotation.
TEST(ILightRigTest, Defaults) {
    LightRig lr;

    EXPECT_EQ(lr.light_type(), LightRigPresetType::NOT_DEFINED);
    EXPECT_EQ(lr.direction(), LightingDirection::NOT_DEFINED);

    auto rot = lr.get_rotation();
    EXPECT_FLOAT_EQ(rot[0], 0.0f);
    EXPECT_FLOAT_EQ(rot[1], 0.0f);
    EXPECT_FLOAT_EQ(rot[2], 0.0f);
}

/// Individual rotation accessors match get_rotation output.
TEST(ILightRigTest, RotationAccessors) {
    LightRig lr;
    lr.set_rotation(10.0f, 20.0f, 30.0f);

    EXPECT_FLOAT_EQ(lr.latitude(), 10.0f);
    EXPECT_FLOAT_EQ(lr.longitude(), 20.0f);
    EXPECT_FLOAT_EQ(lr.revolution(), 30.0f);

    auto rot = lr.get_rotation();
    EXPECT_FLOAT_EQ(rot[0], lr.latitude());
    EXPECT_FLOAT_EQ(rot[1], lr.longitude());
    EXPECT_FLOAT_EQ(rot[2], lr.revolution());
}
