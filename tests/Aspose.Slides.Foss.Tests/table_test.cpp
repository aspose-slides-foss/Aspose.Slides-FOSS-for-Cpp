// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

// ---------------------------------------------------------------------------
// Helper: build a Table with the given column widths and row heights,
// populating each row with default cells whose indices and table pointer
// are correctly set.
// ---------------------------------------------------------------------------

static std::unique_ptr<Table> make_table(const std::vector<double>& col_widths,
                                         const std::vector<double>& row_heights) {
    auto table = std::make_unique<Table>();
    for (std::size_t ci = 0; ci < col_widths.size(); ++ci) {
        table->columns().add(std::make_unique<Column>(col_widths[ci]));
    }
    for (std::size_t ri = 0; ri < row_heights.size(); ++ri) {
        auto row = std::make_unique<Row>(row_heights[ri]);
        for (std::size_t ci = 0; ci < col_widths.size(); ++ci) {
            auto cell = std::make_unique<Cell>();
            cell->set_first_row_index(static_cast<int>(ri));
            cell->set_first_column_index(static_cast<int>(ci));
            cell->set_table(table.get());
            row->add(std::move(cell));
        }
        table->rows().add(std::move(row));
    }
    return table;
}

// ---------------------------------------------------------------------------
// test_create_table — Create a table and verify row/column counts.
// ---------------------------------------------------------------------------

TEST(TableTest, CreateTableRowColumnCounts) {
    auto table = make_table({100, 150, 200}, {40, 40, 40});
    EXPECT_EQ(table->rows().size(), 3u);
    EXPECT_EQ(table->columns().size(), 3u);
}

// ---------------------------------------------------------------------------
// test_cell_text — Cell text round-trips through text_frame.
// ---------------------------------------------------------------------------

TEST(TableTest, CellTextRoundTrip) {
    auto table = make_table({100, 100}, {40, 40});
    table->rows()[0][0].text_frame()->set_text("A");
    table->rows()[0][1].text_frame()->set_text("B");
    table->rows()[1][0].text_frame()->set_text("C");
    table->rows()[1][1].text_frame()->set_text("D");

    EXPECT_EQ(table->rows()[0][0].text_frame()->text(), "A");
    EXPECT_EQ(table->rows()[0][1].text_frame()->text(), "B");
    EXPECT_EQ(table->rows()[1][0].text_frame()->text(), "C");
    EXPECT_EQ(table->rows()[1][1].text_frame()->text(), "D");
}

// ---------------------------------------------------------------------------
// test_merge_cells — Merged cells have correct col_span and is_merged_cell.
// ---------------------------------------------------------------------------

TEST(TableTest, MergeCellsColSpan) {
    auto table = make_table({100, 100, 100}, {40, 40});
    Cell& cell1 = table->rows()[0][0];
    Cell& cell2 = table->rows()[0][1];
    Cell& result = table->merge_cells(cell1, cell2, false);

    EXPECT_TRUE(result.is_merged_cell());
    EXPECT_GE(result.col_span(), 2);
}

TEST(TableTest, MergeCellsContinuationMarked) {
    auto table = make_table({100, 100, 100}, {40, 40});
    Cell& cell1 = table->rows()[0][0];
    Cell& cell2 = table->rows()[0][1];
    table->merge_cells(cell1, cell2, false);

    // The second cell should be marked as a horizontal merge continuation.
    EXPECT_TRUE(table->rows()[0][1].is_merged_cell());
    EXPECT_TRUE(table->rows()[0][1].h_merge());
}

TEST(TableTest, MergeCellsRectangularRegion) {
    auto table = make_table({100, 100}, {40, 40});
    Cell& top_left = table->rows()[0][0];
    Cell& bot_right = table->rows()[1][1];
    Cell& anchor = table->merge_cells(top_left, bot_right, false);

    EXPECT_EQ(anchor.col_span(), 2);
    EXPECT_EQ(anchor.row_span(), 2);
    EXPECT_TRUE(table->rows()[0][1].h_merge());
    EXPECT_TRUE(table->rows()[1][0].v_merge());
    EXPECT_TRUE(table->rows()[1][1].h_merge());
    EXPECT_TRUE(table->rows()[1][1].v_merge());
}

// ---------------------------------------------------------------------------
// test_cell_borders — Cell border properties persist.
// ---------------------------------------------------------------------------

TEST(TableTest, CellBordersWidthPersist) {
    auto table = make_table({150}, {50});
    Cell& cell = table->rows()[0][0];
    cell.text_frame()->set_text("Bordered");

    auto& fmt = cell.cell_format();
    LineFormat* borders[] = {
        &fmt.border_top(), &fmt.border_bottom(),
        &fmt.border_left(), &fmt.border_right()
    };
    for (auto* border : borders) {
        border->fill_format().set_fill_type(FillType::SOLID);
        border->fill_format().solid_fill_color().set_color(Color::red);
        border->set_width(3.0);
    }

    EXPECT_DOUBLE_EQ(fmt.border_top().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_bottom().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_left().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_right().width(), 3.0);

    // Verify fill type and color on borders.
    EXPECT_EQ(fmt.border_top().fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(fmt.border_top().fill_format().solid_fill_color().color(), Color::red);
}

// ---------------------------------------------------------------------------
// test_column_width — Column widths match constructor arguments.
// ---------------------------------------------------------------------------

TEST(TableTest, ColumnWidthMatchesConstructor) {
    auto table = make_table({100, 200, 300}, {40});
    EXPECT_DOUBLE_EQ(table->columns()[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(table->columns()[1].width(), 200.0);
    EXPECT_DOUBLE_EQ(table->columns()[2].width(), 300.0);
}

// ---------------------------------------------------------------------------
// test_cell_fill — Cell fill colour persists.
// ---------------------------------------------------------------------------

TEST(TableTest, CellFillColorPersists) {
    auto table = make_table({200}, {60});
    Cell& cell = table->rows()[0][0];
    cell.cell_format().fill_format().set_fill_type(FillType::SOLID);
    cell.cell_format().fill_format().solid_fill_color().set_color(Color::light_blue);
    cell.text_frame()->set_text("Blue");

    auto& cf = table->rows()[0][0].cell_format();
    EXPECT_EQ(cf.fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(cf.fill_format().solid_fill_color().color(), Color::light_blue);
}

// ---------------------------------------------------------------------------
// test_table_style_options — Table style flags persist.
// ---------------------------------------------------------------------------

TEST(TableTest, StyleFlagsPersist) {
    auto table = make_table({120, 120}, {40, 40, 40});
    table->set_first_row(true);
    table->set_horizontal_banding(true);
    table->set_vertical_banding(false);

    EXPECT_TRUE(table->first_row());
    EXPECT_TRUE(table->horizontal_banding());
    EXPECT_FALSE(table->vertical_banding());
}

// ---------------------------------------------------------------------------
// test_row_height — Row heights match constructor arguments.
// ---------------------------------------------------------------------------

TEST(TableTest, RowHeightsMatchConstructor) {
    auto table = make_table({200}, {30, 50, 70});
    EXPECT_DOUBLE_EQ(table->rows()[0].height(), 30.0);
    EXPECT_DOUBLE_EQ(table->rows()[1].height(), 50.0);
    EXPECT_DOUBLE_EQ(table->rows()[2].height(), 70.0);
}
