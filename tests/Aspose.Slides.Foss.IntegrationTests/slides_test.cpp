// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file slides_test.cpp
/// Integration tests for SlideCollection operations and Slide properties.

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
class SlidesIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("slides_integration_test_" +
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

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, AddEmptySlide) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    EXPECT_EQ(pres.slides().size(), 2);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, InsertEmptySlide) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    pres.slides().insert_empty_slide(1, layout);
    EXPECT_EQ(pres.slides().size(), 3);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, RemoveSlideByRef) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    EXPECT_EQ(pres.slides().size(), 2);
    pres.slides().remove(pres.slides()[1]);
    EXPECT_EQ(pres.slides().size(), 1);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, RemoveSlideAt) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    pres.slides().remove_at(1);
    EXPECT_EQ(pres.slides().size(), 1);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, SlideHidden) {
    Presentation pres;
    pres.slides()[0].set_hidden(true);
    EXPECT_TRUE(pres.slides()[0].hidden());

    auto pres2 = save_and_reopen(pres);
    EXPECT_TRUE(pres2.slides()[0].hidden());
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, CloneSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    pres.slides().add_clone(slide);
    EXPECT_EQ(pres.slides().size(), 2);
    EXPECT_GE(pres.slides()[1].shapes().size(), 1);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, SlideLayoutAccess) {
    Presentation pres;
    EXPECT_NE(pres.slides()[0].layout_slide(), nullptr);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, SlideName) {
    Presentation pres;
    pres.slides()[0].set_name("MySlide");
    EXPECT_EQ(pres.slides()[0].name(), "MySlide");

    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.slides()[0].name(), "MySlide");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, IterateSlides) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    std::vector<Slide*> slides;
    for (auto& s : pres.slides()) {
        slides.push_back(s.get());
    }
    EXPECT_EQ(slides.size(), 2);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(SlidesIntegrationTest, IndexOf) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[0]), 0);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[1]), 1);
}

} // namespace
