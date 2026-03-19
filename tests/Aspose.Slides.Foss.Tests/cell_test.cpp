// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Default construction
// ---------------------------------------------------------------------------

TEST(CellTest, DefaultConstruction) {
    Cell cell;
    EXPECT_EQ(cell.offset_x(), 0.0);
    EXPECT_EQ(cell.offset_y(), 0.0);
    EXPECT_EQ(cell.width(), 0.0);
    EXPECT_EQ(cell.height(), 0.0);
    EXPECT_EQ(cell.minimal_height(), 0.0);
    EXPECT_EQ(cell.first_row_index(), 0);
    EXPECT_EQ(cell.first_column_index(), 0);
    EXPECT_EQ(cell.col_span(), 1);
    EXPECT_EQ(cell.row_span(), 1);
    EXPECT_FALSE(cell.h_merge());
    EXPECT_FALSE(cell.v_merge());
    EXPECT_FALSE(cell.is_merged_cell());
    EXPECT_FALSE(cell.anchor_center());
    EXPECT_EQ(cell.text_vertical_type(), TextVerticalType::NOT_DEFINED);
    EXPECT_EQ(cell.text_anchor_type(), TextAnchorType::NOT_DEFINED);
    EXPECT_NE(cell.text_frame(), nullptr);
    EXPECT_EQ(cell.table(), nullptr);
    EXPECT_EQ(cell.slide(), nullptr);
    EXPECT_EQ(cell.presentation(), nullptr);
}

// ---------------------------------------------------------------------------
// 45720 / EMU_PER_POINT for T/B).
// ---------------------------------------------------------------------------

TEST(CellTest, DefaultMargins) {
    Cell cell;
    constexpr double expected_lr = 91440.0 / 12700.0;
    constexpr double expected_tb = 45720.0 / 12700.0;
    EXPECT_DOUBLE_EQ(cell.margin_left(), expected_lr);
    EXPECT_DOUBLE_EQ(cell.margin_right(), expected_lr);
    EXPECT_DOUBLE_EQ(cell.margin_top(), expected_tb);
    EXPECT_DOUBLE_EQ(cell.margin_bottom(), expected_tb);
}

// ---------------------------------------------------------------------------
// Margin setters
// ---------------------------------------------------------------------------

TEST(CellTest, SetMargins) {
    Cell cell;
    cell.set_margin_left(1.5);
    cell.set_margin_right(2.5);
    cell.set_margin_top(3.5);
    cell.set_margin_bottom(4.5);
    EXPECT_DOUBLE_EQ(cell.margin_left(), 1.5);
    EXPECT_DOUBLE_EQ(cell.margin_right(), 2.5);
    EXPECT_DOUBLE_EQ(cell.margin_top(), 3.5);
    EXPECT_DOUBLE_EQ(cell.margin_bottom(), 4.5);
}

// ---------------------------------------------------------------------------
// Offset, width, height setters
// ---------------------------------------------------------------------------

TEST(CellTest, OffsetAndDimensions) {
    Cell cell;
    cell.set_offset_x(10.0);
    cell.set_offset_y(20.0);
    cell.set_width(100.0);
    cell.set_height(50.0);
    cell.set_minimal_height(30.0);

    EXPECT_DOUBLE_EQ(cell.offset_x(), 10.0);
    EXPECT_DOUBLE_EQ(cell.offset_y(), 20.0);
    EXPECT_DOUBLE_EQ(cell.width(), 100.0);
    EXPECT_DOUBLE_EQ(cell.height(), 50.0);
    EXPECT_DOUBLE_EQ(cell.minimal_height(), 30.0);
}

// ---------------------------------------------------------------------------
// Row/column indices
// ---------------------------------------------------------------------------

TEST(CellTest, RowAndColumnIndices) {
    Cell cell;
    cell.set_first_row_index(2);
    cell.set_first_column_index(3);
    EXPECT_EQ(cell.first_row_index(), 2);
    EXPECT_EQ(cell.first_column_index(), 3);
}

// ---------------------------------------------------------------------------
// Span properties
// ---------------------------------------------------------------------------

TEST(CellTest, ColSpan) {
    Cell cell;
    EXPECT_EQ(cell.col_span(), 1);
    cell.set_col_span(3);
    EXPECT_EQ(cell.col_span(), 3);
}

TEST(CellTest, RowSpan) {
    Cell cell;
    EXPECT_EQ(cell.row_span(), 1);
    cell.set_row_span(2);
    EXPECT_EQ(cell.row_span(), 2);
}

// ---------------------------------------------------------------------------
// is_merged_cell — spanning
// ---------------------------------------------------------------------------

TEST(CellTest, IsMergedCellColSpan) {
    Cell cell;
    EXPECT_FALSE(cell.is_merged_cell());
    cell.set_col_span(2);
    EXPECT_TRUE(cell.is_merged_cell());
}

TEST(CellTest, IsMergedCellRowSpan) {
    Cell cell;
    cell.set_row_span(3);
    EXPECT_TRUE(cell.is_merged_cell());
}

// ---------------------------------------------------------------------------
// is_merged_cell — hMerge / vMerge flags
// ---------------------------------------------------------------------------

TEST(CellTest, IsMergedCellHMerge) {
    Cell cell;
    cell.set_h_merge(true);
    EXPECT_TRUE(cell.is_merged_cell());
}

TEST(CellTest, IsMergedCellVMerge) {
    Cell cell;
    cell.set_v_merge(true);
    EXPECT_TRUE(cell.is_merged_cell());
}

