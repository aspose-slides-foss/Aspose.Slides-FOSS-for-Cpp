// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/i_cell.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;

namespace {

// ---------------------------------------------------------------------------
// Concrete ICell implementation for testing the interface contract.
// Wraps Cell and satisfies ICell's pure virtual requirements.
// ---------------------------------------------------------------------------

class TestCell : public ICell {
public:
    // ISlideComponent / IPresentationComponent
    [[nodiscard]] IPresentation* presentation() override {
        return nullptr;
    }
    [[nodiscard]] const IPresentation* presentation() const override {
        return nullptr;
    }

    // ISlideComponent
    [[nodiscard]] IBaseSlide* slide() override { return nullptr; }
    [[nodiscard]] const IBaseSlide* slide() const override { return nullptr; }
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override { return this; }
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override { return this; }

    // ICell
    [[nodiscard]] double offset_x() const override { return cell_.offset_x(); }
    [[nodiscard]] double offset_y() const override { return cell_.offset_y(); }
    [[nodiscard]] int first_row_index() const override { return cell_.first_row_index(); }
    [[nodiscard]] int first_column_index() const override { return cell_.first_column_index(); }
    [[nodiscard]] double width() const override { return cell_.width(); }
    [[nodiscard]] double height() const override { return cell_.height(); }
    [[nodiscard]] double minimal_height() const override { return cell_.minimal_height(); }

    [[nodiscard]] double margin_left() const override { return cell_.margin_left(); }
    void set_margin_left(double v) override { cell_.set_margin_left(v); }
    [[nodiscard]] double margin_right() const override { return cell_.margin_right(); }
    void set_margin_right(double v) override { cell_.set_margin_right(v); }
    [[nodiscard]] double margin_top() const override { return cell_.margin_top(); }
    void set_margin_top(double v) override { cell_.set_margin_top(v); }
    [[nodiscard]] double margin_bottom() const override { return cell_.margin_bottom(); }
    void set_margin_bottom(double v) override { cell_.set_margin_bottom(v); }

    [[nodiscard]] TextVerticalType text_vertical_type() const override { return cell_.text_vertical_type(); }
    void set_text_vertical_type(TextVerticalType v) override { cell_.set_text_vertical_type(v); }
    [[nodiscard]] TextAnchorType text_anchor_type() const override { return cell_.text_anchor_type(); }
    void set_text_anchor_type(TextAnchorType v) override { cell_.set_text_anchor_type(v); }
    [[nodiscard]] bool anchor_center() const override { return cell_.anchor_center(); }
    void set_anchor_center(bool v) override { cell_.set_anchor_center(v); }

    [[nodiscard]] Column* first_column() const override { return cell_.first_column(); }
    [[nodiscard]] Row* first_row() const override { return cell_.first_row(); }
    [[nodiscard]] int col_span() const override { return cell_.col_span(); }
    [[nodiscard]] int row_span() const override { return cell_.row_span(); }
    [[nodiscard]] TextFrame* text_frame() override { return cell_.text_frame(); }
    [[nodiscard]] Table* table() const override { return cell_.table(); }
    [[nodiscard]] bool is_merged_cell() const override { return cell_.is_merged_cell(); }
    [[nodiscard]] CellFormat& cell_format() override { return cell_.cell_format(); }
    [[nodiscard]] ISlideComponent& as_i_slide_component() override { return *this; }

    Cell& inner() { return cell_; }

private:
    Cell cell_;
};

} // namespace

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class ICellTest : public ::testing::Test {
protected:
    TestCell cell;
};

// ---------------------------------------------------------------------------
// Behavioral intent: geometry properties (offset, width, height) are
// accessible through the interface and retain their values.
// ---------------------------------------------------------------------------

TEST_F(ICellTest, ShapeFrameProperties) {
    cell.inner().set_offset_x(200.0);
    cell.inner().set_offset_y(200.0);
    cell.inner().set_width(300.0);
    cell.inner().set_height(250.0);

    ICell& ic = cell;
    EXPECT_DOUBLE_EQ(ic.offset_x(), 200.0);
    EXPECT_DOUBLE_EQ(ic.offset_y(), 200.0);
    EXPECT_DOUBLE_EQ(ic.width(), 300.0);
    EXPECT_DOUBLE_EQ(ic.height(), 250.0);
}

// ---------------------------------------------------------------------------
// Behavioral intent: cell_format() exposes border objects that can be
// accessed through the ICell interface.
// ---------------------------------------------------------------------------

