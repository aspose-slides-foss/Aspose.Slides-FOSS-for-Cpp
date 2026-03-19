// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/i_paragraph_collection.h>
#include <Aspose/Slides/Foss/i_text_frame_format.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class TextFrameTest : public ::testing::Test {
protected:
    TextFrame frame;
};

// ---------------------------------------------------------------------------
// Behavioral intent: text set on a text frame is retrievable (analogous to
// comment.text round-tripping through save/reload).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, TextRoundTrip) {
    frame.set_text("Review note");
    EXPECT_EQ(frame.text(), "Review note");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text can be overwritten and each value is independently
// retrievable (analogous to filtering comments by different author text).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, TextOverwrite) {
    frame.set_text("Alice's");
    EXPECT_EQ(frame.text(), "Alice's");

    frame.set_text("Bob's");
    EXPECT_EQ(frame.text(), "Bob's");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text is retrievable after being set, ordering preserved
// (analogous to insert_comment placing text at correct index).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, SetTextPreservesValue) {
    frame.set_text("First");
    EXPECT_EQ(frame.text(), "First");
    frame.set_text("Second");
    EXPECT_EQ(frame.text(), "Second");
    frame.set_text("Third");
    EXPECT_EQ(frame.text(), "Third");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text set on a notes text frame persists (notes_text_frame
// is a TextFrame; here we verify the concrete text property).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, NotesTextPersists) {
    frame.set_text("Speaker notes");
    EXPECT_EQ(frame.text(), "Speaker notes");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text frame is accessible and text can be set alongside
// format properties (analogous to setting notes text before header/footer).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, TextFrameFormatAccessible) {
    frame.set_text("Notes");

    auto& fmt = frame.text_frame_format();
    fmt.set_anchoring_type(TextAnchorType::CENTER);
    EXPECT_EQ(frame.text_frame_format().anchoring_type(), TextAnchorType::CENTER);
    EXPECT_EQ(frame.text(), "Notes");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text frame content is accessible through cell-like parent
// (verifying parent_cell/parent_shape nullable contract and text for a
// "Bordered" cell).
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, CellTextBordered) {
    frame.set_text("Bordered");
    EXPECT_EQ(frame.text(), "Bordered");

    // parent_cell and parent_shape return nullptr in a standalone text frame.
    EXPECT_EQ(frame.parent_cell(), nullptr);
    EXPECT_EQ(frame.parent_shape(), nullptr);
}

// ---------------------------------------------------------------------------
// Additional: concrete TextFrame behavior tests
// ---------------------------------------------------------------------------

TEST_F(TextFrameTest, EmptyTextDefault) {
    EXPECT_EQ(frame.text(), "");
}

TEST_F(TextFrameTest, ParagraphsStartEmpty) {
    EXPECT_EQ(frame.paragraphs().size(), 0u);
}

TEST_F(TextFrameTest, SetTextCreatesParagraphs) {
    frame.set_text("Line 1\nLine 2\nLine 3");
    EXPECT_EQ(frame.paragraphs().size(), 3u);
    EXPECT_EQ(frame.paragraphs()[0].text(), "Line 1");
    EXPECT_EQ(frame.paragraphs()[1].text(), "Line 2");
    EXPECT_EQ(frame.paragraphs()[2].text(), "Line 3");
    EXPECT_EQ(frame.text(), "Line 1\nLine 2\nLine 3");
}

TEST_F(TextFrameTest, SetTextHandlesCarriageReturn) {
    frame.set_text("A\rB\r\nC");
    EXPECT_EQ(frame.paragraphs().size(), 3u);
    EXPECT_EQ(frame.text(), "A\nB\nC");
}

TEST_F(TextFrameTest, SetTextEmptyCreatesOneParagraph) {
    frame.set_text("");
    EXPECT_EQ(frame.paragraphs().size(), 1u);
    EXPECT_EQ(frame.paragraphs()[0].text(), "");
}

TEST_F(TextFrameTest, SetTextClearsPreviousParagraphs) {
    frame.set_text("Old text");
    EXPECT_EQ(frame.paragraphs().size(), 1u);
    frame.set_text("New\nText");
    EXPECT_EQ(frame.paragraphs().size(), 2u);
    EXPECT_EQ(frame.text(), "New\nText");
}

TEST_F(TextFrameTest, AsISlideComponent) {
    ISlideComponent* sc = frame.as_i_slide_component();
    EXPECT_EQ(sc, static_cast<ISlideComponent*>(&frame));
}

TEST_F(TextFrameTest, AsIPresentationComponent) {
    IPresentationComponent* pc = frame.as_i_presentation_component();
    EXPECT_EQ(pc, static_cast<IPresentationComponent*>(&frame));
}

TEST_F(TextFrameTest, SlideDefaultsToNull) {
    EXPECT_EQ(frame.slide(), nullptr);
}

TEST_F(TextFrameTest, PresentationDefaultsToNull) {
    EXPECT_EQ(frame.presentation(), nullptr);
}

TEST_F(TextFrameTest, ConstAccess) {
    frame.set_text("Const test");
    const TextFrame& cframe = frame;
    EXPECT_EQ(cframe.text(), "Const test");
    EXPECT_EQ(cframe.parent_shape(), nullptr);
    EXPECT_EQ(cframe.parent_cell(), nullptr);
    EXPECT_NE(cframe.as_i_slide_component(), nullptr);
}
