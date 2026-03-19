// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/row_collection.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/text_frame.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Basic collection operations
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, EmptyByDefault) {
    RowCollection rc;
    EXPECT_EQ(rc.size(), 0u);
}

TEST(RowCollectionTest, AddRow) {
    RowCollection rc;
    auto& row = rc.add(std::make_unique<Row>(50.0));
    EXPECT_EQ(rc.size(), 1u);
    EXPECT_DOUBLE_EQ(row.height(), 50.0);
}

TEST(RowCollectionTest, IndexOperator) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));
    EXPECT_DOUBLE_EQ(rc[0].height(), 50.0);
    EXPECT_DOUBLE_EQ(rc[1].height(), 75.0);
}

TEST(RowCollectionTest, IndexOutOfRangeThrows) {
    RowCollection rc;
    EXPECT_THROW((void)rc[0], std::out_of_range);
}

TEST(RowCollectionTest, ConstIndexOutOfRangeThrows) {
    const RowCollection rc;
    EXPECT_THROW((void)rc[0], std::out_of_range);
}

// ---------------------------------------------------------------------------
// remove_at — ports behavioral intent from:
//   test_comments.py::test_remove_comment (remove_at on collection)
//   test_shapes.py::test_remove_at (remove by index)
//   test_slides.py::test_remove_slide_at (remove_at by index)
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, RemoveAtByIndex) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));
    rc.remove_at(0);
    ASSERT_EQ(rc.size(), 1u);
    EXPECT_DOUBLE_EQ(rc[0].height(), 75.0);
}

TEST(RowCollectionTest, RemoveAtWithFlag) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));
    rc.remove_at(0, false);
    ASSERT_EQ(rc.size(), 1u);
    EXPECT_DOUBLE_EQ(rc[0].height(), 75.0);
}

TEST(RowCollectionTest, RemoveAtOutOfRangeThrows) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    EXPECT_THROW(rc.remove_at(5, false), std::out_of_range);
}

TEST(RowCollectionTest, RemoveAtMiddleElement) {
    // Ports intent from test_remove_comment: add 3, remove middle, verify 2 remain.
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));
    rc.add(std::make_unique<Row>(100.0));
    ASSERT_EQ(rc.size(), 3u);

    rc.remove_at(1);
    ASSERT_EQ(rc.size(), 2u);
    EXPECT_DOUBLE_EQ(rc[0].height(), 50.0);
    EXPECT_DOUBLE_EQ(rc[1].height(), 100.0);
}

// ---------------------------------------------------------------------------
// add_clone — ports behavioral intent from:
//   test_slides.py::test_clone_slide (add_clone duplicates with contents)
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, AddCloneDuplicatesRow) {
    RowCollection rc;
    auto& original = rc.add(std::make_unique<Row>(60.0));
    // Add a cell with text to the original row.
    auto cell = std::make_unique<Cell>();
    cell->text_frame()->set_text("Hello");
    original.add(std::move(cell));

    auto result = rc.add_clone(original, false);
    ASSERT_EQ(rc.size(), 2u);
    ASSERT_EQ(result.size(), 1u);

    // The clone should have the same height.
    EXPECT_DOUBLE_EQ(rc[1].height(), 60.0);
    // The clone should have the same number of cells.
    ASSERT_EQ(rc[1].size(), 1u);
    // The clone's cell text should be copied.
    EXPECT_EQ(rc[1][0].text_frame()->text(), "Hello");
}

TEST(RowCollectionTest, AddCloneReturnsNewRow) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    auto result = rc.add_clone(rc[0], false);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], &rc[1]);
}

TEST(RowCollectionTest, AddCloneIsIndependent) {
    RowCollection rc;
    auto& original = rc.add(std::make_unique<Row>(50.0));
    auto cell = std::make_unique<Cell>();
    cell->text_frame()->set_text("Original");
    original.add(std::move(cell));

    rc.add_clone(original, false);
    // Modify the clone — original should be unaffected.
    rc[1].set_height(999.0);
    rc[1][0].text_frame()->set_text("Modified");

    EXPECT_DOUBLE_EQ(rc[0].height(), 50.0);
    EXPECT_EQ(rc[0][0].text_frame()->text(), "Original");
}

// ---------------------------------------------------------------------------
// insert_clone
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, InsertCloneAtPosition) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(100.0));

    auto result = rc.insert_clone(1, rc[0], false);
    ASSERT_EQ(rc.size(), 3u);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(rc[1].height(), 50.0);
    EXPECT_DOUBLE_EQ(rc[2].height(), 100.0);
}

TEST(RowCollectionTest, InsertCloneAtBeginning) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(75.0));
    rc.insert_clone(0, rc[0], false);
    ASSERT_EQ(rc.size(), 2u);
    EXPECT_DOUBLE_EQ(rc[0].height(), 75.0);
    EXPECT_DOUBLE_EQ(rc[1].height(), 75.0);
}

TEST(RowCollectionTest, InsertCloneAtEnd) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.insert_clone(1, rc[0], false);
    ASSERT_EQ(rc.size(), 2u);
    EXPECT_DOUBLE_EQ(rc[1].height(), 50.0);
}

TEST(RowCollectionTest, InsertCloneOutOfRangeThrows) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    EXPECT_THROW(rc.insert_clone(5, rc[0], false), std::out_of_range);
}

// ---------------------------------------------------------------------------
// as_i_collection / as_i_enumerable
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, AsICollectionReturnsSnapshot) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));

    auto snapshot = rc.as_i_collection();
    ASSERT_EQ(snapshot.size(), 2u);
    EXPECT_EQ(snapshot[0], &rc[0]);
    EXPECT_EQ(snapshot[1], &rc[1]);
}

TEST(RowCollectionTest, AsIEnumerableReturnsSnapshot) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    auto snapshot = rc.as_i_enumerable();
    ASSERT_EQ(snapshot.size(), 1u);
    EXPECT_EQ(snapshot[0], &rc[0]);
}

// ---------------------------------------------------------------------------
// IRowCollection interface
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, ImplementsIRowCollection) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(42.0));
    IRowCollection& irc = rc;
    EXPECT_EQ(irc.size(), 1u);
    EXPECT_DOUBLE_EQ(irc[0].height(), 42.0);
}

// ---------------------------------------------------------------------------
// Iteration
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, RangeBasedForLoop) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(10.0));
    rc.add(std::make_unique<Row>(20.0));
    rc.add(std::make_unique<Row>(30.0));

    double sum = 0;
    for (const auto& row : rc) {
        sum += row->height();
    }
    EXPECT_DOUBLE_EQ(sum, 60.0);
}

// ---------------------------------------------------------------------------
// Clear
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, Clear) {
    RowCollection rc;
    rc.add(std::make_unique<Row>(50.0));
    rc.add(std::make_unique<Row>(75.0));
    rc.clear();
    EXPECT_EQ(rc.size(), 0u);
}

// ---------------------------------------------------------------------------
// Table integration
// ---------------------------------------------------------------------------

TEST(RowCollectionTest, TableRowsAddClone) {
    Table table;
    auto& row = table.rows().add(std::make_unique<Row>(60.0));
    row.add(std::make_unique<Cell>());
    row[0].text_frame()->set_text("Cell0");

    table.rows().add_clone(row, false);
    ASSERT_EQ(table.rows().size(), 2u);
    EXPECT_DOUBLE_EQ(table.rows()[1].height(), 60.0);
    EXPECT_EQ(table.rows()[1][0].text_frame()->text(), "Cell0");
}
