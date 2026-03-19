// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>

using namespace Aspose::Slides::Foss;

// Notes text persists after add_notes_slide.
TEST(INotesSlideManagerTest, AddNotesSlide) {
    NotesSlideManager mgr;
    ASSERT_EQ(mgr.notes_slide(), nullptr);

    auto* notes = mgr.add_notes_slide();
    ASSERT_NE(notes, nullptr);

    notes->notes_text_frame().set_text("Speaker notes");
    EXPECT_EQ(notes->notes_text_frame().text(), "Speaker notes");

    // notes_slide() returns the same slide after add.
    EXPECT_EQ(mgr.notes_slide(), notes);
}

// Calling add_notes_slide twice returns the same notes slide.
TEST(INotesSlideManagerTest, AddNotesSlideIdempotent) {
    NotesSlideManager mgr;
    auto* first = mgr.add_notes_slide();
    auto* second = mgr.add_notes_slide();
    EXPECT_EQ(first, second);
}

// Removing notes sets notes_slide to nullptr.
TEST(INotesSlideManagerTest, RemoveNotesSlide) {
    NotesSlideManager mgr;
    mgr.add_notes_slide();
    ASSERT_NE(mgr.notes_slide(), nullptr);

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);
}

// Removing when no notes exist is a no-op.
TEST(INotesSlideManagerTest, RemoveNotesSlideWhenNone) {
    NotesSlideManager mgr;
    EXPECT_EQ(mgr.notes_slide(), nullptr);
    mgr.remove_notes_slide(); // should not crash
    EXPECT_EQ(mgr.notes_slide(), nullptr);
}

// Header/footer visibility on the notes slide managed by the manager.
TEST(INotesSlideManagerTest, NotesHeaderFooter) {
    NotesSlideManager mgr;
    auto* notes = mgr.add_notes_slide();
    notes->notes_text_frame().set_text("Notes");

    auto& hfm = notes->header_footer_manager();
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());
}

// Notes slide references its parent slide via the manager.
TEST(INotesSlideManagerTest, NotesParentSlide) {
    int dummy = 0;
    auto* fake_slide = reinterpret_cast<ISlide*>(&dummy);

    NotesSlideManager mgr(fake_slide);
    auto* notes = mgr.add_notes_slide();

    EXPECT_EQ(notes->parent_slide(), fake_slide);
}

// Re-add after remove returns a fresh notes slide.
TEST(INotesSlideManagerTest, ReAddAfterRemove) {
    NotesSlideManager mgr;
    auto* first = mgr.add_notes_slide();
    first->notes_text_frame().set_text("Original");

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);

    auto* second = mgr.add_notes_slide();
    ASSERT_NE(second, nullptr);
    // New notes slide has empty text (fresh instance).
    EXPECT_EQ(second->notes_text_frame().text(), "");
}
