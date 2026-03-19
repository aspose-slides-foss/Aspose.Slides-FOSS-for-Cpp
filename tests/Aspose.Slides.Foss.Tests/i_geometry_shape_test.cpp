// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/i_geometry_shape.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;


TEST(IGeometryShapeTest, AddAutoShapePreservesShapeType) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    EXPECT_EQ(slide.shapes().size(), 1u);
    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
}

TEST(IGeometryShapeTest, MultipleShapeTypesPreserved) {
    ShapeType types[] = {ShapeType::RECTANGLE, ShapeType::ELLIPSE, ShapeType::TRIANGLE};
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    for (auto st : types) {
        auto& s = slide.shapes().add_auto_shape(st, 10, 10, 100, 100);
        EXPECT_EQ(s.shape_type(), st);
    }
    EXPECT_EQ(slide.shapes().size(), 3u);
}


TEST(IGeometryShapeTest, ConnectorShapeType) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& conn = slide.shapes().add_connector(
        ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);
    EXPECT_EQ(conn.shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
}

TEST(IGeometryShapeTest, AdjustmentProperties) {
    Presentation pres;
    auto& conn = pres.slides()[0].shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    if (conn.adjustments().size() > 0) {
        auto& adj = conn.adjustments()[0];
        EXPECT_FALSE(adj.name().empty());
        // raw_value is numeric
        adj.set_raw_value(60000);
        EXPECT_EQ(adj.raw_value(), 60000);
        // angle_value is numeric
        EXPECT_DOUBLE_EQ(adj.angle_value(), 1.0);
    }
}

TEST(IGeometryShapeTest, BentConnectorAdjustments) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();

    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    if (conn.adjustments().size() > 0) {
        conn.adjustments()[0].set_raw_value(30000);
        EXPECT_EQ(conn.adjustments()[0].raw_value(), 30000);
    }
}

TEST(IGeometryShapeTest, ConnectShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();

    auto& s1 = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 100, 60);
    auto& s2 = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 350, 200, 100, 60);
    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);

    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);

    EXPECT_NE(conn.start_shape_connected_to(), nullptr);
    EXPECT_NE(conn.end_shape_connected_to(), nullptr);
}

// ---------- IGeometryShape interface tests ----------

TEST(IGeometryShapeTest, ShapeStyleReturnsNull) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    IGeometryShape& geo = shape;
    EXPECT_EQ(geo.shape_style(), nullptr);
}

TEST(IGeometryShapeTest, ShapeTypeViaInterface) {
    AutoShape shape(ShapeType::ELLIPSE, 0, 0, 100, 100);
    IGeometryShape& geo = shape;
    EXPECT_EQ(geo.shape_type(), ShapeType::ELLIPSE);
}

TEST(IGeometryShapeTest, SetShapeTypeViaInterface) {
    AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    IGeometryShape& geo = shape;
    geo.set_shape_type(ShapeType::TRIANGLE);
    EXPECT_EQ(geo.shape_type(), ShapeType::TRIANGLE);
    EXPECT_EQ(shape.shape_type(), ShapeType::TRIANGLE);
}

TEST(IGeometryShapeTest, AdjustmentsViaInterface) {
    Connector conn(ShapeType::BENT_CONNECTOR3, 0, 0, 100, 100);
    IGeometryShape& geo = conn;
    // Adjustments collection is accessible through the interface.
    EXPECT_EQ(geo.adjustments().size(), conn.adjustments().size());
}

TEST(IGeometryShapeTest, ConstShapeStyleReturnsNull) {
    const AutoShape shape(ShapeType::RECTANGLE, 0, 0, 100, 100);
    const IGeometryShape& geo = shape;
    EXPECT_EQ(geo.shape_style(), nullptr);
}
