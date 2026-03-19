// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_row.h>
#include <Aspose/Slides/Foss/row.h>
#include <Aspose/Slides/Foss/row_format.h>
#include <Aspose/Slides/Foss/i_cell_collection.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Default construction
// ---------------------------------------------------------------------------

TEST(RowTest, DefaultConstruction) {
    Row row;
    EXPECT_DOUBLE_EQ(row.height(), 0.0);
    EXPECT_DOUBLE_EQ(row.minimal_height(), 0.0);
    EXPECT_EQ(row.size(), 0u);
}

TEST(RowTest, ConstructWithHeight) {
    Row row(50.0);
    EXPECT_DOUBLE_EQ(row.height(), 50.0);
}

// ---------------------------------------------------------------------------
// Height getter/setter
// ---------------------------------------------------------------------------

TEST(RowTest, SetHeight) {
    Row row;
    row.set_height(75.0);
    EXPECT_DOUBLE_EQ(row.height(), 75.0);
}

// ---------------------------------------------------------------------------
// Row heights match constructor arguments
// Ports: test_table.py::test_row_height
// ---------------------------------------------------------------------------

TEST(RowTest, HeightMatchesConstructorArgs) {
    Table table;
    table.rows().add(std::make_unique<Row>(30.0));
    table.rows().add(std::make_unique<Row>(50.0));
    table.rows().add(std::make_unique<Row>(70.0));

    EXPECT_DOUBLE_EQ(table.rows()[0].height(), 30.0);
    EXPECT_DOUBLE_EQ(table.rows()[1].height(), 50.0);
    EXPECT_DOUBLE_EQ(table.rows()[2].height(), 70.0);
}

// ---------------------------------------------------------------------------
// Minimal height getter/setter
// ---------------------------------------------------------------------------

TEST(RowTest, MinimalHeight) {
    Row row;
    row.set_minimal_height(20.0);
    EXPECT_DOUBLE_EQ(row.minimal_height(), 20.0);
}

// ---------------------------------------------------------------------------
// IRow interface
// ---------------------------------------------------------------------------

TEST(RowTest, ImplementsIRow) {
    Row row(42.0);
    IRow& irow = row;
    EXPECT_DOUBLE_EQ(irow.height(), 42.0);
    EXPECT_DOUBLE_EQ(irow.minimal_height(), 0.0);
    irow.set_minimal_height(10.0);
    EXPECT_DOUBLE_EQ(irow.minimal_height(), 10.0);
}

// ---------------------------------------------------------------------------
// row_format
// ---------------------------------------------------------------------------

TEST(RowTest, RowFormatReturnsObject) {
    Row row;
    [[maybe_unused]] auto& fmt = row.row_format();
    // RowFormat is a valid object (no-op stub for now).
}

// ---------------------------------------------------------------------------
// as_i_cell_collection
// ---------------------------------------------------------------------------

TEST(RowTest, AsICellCollection) {
    Row row;
    row.add();
    row.add();
    ICellCollection& cc = row.as_i_cell_collection();
    EXPECT_EQ(cc.size(), 2u);
}

// ---------------------------------------------------------------------------
// as_i_bulk_text_formattable
// ---------------------------------------------------------------------------

TEST(RowTest, AsIBulkTextFormattable) {
    Row row;
    IBulkTextFormattable& btf = row.as_i_bulk_text_formattable();
    // Verify the reference points to the same object.
    EXPECT_EQ(&btf, static_cast<IBulkTextFormattable*>(&row));
}

// ---------------------------------------------------------------------------
// CellCollection inherited behavior — cells in a row
// ---------------------------------------------------------------------------

TEST(RowTest, AddAndAccessCells) {
    Row row(40.0);
    auto& c0 = row.add();
    auto& c1 = row.add();
    c0.text_frame()->set_text("C0");
    c1.text_frame()->set_text("C1");

    EXPECT_EQ(row.size(), 2u);
    EXPECT_EQ(row[0].text_frame()->text(), "C0");
    EXPECT_EQ(row[1].text_frame()->text(), "C1");
}

TEST(RowTest, IndexOutOfRangeThrows) {
    Row row;
    EXPECT_THROW(row[0], std::out_of_range);
}

TEST(RowTest, ClearCells) {
    Row row;
    row.add();
    row.add();
    EXPECT_EQ(row.size(), 2u);
    row.clear();
    EXPECT_EQ(row.size(), 0u);
}

// ---------------------------------------------------------------------------
// Cell borders via CellFormat (behavioral intent from test_cell_borders)
// ---------------------------------------------------------------------------

TEST(RowTest, CellBordersInRow) {
    Row row(50.0);
    auto& cell = row.add();
    cell.text_frame()->set_text("Bordered");

    auto& fmt = cell.cell_format();
    fmt.border_top().set_width(3.0);
    fmt.border_bottom().set_width(3.0);
    fmt.border_left().set_width(3.0);
    fmt.border_right().set_width(3.0);

    EXPECT_DOUBLE_EQ(fmt.border_top().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_bottom().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_left().width(), 3.0);
    EXPECT_DOUBLE_EQ(fmt.border_right().width(), 3.0);
}
