// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file table_test.cpp
/// Integration tests for Table: create, cell text, merge, borders, style options.

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/column_collection.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/row_collection.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class TableIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("table_integration_test_" +
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

    /// Find the first Table on a slide. Returns nullptr if none.
    Table* find_table(Slide& slide) {
        if (slide.shapes().table_count() == 0) return nullptr;
        return &slide.shapes().table_at(0);
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, CreateTable) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {100, 150, 200};
    std::vector<double> row_heights = {40, 40, 40};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    EXPECT_EQ(table.rows().size(), 3);
    EXPECT_EQ(table.columns().size(), 3);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, CellText) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {100, 100};
    std::vector<double> row_heights = {40, 40};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    table.rows()[0][0].text_frame()->set_text("A");
    table.rows()[0][1].text_frame()->set_text("B");
    table.rows()[1][0].text_frame()->set_text("C");
    table.rows()[1][1].text_frame()->set_text("D");

    auto pres2 = save_and_reopen(pres);
    auto* t2 = find_table(pres2.slides()[0]);
    ASSERT_NE(t2, nullptr);
    EXPECT_EQ(t2->rows()[0][0].text_frame()->text(), "A");
    EXPECT_EQ(t2->rows()[0][1].text_frame()->text(), "B");
    EXPECT_EQ(t2->rows()[1][0].text_frame()->text(), "C");
    EXPECT_EQ(t2->rows()[1][1].text_frame()->text(), "D");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, MergeCells) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {100, 100, 100};
    std::vector<double> row_heights = {40, 40};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    auto& cell1 = table.rows()[0][0];
    auto& cell2 = table.rows()[0][1];
    table.merge_cells(cell1, cell2, false);
    EXPECT_TRUE(cell1.is_merged_cell());
    EXPECT_GE(cell1.col_span(), 2);

    auto pres2 = save_and_reopen(pres);
    auto* t2 = find_table(pres2.slides()[0]);
    ASSERT_NE(t2, nullptr);
    EXPECT_TRUE(t2->rows()[0][0].is_merged_cell());
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, CellBorders) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {150};
    std::vector<double> row_heights = {50};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    auto& cell = table.rows()[0][0];
    cell.text_frame()->set_text("Bordered");
    auto& fmt = cell.cell_format();

    fmt.border_top().fill_format().set_fill_type(FillType::SOLID);
    fmt.border_top().fill_format().solid_fill_color().set_color(Drawing::Color::red);
    fmt.border_top().set_width(3);

    fmt.border_bottom().fill_format().set_fill_type(FillType::SOLID);
    fmt.border_bottom().fill_format().solid_fill_color().set_color(Drawing::Color::red);
    fmt.border_bottom().set_width(3);

    fmt.border_left().fill_format().set_fill_type(FillType::SOLID);
    fmt.border_left().fill_format().solid_fill_color().set_color(Drawing::Color::red);
    fmt.border_left().set_width(3);

    fmt.border_right().fill_format().set_fill_type(FillType::SOLID);
    fmt.border_right().fill_format().solid_fill_color().set_color(Drawing::Color::red);
    fmt.border_right().set_width(3);

    auto pres2 = save_and_reopen(pres);
    auto* t2 = find_table(pres2.slides()[0]);
    ASSERT_NE(t2, nullptr);
    auto& fmt2 = t2->rows()[0][0].cell_format();
    EXPECT_EQ(fmt2.border_top().width(), 3);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, TableStyleOptions) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {120, 120};
    std::vector<double> row_heights = {40, 40, 40};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    table.set_first_row(true);
    table.set_horizontal_banding(true);
    table.set_vertical_banding(false);

    auto pres2 = save_and_reopen(pres);
    auto* t2 = find_table(pres2.slides()[0]);
    ASSERT_NE(t2, nullptr);
    EXPECT_TRUE(t2->first_row());
    EXPECT_TRUE(t2->horizontal_banding());
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, RowHeight) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {200};
    std::vector<double> row_heights = {30, 50, 70};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    EXPECT_EQ(table.rows()[0].height(), 30);
    EXPECT_EQ(table.rows()[1].height(), 50);
    EXPECT_EQ(table.rows()[2].height(), 70);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, ColumnWidth) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {100, 200, 300};
    std::vector<double> row_heights = {40};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    EXPECT_EQ(table.columns()[0].width(), 100);
    EXPECT_EQ(table.columns()[1].width(), 200);
    EXPECT_EQ(table.columns()[2].width(), 300);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(TableIntegrationTest, CellFill) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    std::vector<double> col_widths = {200};
    std::vector<double> row_heights = {60};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    auto& cell = table.rows()[0][0];
    cell.cell_format().fill_format().set_fill_type(FillType::SOLID);
    cell.cell_format().fill_format().solid_fill_color().set_color(Drawing::Color::light_blue);
    cell.text_frame()->set_text("Blue");

    auto pres2 = save_and_reopen(pres);
    auto* t2 = find_table(pres2.slides()[0]);
    ASSERT_NE(t2, nullptr);
    auto& cf2 = t2->rows()[0][0].cell_format();
    EXPECT_EQ(cf2.fill_format().fill_type(), FillType::SOLID);
}

} // namespace
