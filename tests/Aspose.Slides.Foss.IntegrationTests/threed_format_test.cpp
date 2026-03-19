// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file threed_format_test.cpp
/// Integration tests for ThreeDFormat: bevel, camera, light rig, depth.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <Aspose/Slides/Foss/camera_preset_type.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/light_rig_preset_type.h>
#include <Aspose/Slides/Foss/lighting_direction.h>
#include <Aspose/Slides/Foss/material_preset_type.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/three_d_format.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class ThreeDFormatIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("threed_format_integration_test_" +
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
        pres.save(path, SaveFormat::PPTX);
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
TEST_F(ThreeDFormatIntegrationTest, BevelTop) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& tdf = shape.three_d_format();
    tdf.bevel_top().set_bevel_type(BevelPresetType::CIRCLE);
    tdf.bevel_top().set_width(10);
    tdf.bevel_top().set_height(5);

    auto pres2 = save_and_reopen(pres);
    auto& bt = pres2.slides()[0].shapes()[0].three_d_format().bevel_top();
    EXPECT_EQ(bt.bevel_type(), BevelPresetType::CIRCLE);
    EXPECT_EQ(bt.width(), 10);
    EXPECT_EQ(bt.height(), 5);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ThreeDFormatIntegrationTest, Camera) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    shape.three_d_format().camera().set_camera_type(CameraPresetType::PERSPECTIVE_ABOVE);

    auto pres2 = save_and_reopen(pres);
    auto& cam = pres2.slides()[0].shapes()[0].three_d_format().camera();
    EXPECT_EQ(cam.camera_type(), CameraPresetType::PERSPECTIVE_ABOVE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ThreeDFormatIntegrationTest, LightRig) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& lr = shape.three_d_format().light_rig();
    lr.set_light_type(LightRigPresetType::BALANCED);
    lr.set_direction(LightingDirection::TOP);

    auto pres2 = save_and_reopen(pres);
    auto& lr2 = pres2.slides()[0].shapes()[0].three_d_format().light_rig();
    EXPECT_EQ(lr2.light_type(), LightRigPresetType::BALANCED);
    EXPECT_EQ(lr2.direction(), LightingDirection::TOP);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ThreeDFormatIntegrationTest, DepthAndMaterial) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 100, 100, 200, 100);
    auto& tdf = shape.three_d_format();
    tdf.set_depth(20);
    tdf.set_material(MaterialPresetType::METAL);

    auto pres2 = save_and_reopen(pres);
    auto& tdf2 = pres2.slides()[0].shapes()[0].three_d_format();
    EXPECT_EQ(tdf2.depth(), 20);
    EXPECT_EQ(tdf2.material(), MaterialPresetType::METAL);
}

} // namespace