// ---------------------------------------------------------------------------
// Text vertical type
// ---------------------------------------------------------------------------

TEST(CellTest, TextVerticalType) {
    Cell cell;
    EXPECT_EQ(cell.text_vertical_type(), TextVerticalType::NOT_DEFINED);
    cell.set_text_vertical_type(TextVerticalType::VERTICAL);
    EXPECT_EQ(cell.text_vertical_type(), TextVerticalType::VERTICAL);
    cell.set_text_vertical_type(TextVerticalType::VERTICAL270);
    EXPECT_EQ(cell.text_vertical_type(), TextVerticalType::VERTICAL270);
}

// ---------------------------------------------------------------------------
// Text anchor type
// ---------------------------------------------------------------------------

TEST(CellTest, TextAnchorType) {
    Cell cell;
    EXPECT_EQ(cell.text_anchor_type(), TextAnchorType::NOT_DEFINED);
    cell.set_text_anchor_type(TextAnchorType::CENTER);
    EXPECT_EQ(cell.text_anchor_type(), TextAnchorType::CENTER);
    cell.set_text_anchor_type(TextAnchorType::BOTTOM);
    EXPECT_EQ(cell.text_anchor_type(), TextAnchorType::BOTTOM);
}

// ---------------------------------------------------------------------------
// Anchor center
// ---------------------------------------------------------------------------

TEST(CellTest, AnchorCenter) {
    Cell cell;
    EXPECT_FALSE(cell.anchor_center());
    cell.set_anchor_center(true);
    EXPECT_TRUE(cell.anchor_center());
    cell.set_anchor_center(false);
    EXPECT_FALSE(cell.anchor_center());
}

// ---------------------------------------------------------------------------
// Text frame
// ---------------------------------------------------------------------------

TEST(CellTest, TextFrameNotNull) {
    Cell cell;
    ASSERT_NE(cell.text_frame(), nullptr);
}

// ---------------------------------------------------------------------------
// Cell format
// ---------------------------------------------------------------------------

TEST(CellTest, CellFormatAccessible) {
    Cell cell;
    // Should be able to access cell_format and its sub-objects.
    auto& cf = cell.cell_format();
    (void)cf.fill_format();
    (void)cf.border_left();
    (void)cf.border_top();
    (void)cf.border_right();
    (void)cf.border_bottom();
}

// ---------------------------------------------------------------------------
// Table back-reference
// ---------------------------------------------------------------------------

TEST(CellTest, TableBackReference) {
    Cell cell;
    EXPECT_EQ(cell.table(), nullptr);

    Table table;
    cell.set_table(&table);
    EXPECT_EQ(cell.table(), &table);
}

// ---------------------------------------------------------------------------
// Slide back-reference
// ---------------------------------------------------------------------------

TEST(CellTest, SlideBackReference) {
    Cell cell;
    EXPECT_EQ(cell.slide(), nullptr);
    // We just verify the setter/getter round-trips; we don't create a real Slide.
}

// ---------------------------------------------------------------------------
// first_row / first_column via table
// ---------------------------------------------------------------------------

TEST(CellTest, FirstRowFromTable) {
    Table table;
    auto row0 = std::make_unique<Row>(30.0);
    auto row1 = std::make_unique<Row>(40.0);
    Row* row1_ptr = row1.get();
    table.rows().add(std::move(row0));
    table.rows().add(std::move(row1));

    Cell cell;
    cell.set_table(&table);
    cell.set_first_row_index(1);
    ASSERT_NE(cell.first_row(), nullptr);
    EXPECT_EQ(cell.first_row(), row1_ptr);
    EXPECT_DOUBLE_EQ(cell.first_row()->height(), 40.0);
}

TEST(CellTest, FirstColumnFromTable) {
    Table table;
    auto col0 = std::make_unique<Column>(100.0);
    auto col1 = std::make_unique<Column>(200.0);
    Column* col1_ptr = col1.get();
    table.columns().add(std::move(col0));
    table.columns().add(std::move(col1));

    Cell cell;
    cell.set_table(&table);
    cell.set_first_column_index(1);
    ASSERT_NE(cell.first_column(), nullptr);
    EXPECT_EQ(cell.first_column(), col1_ptr);
    EXPECT_DOUBLE_EQ(cell.first_column()->width(), 200.0);
}

TEST(CellTest, FirstRowNullWithoutTable) {
    Cell cell;
    cell.set_first_row_index(0);
    EXPECT_EQ(cell.first_row(), nullptr);
}

TEST(CellTest, FirstColumnNullWithoutTable) {
    Cell cell;
    cell.set_first_column_index(0);
    EXPECT_EQ(cell.first_column(), nullptr);
}

TEST(CellTest, FirstRowOutOfBounds) {
    Table table;
    table.rows().add(std::make_unique<Row>(10.0));

    Cell cell;
    cell.set_table(&table);
    cell.set_first_row_index(5);
    EXPECT_EQ(cell.first_row(), nullptr);
}

TEST(CellTest, FirstColumnOutOfBounds) {
    Table table;
    table.columns().add(std::make_unique<Column>(50.0));

    Cell cell;
    cell.set_table(&table);
    cell.set_first_column_index(5);
    EXPECT_EQ(cell.first_column(), nullptr);
}

// ---------------------------------------------------------------------------
// EMU constant
// ---------------------------------------------------------------------------

TEST(CellTest, EmuPerPointConstant) {
    EXPECT_DOUBLE_EQ(kEmuPerPoint, 12700.0);
}
