// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file shapes_test.cpp
/// Integration tests for ShapeCollection operations and shape frame properties.

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class ShapesIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("shapes_integration_test_" +
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

    Slide& blank_slide(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        return pres.slides()[0];
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, AddAutoShape) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    EXPECT_EQ(slide.shapes().size(), 1);
    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, MultipleShapeTypes) {
    std::vector<ShapeType> types = {ShapeType::RECTANGLE, ShapeType::ELLIPSE, ShapeType::TRIANGLE};
    Presentation pres;
    auto& slide = blank_slide(pres);
    for (auto st : types) {
        auto& s = slide.shapes().add_auto_shape(st, 10, 10, 100, 100);
        EXPECT_EQ(s.shape_type(), st);
    }
    EXPECT_EQ(slide.shapes().size(), 3);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, InsertAutoShape) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    slide.shapes().insert_auto_shape(1, ShapeType::TRIANGLE, 150, 200, 100, 100);
    EXPECT_EQ(slide.shapes().size(), 3);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, RemoveShape) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& s = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    EXPECT_EQ(slide.shapes().size(), 2);
    slide.shapes().remove(s);
    EXPECT_EQ(slide.shapes().size(), 1);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, RemoveAt) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    slide.shapes().remove_at(0);
    EXPECT_EQ(slide.shapes().size(), 1);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, ClearShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    slide.shapes().clear();
    EXPECT_EQ(slide.shapes().size(), 0);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, ShapeFrameProperties) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 200, 200, 300, 250);
    shape.set_rotation(45);

    auto pres2 = save_and_reopen(pres);
    auto& s2 = pres2.slides()[0].shapes()[0];
    EXPECT_EQ(s2.x(), 200);
    EXPECT_EQ(s2.y(), 200);
    EXPECT_EQ(s2.width(), 300);
    EXPECT_EQ(s2.height(), 250);
    EXPECT_EQ(s2.rotation(), 45);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, ReorderShapes) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    auto& ellipse = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    slide.shapes().reorder(0, ellipse);
    EXPECT_EQ(slide.shapes()[0].shape_type(), ShapeType::ELLIPSE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, IterateShapes) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    std::vector<Shape*> shapes;
    for (auto& s : slide.shapes()) {
        shapes.push_back(&*s);
    }
    EXPECT_EQ(shapes.size(), 2);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(ShapesIntegrationTest, ShapePersistsAfterReload) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    auto pres2 = save_and_reopen(pres);
    EXPECT_GE(pres2.slides()[0].shapes().size(), 1);
    EXPECT_EQ(pres2.slides()[0].shapes()[0].shape_type(), ShapeType::RECTANGLE);
}

} // namespace
