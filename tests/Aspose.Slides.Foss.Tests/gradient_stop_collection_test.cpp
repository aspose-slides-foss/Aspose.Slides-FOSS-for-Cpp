// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/gradient_stop_collection.h>
#include <Aspose/Slides/Foss/preset_color.h>
#include <Aspose/Slides/Foss/scheme_color.h>

using namespace Aspose::Slides::Foss;

/// Adding gradient stops increases size and stores position/color.
TEST(GradientStopCollectionTest, AddStopsWithColor) {
    GradientStopCollection coll;
    EXPECT_EQ(coll.size(), 0u);

    coll.add(0.0f, Drawing::Color::blue);
    coll.add(1.0f, Drawing::Color::red);

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_FLOAT_EQ(coll[0].position(), 0.0f);
    EXPECT_EQ(coll[0].color().color(), Drawing::Color::blue);
    EXPECT_FLOAT_EQ(coll[1].position(), 1.0f);
    EXPECT_EQ(coll[1].color().color(), Drawing::Color::red);
}

/// Adding a stop with a PresetColor sets the preset.
TEST(GradientStopCollectionTest, AddWithPresetColor) {
    GradientStopCollection coll;
    auto& stop = coll.add(0.5f, PresetColor::CORAL);

    ASSERT_EQ(coll.size(), 1u);
    EXPECT_FLOAT_EQ(stop.position(), 0.5f);
    EXPECT_EQ(stop.color().preset_color(), PresetColor::CORAL);
}

/// Adding a stop with a SchemeColor sets the scheme.
TEST(GradientStopCollectionTest, AddWithSchemeColor) {
    GradientStopCollection coll;
    auto& stop = coll.add(0.25f, SchemeColor::ACCENT1);

    ASSERT_EQ(coll.size(), 1u);
    EXPECT_FLOAT_EQ(stop.position(), 0.25f);
    EXPECT_EQ(stop.color().scheme_color(), SchemeColor::ACCENT1);
}

/// remove_at removes by index.
TEST(GradientStopCollectionTest, RemoveAt) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.add(0.5f, Drawing::Color::green);
    coll.add(1.0f, Drawing::Color::red);
    ASSERT_EQ(coll.size(), 3u);

    coll.remove_at(1);
    ASSERT_EQ(coll.size(), 2u);
    EXPECT_FLOAT_EQ(coll[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(coll[1].position(), 1.0f);
}

/// remove_at with out-of-range index is a no-op.
TEST(GradientStopCollectionTest, RemoveAtOutOfRangeIsNoop) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.remove_at(5);
    EXPECT_EQ(coll.size(), 1u);
}

/// insert places a stop at the requested index.
TEST(GradientStopCollectionTest, InsertAtIndex) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.add(1.0f, Drawing::Color::red);

    coll.insert(1, 0.5f, Drawing::Color::green);

    ASSERT_EQ(coll.size(), 3u);
    EXPECT_FLOAT_EQ(coll[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(coll[1].position(), 0.5f);
    EXPECT_FLOAT_EQ(coll[2].position(), 1.0f);
    EXPECT_EQ(coll[1].color().color(), Drawing::Color::green);
}

/// insert beyond size appends.
TEST(GradientStopCollectionTest, InsertBeyondSizeAppends) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.insert(100, 1.0f, Drawing::Color::red);

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_FLOAT_EQ(coll[1].position(), 1.0f);
}

/// clear removes all stops.
TEST(GradientStopCollectionTest, Clear) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.add(0.5f, Drawing::Color::green);
    coll.add(1.0f, Drawing::Color::red);

    coll.clear();
    EXPECT_EQ(coll.size(), 0u);
}

/// operator[] throws on out-of-range index.
TEST(GradientStopCollectionTest, IndexOutOfRangeThrows) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);

    EXPECT_THROW((void)coll[1], std::out_of_range);
    EXPECT_THROW((void)coll[100], std::out_of_range);
}

/// Range-based for loop iterates all stops.
TEST(GradientStopCollectionTest, Iteration) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.add(0.5f, Drawing::Color::green);
    coll.add(1.0f, Drawing::Color::red);

    std::size_t count = 0;
    for ([[maybe_unused]] const auto& stop : coll) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

/// as_i_collection returns a copy of all stops.
TEST(GradientStopCollectionTest, AsICollection) {
    GradientStopCollection coll;
    coll.add(0.0f, Drawing::Color::blue);
    coll.add(1.0f, Drawing::Color::red);

    auto vec = coll.as_i_collection();
    ASSERT_EQ(vec.size(), 2u);
    EXPECT_FLOAT_EQ(vec[0].position(), 0.0f);
    EXPECT_FLOAT_EQ(vec[1].position(), 1.0f);
}

/// as_i_enumerable returns same data as as_i_collection.
TEST(GradientStopCollectionTest, AsIEnumerable) {
    GradientStopCollection coll;
    coll.add(0.5f, Drawing::Color::green);

    auto vec = coll.as_i_enumerable();
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_FLOAT_EQ(vec[0].position(), 0.5f);
}
