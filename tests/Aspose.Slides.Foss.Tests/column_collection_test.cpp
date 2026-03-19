// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/column_collection.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/text_frame.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Basic collection operations
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, EmptyByDefault) {
    ColumnCollection cc;
    EXPECT_EQ(cc.size(), 0u);
}

TEST(ColumnCollectionTest, AddColumn) {
    ColumnCollection cc;
    auto& col = cc.add(std::make_unique<Column>(100.0));
    EXPECT_EQ(cc.size(), 1u);
    EXPECT_DOUBLE_EQ(col.width(), 100.0);
}

TEST(ColumnCollectionTest, IndexOperator) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));
    EXPECT_DOUBLE_EQ(cc[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(cc[1].width(), 200.0);
}

TEST(ColumnCollectionTest, IndexOutOfRangeThrows) {
    ColumnCollection cc;
    EXPECT_THROW(cc[0], std::out_of_range);
}

TEST(ColumnCollectionTest, ConstIndexOutOfRangeThrows) {
    const ColumnCollection cc;
    EXPECT_THROW(cc[0], std::out_of_range);
}

// ---------------------------------------------------------------------------
// remove_at — ports behavioral intent from:
//   test_comments.py::test_remove_comment (remove_at on collection)
//   test_shapes.py::test_remove_at (remove by index)
//   test_slides.py::test_remove_slide_at (remove_at by index)
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, RemoveAtByIndex) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));
    cc.remove_at(0);
    ASSERT_EQ(cc.size(), 1u);
    EXPECT_DOUBLE_EQ(cc[0].width(), 200.0);
}

TEST(ColumnCollectionTest, RemoveAtWithFlag) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));
    cc.remove_at(0, false);
    ASSERT_EQ(cc.size(), 1u);
    EXPECT_DOUBLE_EQ(cc[0].width(), 200.0);
}

TEST(ColumnCollectionTest, RemoveAtOutOfRangeThrows) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    EXPECT_THROW(cc.remove_at(5, false), std::out_of_range);
}

TEST(ColumnCollectionTest, RemoveAtMiddleElement) {
    // Ports intent from test_remove_comment: add 3, remove middle, verify 2 remain.
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));
    cc.add(std::make_unique<Column>(300.0));
    ASSERT_EQ(cc.size(), 3u);

    cc.remove_at(1);
    ASSERT_EQ(cc.size(), 2u);
    EXPECT_DOUBLE_EQ(cc[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(cc[1].width(), 300.0);
}

// ---------------------------------------------------------------------------
// add_clone — ports behavioral intent from:
//   test_slides.py::test_clone_slide (add_clone duplicates with contents)
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, AddCloneDuplicatesColumn) {
    ColumnCollection cc;
    auto& original = cc.add(std::make_unique<Column>(150.0));
    // Add a cell with text to the original column.
    auto cell = std::make_unique<Cell>();
    cell->text_frame()->set_text("Hello");
    original.add(std::move(cell));

    auto result = cc.add_clone(original, false);
    ASSERT_EQ(cc.size(), 2u);
    ASSERT_EQ(result.size(), 1u);

    // The clone should have the same width.
    EXPECT_DOUBLE_EQ(cc[1].width(), 150.0);
    // The clone should have the same number of cells.
    ASSERT_EQ(cc[1].size(), 1u);
    // The clone's cell text should be copied.
    EXPECT_EQ(cc[1][0].text_frame()->text(), "Hello");
}

TEST(ColumnCollectionTest, AddCloneReturnsNewColumn) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    auto result = cc.add_clone(cc[0], false);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], &cc[1]);
}

TEST(ColumnCollectionTest, AddCloneIsIndependent) {
    ColumnCollection cc;
    auto& original = cc.add(std::make_unique<Column>(100.0));
    auto cell = std::make_unique<Cell>();
    cell->text_frame()->set_text("Original");
    original.add(std::move(cell));

    cc.add_clone(original, false);
    // Modify the clone — original should be unaffected.
    cc[1].set_width(999.0);
    cc[1][0].text_frame()->set_text("Modified");

    EXPECT_DOUBLE_EQ(cc[0].width(), 100.0);
    EXPECT_EQ(cc[0][0].text_frame()->text(), "Original");
}

// ---------------------------------------------------------------------------
// insert_clone
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, InsertCloneAtPosition) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(300.0));

    auto result = cc.insert_clone(1, cc[0], false);
    ASSERT_EQ(cc.size(), 3u);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(cc[1].width(), 100.0);
    EXPECT_DOUBLE_EQ(cc[2].width(), 300.0);
}

TEST(ColumnCollectionTest, InsertCloneAtBeginning) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(200.0));
    cc.insert_clone(0, cc[0], false);
    ASSERT_EQ(cc.size(), 2u);
    EXPECT_DOUBLE_EQ(cc[0].width(), 200.0);
    EXPECT_DOUBLE_EQ(cc[1].width(), 200.0);
}

TEST(ColumnCollectionTest, InsertCloneAtEnd) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.insert_clone(1, cc[0], false);
    ASSERT_EQ(cc.size(), 2u);
    EXPECT_DOUBLE_EQ(cc[1].width(), 100.0);
}

TEST(ColumnCollectionTest, InsertCloneOutOfRangeThrows) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    EXPECT_THROW(cc.insert_clone(5, cc[0], false), std::out_of_range);
}

// ---------------------------------------------------------------------------
// as_i_collection / as_i_enumerable
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, AsICollectionReturnsSnapshot) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));

    auto snapshot = cc.as_i_collection();
    ASSERT_EQ(snapshot.size(), 2u);
    EXPECT_EQ(snapshot[0], &cc[0]);
    EXPECT_EQ(snapshot[1], &cc[1]);
}

TEST(ColumnCollectionTest, AsIEnumerableReturnsSnapshot) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    auto snapshot = cc.as_i_enumerable();
    ASSERT_EQ(snapshot.size(), 1u);
    EXPECT_EQ(snapshot[0], &cc[0]);
}

// ---------------------------------------------------------------------------
// IColumnCollection interface
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, ImplementsIColumnCollection) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(42.0));
    IColumnCollection& icc = cc;
    EXPECT_EQ(icc.size(), 1u);
    EXPECT_DOUBLE_EQ(icc[0].width(), 42.0);
}

// ---------------------------------------------------------------------------
// Iteration
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, RangeBasedForLoop) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(10.0));
    cc.add(std::make_unique<Column>(20.0));
    cc.add(std::make_unique<Column>(30.0));

    double sum = 0;
    for (const auto& col : cc) {
        sum += col->width();
    }
    EXPECT_DOUBLE_EQ(sum, 60.0);
}

// ---------------------------------------------------------------------------
// Clear
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, Clear) {
    ColumnCollection cc;
    cc.add(std::make_unique<Column>(100.0));
    cc.add(std::make_unique<Column>(200.0));
    cc.clear();
    EXPECT_EQ(cc.size(), 0u);
}

// ---------------------------------------------------------------------------
// Table integration
// ---------------------------------------------------------------------------

TEST(ColumnCollectionTest, TableColumnsAddClone) {
    Table table;
    auto& col = table.columns().add(std::make_unique<Column>(150.0));
    col.add(std::make_unique<Cell>());
    col[0].text_frame()->set_text("Cell0");

    table.columns().add_clone(col, false);
    ASSERT_EQ(table.columns().size(), 2u);
    EXPECT_DOUBLE_EQ(table.columns()[1].width(), 150.0);
    EXPECT_EQ(table.columns()[1][0].text_frame()->text(), "Cell0");
}
