// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/graphical_object.h>
#include <Aspose/Slides/Foss/i_graphical_object_lock.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Concrete subclass for testing the abstract GraphicalObject.
class TestGraphicalObject : public GraphicalObject {
public:
    TestGraphicalObject() = default;

    TestGraphicalObject(ShapeType type, double x, double y, double w, double h)
        : GraphicalObject(type, x, y, w, h) {}

    [[nodiscard]] IGraphicalObjectLock* graphical_object_lock() const override {
        return nullptr;
    }
};

} // namespace

TEST(GraphicalObjectTest, IsAbstract) {
    // GraphicalObject cannot be instantiated directly; we use the test subclass.
    static_assert(!std::is_constructible_v<GraphicalObject>);
}

TEST(GraphicalObjectTest, InheritsShapeProperties) {
    TestGraphicalObject obj(ShapeType::RECTANGLE, 10, 20, 300, 400);
    EXPECT_EQ(obj.shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(obj.x(), 10);
    EXPECT_EQ(obj.y(), 20);
    EXPECT_EQ(obj.width(), 300);
    EXPECT_EQ(obj.height(), 400);
}

TEST(GraphicalObjectTest, ImplementsIGraphicalObject) {
    TestGraphicalObject obj;
    IGraphicalObject* iface = &obj;
    EXPECT_EQ(iface->graphical_object_lock(), nullptr);
}

TEST(GraphicalObjectTest, ImplementsIShape) {
    TestGraphicalObject obj;
    IShape* iface = &obj;
    EXPECT_EQ(iface->shape_type(), ShapeType::NOT_DEFINED);
}

TEST(GraphicalObjectTest, DefaultConstruction) {
    TestGraphicalObject obj;
    EXPECT_EQ(obj.shape_type(), ShapeType::NOT_DEFINED);
    EXPECT_EQ(obj.x(), 0);
    EXPECT_EQ(obj.y(), 0);
    EXPECT_EQ(obj.width(), 0);
    EXPECT_EQ(obj.height(), 0);
    EXPECT_FALSE(obj.hidden());
    EXPECT_TRUE(obj.name().empty());
}
