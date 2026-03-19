// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

/// Ports: test_add_straight_connector
TEST(ConnectorTest, AddStraightConnector) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& conn = slide.shapes().add_connector(
        ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);
    EXPECT_EQ(conn.shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
}

/// Ports: test_bent_connector_adjustments
TEST(ConnectorTest, BentConnectorAdjustments) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();

    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    if (conn.adjustments().size() > 0) {
        conn.adjustments()[0].set_raw_value(30000);
        EXPECT_EQ(conn.adjustments()[0].raw_value(), 30000);
    }

    EXPECT_EQ(conn.shape_type(), ShapeType::BENT_CONNECTOR3);
}

/// Ports: test_connect_shapes
TEST(ConnectorTest, ConnectShapes) {
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
    EXPECT_EQ(conn.start_shape_connection_site_index(), 3u);
    EXPECT_EQ(conn.end_shape_connection_site_index(), 1u);
}

/// Ports: test_reroute
TEST(ConnectorTest, Reroute) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    auto& s1 = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 50, 100, 80, 80);
    auto& s2 = slide.shapes().add_auto_shape(
        ShapeType::ELLIPSE, 400, 100, 80, 80);
    auto& conn = slide.shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);

    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3); // right-center
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);   // left-center
    conn.reroute();

    // After reroute the connector should span between the shapes.
    EXPECT_TRUE(conn.width() > 0 || conn.height() > 0);
}

/// Ports: test_adjustment_properties
TEST(ConnectorTest, AdjustmentProperties) {
    Presentation pres;
    auto& conn = pres.slides()[0].shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    if (conn.adjustments().size() > 0) {
        auto& adj = conn.adjustments()[0];
        adj.set_raw_value(60000);
        EXPECT_EQ(adj.raw_value(), 60000);
        EXPECT_DOUBLE_EQ(adj.angle_value(), 1.0);
    }
}

TEST(ConnectorTest, StubProperties) {
    Connector conn(ShapeType::STRAIGHT_CONNECTOR1, 0, 0, 100, 100);
    EXPECT_FALSE(conn.is_text_holder());
    EXPECT_EQ(conn.placeholder(), nullptr);
    EXPECT_EQ(conn.custom_data(), nullptr);
    EXPECT_EQ(conn.shape_style(), nullptr);
    EXPECT_EQ(conn.connector_lock(), nullptr);
    EXPECT_NE(conn.as_i_geometry_shape(), nullptr);
}

/// Ports: test_add_auto_shape (from test_shapes.py)
TEST(ConnectorTest, AddAutoShapePreservesType) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& shape = slide.shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 200, 100);
    EXPECT_EQ(slide.shapes().size(), 1u);
    EXPECT_EQ(shape.shape_type(), ShapeType::RECTANGLE);
}
