// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_layout_slide.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/slide_layout_type.h>

using namespace Aspose::Slides::Foss;

TEST(ILayoutSlideTest, DefaultLayoutTypeIsCustom) {
    LayoutSlide layout;
    const ILayoutSlide& iface = layout;
    EXPECT_EQ(iface.layout_type(), SlideLayoutType::CUSTOM);
}

TEST(ILayoutSlideTest, LayoutTypeReturnsSetValue) {
    LayoutSlide layout;
    layout.set_layout_type(SlideLayoutType::TITLE);
    const ILayoutSlide& iface = layout;
    EXPECT_EQ(iface.layout_type(), SlideLayoutType::TITLE);
}

TEST(ILayoutSlideTest, MasterSlideDefaultsToNull) {
    LayoutSlide layout;
    const ILayoutSlide& iface = layout;
    EXPECT_EQ(iface.master_slide(), nullptr);
}

TEST(ILayoutSlideTest, SetMasterSlideViaInterface) {
    LayoutSlide layout;
    MasterSlide master;
    ILayoutSlide& iface = layout;
    iface.set_master_slide(&master);
    EXPECT_EQ(iface.master_slide(), &master);
}

TEST(ILayoutSlideTest, SetMasterSlideToNull) {
    LayoutSlide layout;
    MasterSlide master;
    ILayoutSlide& iface = layout;
    iface.set_master_slide(&master);
    iface.set_master_slide(nullptr);
    EXPECT_EQ(iface.master_slide(), nullptr);
}
