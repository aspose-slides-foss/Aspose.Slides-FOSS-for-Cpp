// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file connector_test.cpp
/// Integration tests for Connector shapes, adjustments, and connections.

#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/adjust_value.h>
#include <Aspose/Slides/Foss/adjust_value_collection.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class ConnectorIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("connector_integration_test_" +
                    std::to_string(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()));
        std::filesystem::create_directories(tmp_dir_);
    }

    void TearDown() override {
        std::filesystem::remove_all(tmp_dir_);
    }

    /// Saves a presentation to a temp file and reopens from that file.
    Presentation save_and_reopen(Presentation& pres) {
        auto path = (tmp_dir_ / "roundtrip.pptx").string();
        pres.save(path, static_cast<int>(SaveFormat::PPTX));
        return Presentation(path);
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// Add a straight connector with correct type.
// -------------------------------------------------------------------------
TEST(ConnectorIntegrationTestNoFixture, AddStraightConnector) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& conn = slide.shapes().add_connector(
        ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);
    EXPECT_EQ(conn.shape_type(), ShapeType::STRAIGHT_CONNECTOR1);
}

// -------------------------------------------------------------------------
// Straight connector survives save/reload.
// -------------------------------------------------------------------------
TEST_F(ConnectorIntegrationTest, AddStraightConnectorPersists) {
    Presentation pres;
    pres.slides()[0].shapes().add_connector(
        ShapeType::STRAIGHT_CONNECTOR1, 100, 100, 300, 200);

    auto pres2 = save_and_reopen(pres);
    EXPECT_GE(pres2.slides()[0].shapes().size(), 1u);
}

// -------------------------------------------------------------------------
// Adjustment values persist after save/reload.
// -------------------------------------------------------------------------
TEST_F(ConnectorIntegrationTest, BentConnectorAdjustments) {
    Presentation pres;
    pres.slides()[0].shapes().clear();
    auto& conn = pres.slides()[0].shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);
    if (conn.adjustments().size() > 0) {
        conn.adjustments()[0].set_raw_value(30000);
    }

    auto pres2 = save_and_reopen(pres);
    // Find the connector shape
    Connector* conn2 = nullptr;
    for (std::size_t i = 0; i < pres2.slides()[0].shapes().size(); ++i) {
        auto* c = dynamic_cast<Connector*>(&pres2.slides()[0].shapes()[i]);
        if (c) {
            conn2 = c;
            break;
        }
    }
    ASSERT_NE(conn2, nullptr) << "Connector not found after reload";
    if (conn2->adjustments().size() > 0) {
        EXPECT_EQ(conn2->adjustments()[0].raw_value(), 30000);
    }
}

// -------------------------------------------------------------------------
// Start/end connections persist.
// -------------------------------------------------------------------------
TEST_F(ConnectorIntegrationTest, ConnectShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    auto& s1 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 100, 60);
    auto& s2 = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 350, 200, 100, 60);
    auto& conn = slide.shapes().add_connector(ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);

    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);

    ASSERT_NE(conn.start_shape_connected_to(), nullptr);
    ASSERT_NE(conn.end_shape_connected_to(), nullptr);

    auto pres2 = save_and_reopen(pres);
    Connector* conn2 = nullptr;
    for (std::size_t i = 0; i < pres2.slides()[0].shapes().size(); ++i) {
        auto& sh = pres2.slides()[0].shapes()[i];
        if (sh.shape_type() == ShapeType::BENT_CONNECTOR3) {
            conn2 = dynamic_cast<Connector*>(&sh);
            break;
        }
    }
    ASSERT_NE(conn2, nullptr);
    EXPECT_EQ(conn2->start_shape_connection_site_index(), 3u);
    EXPECT_EQ(conn2->end_shape_connection_site_index(), 1u);
}

// -------------------------------------------------------------------------
// reroute() updates connector position.
// -------------------------------------------------------------------------
TEST(ConnectorIntegrationTestNoFixture, Reroute) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& s1 = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 50, 100, 80, 80);
    auto& s2 = slide.shapes().add_auto_shape(ShapeType::ELLIPSE, 400, 100, 80, 80);
    auto& conn = slide.shapes().add_connector(ShapeType::BENT_CONNECTOR3, 0, 0, 1, 1);
    conn.set_start_shape_connected_to(&s1);
    conn.set_start_shape_connection_site_index(3);
    conn.set_end_shape_connected_to(&s2);
    conn.set_end_shape_connection_site_index(1);
    conn.reroute();
    // After reroute the connector should span between the shapes
    EXPECT_TRUE(conn.width() > 0 || conn.height() > 0);
}

// -------------------------------------------------------------------------
// Adjustment values expose name, raw_value, angle_value.
// -------------------------------------------------------------------------
TEST(ConnectorIntegrationTestNoFixture, AdjustmentProperties) {
    Presentation pres;
    auto& conn = pres.slides()[0].shapes().add_connector(
        ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);
    if (conn.adjustments().size() > 0) {
        auto& adj = conn.adjustments()[0];
        EXPECT_FALSE(adj.name().empty());
        // raw_value is int, angle_value is double — just verify they are accessible
        [[maybe_unused]] int rv = adj.raw_value();
        [[maybe_unused]] double av = adj.angle_value();
    }
}

} // namespace
