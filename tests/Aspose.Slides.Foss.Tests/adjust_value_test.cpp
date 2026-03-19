// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/adjust_value.h>
#include <Aspose/Slides/Foss/adjust_value_collection.h>
#include <Aspose/Slides/Foss/i_adjust_value_collection.h>
#include <Aspose/Slides/Foss/connector.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>

using namespace Aspose::Slides::Foss;

// -- AdjustValue unit tests --

TEST(AdjustValueTest, DefaultConstructedHasEmptyNameAndZeroValue) {
    AdjustValue adj;
    EXPECT_EQ(adj.name(), "");
    EXPECT_EQ(adj.raw_value(), 0);
    EXPECT_DOUBLE_EQ(adj.angle_value(), 0.0);
}

TEST(AdjustValueTest, ConstructWithNameAndRawValue) {
    AdjustValue adj("adj1", 30000);
    EXPECT_EQ(adj.name(), "adj1");
    EXPECT_EQ(adj.raw_value(), 30000);
}

TEST(AdjustValueTest, SetRawValue) {
    AdjustValue adj("adj1", 0);
    adj.set_raw_value(50000);
    EXPECT_EQ(adj.raw_value(), 50000);
}

TEST(AdjustValueTest, AngleValueConversion) {
    AdjustValue adj("adj1", 60000);
    EXPECT_DOUBLE_EQ(adj.angle_value(), 1.0);

    adj.set_raw_value(180000);
    EXPECT_DOUBLE_EQ(adj.angle_value(), 3.0);
}

TEST(AdjustValueTest, SetAngleValue) {
    AdjustValue adj;
    adj.set_angle_value(45.0);
    EXPECT_EQ(adj.raw_value(), 2700000);
    EXPECT_DOUBLE_EQ(adj.angle_value(), 45.0);
}

TEST(AdjustValueTest, AngleValueRounding) {
    AdjustValue adj;
    // 1.5 degrees = 90000 raw units
    adj.set_angle_value(1.5);
    EXPECT_EQ(adj.raw_value(), 90000);

    // Fractional that requires rounding: 0.333... degrees
    adj.set_angle_value(1.0 / 3.0);
    EXPECT_EQ(adj.raw_value(), 20000);
}

// -- AdjustValueCollection tests --

TEST(AdjustValueCollectionTest, EmptyByDefault) {
    AdjustValueCollection coll;
    EXPECT_EQ(coll.size(), 0u);
}

TEST(AdjustValueCollectionTest, AddAndAccess) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("adj1", 10000));
    coll.add(AdjustValue("adj2", 20000));

    EXPECT_EQ(coll.size(), 2u);
    EXPECT_EQ(coll[0].name(), "adj1");
    EXPECT_EQ(coll[0].raw_value(), 10000);
    EXPECT_EQ(coll[1].name(), "adj2");
    EXPECT_EQ(coll[1].raw_value(), 20000);
}

TEST(AdjustValueCollectionTest, MutateViaIndex) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("adj1", 10000));
    coll[0].set_raw_value(30000);
    EXPECT_EQ(coll[0].raw_value(), 30000);
}

TEST(AdjustValueCollectionTest, OutOfRangeThrows) {
    AdjustValueCollection coll;
    EXPECT_THROW((void)coll[0], std::out_of_range);
}

TEST(AdjustValueCollectionTest, Clear) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("adj1", 10000));
    coll.clear();
    EXPECT_EQ(coll.size(), 0u);
}

TEST(AdjustValueCollectionTest, RangeBasedFor) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("a", 1));
    coll.add(AdjustValue("b", 2));

    int sum = 0;
    for (const auto& adj : coll) {
        sum += adj.raw_value();
    }
    EXPECT_EQ(sum, 3);
}

TEST(AdjustValueCollectionTest, ToArrayReturnsSnapshot) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("adj1", 10000));
    coll.add(AdjustValue("adj2", 20000));

    auto arr = coll.to_array();
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0].name(), "adj1");
    EXPECT_EQ(arr[0].raw_value(), 10000);
    EXPECT_EQ(arr[1].name(), "adj2");
    EXPECT_EQ(arr[1].raw_value(), 20000);

    // Modifying snapshot does not affect original
    arr[0].set_raw_value(99999);
    EXPECT_EQ(coll[0].raw_value(), 10000);
}

TEST(AdjustValueCollectionTest, ToArrayEmptyCollection) {
    AdjustValueCollection coll;
    auto arr = coll.to_array();
    EXPECT_TRUE(arr.empty());
}

TEST(AdjustValueCollectionTest, ImplementsInterface) {
    AdjustValueCollection coll;
    coll.add(AdjustValue("adj1", 10000));

    IAdjustValueCollection& iface = coll;
    EXPECT_EQ(iface.size(), 1u);
    EXPECT_EQ(iface[0].name(), "adj1");

    auto arr = iface.to_array();
    ASSERT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0].raw_value(), 10000);
}

// -- Integration: Connector adjustments (ports test_adjustment_properties) --

TEST(ConnectorAdjustmentTest, AdjustmentValuesExposeProperties) {
    ShapeCollection shapes;
    auto& conn = shapes.add_connector(ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    // Simulate what the presentation layer would do: populate adjustments
    conn.adjustments().add(AdjustValue("adj1", 50000));

    ASSERT_GT(conn.adjustments().size(), 0u);

    auto& adj = conn.adjustments()[0];
    EXPECT_FALSE(adj.name().empty());
    EXPECT_EQ(adj.raw_value(), 50000);
    EXPECT_TRUE(adj.angle_value() > 0.0 || adj.angle_value() <= 0.0); // is a number
}

// -- Integration: Connector adjustment persistence (ports test_bent_connector_adjustments) --

TEST(ConnectorAdjustmentTest, RawValuePersistsOnObject) {
    ShapeCollection shapes;
    auto& conn = shapes.add_connector(ShapeType::BENT_CONNECTOR3, 50, 50, 300, 200);

    conn.adjustments().add(AdjustValue("adj1", 0));
    ASSERT_GT(conn.adjustments().size(), 0u);

    conn.adjustments()[0].set_raw_value(30000);
    EXPECT_EQ(conn.adjustments()[0].raw_value(), 30000);

    // Access through the collection again to verify it persisted
    auto& adj = conn.adjustments()[0];
    EXPECT_EQ(adj.raw_value(), 30000);
}
