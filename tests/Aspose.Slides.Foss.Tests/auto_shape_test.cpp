// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
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


TEST(ShapeCollectionTest, AddAutoShape) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    EXPECT_EQ(slide.shapes().size(), 1);
    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
}

TEST(ShapeCollectionTest, MultipleShapeTypes) {
    ShapeType types[] = {ShapeType::RECTANGLE, ShapeType::ELLIPSE, ShapeType::TRIANGLE};
    Presentation pres;
    auto& slide = blank_slide(pres);
    for (auto st : types) {
        auto& s = slide.shapes().add_auto_shape(st, 10, 10, 100, 100);
        EXPECT_EQ(s.shape_type(), st);
    }
    EXPECT_EQ(slide.shapes().size(), 3);
}

TEST(ShapeCollectionTest, ReorderShapes) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    auto& ellipse = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 300, 50, 150, 150);
    slide.shapes().reorder(0, ellipse);
    EXPECT_EQ(slide.shapes()[0].shape_type(), ShapeType::ELLIPSE);
}

// Since there is no PPTX serialization yet, we verify that shape properties
// are correctly retained in memory after creation.
TEST(ShapeCollectionTest, ShapePersistsProperties) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);

    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(shape.x(), 50);
    EXPECT_EQ(shape.y(), 50);
    EXPECT_EQ(shape.width(), 200);
    EXPECT_EQ(shape.height(), 100);

    // Verify accessible through the collection.
    EXPECT_EQ(slide.shapes().size(), 1);
    EXPECT_EQ(slide.shapes()[0].shape_type(), ShapeType::RECTANGLE);
}

// ---------- AutoShape-specific tests ----------

TEST(AutoShapeTest, TextFrameInitiallyNull) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    EXPECT_EQ(shape.text_frame(), nullptr);
    EXPECT_FALSE(shape.is_text_box());
}

TEST(AutoShapeTest, AddTextFrame) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    auto& tf = shape.add_text_frame("Hello World");
    EXPECT_TRUE(shape.is_text_box());
    EXPECT_NE(shape.text_frame(), nullptr);
    EXPECT_EQ(tf.text(), "Hello World");
}

TEST(AutoShapeTest, AddTextFrameMultiLine) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    auto& tf = shape.add_text_frame("Line1\nLine2\r\nLine3\rLine4");
    ASSERT_EQ(tf.paragraphs().size(), 4u);
    EXPECT_EQ(tf.paragraphs()[0].text(), "Line1");
    EXPECT_EQ(tf.paragraphs()[1].text(), "Line2");
    EXPECT_EQ(tf.paragraphs()[2].text(), "Line3");
    EXPECT_EQ(tf.paragraphs()[3].text(), "Line4");
}

TEST(AutoShapeTest, AddTextFrameReplacesExisting) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    shape.add_text_frame("First");
    auto& tf = shape.add_text_frame("Second");
    EXPECT_EQ(tf.text(), "Second");
}

TEST(AutoShapeTest, AsIGeometryShape) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    GeometryShape& geo = shape.as_i_geometry_shape();
    EXPECT_EQ(&geo, &shape);
}

TEST(AutoShapeTest, ShapeTypeGetSet) {
    AutoShape shape;
    EXPECT_EQ(shape.shape_type(), ShapeType::NOT_DEFINED);
    shape.set_shape_type(ShapeType::ELLIPSE);
    EXPECT_EQ(shape.shape_type(), ShapeType::ELLIPSE);
}
