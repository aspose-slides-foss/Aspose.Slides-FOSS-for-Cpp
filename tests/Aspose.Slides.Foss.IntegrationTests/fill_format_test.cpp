// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file fill_format_test.cpp
/// Integration tests for FillFormat: solid, gradient, pattern, picture, no-fill.

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_format.h>
#include <Aspose/Slides/Foss/gradient_shape.h>
#include <Aspose/Slides/Foss/pattern_format.h>
#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/picture_fill_format.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Generate minimal bytes with PNG signature for image content type detection.
std::vector<uint8_t> create_test_png(uint8_t /*r*/ = 255,
                                     uint8_t /*g*/ = 0,
                                     uint8_t /*b*/ = 0) {
    // Minimal bytes: PNG signature + partial IHDR (enough for detection + dimensions).
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  // PNG signature
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,  // IHDR chunk (len=13)
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,  // width=1, height=1
        0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,  // 8-bit RGB, CRC start
        0xDE,                                              // CRC end
    };
}

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class FillFormatIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("fill_format_integration_test_" +
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

    Slide& clear_slide(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        return pres.slides()[0];
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(FillFormatIntegrationTest, SolidFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    shape.fill_format().set_fill_type(FillType::SOLID);
    shape.fill_format().solid_fill_color().set_color(
        Color::from_argb(255, 0, 128, 255));

    auto pres2 = save_and_reopen(pres);
    auto& ff = pres2.slides()[0].shapes()[0].fill_format();
    EXPECT_EQ(ff.fill_type(), FillType::SOLID);
    auto c = ff.solid_fill_color().color();
    EXPECT_EQ(c.r(), 0);
    EXPECT_EQ(c.g(), 128);
    EXPECT_EQ(c.b(), 255);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(FillFormatIntegrationTest, GradientFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 300, 150);
    shape.fill_format().set_fill_type(FillType::GRADIENT);
    auto& gf = shape.fill_format().gradient_format();
    gf.set_gradient_shape(GradientShape::LINEAR);
    gf.set_linear_gradient_angle(45);
    gf.gradient_stops().add(0.0f, Color::blue);
    gf.gradient_stops().add(1.0f, Color::red);

    auto pres2 = save_and_reopen(pres);
    auto& ff2 = pres2.slides()[0].shapes()[0].fill_format();
    EXPECT_EQ(ff2.fill_type(), FillType::GRADIENT);
    EXPECT_GE(ff2.gradient_format().gradient_stops().size(), 2u);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(FillFormatIntegrationTest, PatternFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    shape.fill_format().set_fill_type(FillType::PATTERN);
    auto& pf = shape.fill_format().pattern_format();
    pf.set_pattern_style(PatternStyle::PERCENT50);
    pf.fore_color().set_color(Color::dark_blue);
    pf.back_color().set_color(Color::light_yellow);

    auto pres2 = save_and_reopen(pres);
    auto& ff2 = pres2.slides()[0].shapes()[0].fill_format();
    EXPECT_EQ(ff2.fill_type(), FillType::PATTERN);
    EXPECT_EQ(ff2.pattern_format().pattern_style(), PatternStyle::PERCENT50);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(FillFormatIntegrationTest, NoFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    shape.fill_format().set_fill_type(FillType::NO_FILL);

    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.slides()[0].shapes()[0].fill_format().fill_type(), FillType::NO_FILL);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(FillFormatIntegrationTest, PictureFill) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 200);
    shape.fill_format().set_fill_type(FillType::PICTURE);
    auto& pff = shape.fill_format().picture_fill_format();
    pff.set_picture_fill_mode(PictureFillMode::STRETCH);
    auto png = create_test_png(0, 255, 0);
    auto& img = pres.images().add_image(
        std::span<const uint8_t>(png.data(), png.size()));
    pff.picture().set_image(&img);

    auto pres2 = save_and_reopen(pres);
    auto& ff2 = pres2.slides()[0].shapes()[0].fill_format();
    EXPECT_EQ(ff2.fill_type(), FillType::PICTURE);
}

} // namespace
