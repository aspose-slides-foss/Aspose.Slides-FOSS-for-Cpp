// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file text_formatting_test.cpp
/// Integration tests for text formatting: bold, italic, underline, font, colour, alignment.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/font_data.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_alignment.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/text_strikethrough_type.h>
#include <Aspose/Slides/Foss/text_underline_type.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class TextFormattingIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("text_formatting_integration_test_" +
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

    /// Helper: clear slide, add a rectangle with text and return (shape, portion_format).
    std::pair<AutoShape*, PortionFormat*> shaped(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        auto& shape = pres.slides()[0].shapes().add_auto_shape(
            ShapeType::RECTANGLE, 50, 50, 400, 60);
        shape.text_frame()->set_text("Sample");
        auto& fmt = shape.text_frame()->paragraphs()[0].portions()[0].portion_format();
        return {&shape, &fmt};
    }

    /// Get the first portion format from the first shape after reload.
    PortionFormat& reloaded_portion_format(Presentation& pres) {
        auto& shape = dynamic_cast<AutoShape&>(pres.slides()[0].shapes()[0]);
        return shape.text_frame()->paragraphs()[0].portions()[0].portion_format();
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, BoldItalic) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->set_font_bold(NullableBool::TRUE);
    fmt->set_font_italic(NullableBool::TRUE);

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    EXPECT_EQ(fmt2.font_bold(), NullableBool::TRUE);
    EXPECT_EQ(fmt2.font_italic(), NullableBool::TRUE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, Underline) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->set_font_underline(TextUnderlineType::SINGLE);

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    EXPECT_EQ(fmt2.font_underline(), TextUnderlineType::SINGLE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, Strikethrough) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->set_strikethrough_type(TextStrikethroughType::SINGLE);

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    EXPECT_EQ(fmt2.strikethrough_type(), TextStrikethroughType::SINGLE);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, FontSize) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->set_font_height(28);

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    EXPECT_EQ(fmt2.font_height(), 28);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, FontColor) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->fill_format().set_fill_type(FillType::SOLID);
    fmt->fill_format().solid_fill_color().set_color(Color::red);

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    EXPECT_EQ(fmt2.fill_format().fill_type(), FillType::SOLID);
    auto c = fmt2.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), 255);
    EXPECT_EQ(c.g(), 0);
    EXPECT_EQ(c.b(), 0);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, LatinFont) {
    Presentation pres;
    auto [shape, fmt] = shaped(pres);
    fmt->set_latin_font(FontData("Courier New"));

    auto pres2 = save_and_reopen(pres);
    auto& fmt2 = reloaded_portion_format(pres2);
    ASSERT_TRUE(fmt2.latin_font().has_value());
    EXPECT_EQ(fmt2.latin_font()->font_name(), "Courier New");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TextFormattingIntegrationTest, ParagraphAlignment) {
    Presentation pres;
    pres.slides()[0].shapes().clear();
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 400, 200);
    shape.text_frame()->set_text("Centered");
    shape.text_frame()->paragraphs()[0].paragraph_format().set_alignment(
        TextAlignment::CENTER);

    auto pres2 = save_and_reopen(pres);
    auto& reloaded = dynamic_cast<AutoShape&>(pres2.slides()[0].shapes()[0]);
    auto& pf = reloaded.text_frame()->paragraphs()[0].paragraph_format();
    EXPECT_EQ(pf.alignment(), TextAlignment::CENTER);
}

} // namespace
