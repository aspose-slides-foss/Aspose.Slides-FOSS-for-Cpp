// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file line_format_test.cpp
/// Integration tests for LineFormat: colour, width, dash style.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_dash_style.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class LineFormatIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("line_format_integration_test_" +
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
// after save/reload.
// -------------------------------------------------------------------------
TEST_F(LineFormatIntegrationTest, LineColorAndWidth) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    auto& lf = shape.line_format();
    lf.set_width(5);
    lf.fill_format().set_fill_type(FillType::SOLID);
    lf.fill_format().solid_fill_color().set_color(Color::dark_red);

    auto pres2 = save_and_reopen(pres);
    auto& lf2 = pres2.slides()[0].shapes()[0].line_format();
    EXPECT_EQ(lf2.width(), 5);
    EXPECT_EQ(lf2.fill_format().fill_type(), FillType::SOLID);
    auto c = lf2.fill_format().solid_fill_color().color();
    EXPECT_EQ(c.r(), Color::dark_red.r());
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(LineFormatIntegrationTest, LineDashStyle) {
    Presentation pres;
    auto& slide = clear_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    auto& lf = shape.line_format();
    lf.set_width(3);
    lf.set_dash_style(Aspose::Slides::Foss::LineDashStyle::DASH);
    lf.fill_format().set_fill_type(FillType::SOLID);
    lf.fill_format().solid_fill_color().set_color(Color::black);

    auto pres2 = save_and_reopen(pres);
    auto& lf2 = pres2.slides()[0].shapes()[0].line_format();
    EXPECT_EQ(lf2.dash_style(), Aspose::Slides::Foss::LineDashStyle::DASH);
}

// -------------------------------------------------------------------------
// in-memory.
// -------------------------------------------------------------------------
TEST_F(LineFormatIntegrationTest, MultipleDashStyles) {
    std::vector<Aspose::Slides::Foss::LineDashStyle> styles = {
        Aspose::Slides::Foss::LineDashStyle::SOLID,
        Aspose::Slides::Foss::LineDashStyle::DASH,
        Aspose::Slides::Foss::LineDashStyle::DOT,
        Aspose::Slides::Foss::LineDashStyle::DASH_DOT,
    };
    Presentation pres;
    auto& slide = pres.slides()[0];
    for (auto style : styles) {
        auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 50);
        shape.line_format().set_dash_style(style);
        EXPECT_EQ(shape.line_format().dash_style(), style);
    }
}

} // namespace
