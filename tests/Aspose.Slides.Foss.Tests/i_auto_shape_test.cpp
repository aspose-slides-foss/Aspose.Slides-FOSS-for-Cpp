// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/i_auto_shape.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_frame.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: return a slide with all shapes cleared.
Slide& blank_slide(Presentation& pres) {
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    return slide;
}

} // namespace


// add_text_frame on a shape created without text.
TEST(IAutoShapeTest, AddTextFrame) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100, false);
    shape.add_text_frame("via add_text_frame");
    ASSERT_NE(shape.text_frame(), nullptr);
    EXPECT_EQ(shape.text_frame()->text(), "via add_text_frame");
}

// Overwriting text replaces the previous value.
TEST(IAutoShapeTest, OverwriteText) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 100);
    shape.add_text_frame("First");
    ASSERT_NE(shape.text_frame(), nullptr);
    EXPECT_EQ(shape.text_frame()->text(), "First");

    // Overwrite by adding a new text frame.
    shape.add_text_frame("Second");
    EXPECT_EQ(shape.text_frame()->text(), "Second");
}

// Adding text to an existing text frame appends content.
// Adapted: since TextFrame uses simple string paragraphs,
// we verify text manipulation via set_text after add_text_frame.
TEST(IAutoShapeTest, AddPortion) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 400, 100);
    shape.add_text_frame("Hello ");
    ASSERT_NE(shape.text_frame(), nullptr);

    // Simulate appending text by modifying the text content.
    std::string current = shape.text_frame()->text();
    shape.text_frame()->set_text(current + "World!");
    EXPECT_NE(shape.text_frame()->text().find("World!"), std::string::npos);
}


// Cell text can be set and read back.
TEST(IAutoShapeTest, CellText) {
    Cell cell;
    ASSERT_NE(cell.text_frame(), nullptr);

    cell.text_frame()->set_text("A");
    EXPECT_EQ(cell.text_frame()->text(), "A");

    // Overwrite text in another cell.
    Cell cell2;
    cell2.text_frame()->set_text("B");
    EXPECT_EQ(cell2.text_frame()->text(), "B");

    // Verify first cell is unaffected.
    EXPECT_EQ(cell.text_frame()->text(), "A");
}

// Cell borders can be configured and persist in memory.
TEST(IAutoShapeTest, CellBorders) {
    Cell cell;
    cell.text_frame()->set_text("Bordered");

    auto& fmt = cell.cell_format();
    LineFormat* borders[] = {
        &fmt.border_top(), &fmt.border_bottom(),
        &fmt.border_left(), &fmt.border_right()};

    for (auto* border : borders) {
        border->fill_format().set_fill_type(FillType::SOLID);
        border->fill_format().solid_fill_color().set_color(Drawing::Color::red);
        border->set_width(3);
    }

    // Verify borders persist.
    EXPECT_EQ(fmt.border_top().width(), 3);
    EXPECT_EQ(fmt.border_bottom().width(), 3);
    EXPECT_EQ(fmt.border_left().width(), 3);
    EXPECT_EQ(fmt.border_right().width(), 3);
    EXPECT_EQ(fmt.border_top().fill_format().fill_type(), FillType::SOLID);
}

// Cell fill colour can be set and read back.
TEST(IAutoShapeTest, CellFill) {
    Cell cell;
    cell.text_frame()->set_text("Blue");

    auto& fmt = cell.cell_format();
    fmt.fill_format().set_fill_type(FillType::SOLID);
    fmt.fill_format().solid_fill_color().set_color(Drawing::Color::light_blue);

    EXPECT_EQ(fmt.fill_format().fill_type(), FillType::SOLID);
    EXPECT_EQ(fmt.fill_format().solid_fill_color().color(), Drawing::Color::light_blue);
}

// ---------- IAutoShape interface contract ----------

// Verify AutoShape satisfies IAutoShape interface.
TEST(IAutoShapeTest, InterfaceContract) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    IAutoShape& iface = shape;

    // Initially no text frame.
    EXPECT_EQ(iface.text_frame(), nullptr);
    EXPECT_FALSE(iface.is_text_box());

    // Add text frame through interface.
    auto& tf = iface.add_text_frame("Interface text");
    EXPECT_TRUE(iface.is_text_box());
    EXPECT_EQ(tf.text(), "Interface text");

    // as_i_geometry_shape returns the same object.
    EXPECT_EQ(&iface.as_i_geometry_shape(), &shape);
}
