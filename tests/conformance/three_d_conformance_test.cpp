// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file three_d_conformance_test.cpp
/// The 3-D scene elements, checked against what CT_LightRig and CT_Camera
/// require rather than against what the in-memory objects remember.

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <Aspose/Slides/Foss/light_rig.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/material_preset_type.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/three_d_format.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;

namespace {

class ThreeDConformance : public conformance::SavedDeckTest {
protected:
    AutoShape& fresh_shape(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        return pres.slides()[0].shapes().add_auto_shape(ShapeType::RECTANGLE,
                                                        100, 100, 200, 100);
    }
};

/// `dir` is required on `a:lightRig` by CT_LightRig; the API lets a caller set
/// the rig without a direction, and a lightRig with no `dir` is a file
/// PowerPoint refuses to open.
TEST_F(ThreeDConformance, ALightRigWithNoDirectionSetStillWritesADirection) {
    Presentation pres;
    auto& shape = fresh_shape(pres);
    shape.three_d_format().light_rig().set_light_type(
        LightRigPresetType::THREE_PT);
    // No set_direction call: this is the case the caller is allowed to write
    // and the one that produces an unopenable file.

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:scene3d/a:lightRig",
                                           {{"rig", "threePt"}}));
    auto node = pkg.xml("ppt/slides/slide1.xml")
                    .select_node("//a:scene3d/a:lightRig")
                    .node();
    ASSERT_TRUE(node) << "no a:lightRig was written at all";
    EXPECT_TRUE(node.attribute("dir"))
        << "a:lightRig has no dir attribute, which CT_LightRig requires; "
           "PowerPoint refuses the file";
}

/// An explicit direction is written correctly today. Pinned so the default
/// cannot be introduced by overwriting what the caller asked for.
TEST_F(ThreeDConformance, AnExplicitLightingDirectionIsWrittenAsGiven) {
    Presentation pres;
    auto& shape = fresh_shape(pres);
    auto& rig = shape.three_d_format().light_rig();
    rig.set_light_type(LightRigPresetType::BALANCED);
    rig.set_direction(LightingDirection::TOP);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:scene3d/a:lightRig",
                                           {{"rig", "balanced"}, {"dir", "t"}}));
}

/// `extrusionH` on `a:sp3d` is the extrusion height. The API exposes both a
/// depth and an extrusion height and only depth reaches the file, so a caller
/// who sets the extrusion height gets a shape with none.
TEST_F(ThreeDConformance, TheExtrusionHeightThatWasSetIsTheOneWritten) {
    Presentation pres;
    auto& shape = fresh_shape(pres);
    auto& fmt = shape.three_d_format();
    fmt.set_extrusion_height(20); // 20 pt -> 254000 EMU
    fmt.set_material(MaterialPresetType::METAL);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:sp3d",
                                           {{"extrusionH", "254000"}}));
}

/// Contour width and the two 3-D colours are settable and never serialised.
TEST_F(ThreeDConformance, TheContourWidthThatWasSetReachesTheFile) {
    Presentation pres;
    auto& shape = fresh_shape(pres);
    auto& fmt = shape.three_d_format();
    fmt.set_contour_width(2); // 2 pt -> 25400 EMU
    fmt.set_depth(10);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:sp3d", {{"contourW", "25400"}}));
}

/// Bevel and material are written correctly today; pinned as a regression
/// guard for the rest of the 3-D repair.
TEST_F(ThreeDConformance, TheBevelAndMaterialThatWereSetReachTheFile) {
    Presentation pres;
    auto& shape = fresh_shape(pres);
    auto& fmt = shape.three_d_format();
    fmt.bevel_top().set_bevel_type(BevelPresetType::CIRCLE);
    fmt.bevel_top().set_width(6);
    fmt.bevel_top().set_height(6);
    fmt.set_material(MaterialPresetType::METAL);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, "ppt/slides/slide1.xml", "//a:sp3d/a:bevelT",
        {{"prst", "circle"}, {"w", "76200"}, {"h", "76200"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:sp3d",
                                           {{"prstMaterial", "metal"}}));
}

} // namespace
