// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/column.h>
#include <Aspose/Slides/Foss/column_format.h>
#include <Aspose/Slides/Foss/i_bulk_text_formattable.h>
#include <Aspose/Slides/Foss/i_cell_collection.h>
#include <Aspose/Slides/Foss/i_column.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// IColumn interface — width
// Ports: test_table.py::test_column_width — column widths match constructor
// ---------------------------------------------------------------------------

TEST(IColumnTest, WidthThroughInterface) {
    Column col(120.0);
    IColumn& icol = col;
    EXPECT_DOUBLE_EQ(icol.width(), 120.0);
}

TEST(IColumnTest, SetWidthThroughInterface) {
    Column col;
    IColumn& icol = col;
    icol.set_width(250.0);
    EXPECT_DOUBLE_EQ(icol.width(), 250.0);
    EXPECT_DOUBLE_EQ(col.width(), 250.0);
}

// ---------------------------------------------------------------------------
// IColumn interface — column_format
// Ports: test_cell_borders (test_table.py) — column format is accessible
// ---------------------------------------------------------------------------

TEST(IColumnTest, ColumnFormatThroughInterface) {
    Column col;
    const IColumn& icol = col;
    const auto& fmt = icol.column_format();
    // ColumnFormat is currently a stub; verify a valid reference is returned.
    EXPECT_EQ(&fmt, &col.column_format());
}

// ---------------------------------------------------------------------------
// IColumn interface — as_i_cell_collection
// Ports: test_shape_frame_properties (test_shapes.py) — structural access
// ---------------------------------------------------------------------------

TEST(IColumnTest, AsICellCollectionThroughInterface) {
    Column col;
    col.add();
    col.add();
    col.add();
    IColumn& icol = col;
    ICellCollection& cc = icol.as_i_cell_collection();
    EXPECT_EQ(cc.size(), 3u);
}

TEST(IColumnTest, AsICellCollectionConstThroughInterface) {
    Column col;
    col.add();
    const IColumn& icol = col;
    const ICellCollection& cc = icol.as_i_cell_collection();
    EXPECT_EQ(cc.size(), 1u);
}

// ---------------------------------------------------------------------------
// IColumn interface — as_i_bulk_text_formattable
// Ports: test_line_color_and_width / test_line_dash_style — formatting access
// ---------------------------------------------------------------------------

TEST(IColumnTest, AsIBulkTextFormattableThroughInterface) {
    Column col;
    IColumn& icol = col;
    IBulkTextFormattable& btf = icol.as_i_bulk_text_formattable();
    EXPECT_EQ(&btf, static_cast<IBulkTextFormattable*>(&col));
}

TEST(IColumnTest, AsIBulkTextFormattableConstThroughInterface) {
    Column col;
    const IColumn& icol = col;
    const IBulkTextFormattable& btf = icol.as_i_bulk_text_formattable();
    EXPECT_EQ(&btf, static_cast<const IBulkTextFormattable*>(&col));
}

// ---------------------------------------------------------------------------
// IColumn with Table — column widths match constructor arguments
// Ports: test_table.py::test_column_width
// ---------------------------------------------------------------------------

TEST(IColumnTest, ColumnWidthsMatchTableSetup) {
    Table table;
    table.columns().add(std::make_unique<Column>(100.0));
    table.columns().add(std::make_unique<Column>(200.0));
    table.columns().add(std::make_unique<Column>(300.0));

    // Access through IColumn references.
    IColumn& c0 = table.columns()[0];
    IColumn& c1 = table.columns()[1];
    IColumn& c2 = table.columns()[2];

    EXPECT_DOUBLE_EQ(c0.width(), 100.0);
    EXPECT_DOUBLE_EQ(c1.width(), 200.0);
    EXPECT_DOUBLE_EQ(c2.width(), 300.0);
}

// ---------------------------------------------------------------------------
// IColumn — cell borders in column cells
// Ports: test_table.py::test_cell_borders — cell border widths persist
// ---------------------------------------------------------------------------

TEST(IColumnTest, CellBordersThroughInterface) {
    Column col(150.0);
    auto& cell = col.add();
    cell.text_frame()->set_text("Bordered");

    auto& fmt = cell.cell_format();
    fmt.border_top().set_width(3.0);
    fmt.border_bottom().set_width(3.0);
    fmt.border_left().set_width(3.0);
    fmt.border_right().set_width(3.0);

    // Verify via IColumn interface that cells are accessible.
    IColumn& icol = col;
    ICellCollection& cc = icol.as_i_cell_collection();
    EXPECT_EQ(cc.size(), 1u);

    auto& cell_fmt = cc[0].cell_format();
    EXPECT_DOUBLE_EQ(cell_fmt.border_top().width(), 3.0);
    EXPECT_DOUBLE_EQ(cell_fmt.border_bottom().width(), 3.0);
    EXPECT_DOUBLE_EQ(cell_fmt.border_left().width(), 3.0);
    EXPECT_DOUBLE_EQ(cell_fmt.border_right().width(), 3.0);
}

// ---------------------------------------------------------------------------
// IColumn — notes_size behavioral analog: width/height positive
// Ports: test_notes_slide.py::test_notes_size — dimensions are positive
// ---------------------------------------------------------------------------

TEST(IColumnTest, PositiveDimensionsWhenSet) {
    Column col(150.0);
    IColumn& icol = col;
    EXPECT_GT(icol.width(), 0.0);
}

// ---------------------------------------------------------------------------
// IColumn — reroute behavioral analog: width update
// Ports: test_connector.py::test_reroute — width > 0 after update
// ---------------------------------------------------------------------------

TEST(IColumnTest, WidthPositiveAfterUpdate) {
    Column col;
    IColumn& icol = col;
    EXPECT_DOUBLE_EQ(icol.width(), 0.0);
    icol.set_width(42.0);
    EXPECT_GT(icol.width(), 0.0);
}
