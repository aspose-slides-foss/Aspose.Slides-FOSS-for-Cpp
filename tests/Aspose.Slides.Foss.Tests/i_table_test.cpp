// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <memory>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Helper: build a Table with the given column widths and row heights,
// populating each row with default cells.
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
// test_create_table — row/column counts
// ---------------------------------------------------------------------------

TEST(ITableTest, CreateTableRowColumnCounts) {
    auto table = make_table({100, 150, 200}, {40, 40, 40});
    EXPECT_EQ(table->rows().size(), 3u);
    EXPECT_EQ(table->columns().size(), 3u);
}

// ---------------------------------------------------------------------------
// test_column_width — widths match constructor arguments
// ---------------------------------------------------------------------------

TEST(ITableTest, ColumnWidthMatchesConstructor) {
    auto table = make_table({100, 200, 300}, {40});
    EXPECT_DOUBLE_EQ(table->columns()[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(table->columns()[1].width(), 200.0);
    EXPECT_DOUBLE_EQ(table->columns()[2].width(), 300.0);
}

// ---------------------------------------------------------------------------
// test_cell_text — cell text round-trips through text_frame
// ---------------------------------------------------------------------------

TEST(ITableTest, CellTextRoundTrip) {
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
// test_merge_cells — merged cell has correct col_span and is_merged_cell
// ---------------------------------------------------------------------------

TEST(ITableTest, MergeCellsColSpan) {
    auto table = make_table({100, 100, 100}, {40, 40});
    Cell& cell1 = table->rows()[0][0];
    Cell& cell2 = table->rows()[0][1];
    Cell& result = table->merge_cells(cell1, cell2, false);

    EXPECT_TRUE(result.is_merged_cell());
    EXPECT_GE(result.col_span(), 2);
    // The second cell should be marked as a horizontal merge continuation.
    EXPECT_TRUE(table->rows()[0][1].is_merged_cell());
}

// ---------------------------------------------------------------------------
// test_cell_borders — CellFormat border access
// ---------------------------------------------------------------------------

TEST(ITableTest, CellBordersAccessible) {
    auto table = make_table({150}, {50});
    Cell& cell = table->rows()[0][0];
    auto& fmt = cell.cell_format();
    // Verify border objects are accessible without throwing.
    (void)fmt.border_top();
    (void)fmt.border_bottom();
    (void)fmt.border_left();
    (void)fmt.border_right();
}

// ---------------------------------------------------------------------------
// test_cell_fill — cell fill format accessible
// ---------------------------------------------------------------------------

TEST(ITableTest, CellFillFormatAccessible) {
    auto table = make_table({200}, {60});
    Cell& cell = table->rows()[0][0];
    auto& fmt = cell.cell_format();
    (void)fmt.fill_format();
}

// ---------------------------------------------------------------------------
// Style flag defaults
// ---------------------------------------------------------------------------

TEST(ITableTest, StyleFlagDefaults) {
    Table table;
    EXPECT_FALSE(table.first_row());
    EXPECT_FALSE(table.first_col());
    EXPECT_FALSE(table.last_row());
    EXPECT_FALSE(table.last_col());
    EXPECT_FALSE(table.horizontal_banding());
    EXPECT_FALSE(table.vertical_banding());
    EXPECT_FALSE(table.right_to_left());
    EXPECT_EQ(table.style_preset(), TableStylePreset::NONE);
}

// ---------------------------------------------------------------------------
// Style flags round-trip
// ---------------------------------------------------------------------------

TEST(ITableTest, StyleFlagsRoundTrip) {
    Table table;
    table.set_first_row(true);
    table.set_first_col(true);
    table.set_last_row(true);
    table.set_last_col(true);
    table.set_horizontal_banding(true);
    table.set_vertical_banding(true);
    table.set_right_to_left(true);
    table.set_style_preset(TableStylePreset::MEDIUM_STYLE2_ACCENT1);

    EXPECT_TRUE(table.first_row());
    EXPECT_TRUE(table.first_col());
    EXPECT_TRUE(table.last_row());
    EXPECT_TRUE(table.last_col());
    EXPECT_TRUE(table.horizontal_banding());
    EXPECT_TRUE(table.vertical_banding());
    EXPECT_TRUE(table.right_to_left());
    EXPECT_EQ(table.style_preset(), TableStylePreset::MEDIUM_STYLE2_ACCENT1);
}

// ---------------------------------------------------------------------------
// Interface downcasts
// ---------------------------------------------------------------------------

TEST(ITableTest, AsIGraphicalObject) {
    Table table;
    IGraphicalObject& obj = table.as_i_graphical_object();
    EXPECT_EQ(&obj, static_cast<IGraphicalObject*>(&table));
}

TEST(ITableTest, AsIBulkTextFormattable) {
    Table table;
    IBulkTextFormattable& btf = table.as_i_bulk_text_formattable();
    EXPECT_EQ(&btf, static_cast<IBulkTextFormattable*>(&table));
}

// ---------------------------------------------------------------------------
// Table format access
// ---------------------------------------------------------------------------

TEST(ITableTest, TableFormatAccessible) {
    Table table;
    ITableFormat& fmt = table.table_format();
    (void)fmt.fill_format();
}

// ---------------------------------------------------------------------------
// Row heights match constructor arguments
// ---------------------------------------------------------------------------

TEST(ITableTest, RowHeightsMatchConstructor) {
    auto table = make_table({200}, {30, 50, 70});
    EXPECT_DOUBLE_EQ(table->rows()[0].height(), 30.0);
    EXPECT_DOUBLE_EQ(table->rows()[1].height(), 50.0);
    EXPECT_DOUBLE_EQ(table->rows()[2].height(), 70.0);
}
