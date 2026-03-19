// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/presentation.h>

using namespace Aspose::Slides::Foss;

// -- IMasterSlide.layout_slides contract --

TEST(IMasterSlideTest, LayoutSlidesInitiallyEmpty) {
    MasterSlide master;
    EXPECT_EQ(master.layout_slides().size(), 0);
}

TEST(IMasterSlideTest, LayoutSlidesAddAndAccess) {
    MasterSlide master;
    LayoutSlide layout;
    master.layout_slides().add(&layout);
    EXPECT_EQ(master.layout_slides().size(), 1);
    EXPECT_EQ(&master.layout_slides()[0], &layout);
}


TEST(IMasterSlideTest, SlideCountAfterAdd) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().size(), 2);
}


TEST(IMasterSlideTest, AddEmptySlide) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().size(), 2);
}

TEST(IMasterSlideTest, InsertEmptySlide) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    pres.slides().insert_empty_slide(1, &layout);
    EXPECT_EQ(pres.slides().size(), 3);
}

TEST(IMasterSlideTest, RemoveSlideAt) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    pres.slides().remove_at(1);
    EXPECT_EQ(pres.slides().size(), 1);
}

TEST(IMasterSlideTest, IterateSlides) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);

    std::size_t count = 0;
    for ([[maybe_unused]] auto& s : pres.slides()) {
        ++count;
    }
    EXPECT_EQ(count, 2);
}

TEST(IMasterSlideTest, IndexOf) {
    Presentation pres;
    auto& layout = pres.layout_slides()[0];
    pres.slides().add_empty_slide(&layout);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[0]), 0);
    EXPECT_EQ(pres.slides().index_of(pres.slides()[1]), 1);
}
