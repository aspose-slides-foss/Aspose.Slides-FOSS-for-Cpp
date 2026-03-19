// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

// Notes text persists after add_notes_slide via Presentation API.
TEST(NotesSlideManagerTest, AddNotes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);

    notes->notes_text_frame().set_text("Speaker notes");
    EXPECT_EQ(notes->notes_text_frame().text(), "Speaker notes");

    // notes_slide() returns the same cached instance.
    auto* ns = slide.notes_slide_manager().notes_slide();
    ASSERT_NE(ns, nullptr);
    EXPECT_EQ(ns->notes_text_frame().text(), "Speaker notes");
}

// Removing notes clears the notes slide.
TEST(NotesSlideManagerTest, RemoveNotes) {
    Presentation pres;
    auto& mgr = pres.slides()[0].notes_slide_manager();
    mgr.add_notes_slide();
    ASSERT_NE(mgr.notes_slide(), nullptr);

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);
}

// Header/footer visibility persists on the notes slide.
TEST(NotesSlideManagerTest, NotesHeaderFooter) {
    Presentation pres;
    auto* notes = pres.slides()[0].notes_slide_manager().add_notes_slide();
    notes->notes_text_frame().set_text("Notes");

    auto& hfm = notes->header_footer_manager();
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());

    // Re-access through the manager to verify consistency.
    auto* ns = pres.slides()[0].notes_slide_manager().notes_slide();
    ASSERT_NE(ns, nullptr);
    EXPECT_TRUE(ns->header_footer_manager().is_footer_visible());
    EXPECT_TRUE(ns->header_footer_manager().is_slide_number_visible());
}

// Notes slide references its parent slide.
TEST(NotesSlideManagerTest, NotesParentSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    EXPECT_EQ(notes->parent_slide(), static_cast<ISlide*>(&slide));
}
