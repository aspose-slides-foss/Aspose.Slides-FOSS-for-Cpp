// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// -- MasterSlideCollection unit tests --

TEST(MasterSlideCollectionTest, InitiallyHasOneMaster) {
    Presentation pres;
    EXPECT_EQ(pres.masters().size(), 1);
}

TEST(MasterSlideCollectionTest, AsICollectionReturnsSelf) {
    Presentation pres;
    EXPECT_EQ(&pres.masters().as_i_collection(), &pres.masters());
}

TEST(MasterSlideCollectionTest, AsIEnumerableReturnsSelf) {
    Presentation pres;
    EXPECT_EQ(&pres.masters().as_i_enumerable(), &pres.masters());
}

TEST(MasterSlideCollectionTest, IndexOutOfRangeThrows) {
    Presentation pres;
    EXPECT_THROW((void)pres.masters()[99], std::out_of_range);
}

TEST(MasterSlideCollectionTest, AddCloneIncreasesSize) {
    Presentation pres;
    auto& source = pres.masters()[0];
    pres.masters().add_clone(source);
    EXPECT_EQ(pres.masters().size(), 2);
}

TEST(MasterSlideCollectionTest, AddCloneReturnsNewMaster) {
    Presentation pres;
    auto& source = pres.masters()[0];
    auto& cloned = pres.masters().add_clone(source);
    EXPECT_EQ(&cloned, &pres.masters()[1]);
}

TEST(MasterSlideCollectionTest, AddCloneCopiesShapes) {
    Presentation pres;
    auto& source = pres.masters()[0];
    source.shapes().add_auto_shape(ShapeType::RECTANGLE, 10, 20, 100, 50);
    source.shapes().add_auto_shape(ShapeType::ELLIPSE, 30, 40, 80, 60);

    auto& cloned = pres.masters().add_clone(source);
    EXPECT_EQ(cloned.shapes().size(), 2);
    EXPECT_EQ(cloned.shapes()[0].shape_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(cloned.shapes()[1].shape_type(), ShapeType::ELLIPSE);
}

TEST(MasterSlideCollectionTest, AddCloneCopiesLayoutSlides) {
    Presentation pres;
    auto& source = pres.masters()[0];

    // Add a layout to the source master via the global collection.
    auto layout = std::make_unique<LayoutSlide>();
    layout->set_layout_type(SlideLayoutType::TITLE);
    layout->set_master_slide(&source);
    auto& layout_ref = pres.layout_slides().add(std::move(layout));
    source.layout_slides().add(&layout_ref);

    ASSERT_EQ(source.layout_slides().size(), 1);

    auto& cloned = pres.masters().add_clone(source);
    EXPECT_EQ(cloned.layout_slides().size(), 1);
    EXPECT_EQ(cloned.layout_slides()[0].layout_type(), SlideLayoutType::TITLE);
    // Cloned layout should point to the new master, not the source.
    EXPECT_EQ(cloned.layout_slides()[0].master_slide(), &cloned);
}

TEST(MasterSlideCollectionTest, IterableWithRangeFor) {
    Presentation pres;
    pres.masters().add_clone(pres.masters()[0]);
    std::size_t count = 0;
    for ([[maybe_unused]] auto& m : pres.masters()) {
        ++count;
    }
    EXPECT_EQ(count, 2);
}

// Tests that add_clone on SlideCollection duplicates a slide with its shapes.

TEST(MasterSlideCollectionTest, CloneSlideWithShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    pres.slides().add_clone(slide);
    EXPECT_EQ(pres.slides().size(), 2);
    EXPECT_GE(pres.slides()[1].shapes().size(), 1);
}