TEST_F(ICellTest, CellBordersAccessible) {
    ICell& ic = cell;
    auto& fmt = ic.cell_format();

    // Verify all four borders are accessible (no crash / well-formed).
    [[maybe_unused]] auto& top = fmt.border_top();
    [[maybe_unused]] auto& bottom = fmt.border_bottom();
    [[maybe_unused]] auto& left = fmt.border_left();
    [[maybe_unused]] auto& right = fmt.border_right();

    // Fill format is also accessible through cell_format.
    [[maybe_unused]] auto& fill = fmt.fill_format();
}

// ---------------------------------------------------------------------------
// Behavioral intent: after setting dimensions, width/height are positive.
// reroute; here we test the analogous ICell contract.)
// ---------------------------------------------------------------------------

TEST_F(ICellTest, PositiveDimensions) {
    cell.inner().set_width(350.0);
    cell.inner().set_height(80.0);

    ICell& ic = cell;
    EXPECT_TRUE(ic.width() > 0 || ic.height() > 0);
}

// ---------------------------------------------------------------------------
// Behavioral intent: size properties have meaningful positive values.
// ---------------------------------------------------------------------------

TEST_F(ICellTest, PositiveMinimalHeight) {
    cell.inner().set_minimal_height(42.0);

    ICell& ic = cell;
    EXPECT_GT(ic.minimal_height(), 0.0);
}

// ---------------------------------------------------------------------------
// Behavioral intent: formatting properties are accessible and retain values.
// Adapted to ICell margins (the closest read/write formatting on ICell).
// ---------------------------------------------------------------------------

TEST_F(ICellTest, MarginValuesRetained) {
    ICell& ic = cell;
    ic.set_margin_left(5.0);
    ic.set_margin_right(10.0);
    ic.set_margin_top(3.0);
    ic.set_margin_bottom(7.0);

    EXPECT_DOUBLE_EQ(ic.margin_left(), 5.0);
    EXPECT_DOUBLE_EQ(ic.margin_right(), 10.0);
    EXPECT_DOUBLE_EQ(ic.margin_top(), 3.0);
    EXPECT_DOUBLE_EQ(ic.margin_bottom(), 7.0);
}

// ---------------------------------------------------------------------------
// Behavioral intent: enum-typed properties retain their values through
// the interface. Adapted to text_vertical_type/text_anchor_type.
// ---------------------------------------------------------------------------

TEST_F(ICellTest, EnumPropertiesRetained) {
    ICell& ic = cell;

    ic.set_text_vertical_type(TextVerticalType::VERTICAL);
    EXPECT_EQ(ic.text_vertical_type(), TextVerticalType::VERTICAL);

    ic.set_text_anchor_type(TextAnchorType::CENTER);
    EXPECT_EQ(ic.text_anchor_type(), TextAnchorType::CENTER);

    ic.set_anchor_center(true);
    EXPECT_TRUE(ic.anchor_center());
}

// ---------------------------------------------------------------------------
// Additional: interface structural tests
// ---------------------------------------------------------------------------

TEST_F(ICellTest, TextFrameNotNull) {
    ICell& ic = cell;
    ASSERT_NE(ic.text_frame(), nullptr);
}

TEST_F(ICellTest, MergeFlagsViaInterface) {
    ICell& ic = cell;
    EXPECT_FALSE(ic.is_merged_cell());

    cell.inner().set_col_span(2);
    EXPECT_TRUE(ic.is_merged_cell());
    EXPECT_EQ(ic.col_span(), 2);
}

TEST_F(ICellTest, SpanViaInterface) {
    cell.inner().set_row_span(3);
    ICell& ic = cell;
    EXPECT_EQ(ic.row_span(), 3);
    EXPECT_TRUE(ic.is_merged_cell());
}

TEST_F(ICellTest, FirstRowAndColumnViaTable) {
    Table table;
    table.rows().add(std::make_unique<Row>(30.0));
    table.rows().add(std::make_unique<Row>(40.0));
    table.columns().add(std::make_unique<Column>(100.0));
    table.columns().add(std::make_unique<Column>(200.0));

    cell.inner().set_table(&table);
    cell.inner().set_first_row_index(1);
    cell.inner().set_first_column_index(1);

    ICell& ic = cell;
    ASSERT_NE(ic.first_row(), nullptr);
    EXPECT_DOUBLE_EQ(ic.first_row()->height(), 40.0);
    ASSERT_NE(ic.first_column(), nullptr);
    EXPECT_DOUBLE_EQ(ic.first_column()->width(), 200.0);
    EXPECT_EQ(ic.table(), &table);
}

TEST_F(ICellTest, AsISlideComponent) {
    ICell& ic = cell;
    ISlideComponent& sc = ic.as_i_slide_component();
    // The returned reference should be the same object.
    EXPECT_EQ(&sc, static_cast<ISlideComponent*>(&cell));
}
