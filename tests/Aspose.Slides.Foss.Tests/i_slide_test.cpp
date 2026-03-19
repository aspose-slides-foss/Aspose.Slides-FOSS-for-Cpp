// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <chrono>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/i_notes_slide.h>
#include <Aspose/Slides/Foss/i_notes_slide_manager.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/i_layout_slide.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

// Setting hidden persists on the slide.
TEST(ISlideTest, SlideHidden) {
    Presentation pres;
    EXPECT_FALSE(pres.slides()[0].hidden());

    pres.slides()[0].set_hidden(true);
    EXPECT_TRUE(pres.slides()[0].hidden());

    pres.slides()[0].set_hidden(false);
    EXPECT_FALSE(pres.slides()[0].hidden());
}

// get_slide_comments filters by author.
TEST(ISlideTest, GetSlideComments) {
    Presentation pres;
    auto& a1 = pres.comment_authors().add_author("Alice", "A");
    auto& a2 = pres.comment_authors().add_author("Bob", "B");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    a1.comments().add_comment("Alice's", slide, PointF(1, 1), now);
    a2.comments().add_comment("Bob's", slide, PointF(2, 2), now);

    auto all_c = slide.get_slide_comments(nullptr);
    EXPECT_EQ(all_c.size(), 2);

    auto bob_c = slide.get_slide_comments(&a2);
    ASSERT_EQ(bob_c.size(), 1);
    EXPECT_EQ(bob_c[0]->text(), "Bob's");
}

// Notes text persists through the notes slide manager on a Slide.
TEST(ISlideTest, AddNotesViaSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto& mgr = slide.notes_slide_manager();

    auto* notes = mgr.add_notes_slide();
    ASSERT_NE(notes, nullptr);
    notes->notes_text_frame().set_text("Speaker notes");
    EXPECT_EQ(notes->notes_text_frame().text(), "Speaker notes");

    // Retrieving again returns the same notes slide.
    auto* notes2 = mgr.notes_slide();
    EXPECT_EQ(notes, notes2);
}

// Removing notes clears the notes slide.
TEST(ISlideTest, RemoveNotesViaSlide) {
    Presentation pres;
    auto& mgr = pres.slides()[0].notes_slide_manager();
    mgr.add_notes_slide();
    ASSERT_NE(mgr.notes_slide(), nullptr);

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);
}

// Header/footer visibility on notes slide accessed via Slide.
TEST(ISlideTest, NotesHeaderFooterViaSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    notes->notes_text_frame().set_text("Notes");

    auto& hfm = notes->header_footer_manager();
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());
}

// Notes slide references its parent slide via the Slide's notes manager.
TEST(ISlideTest, NotesParentSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    EXPECT_EQ(notes->parent_slide(), &slide);
}

// Test slide_number default and setter.
TEST(ISlideTest, SlideNumber) {
    Presentation pres;
    EXPECT_EQ(pres.slides()[0].slide_number(), 1);

    pres.slides()[0].set_slide_number(5);
    EXPECT_EQ(pres.slides()[0].slide_number(), 5);
}

// Test layout_slide getter and setter.
TEST(ISlideTest, LayoutSlide) {
    Presentation pres;
    // A default presentation assigns the first layout slide to its initial slide.
    EXPECT_NE(pres.slides()[0].layout_slide(), nullptr);

    // Test set/get roundtrip with another layout pointer.
    int dummy = 0;
    auto* fake_layout = reinterpret_cast<ILayoutSlide*>(&dummy);
    pres.slides()[0].set_layout_slide(fake_layout);
    EXPECT_EQ(pres.slides()[0].layout_slide(), fake_layout);
}

// Test remove() removes the slide from its presentation.
TEST(ISlideTest, RemoveSlide) {
    Presentation pres;
    ASSERT_EQ(pres.slides().size(), 1);

    // We can't remove the only slide and verify count goes to 0 easily,
    // but we can verify remove works with the collection.
    pres.slides()[0].remove();
    EXPECT_EQ(pres.slides().size(), 0);
}
