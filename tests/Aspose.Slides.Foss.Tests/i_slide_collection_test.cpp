// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// add_empty_slide increases slide count.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, AddEmptySlide) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().size(), 2u);
}

// ---------------------------------------------------------------------------
// add_clone duplicates a slide with its shapes.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, CloneSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    pres.slides().add_clone(slide);
    ASSERT_EQ(pres.slides().size(), 2u);
    EXPECT_GE(pres.slides()[1].shapes().size(), 1u);
}

// ---------------------------------------------------------------------------
// index_of returns the correct position.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, IndexOf) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[0]), 0);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[1]), 1);
}

// ---------------------------------------------------------------------------
// Adding a slide increases slide count to 2.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, SlideCountAfterAdd) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().size(), 2u);
}

// ---------------------------------------------------------------------------
// remove_at removes by index — applied to slides.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, RemoveAt) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    ASSERT_EQ(pres.slides().size(), 2u);
    pres.slides().remove_at(1);
    EXPECT_EQ(pres.slides().size(), 1u);
}

// ---------------------------------------------------------------------------
// Removing an item by index from a collection persists.
// Applied here to SlideCollection::remove_at.
// ---------------------------------------------------------------------------
TEST(ISlideCollectionTest, RemoveAtPersists) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    pres.slides().add_empty_slide(&layout);
    ASSERT_EQ(pres.slides().size(), 3u);

    pres.slides().remove_at(1);
    EXPECT_EQ(pres.slides().size(), 2u);
}

// ---------------------------------------------------------------------------
// Additional tests for full ISlideCollection contract coverage.
// ---------------------------------------------------------------------------

TEST(ISlideCollectionTest, AsICollectionReturnsSelf) {
    Presentation pres;
    EXPECT_EQ(&pres.slides().as_i_collection(), &pres.slides());
}

TEST(ISlideCollectionTest, AsIEnumerableReturnsSelf) {
    Presentation pres;
    EXPECT_EQ(&pres.slides().as_i_enumerable(), &pres.slides());
}

TEST(ISlideCollectionTest, InsertEmptySlide) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    pres.slides().insert_empty_slide(1, &layout);
    EXPECT_EQ(pres.slides().size(), 3u);
}

TEST(ISlideCollectionTest, RemoveByReference) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    ASSERT_EQ(pres.slides().size(), 2u);
    pres.slides().remove(pres.slides()[1]);
    EXPECT_EQ(pres.slides().size(), 1u);
}

TEST(ISlideCollectionTest, ToArray) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);

    auto arr = pres.slides().to_array();
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], &pres.slides()[0]);
    EXPECT_EQ(arr[1], &pres.slides()[1]);
}

TEST(ISlideCollectionTest, ToArrayRange) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    pres.slides().add_empty_slide(&layout);

    auto arr = pres.slides().to_array(1, 2);
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], &pres.slides()[1]);
    EXPECT_EQ(arr[1], &pres.slides()[2]);
}

TEST(ISlideCollectionTest, IndexOfNotFound) {
    Presentation pres;
    Presentation pres2;
    // A slide from another presentation should not be found.
    EXPECT_EQ(pres.slides().index_of(pres2.slides()[0]), -1);
}

TEST(ISlideCollectionTest, InsertClone) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 10, 10, 50, 50);
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);

    pres.slides().insert_clone(1, slide);
    ASSERT_EQ(pres.slides().size(), 3u);
    EXPECT_GE(pres.slides()[1].shapes().size(), 1u);
}
