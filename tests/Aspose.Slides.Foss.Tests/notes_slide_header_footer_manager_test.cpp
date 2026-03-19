// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/notes_slide_header_footer_manager.h>
#include <Aspose/Slides/Foss/notes_slide_part.h>

using namespace Aspose::Slides::Foss;

// Tests header/footer visibility and text assignment on a notes slide.
TEST(NotesSlideHeaderFooterManagerTest, FooterAndSlideNumberVisibility) {
    NotesSlidePart part;
    NotesSlideHeaderFooterManager hfm(&part);

    // Initially no placeholders are visible.
    EXPECT_FALSE(hfm.is_footer_visible());
    EXPECT_FALSE(hfm.is_slide_number_visible());
    EXPECT_FALSE(hfm.is_date_time_visible());
    EXPECT_FALSE(hfm.is_header_visible());

    // Enable footer and slide number, set footer text.
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());
}

TEST(NotesSlideHeaderFooterManagerTest, DateTimeAndHeaderVisibility) {
    NotesSlidePart part;
    NotesSlideHeaderFooterManager hfm(&part);

    hfm.set_date_time_visibility(true);
    hfm.set_date_time_text("2026-03-17");
    hfm.set_header_visibility(true);
    hfm.set_header_text("My Header");

    EXPECT_TRUE(hfm.is_date_time_visible());
    EXPECT_TRUE(hfm.is_header_visible());
}

// Test that disabling visibility removes the placeholder.
TEST(NotesSlideHeaderFooterManagerTest, DisableVisibility) {
    NotesSlidePart part;
    NotesSlideHeaderFooterManager hfm(&part);

    hfm.set_footer_visibility(true);
    ASSERT_TRUE(hfm.is_footer_visible());

    hfm.set_footer_visibility(false);
    EXPECT_FALSE(hfm.is_footer_visible());

    hfm.set_slide_number_visibility(true);
    ASSERT_TRUE(hfm.is_slide_number_visible());

    hfm.set_slide_number_visibility(false);
    EXPECT_FALSE(hfm.is_slide_number_visible());

    hfm.set_header_visibility(true);
    ASSERT_TRUE(hfm.is_header_visible());

    hfm.set_header_visibility(false);
    EXPECT_FALSE(hfm.is_header_visible());

    hfm.set_date_time_visibility(true);
    ASSERT_TRUE(hfm.is_date_time_visible());

    hfm.set_date_time_visibility(false);
    EXPECT_FALSE(hfm.is_date_time_visible());
}

// Test text setters assign content to placeholders.
TEST(NotesSlideHeaderFooterManagerTest, TextSetters) {
    NotesSlidePart part;
    NotesSlideHeaderFooterManager hfm(&part);

    hfm.set_footer_text("Footer");
    hfm.set_date_time_text("Date");
    hfm.set_header_text("Header");

    // Setting text implicitly creates the placeholder.
    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_date_time_visible());
    EXPECT_TRUE(hfm.is_header_visible());

    // Verify text content via the backing part.
    EXPECT_EQ(part.get_placeholder_text("ftr"), "Footer");
    EXPECT_EQ(part.get_placeholder_text("dt"), "Date");
    EXPECT_EQ(part.get_placeholder_text("hdr"), "Header");
}

// Test interface cast methods return the same object.
TEST(NotesSlideHeaderFooterManagerTest, InterfaceCasts) {
    NotesSlidePart part;
    NotesSlideHeaderFooterManager hfm(&part);

    auto& base_handout = hfm.as_i_base_handout_notes_slide_header_footer_manager();
    auto& base_slide = hfm.as_i_base_slide_header_footer_manager();
    auto& base_hf = hfm.as_i_base_header_footer_manager();

    // All casts should point to the same object.
    EXPECT_EQ(static_cast<void*>(&base_handout), static_cast<void*>(&hfm));
    EXPECT_EQ(static_cast<void*>(&base_slide), static_cast<void*>(&hfm));
    EXPECT_EQ(static_cast<void*>(&base_hf), static_cast<void*>(&hfm));
}

// Test const interface cast methods.
TEST(NotesSlideHeaderFooterManagerTest, ConstInterfaceCasts) {
    NotesSlidePart part;
    const NotesSlideHeaderFooterManager hfm(&part);

    const auto& base_handout =
        hfm.as_i_base_handout_notes_slide_header_footer_manager();
    EXPECT_EQ(static_cast<const void*>(&base_handout),
              static_cast<const void*>(&hfm));
}
