// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// IParagraph interface tests exercised through the Paragraph concrete class.
// ---------------------------------------------------------------------------

TEST(IParagraphTest, TextGetterSetter) {
    Paragraph para;
    EXPECT_EQ(para.text(), "");

    para.set_text("Review note");
    EXPECT_EQ(para.text(), "Review note");

    // Verify through interface pointer.
    IParagraph* ip = &para;
    EXPECT_EQ(ip->text(), "Review note");
    ip->set_text("Updated");
    EXPECT_EQ(ip->text(), "Updated");
}

TEST(IParagraphTest, MultipleParagraphsDistinctText) {
    Paragraph p1("Alice's");
    Paragraph p2("Bob's");

    EXPECT_EQ(p1.text(), "Alice's");
    EXPECT_EQ(p2.text(), "Bob's");
    EXPECT_NE(p1.text(), p2.text());
}

TEST(IParagraphTest, TextReassignment) {
    Paragraph para("First");
    EXPECT_EQ(para.text(), "First");

    para.set_text("Second");
    EXPECT_EQ(para.text(), "Second");

    para.set_text("Third");
    EXPECT_EQ(para.text(), "Third");
}

TEST(IParagraphTest, ConstructWithText) {
    Paragraph para("Speaker notes");
    EXPECT_EQ(para.text(), "Speaker notes");
}

TEST(IParagraphTest, ParagraphFormatAccess) {
    Paragraph para;
    IParagraph* ip = &para;

    // Verify paragraph_format is accessible and modifiable.
    auto& fmt = ip->paragraph_format();
    // The format should be a valid reference (no crash).
    (void)fmt;

    // Const access also works.
    const IParagraph* cip = &para;
    const auto& cfmt = cip->paragraph_format();
    (void)cfmt;
}

TEST(IParagraphTest, PortionsCollectionAccess) {
    Paragraph para;
    IParagraph* ip = &para;

    // Initially empty.
    EXPECT_EQ(ip->portions().size(), 0);

    // Add a portion through the concrete type.
    para.portions().add(Portion("Bordered"));
    EXPECT_EQ(ip->portions().size(), 1);
}

// Test as_i_slide_component returns a valid pointer to the same object.
TEST(IParagraphTest, AsISlideComponent) {
    Paragraph para("test");
    IParagraph* ip = &para;

    ISlideComponent* sc = ip->as_i_slide_component();
    ASSERT_NE(sc, nullptr);

    // The returned pointer should refer to the same object.
    EXPECT_EQ(sc, static_cast<ISlideComponent*>(&para));

    // Const overload.
    const IParagraph* cip = &para;
    const ISlideComponent* csc = cip->as_i_slide_component();
    ASSERT_NE(csc, nullptr);
}

// Test IPresentationComponent access through the hierarchy.
TEST(IParagraphTest, AsIPresentationComponent) {
    Paragraph para;
    ISlideComponent* sc = para.as_i_slide_component();
    IPresentationComponent* pc = sc->as_i_presentation_component();
    ASSERT_NE(pc, nullptr);
}

// Test that slide() returns nullptr for a standalone paragraph.
TEST(IParagraphTest, SlideReturnsNullForStandalone) {
    Paragraph para;
    EXPECT_EQ(para.slide(), nullptr);
}

// Test that presentation() returns nullptr for a standalone paragraph.
TEST(IParagraphTest, PresentationReturnsNullForStandalone) {
    Paragraph para;
    EXPECT_EQ(para.presentation(), nullptr);
}

// Test move semantics preserve state.
//
// A move transfers the paragraph; it does not edit it.  Every portion the
// source held has to be present in the destination, and the paragraph's text
// is the concatenation of them all.  ParagraphCollection::add and ::insert
// both take a Paragraph by value, so every paragraph attached to a text frame
// goes through this constructor: a move that dropped portions would make a
// paragraph with more than one differently formatted run impossible to build.
TEST(IParagraphTest, MoveSemantics) {
    Paragraph p1("movable");
    p1.portions().add(Portion("part1"));

    Paragraph p2(std::move(p1));
    EXPECT_EQ(p2.portions().size(), 2u);
    EXPECT_EQ(p2.text(), "movablepart1");
}
