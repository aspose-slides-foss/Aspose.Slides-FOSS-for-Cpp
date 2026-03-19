// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;

TEST(PortionTest, DefaultConstructorEmptyText) {
    Portion p;
    EXPECT_EQ(p.text(), "");
}

TEST(PortionTest, StringConstructorSetsText) {
    Portion p("Hello");
    EXPECT_EQ(p.text(), "Hello");
}

TEST(PortionTest, SetText) {
    Portion p;
    p.set_text("World");
    EXPECT_EQ(p.text(), "World");
}

TEST(PortionTest, SetTextOverwrite) {
    Portion p("Initial");
    p.set_text("Updated");
    EXPECT_EQ(p.text(), "Updated");
}

TEST(PortionTest, PortionFormatAccessible) {
    Portion p("Test");
    PortionFormat& fmt = p.portion_format();
    // Just verify we can access the format without crashing.
    (void)fmt;
}

TEST(PortionTest, PortionFormatConst) {
    const Portion p("Test");
    const PortionFormat& fmt = p.portion_format();
    (void)fmt;
}

TEST(PortionTest, AsISlideComponent) {
    Portion p;
    ISlideComponent* sc = p.as_i_slide_component();
    ASSERT_NE(sc, nullptr);
    // Verify functional equivalence — same slide() result.
    EXPECT_EQ(sc->slide(), nullptr);
}

TEST(PortionTest, AsISlideComponentConst) {
    const Portion p;
    const ISlideComponent* sc = p.as_i_slide_component();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->slide(), nullptr);
}

TEST(PortionTest, AsIPresentationComponent) {
    Portion p;
    IPresentationComponent* pc = p.as_i_presentation_component();
    ASSERT_NE(pc, nullptr);
    EXPECT_EQ(pc->presentation(), nullptr);
}

TEST(PortionTest, AsIPresentationComponentConst) {
    const Portion p;
    const IPresentationComponent* pc = p.as_i_presentation_component();
    ASSERT_NE(pc, nullptr);
    EXPECT_EQ(pc->presentation(), nullptr);
}

TEST(PortionTest, SlideReturnsNullForStandalone) {
    Portion p;
    EXPECT_EQ(p.slide(), nullptr);
}

TEST(PortionTest, PresentationReturnsNullForStandalone) {
    Portion p;
    EXPECT_EQ(p.presentation(), nullptr);
}

TEST(PortionTest, SlideConstReturnsNull) {
    const Portion p;
    EXPECT_EQ(p.slide(), nullptr);
}

TEST(PortionTest, PresentationConstReturnsNull) {
    const Portion p;
    EXPECT_EQ(p.presentation(), nullptr);
}

// Test that IPortion* can be obtained via interface hierarchy.
TEST(PortionTest, InterfacePointerAssignment) {
    Portion p("interface test");
    IPortion* ip = &p;
    EXPECT_EQ(ip->text(), "interface test");

    ISlideComponent* isc = &p;
    EXPECT_EQ(isc->slide(), nullptr);

    IPresentationComponent* ipc = &p;
    EXPECT_EQ(ipc->presentation(), nullptr);
}

// Test move semantics preserve text.
TEST(PortionTest, MoveConstructor) {
    Portion p1("movable");
    Portion p2(std::move(p1));
    EXPECT_EQ(p2.text(), "movable");
}

// Test move assignment preserves text.
TEST(PortionTest, MoveAssignment) {
    Portion p1("source");
    Portion p2;
    p2 = std::move(p1);
    EXPECT_EQ(p2.text(), "source");
}

TEST(PortionTest, SlideReturnsParentSlideWhenSet) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Portion p("test");
    p.set_slide(&slide);
    EXPECT_EQ(p.slide(), &slide);
}

TEST(PortionTest, SlideConstReturnsParentSlideWhenSet) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Portion p("test");
    p.set_slide(&slide);
    const Portion& cp = p;
    EXPECT_EQ(cp.slide(), &slide);
}

TEST(PortionTest, SlideReturnsNullAfterClearing) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Portion p("test");
    p.set_slide(&slide);
    EXPECT_NE(p.slide(), nullptr);
    p.set_slide(nullptr);
    EXPECT_EQ(p.slide(), nullptr);
}

TEST(PortionTest, PresentationReturnsPresentationViaSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Portion p("test");
    p.set_slide(&slide);
    EXPECT_EQ(p.presentation(), slide.presentation());
    EXPECT_NE(p.presentation(), nullptr);
}
