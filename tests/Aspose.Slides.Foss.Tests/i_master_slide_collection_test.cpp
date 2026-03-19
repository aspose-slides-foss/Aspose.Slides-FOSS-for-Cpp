// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// -- IMasterSlideCollection contract tests --

TEST(IMasterSlideCollectionTest, InitiallyHasOneMaster) {
    Presentation pres;
    EXPECT_EQ(pres.masters().size(), 1);
}

TEST(IMasterSlideCollectionTest, IndexAccess) {
    Presentation pres;
    auto& master = pres.masters()[0];
    // Should not throw — just verify we can access it.
    EXPECT_EQ(master.layout_slides().size(), 0);
}

TEST(IMasterSlideCollectionTest, IndexOutOfRangeThrows) {
    Presentation pres;
    EXPECT_THROW((void)pres.masters()[99], std::out_of_range);
}

TEST(IMasterSlideCollectionTest, AsICollectionReturnsSelf) {
    Presentation pres;
    auto& coll = pres.masters().as_i_collection();
    EXPECT_EQ(&coll, &pres.masters());
}

TEST(IMasterSlideCollectionTest, AsIEnumerableReturnsSelf) {
    Presentation pres;
    auto& en = pres.masters().as_i_enumerable();
    EXPECT_EQ(&en, &pres.masters());
}

TEST(IMasterSlideCollectionTest, AddCloneIncreasesSize) {
    Presentation pres;
    MasterSlide source;
    pres.masters().add_clone(source);
    EXPECT_EQ(pres.masters().size(), 2);
}

TEST(IMasterSlideCollectionTest, AddCloneReturnsNewMaster) {
    Presentation pres;
    MasterSlide source;
    auto& cloned = pres.masters().add_clone(source);
    EXPECT_EQ(&cloned, &pres.masters()[1]);
}


TEST(IMasterSlideCollectionTest, CloneSlideWithShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 100);
    pres.slides().add_clone(slide);
    EXPECT_EQ(pres.slides().size(), 2);
    EXPECT_GE(pres.slides()[1].shapes().size(), 1);
}
