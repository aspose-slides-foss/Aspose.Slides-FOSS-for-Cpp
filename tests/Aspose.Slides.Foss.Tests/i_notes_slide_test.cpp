// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>

using namespace Aspose::Slides::Foss;

// Notes text persists through the text frame.
TEST(INotesSlideTest, AddNotesTextFrame) {
    NotesSlideManager mgr;
    ASSERT_EQ(mgr.notes_slide(), nullptr);

    auto* notes = mgr.add_notes_slide();
    ASSERT_NE(notes, nullptr);

    notes->notes_text_frame().set_text("Speaker notes");
    EXPECT_EQ(notes->notes_text_frame().text(), "Speaker notes");

    // Calling add again returns the same slide.
    auto* notes2 = mgr.add_notes_slide();
    EXPECT_EQ(notes, notes2);
    EXPECT_EQ(notes2->notes_text_frame().text(), "Speaker notes");
}

TEST(INotesSlideTest, RemoveNotes) {
    NotesSlideManager mgr;
    mgr.add_notes_slide();
    ASSERT_NE(mgr.notes_slide(), nullptr);

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);
}

// Header/footer visibility and text assignment on a notes slide.
TEST(INotesSlideTest, HeaderFooterManager) {
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

// Notes slide references its parent slide.
TEST(INotesSlideTest, ParentSlide) {
    // Use a reinterpret trick: we just need a non-null pointer for identity.
    int dummy = 0;
    auto* fake_slide = reinterpret_cast<ISlide*>(&dummy);

    NotesSlideManager mgr(fake_slide);
    auto* notes = mgr.add_notes_slide();

    EXPECT_EQ(notes->parent_slide(), fake_slide);
}

// Test as_i_base_slide returns a valid IBaseSlide reference to the same object.
TEST(INotesSlideTest, AsIBaseSlide) {
    NotesSlide ns;
    ns.set_name("TestNotes");
    IBaseSlide& base = ns.as_i_base_slide();
    EXPECT_EQ(base.name(), "TestNotes");

    // Const overload works too.
    const NotesSlide& cns = ns;
    const IBaseSlide& cbase = cns.as_i_base_slide();
    EXPECT_EQ(cbase.name(), "TestNotes");
}
