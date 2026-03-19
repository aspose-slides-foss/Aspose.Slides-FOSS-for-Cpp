// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/shape_collection.h>

using namespace Aspose::Slides::Foss;

/// Tests BaseSlide::name default value.
TEST(BaseSlideTest, DefaultNameIsEmpty) {
    MasterSlide slide;
    EXPECT_EQ(slide.name(), "");
}

/// Tests BaseSlide::set_name / name round-trip.
TEST(BaseSlideTest, SetNameRoundTrip) {
    MasterSlide slide;
    slide.set_name("Test Slide");
    EXPECT_EQ(slide.name(), "Test Slide");
}

/// Tests BaseSlide::slide_id default value.
TEST(BaseSlideTest, DefaultSlideIdIsZero) {
    LayoutSlide slide;
    EXPECT_EQ(slide.slide_id(), 0u);
}

/// Tests BaseSlide::presentation returns nullptr by default.
TEST(BaseSlideTest, DefaultPresentationIsNull) {
    MasterSlide slide;
    EXPECT_EQ(slide.presentation(), nullptr);
}

/// Tests BaseSlide::shapes returns a valid collection.
TEST(BaseSlideTest, ShapesReturnsCollection) {
    MasterSlide slide;
    EXPECT_EQ(slide.shapes().size(), 0u);
}

/// Tests BaseSlide as accessed through a Presentation's slide.
TEST(BaseSlideTest, SlideNameViaPresentation) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    EXPECT_EQ(slide.shapes().size(), 0u);
}

/// Tests that BaseSlide subclass LayoutSlide provides shapes.
TEST(BaseSlideTest, LayoutSlideShapes) {
    LayoutSlide layout;
    EXPECT_EQ(layout.shapes().size(), 0u);
    EXPECT_EQ(layout.name(), "");
}

/// Tests that BaseSlide subclass NotesSlide provides shapes.
TEST(BaseSlideTest, NotesSlideShapes) {
    NotesSlide notes;
    EXPECT_EQ(notes.shapes().size(), 0u);
    EXPECT_EQ(notes.presentation(), nullptr);
}

/// Tests IBaseSlide polymorphism through BaseSlide pointer.
TEST(BaseSlideTest, PolymorphicAccess) {
    MasterSlide master;
    master.set_name("Master");

    IBaseSlide* base = &master;
    EXPECT_EQ(base->name(), "Master");
    EXPECT_EQ(base->slide_id(), 0u);
    EXPECT_EQ(base->shapes().size(), 0u);
    EXPECT_EQ(base->presentation(), nullptr);
}
