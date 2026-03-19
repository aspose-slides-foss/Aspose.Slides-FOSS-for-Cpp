// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file text_test.cpp
/// Integration tests for TextFrame, Paragraph, and Portion CRUD.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_frame.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class TextIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("text_integration_test_" +
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
TEST_F(TextIntegrationTest, TextFrameText) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("Hello, World!");
    EXPECT_EQ(shape.text_frame()->text(), "Hello, World!");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, OverwriteText) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("First");
    shape.text_frame()->set_text("Second");
    EXPECT_EQ(shape.text_frame()->text(), "Second");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, ParagraphsCount) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("Line");
    EXPECT_GE(shape.text_frame()->paragraphs().size(), 1u);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, ParagraphText) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("Original");
    auto& para = shape.text_frame()->paragraphs()[0];
    EXPECT_EQ(para.text(), "Original");
    para.set_text("Modified");
    EXPECT_EQ(para.text(), "Modified");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, PortionsCount) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("Hello");
    EXPECT_GE(shape.text_frame()->paragraphs()[0].portions().count(), 1u);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, AddPortion) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 400, 100);
    shape.text_frame()->set_text("Hello ");
    Portion new_portion("World!");
    shape.text_frame()->paragraphs()[0].portions().add(std::move(new_portion));
    EXPECT_NE(shape.text_frame()->text().find("World!"), std::string::npos);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, TextPersists) {
    Presentation pres;
    pres.slides()[0].shapes().clear();
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.text_frame()->set_text("Persistent text");

    auto pres2 = save_and_reopen(pres);
    auto& reloaded_shape = dynamic_cast<AutoShape&>(pres2.slides()[0].shapes()[0]);
    EXPECT_EQ(reloaded_shape.text_frame()->text(), "Persistent text");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextIntegrationTest, AddTextFrame) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100, false);
    shape.add_text_frame("via add_text_frame");
    EXPECT_EQ(shape.text_frame()->text(), "via add_text_frame");
}

} // namespace
