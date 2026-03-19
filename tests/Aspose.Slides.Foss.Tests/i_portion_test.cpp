// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <chrono>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/i_portion.h>
#include <Aspose/Slides/Foss/i_portion_format.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/table.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

// ---------------------------------------------------------------------------
// IPortion interface basics
// ---------------------------------------------------------------------------

// Verify portion_format() is accessible through IPortion interface.
TEST(IPortionTest, PortionFormatViaInterface) {
    Portion p("Hello");
    IPortion* ip = &p;
    IPortionFormat& fmt = ip->portion_format();
    // Verify we get a valid reference (no crash).
    (void)fmt;
}

// Verify const portion_format() is accessible through const IPortion.
TEST(IPortionTest, PortionFormatConstViaInterface) {
    const Portion p("Hello");
    const IPortion* ip = &p;
    const IPortionFormat& fmt = ip->portion_format();
    (void)fmt;
}

// Verify text() and set_text() through IPortion interface.
TEST(IPortionTest, TextViaInterface) {
    Portion p;
    IPortion* ip = &p;
    ip->set_text("Review note");
    EXPECT_EQ(ip->text(), "Review note");
}

// Verify as_i_slide_component() returns non-null and functional.
TEST(IPortionTest, AsISlideComponentViaInterface) {
    Portion p;
    IPortion* ip = &p;
    ISlideComponent* sc = ip->as_i_slide_component();
    ASSERT_NE(sc, nullptr);
}

// ---------------------------------------------------------------------------
// Verifies text portion content on a comment accessed through the collection.
// ---------------------------------------------------------------------------
TEST(IPortionTest, CommentTextAsPortion) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();
    auto& comment = author.comments().add_comment(
        "Review note", slide, PointF(2.0f, 3.0f), now);
    // The comment text should be accessible — this exercises the same
    // textual round-trip that IPortion.text represents.
    EXPECT_EQ(comment.text(), "Review note");
    EXPECT_EQ(comment.author()->name(), "Alice");
}

// ---------------------------------------------------------------------------
// Verifies text content filtering by author on a slide.
// ---------------------------------------------------------------------------
TEST(IPortionTest, SlideCommentsTextFiltering) {
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

// ---------------------------------------------------------------------------
// Verifies that insert_comment places text at the correct index.
// ---------------------------------------------------------------------------
TEST(IPortionTest, InsertCommentTextAtIndex) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("First", slide, PointF(1, 1), now);
    author.comments().add_comment("Third", slide, PointF(1, 3), now);
    author.comments().insert_comment(1, "Second", slide, PointF(1, 2), now);

    ASSERT_EQ(author.comments().size(), 3);
    EXPECT_EQ(author.comments()[0].text(), "First");
    EXPECT_EQ(author.comments()[1].text(), "Second");
    EXPECT_EQ(author.comments()[2].text(), "Third");
}

// ---------------------------------------------------------------------------
// Verifies text frame text on a notes slide — exercises the same text
// property pattern as IPortion.text.
// ---------------------------------------------------------------------------
TEST(IPortionTest, NotesSlideTextFrame) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);

    notes->notes_text_frame().set_text("Speaker notes");
    EXPECT_EQ(notes->notes_text_frame().text(), "Speaker notes");

    // Verify parent slide reference.
    EXPECT_EQ(notes->parent_slide(), &slide);
}

// ---------------------------------------------------------------------------
// Verifies header/footer visibility on a notes slide.
// ---------------------------------------------------------------------------
TEST(IPortionTest, NotesHeaderFooterVisibility) {
    Presentation pres;
    auto* notes = pres.slides()[0].notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);

    notes->notes_text_frame().set_text("Notes");
    auto& hfm = notes->header_footer_manager();
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());
}

// ---------------------------------------------------------------------------
// Verifies cell border properties persist — exercises CellFormat and
// LineFormat which parallel portion formatting structure.
// ---------------------------------------------------------------------------
TEST(IPortionTest, CellBordersPersist) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    slide.shapes().clear();

    std::array<double, 1> col_widths = {150.0};
    std::array<double, 1> row_heights = {50.0};
    auto& table = slide.shapes().add_table(50, 50, col_widths, row_heights);
    auto& cell = table.cell(0, 0);
    cell.text_frame()->set_text("Bordered");

    auto& fmt = cell.cell_format();
    for (auto* border : {&fmt.border_top(), &fmt.border_bottom(),
                         &fmt.border_left(), &fmt.border_right()}) {
        border->fill_format().set_fill_type(FillType::SOLID);
        border->fill_format().solid_fill_color().set_color(Color::red);
        border->set_width(3);
    }

    // Verify border properties were set.
    EXPECT_EQ(fmt.border_top().width(), 3);
    EXPECT_EQ(fmt.border_bottom().width(), 3);
    EXPECT_EQ(fmt.border_left().width(), 3);
    EXPECT_EQ(fmt.border_right().width(), 3);
    EXPECT_EQ(fmt.border_top().fill_format().fill_type(), FillType::SOLID);
}

// ---------------------------------------------------------------------------
// Verify portion_format identity — same format object on repeated calls.
// ---------------------------------------------------------------------------
TEST(IPortionTest, PortionFormatIdentity) {
    Portion p("test");
    IPortion* ip = &p;
    IPortionFormat* fmt1 = &ip->portion_format();
    IPortionFormat* fmt2 = &ip->portion_format();
    EXPECT_EQ(fmt1, fmt2);
}
