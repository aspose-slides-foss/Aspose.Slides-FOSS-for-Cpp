// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_text_frame.h>
#include <Aspose/Slides/Foss/i_paragraph_collection.h>
#include <Aspose/Slides/Foss/i_text_frame_format.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/text_frame_format.h>

using namespace Aspose::Slides::Foss;

namespace {

// ---------------------------------------------------------------------------
// Stub implementation of ITextFrame for testing the interface contract.
// ---------------------------------------------------------------------------

class StubTextFrame : public ITextFrame {
public:
    // IPresentationComponent
    [[nodiscard]] IPresentation* presentation() override { return nullptr; }
    [[nodiscard]] const IPresentation* presentation() const override { return nullptr; }

    // ISlideComponent
    [[nodiscard]] IBaseSlide* slide() override { return nullptr; }
    [[nodiscard]] const IBaseSlide* slide() const override { return nullptr; }
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override { return this; }
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override { return this; }

    // ITextFrame
    [[nodiscard]] IParagraphCollection& paragraphs() override { return paragraphs_; }
    [[nodiscard]] const IParagraphCollection& paragraphs() const override { return paragraphs_; }

    [[nodiscard]] std::string text() const override { return text_; }
    void set_text(const std::string& value) override { text_ = value; }

    [[nodiscard]] ITextFrameFormat& text_frame_format() override { return format_; }
    [[nodiscard]] const ITextFrameFormat& text_frame_format() const override { return format_; }

    [[nodiscard]] IShape* parent_shape() override { return nullptr; }
    [[nodiscard]] const IShape* parent_shape() const override { return nullptr; }

    [[nodiscard]] ICell* parent_cell() override { return nullptr; }
    [[nodiscard]] const ICell* parent_cell() const override { return nullptr; }

    [[nodiscard]] ISlideComponent* as_i_slide_component() override { return this; }
    [[nodiscard]] const ISlideComponent* as_i_slide_component() const override { return this; }

private:
    std::string text_;
    ParagraphCollection paragraphs_;
    TextFrameFormat format_;
};

} // namespace

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class ITextFrameTest : public ::testing::Test {
protected:
    StubTextFrame frame;
};

// ---------------------------------------------------------------------------
// Behavioral intent: text set on a text frame is retrievable through the
// interface (analogous to comment.text round-tripping).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, TextRoundTrip) {
    ITextFrame& itf = frame;
    itf.set_text("Review note");
    EXPECT_EQ(itf.text(), "Review note");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text can be set to different values and each is
// independently retrievable (analogous to filtering comments by author text).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, TextOverwrite) {
    ITextFrame& itf = frame;
    itf.set_text("Alice's");
    EXPECT_EQ(itf.text(), "Alice's");

    itf.set_text("Bob's");
    EXPECT_EQ(itf.text(), "Bob's");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text is retrievable after being set, ordering is
// preserved (analogous to insert_comment placing text at correct index).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, SetTextPreservesValue) {
    ITextFrame& itf = frame;
    itf.set_text("First");
    EXPECT_EQ(itf.text(), "First");
    itf.set_text("Second");
    EXPECT_EQ(itf.text(), "Second");
    itf.set_text("Third");
    EXPECT_EQ(itf.text(), "Third");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text set on a notes text frame persists (notes_text_frame
// is an ITextFrame; here we verify the text property contract).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, NotesTextPersists) {
    ITextFrame& itf = frame;
    itf.set_text("Speaker notes");
    EXPECT_EQ(itf.text(), "Speaker notes");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text frame is accessible and text can be set alongside
// other properties (analogous to setting notes text before header/footer).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, TextFrameFormatAccessible) {
    ITextFrame& itf = frame;
    itf.set_text("Notes");

    // Format is accessible and modifiable through the interface.
    auto& fmt = itf.text_frame_format();
    fmt.set_anchoring_type(TextAnchorType::CENTER);
    EXPECT_EQ(itf.text_frame_format().anchoring_type(), TextAnchorType::CENTER);
    EXPECT_EQ(itf.text(), "Notes");
}

// ---------------------------------------------------------------------------
// Behavioral intent: text frame content is accessible through cell-like
// parent (here we verify parent_cell/parent_shape nullable contract and
// text set on the frame for a "Bordered" cell).
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, CellTextBordered) {
    ITextFrame& itf = frame;
    itf.set_text("Bordered");
    EXPECT_EQ(itf.text(), "Bordered");

    // parent_cell and parent_shape return nullptr in a standalone text frame.
    EXPECT_EQ(itf.parent_cell(), nullptr);
    EXPECT_EQ(itf.parent_shape(), nullptr);
}

// ---------------------------------------------------------------------------
// Additional: interface structural tests
// ---------------------------------------------------------------------------

TEST_F(ITextFrameTest, ParagraphsAccessible) {
    ITextFrame& itf = frame;
    // Paragraphs collection is accessible (starts empty).
    EXPECT_EQ(itf.paragraphs().size(), 0u);
}

TEST_F(ITextFrameTest, AsISlideComponent) {
    ITextFrame& itf = frame;
    ISlideComponent* sc = itf.as_i_slide_component();
    EXPECT_EQ(sc, static_cast<ISlideComponent*>(&frame));
}

TEST_F(ITextFrameTest, EmptyTextDefault) {
    ITextFrame& itf = frame;
    EXPECT_EQ(itf.text(), "");
}

TEST_F(ITextFrameTest, ConstAccess) {
    frame.set_text("Const test");
    const ITextFrame& citf = frame;
    EXPECT_EQ(citf.text(), "Const test");
    EXPECT_EQ(citf.parent_shape(), nullptr);
    EXPECT_EQ(citf.parent_cell(), nullptr);
    EXPECT_NE(citf.as_i_slide_component(), nullptr);
}
