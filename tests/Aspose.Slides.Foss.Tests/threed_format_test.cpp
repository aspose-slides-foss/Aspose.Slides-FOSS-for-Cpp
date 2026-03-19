// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_bevel.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/material_preset_type.h>
#include <Aspose/Slides/Foss/three_d_format.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: clear shapes from first slide and return a reference.
Slide& clear_slide(Presentation& pres) {
    pres.slides()[0].shapes().clear();
    return pres.slides()[0];
}

} // namespace

/// Light rig preset and direction persist in memory.
/// Ports: test_light_rig
TEST(ThreeDFormatTest, LightRig) {
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

/// Bevel top type, width, and height persist in memory.
/// Ports: test_threed_format.py::test_bevel_top
TEST(ThreeDFormatTest, BevelTop) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    auto& bt = shape.three_d_format().bevel_top();
    bt.set_bevel_type(BevelPresetType::CIRCLE);
    bt.set_width(10.0);
    bt.set_height(5.0);

    // Verify values persist on the same object.
    EXPECT_EQ(shape.three_d_format().bevel_top().bevel_type(),
              BevelPresetType::CIRCLE);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_top().width(), 10.0);
    EXPECT_DOUBLE_EQ(shape.three_d_format().bevel_top().height(), 5.0);
}

/// Camera preset type persists in memory.
/// Ports: test_threed_format.py::test_camera
TEST(ThreeDFormatTest, Camera) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    shape.three_d_format().camera().set_camera_type(
        CameraPresetType::PERSPECTIVE_ABOVE);

    EXPECT_EQ(shape.three_d_format().camera().camera_type(),
              CameraPresetType::PERSPECTIVE_ABOVE);
}

/// Camera field of view angle persists.
TEST(ThreeDFormatTest, CameraFieldOfView) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    shape.three_d_format().camera().set_field_of_view_angle(45.0f);

    EXPECT_FLOAT_EQ(shape.three_d_format().camera().field_of_view_angle(),
                    45.0f);
}

/// Camera zoom persists.
TEST(ThreeDFormatTest, CameraZoom) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    // Default zoom is 100%.
    EXPECT_FLOAT_EQ(shape.three_d_format().camera().zoom(), 100.0f);

    shape.three_d_format().camera().set_zoom(150.0f);
    EXPECT_FLOAT_EQ(shape.three_d_format().camera().zoom(), 150.0f);
}

/// Camera rotation (set/get) persists.
TEST(ThreeDFormatTest, CameraRotation) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    shape.three_d_format().camera().set_rotation(30.0f, 60.0f, 90.0f);

    auto rot = shape.three_d_format().camera().get_rotation();
    EXPECT_FLOAT_EQ(rot[0], 30.0f);
    EXPECT_FLOAT_EQ(rot[1], 60.0f);
    EXPECT_FLOAT_EQ(rot[2], 90.0f);
}

/// Camera defaults: NOT_DEFINED type, 0 FOV, 100 zoom, zero rotation.
TEST(ThreeDFormatTest, CameraDefaults) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    const auto& cam = shape.three_d_format().camera();
    EXPECT_EQ(cam.camera_type(), CameraPresetType::NOT_DEFINED);
    EXPECT_FLOAT_EQ(cam.field_of_view_angle(), 0.0f);
    EXPECT_FLOAT_EQ(cam.zoom(), 100.0f);

    auto rot = cam.get_rotation();
    EXPECT_FLOAT_EQ(rot[0], 0.0f);
    EXPECT_FLOAT_EQ(rot[1], 0.0f);
    EXPECT_FLOAT_EQ(rot[2], 0.0f);
}

/// Extrusion depth and material persist in memory.
/// Ports: test_threed_format.py::test_depth_and_material
TEST(ThreeDFormatTest, DepthAndMaterial) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 100, 100, 200, 100);

    auto& tdf = shape.three_d_format();
    tdf.set_depth(20.0);
    tdf.set_material(MaterialPresetType::METAL);

    EXPECT_DOUBLE_EQ(shape.three_d_format().depth(), 20.0);
    EXPECT_EQ(shape.three_d_format().material(), MaterialPresetType::METAL);
}
