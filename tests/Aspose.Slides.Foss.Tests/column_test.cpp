// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/column_format.h>
#include <Aspose/Slides/Foss/i_cell_collection.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Default construction
// ---------------------------------------------------------------------------

TEST(ColumnTest, DefaultConstruction) {
    Column col;
    EXPECT_DOUBLE_EQ(col.width(), 0.0);
    EXPECT_EQ(col.size(), 0u);
}

TEST(ColumnTest, ConstructWithWidth) {
    Column col(150.0);
    EXPECT_DOUBLE_EQ(col.width(), 150.0);
}

// ---------------------------------------------------------------------------
// Width getter/setter
// Ports: test_table.py::test_column_width — column widths match constructor
// ---------------------------------------------------------------------------

TEST(ColumnTest, SetWidth) {
    Column col;
    col.set_width(200.0);
    EXPECT_DOUBLE_EQ(col.width(), 200.0);
}

TEST(ColumnTest, WidthMatchesConstructorArgs) {
    Table table;
    table.columns().add(std::make_unique<Column>(100.0));
    table.columns().add(std::make_unique<Column>(200.0));
    table.columns().add(std::make_unique<Column>(300.0));

    EXPECT_DOUBLE_EQ(table.columns()[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(table.columns()[1].width(), 200.0);
    EXPECT_DOUBLE_EQ(table.columns()[2].width(), 300.0);
}

// ---------------------------------------------------------------------------
// IColumn interface
// ---------------------------------------------------------------------------

TEST(ColumnTest, ImplementsIColumn) {
    Column col(42.0);
    IColumn& icol = col;
    EXPECT_DOUBLE_EQ(icol.width(), 42.0);
    icol.set_width(99.0);
    EXPECT_DOUBLE_EQ(icol.width(), 99.0);
}

// ---------------------------------------------------------------------------
// column_format
// ---------------------------------------------------------------------------

TEST(ColumnTest, ColumnFormatReturnsObject) {
    Column col;
    auto fmt = col.column_format();
    // ColumnFormat is a valid object (no-op stub for now).
    (void)fmt;
}

// ---------------------------------------------------------------------------
// as_i_cell_collection
// ---------------------------------------------------------------------------

TEST(ColumnTest, AsICellCollection) {
    Column col;
    col.add();
    col.add();
    ICellCollection& cc = col.as_i_cell_collection();
    EXPECT_EQ(cc.size(), 2u);
}

// ---------------------------------------------------------------------------
// as_i_bulk_text_formattable
// ---------------------------------------------------------------------------

TEST(ColumnTest, AsIBulkTextFormattable) {
    Column col;
    IBulkTextFormattable& btf = col.as_i_bulk_text_formattable();
    // Verify the reference points to the same object.
    EXPECT_EQ(&btf, static_cast<IBulkTextFormattable*>(&col));
}

// ---------------------------------------------------------------------------
// CellCollection inherited behavior — cells in a column
// ---------------------------------------------------------------------------

TEST(ColumnTest, AddAndAccessCells) {
    Column col(120.0);
    auto& c0 = col.add();
    auto& c1 = col.add();
    c0.text_frame()->set_text("R0");
    c1.text_frame()->set_text("R1");

    EXPECT_EQ(col.size(), 2u);
    EXPECT_EQ(col[0].text_frame()->text(), "R0");
    EXPECT_EQ(col[1].text_frame()->text(), "R1");
}

TEST(ColumnTest, IndexOutOfRangeThrows) {
    Column col;
    EXPECT_THROW(col[0], std::out_of_range);
}

TEST(ColumnTest, ClearCells) {
    Column col;
    col.add();
    col.add();
    EXPECT_EQ(col.size(), 2u);
    col.clear();
    EXPECT_EQ(col.size(), 0u);
}

// ---------------------------------------------------------------------------
// Cell borders via CellFormat (behavioral intent from test_cell_borders)
// ---------------------------------------------------------------------------

TEST(ColumnTest, CellBordersInColumn) {
    Column col(150.0);
    auto& cell = col.add();
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
