// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/drawing/rectangle_f.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/shape_frame.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

/// x, y, width, height, rotation are stored and retrievable.
/// Ports: test_shapes.py::test_shape_frame_properties
TEST(IShapeFrameTest, BasicProperties) {
    ShapeFrame frame(200, 200, 300, 250, NullableBool::FALSE, NullableBool::FALSE, 45.0);

    EXPECT_DOUBLE_EQ(frame.x(), 200.0);
    EXPECT_DOUBLE_EQ(frame.y(), 200.0);
    EXPECT_DOUBLE_EQ(frame.width(), 300.0);
    EXPECT_DOUBLE_EQ(frame.height(), 250.0);
    EXPECT_DOUBLE_EQ(frame.rotation(), 45.0);
}

/// center_x and center_y are computed from x, y, width, height.
TEST(IShapeFrameTest, CenterCoordinates) {
    ShapeFrame frame(100, 200, 300, 400);

    EXPECT_DOUBLE_EQ(frame.center_x(), 250.0);  // 100 + 300/2
    EXPECT_DOUBLE_EQ(frame.center_y(), 400.0);  // 200 + 400/2
}

/// flip_h and flip_v return the values provided at construction.
TEST(IShapeFrameTest, FlipProperties) {
    ShapeFrame frame(0, 0, 100, 100, NullableBool::TRUE, NullableBool::FALSE);

    EXPECT_EQ(frame.flip_h(), NullableBool::TRUE);
    EXPECT_EQ(frame.flip_v(), NullableBool::FALSE);
}

/// rectangle() returns x, y, width, height as a RectangleF.
TEST(IShapeFrameTest, Rectangle) {
    ShapeFrame frame(50, 75, 200, 150);
    auto rect = frame.rectangle();

    EXPECT_FLOAT_EQ(rect.x, 50.0f);
    EXPECT_FLOAT_EQ(rect.y, 75.0f);
    EXPECT_FLOAT_EQ(rect.width, 200.0f);
    EXPECT_FLOAT_EQ(rect.height, 150.0f);
}

/// clone_t returns an independent copy through the interface.
TEST(IShapeFrameTest, CloneT) {
    ShapeFrame frame(10, 20, 300, 400, NullableBool::TRUE, NullableBool::TRUE, 90.0);
    auto cloned = frame.clone_t();

    ASSERT_NE(cloned, nullptr);
    EXPECT_DOUBLE_EQ(cloned->x(), 10.0);
    EXPECT_DOUBLE_EQ(cloned->y(), 20.0);
    EXPECT_DOUBLE_EQ(cloned->width(), 300.0);
    EXPECT_DOUBLE_EQ(cloned->height(), 400.0);
    EXPECT_DOUBLE_EQ(cloned->rotation(), 90.0);
    EXPECT_EQ(cloned->flip_h(), NullableBool::TRUE);
    EXPECT_EQ(cloned->flip_v(), NullableBool::TRUE);
}

/// Default-constructed frame has zero values.
TEST(IShapeFrameTest, DefaultValues) {
    ShapeFrame frame;

    EXPECT_DOUBLE_EQ(frame.x(), 0.0);
    EXPECT_DOUBLE_EQ(frame.y(), 0.0);
    EXPECT_DOUBLE_EQ(frame.width(), 0.0);
    EXPECT_DOUBLE_EQ(frame.height(), 0.0);
    EXPECT_DOUBLE_EQ(frame.rotation(), 0.0);
    EXPECT_EQ(frame.flip_h(), NullableBool::FALSE);
    EXPECT_EQ(frame.flip_v(), NullableBool::FALSE);
}

/// Equality comparison works correctly.
TEST(IShapeFrameTest, Equality) {
    ShapeFrame a(10, 20, 30, 40, NullableBool::FALSE, NullableBool::TRUE, 15.0);
    ShapeFrame b(10, 20, 30, 40, NullableBool::FALSE, NullableBool::TRUE, 15.0);
    ShapeFrame c(10, 20, 30, 40, NullableBool::FALSE, NullableBool::FALSE, 15.0);

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

/// Interface pointer provides polymorphic access.
TEST(IShapeFrameTest, PolymorphicAccess) {
    auto frame = std::make_unique<ShapeFrame>(50, 100, 80, 80);
    const IShapeFrame* iface = frame.get();

    EXPECT_DOUBLE_EQ(iface->x(), 50.0);
    EXPECT_DOUBLE_EQ(iface->y(), 100.0);
    EXPECT_DOUBLE_EQ(iface->width(), 80.0);
    EXPECT_DOUBLE_EQ(iface->height(), 80.0);
    EXPECT_DOUBLE_EQ(iface->center_x(), 90.0);
    EXPECT_DOUBLE_EQ(iface->center_y(), 140.0);
}

/// Width or height > 0 indicates a non-degenerate frame.
/// Ports: test_notes_slide.py::test_notes_size (behavioral: size has positive dimensions)
TEST(IShapeFrameTest, PositiveDimensions) {
    ShapeFrame frame(0, 0, 720, 540);

    EXPECT_GT(frame.width(), 0.0);
    EXPECT_GT(frame.height(), 0.0);

    auto rect = frame.rectangle();
    EXPECT_GT(rect.width, 0.0f);
    EXPECT_GT(rect.height, 0.0f);
}
