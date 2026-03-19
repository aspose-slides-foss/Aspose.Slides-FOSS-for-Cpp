// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/layout_slide_collection.h>
#include <Aspose/Slides/Foss/slide_layout_type.h>

#include <memory>
#include <stdexcept>

using namespace Aspose::Slides::Foss;

TEST(ILayoutSlideCollectionTest, EmptyCollectionHasSizeZero) {
    LayoutSlideCollection coll;
    EXPECT_EQ(coll.size(), 0u);
}

TEST(ILayoutSlideCollectionTest, SizeIncreasesAfterAdd) {
    LayoutSlideCollection coll;
    auto slide = std::make_unique<LayoutSlide>();
    coll.add(std::move(slide));
    EXPECT_EQ(coll.size(), 1u);
}

TEST(ILayoutSlideCollectionTest, OperatorBracketReturnsCorrectSlide) {
    LayoutSlideCollection coll;
    auto slide = std::make_unique<LayoutSlide>();
    slide->set_layout_type(SlideLayoutType::TITLE);
    coll.add(std::move(slide));

    ILayoutSlideCollection& iface = coll;
    EXPECT_EQ(iface[0].layout_type(), SlideLayoutType::TITLE);
}

TEST(ILayoutSlideCollectionTest, OperatorBracketThrowsOnOutOfRange) {
    LayoutSlideCollection coll;
    ILayoutSlideCollection& iface = coll;
    EXPECT_THROW((void)iface[0], std::out_of_range);
}

TEST(ILayoutSlideCollectionTest, ConstOperatorBracketWorks) {
    LayoutSlideCollection coll;
    auto slide = std::make_unique<LayoutSlide>();
    slide->set_layout_type(SlideLayoutType::BLANK);
    coll.add(std::move(slide));

    const ILayoutSlideCollection& iface = coll;
    EXPECT_EQ(iface[0].layout_type(), SlideLayoutType::BLANK);
}

TEST(ILayoutSlideCollectionTest, AsICollectionReturnsAllSlides) {
    LayoutSlideCollection coll;
    auto s1 = std::make_unique<LayoutSlide>();
    auto s2 = std::make_unique<LayoutSlide>();
    auto* p1 = s1.get();
    auto* p2 = s2.get();
    coll.add(std::move(s1));
    coll.add(std::move(s2));

    auto vec = coll.as_i_collection();
    ASSERT_EQ(vec.size(), 2u);
    EXPECT_EQ(vec[0], p1);
    EXPECT_EQ(vec[1], p2);
}

TEST(ILayoutSlideCollectionTest, AsIEnumerableReturnsAllSlides) {
    LayoutSlideCollection coll;
    auto s1 = std::make_unique<LayoutSlide>();
    auto* p1 = s1.get();
    coll.add(std::move(s1));

    const auto& const_coll = coll;
    auto vec = const_coll.as_i_enumerable();
    ASSERT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], p1);
}

TEST(ILayoutSlideCollectionTest, GetByTypeFindsMatch) {
    LayoutSlideCollection coll;
    auto s1 = std::make_unique<LayoutSlide>();
    s1->set_layout_type(SlideLayoutType::TITLE);
    auto s2 = std::make_unique<LayoutSlide>();
    s2->set_layout_type(SlideLayoutType::BLANK);
    auto* p2 = s2.get();
    coll.add(std::move(s1));
    coll.add(std::move(s2));

    EXPECT_EQ(coll.get_by_type(SlideLayoutType::BLANK), p2);
}

TEST(ILayoutSlideCollectionTest, GetByTypeReturnsFirstMatch) {
    LayoutSlideCollection coll;
    auto s1 = std::make_unique<LayoutSlide>();
    s1->set_layout_type(SlideLayoutType::TITLE);
    auto s2 = std::make_unique<LayoutSlide>();
    s2->set_layout_type(SlideLayoutType::TITLE);
    auto* p1 = s1.get();
    coll.add(std::move(s1));
    coll.add(std::move(s2));

    EXPECT_EQ(coll.get_by_type(SlideLayoutType::TITLE), p1);
}

TEST(ILayoutSlideCollectionTest, GetByTypeReturnsNullptrWhenNoMatch) {
    LayoutSlideCollection coll;
    auto s1 = std::make_unique<LayoutSlide>();
    s1->set_layout_type(SlideLayoutType::TITLE);
    coll.add(std::move(s1));

    EXPECT_EQ(coll.get_by_type(SlideLayoutType::BLANK), nullptr);
}

TEST(ILayoutSlideCollectionTest, GetByTypeOnEmptyReturnsNullptr) {
    LayoutSlideCollection coll;
    EXPECT_EQ(coll.get_by_type(SlideLayoutType::CUSTOM), nullptr);
}
