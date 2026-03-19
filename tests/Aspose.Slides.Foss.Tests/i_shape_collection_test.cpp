// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/i_shape_collection.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Tests that a connector added to the collection remains accessible.
// ---------------------------------------------------------------------------
TEST(IShapeCollectionTest, AddStraightConnectorPersists) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_connector(ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);

    EXPECT_GE(slide.shapes().size(), 1u);
    bool found = false;
    for (std::size_t i = 0; i < slide.shapes().size(); ++i) {
        if (slide.shapes()[i].shape_type() == ShapeType::STRAIGHT_CONNECTOR1) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

TEST(IShapeCollectionTest, ParentGroupIsNullForSlide) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    EXPECT_EQ(shapes.parent_group(), nullptr);
}

TEST(IShapeCollectionTest, AsICollectionReturnsSelf) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    EXPECT_EQ(&shapes.as_i_collection(), &shapes);
}

TEST(IShapeCollectionTest, AsIEnumerableReturnsSelf) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    EXPECT_EQ(&shapes.as_i_enumerable(), &shapes);
}

TEST(IShapeCollectionTest, ToArray) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    auto& s1 = shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);

    auto arr = shapes.to_array();
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], &s1);
    EXPECT_EQ(arr[1], &s2);
}

TEST(IShapeCollectionTest, ToArrayRange) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    auto& s3 = shapes.add_auto_shape(ShapeType::TRIANGLE, 40, 40, 10, 10);

    auto arr = shapes.to_array(1, 2);
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], &s2);
    EXPECT_EQ(arr[1], &s3);
}

TEST(IShapeCollectionTest, IndexOf) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    auto& s1 = shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);

    EXPECT_EQ(shapes.index_of(s1), 0);
    EXPECT_EQ(shapes.index_of(s2), 1);

    // Shape not in collection returns -1.
    AutoShape detached(ShapeType::RECTANGLE, 0, 0, 1, 1);
    EXPECT_EQ(shapes.index_of(detached), -1);
}

TEST(IShapeCollectionTest, InsertConnector) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    shapes.add_auto_shape(ShapeType::RECTANGLE, 50, 50, 10, 10);

    auto& conn = shapes.insert_connector(1, ShapeType::STRAIGHT_CONNECTOR1,
                                         10, 10, 40, 40);
    EXPECT_EQ(shapes.size(), 3u);
    EXPECT_EQ(shapes[1].shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
    EXPECT_EQ(shapes.index_of(conn), 1);
}

TEST(IShapeCollectionTest, ReorderSingleShape) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    shapes.add_auto_shape(ShapeType::TRIANGLE, 40, 40, 10, 10);

    // Move s2 to the front.
    shapes.reorder(0, s2);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::ELLIPSE);
    EXPECT_EQ(shapes.size(), 3u);
}

TEST(IShapeCollectionTest, ReorderMultipleShapes) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    auto& s3 = shapes.add_auto_shape(ShapeType::TRIANGLE, 40, 40, 10, 10);

    Shape* to_reorder[] = {&s2, &s3};
    shapes.reorder(0, to_reorder);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::ELLIPSE);
    EXPECT_EQ(shapes[1].shape_type(), ShapeType::TRIANGLE);
    EXPECT_EQ(shapes[2].shape_type(), ShapeType::RECTANGLE);
}

TEST(IShapeCollectionTest, RemoveAt) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    shapes.add_auto_shape(ShapeType::TRIANGLE, 40, 40, 10, 10);

    shapes.remove_at(1);
    ASSERT_EQ(shapes.size(), 2u);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(shapes[1].shape_type(), ShapeType::TRIANGLE);
}

TEST(IShapeCollectionTest, RemoveByReference) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s2 = shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    shapes.add_auto_shape(ShapeType::TRIANGLE, 40, 40, 10, 10);

    shapes.remove(s2);
    ASSERT_EQ(shapes.size(), 2u);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(shapes[1].shape_type(), ShapeType::TRIANGLE);
}

TEST(IShapeCollectionTest, Clear) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    shapes.add_auto_shape(ShapeType::ELLIPSE, 20, 20, 10, 10);
    ASSERT_GE(shapes.size(), 2u);

    shapes.clear();
    EXPECT_EQ(shapes.size(), 0u);
}

TEST(IShapeCollectionTest, AddAutoShapeWithTemplate) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    auto& s = shapes.add_auto_shape(ShapeType::RECTANGLE, 10, 10, 100, 50, true);
    EXPECT_EQ(s.shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(shapes.size(), 1u);
}

TEST(IShapeCollectionTest, InsertAutoShapeWithTemplate) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& s = shapes.insert_auto_shape(0, ShapeType::ELLIPSE, 5, 5, 20, 20, false);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::ELLIPSE);
    EXPECT_EQ(shapes.size(), 2u);
    EXPECT_EQ(shapes.index_of(s), 0);
}

TEST(IShapeCollectionTest, AddConnectorWithTemplate) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    auto& c = shapes.add_connector(ShapeType::STRAIGHT_CONNECTOR1, 0, 0, 100, 100, true);
    EXPECT_EQ(c.shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
}

TEST(IShapeCollectionTest, InsertConnectorWithTemplate) {
    Presentation pres;
    auto& shapes = pres.slides()[0].shapes();
    shapes.clear();
    shapes.add_auto_shape(ShapeType::RECTANGLE, 0, 0, 10, 10);
    auto& c = shapes.insert_connector(0, ShapeType::BENT_CONNECTOR3, 0, 0, 50, 50, false);
    EXPECT_EQ(shapes[0].shape_type(), ShapeType::BENT_CONNECTOR3);
    EXPECT_EQ(shapes.index_of(c), 0);
}
