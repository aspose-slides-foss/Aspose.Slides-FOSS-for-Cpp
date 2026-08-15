// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file text_body_conformance_test.cpp
/// The text body of a deck built in memory: bullets, paragraph properties,
/// text-frame properties, and whether a paragraph keeps all of its portions.
///
/// A deck built in memory is the path every README sample takes, and it is
/// served by a different serialiser from a deck loaded off disk. The two
/// disagree about how much of the formatting model exists.

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/bullet_format.h>
#include <Aspose/Slides/Foss/bullet_type.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_alignment.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/text_frame_format.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

constexpr const char* kSlide = "ppt/slides/slide1.xml";

class TextBodyConformance : public conformance::SavedDeckTest {
protected:
    AutoShape& shape_with_text(Presentation& pres, const std::string& text) {
        pres.slides()[0].shapes().clear();
        auto& shape = pres.slides()[0].shapes().add_auto_shape(
            ShapeType::RECTANGLE, 50, 50, 400, 120);
        shape.text_frame()->set_text(text);
        return shape;
    }
};

// -- Bullets ----------------------------------------------------------------

/// A bulleted line is `<a:buChar>` (or `<a:buAutoNum>`) inside `<a:pPr>`.
/// Without it the line opens as plain text, whatever the in-memory bullet
/// format says.
TEST_F(TextBodyConformance, ACharacterBulletReachesTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Bulleted line");
    auto& para = shape.text_frame()->paragraphs()[0];
    auto& bullet = para.paragraph_format().bullet();
    bullet.set_type(BulletType::SYMBOL);
    bullet.set_char("\xE2\x80\xA2"); // U+2022 BULLET
    bullet.set_font_name("Arial");

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p/a:pPr/a:buChar"))
        << "the line opens with no bullet on it";
}

TEST_F(TextBodyConformance, ANumberedBulletReachesTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Numbered line");
    auto& bullet =
        shape.text_frame()->paragraphs()[0].paragraph_format().bullet();
    bullet.set_type(BulletType::NUMBERED);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide,
                                           "//a:p/a:pPr/a:buAutoNum"));
}

// -- Paragraph properties ---------------------------------------------------

/// An alignment nobody set must not be invented. Writing `algn` unconditionally
/// removes the caller's only way of saying "inherit from the layout", and makes
/// a paragraph that was never aligned indistinguishable from one that was
/// explicitly centred.
TEST_F(TextBodyConformance, AnUnsetAlignmentWritesNoAlgnAttribute) {
    Presentation pres;
    shape_with_text(pres, "Alignment never touched");

    auto pkg = save_and_inspect(pres);
    auto ppr = pkg.xml(kSlide).select_node("//a:p/a:pPr").node();
    if (!ppr) SUCCEED() << "no a:pPr is written, which also leaves inheritance intact";
    else
        EXPECT_FALSE(ppr.attribute("algn"))
            << "algn=\"" << ppr.attribute("algn").value()
            << "\" was written for a paragraph whose alignment was never set";
}

TEST_F(TextBodyConformance, AnExplicitAlignmentIsWrittenAsGiven) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Right aligned");
    shape.text_frame()->paragraphs()[0].paragraph_format().set_alignment(
        TextAlignment::RIGHT);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p/a:pPr",
                                           {{"algn", "r"}}));
}

TEST_F(TextBodyConformance, ParagraphIndentAndMarginReachTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Indented line");
    auto& fmt = shape.text_frame()->paragraphs()[0].paragraph_format();
    fmt.set_margin_left(22.5); // 22.5 pt -> 285750 EMU
    fmt.set_indent(-22.5);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:p/a:pPr", {{"marL", "285750"}, {"indent", "-285750"}}));
}

TEST_F(TextBodyConformance, TheParagraphDepthThatWasSetReachesTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Second level");
    shape.text_frame()->paragraphs()[0].paragraph_format().set_depth(1);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p/a:pPr",
                                           {{"lvl", "1"}}));
}

// -- Text-frame properties --------------------------------------------------

TEST_F(TextBodyConformance, TextFrameAnchoringReachesTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Anchored to the top");
    shape.text_frame()->text_frame_format().set_anchoring_type(
        TextAnchorType::TOP);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:txBody/a:bodyPr",
                                           {{"anchor", "t"}}))
        << "the text frame is written with a fixed anchor, so the anchoring "
           "the caller asked for is discarded";
}

TEST_F(TextBodyConformance, TextFrameMarginsReachTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Wide margins");
    auto& fmt = shape.text_frame()->text_frame_format();
    fmt.set_margin_left(10);  // 10 pt -> 127000 EMU
    fmt.set_margin_right(10);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//p:txBody/a:bodyPr",
        {{"lIns", "127000"}, {"rIns", "127000"}}));
}

TEST_F(TextBodyConformance, DisablingTextWrapReachesTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "No wrapping");
    shape.text_frame()->text_frame_format().set_wrap_text(NullableBool::FALSE);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:txBody/a:bodyPr",
                                           {{"wrap", "none"}}));
}

// -- The loaded-deck path ---------------------------------------------------

/// Editing a deck opened from a file is what these libraries are best at, and
/// the paragraph and text-frame formatting models did not reach it at all:
/// their setters were defined inline in the header and only ever assigned a
/// member, so on a loaded deck everything was accepted, read back, and
/// dropped. Only `<a:bodyPr>` written from scratch and only
/// `ParagraphFormat::set_alignment` were XML-backed.
TEST_F(TextBodyConformance, ParagraphFormattingSetOnALoadedDeckReachesTheFile) {
    Presentation pres;
    shape_with_text(pres, "A line of text");
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto* shape = dynamic_cast<AutoShape*>(&loaded.slides()[0].shapes()[0]);
    ASSERT_NE(shape, nullptr);
    auto& fmt = shape->text_frame()->paragraphs()[0].paragraph_format();
    fmt.set_depth(1);
    fmt.set_margin_left(22.5);  // 22.5 pt -> 285750 EMU
    fmt.set_indent(-22.5);
    fmt.set_space_before(-6.0); // negative = points -> a:spcPts val="600"
    fmt.set_right_to_left(NullableBool::TRUE);

    conformance::Package pkg(save_to(loaded, path_for("formatted.pptx")));
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:p/a:pPr",
        {{"lvl", "1"},
         {"marL", "285750"},
         {"indent", "-285750"},
         {"rtl", "1"}}))
        << "paragraph formatting set on a loaded deck never reached a:pPr";
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:p/a:pPr/a:spcBef/a:spcPts", {{"val", "600"}}));
}

/// A bullet is a child of `<a:pPr>`, so it is lost the same way and costs more.
TEST_F(TextBodyConformance, ABulletSetOnALoadedDeckReachesTheFile) {
    Presentation pres;
    shape_with_text(pres, "A bulleted line");
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto* shape = dynamic_cast<AutoShape*>(&loaded.slides()[0].shapes()[0]);
    ASSERT_NE(shape, nullptr);
    auto& bullet =
        shape->text_frame()->paragraphs()[0].paragraph_format().bullet();
    bullet.set_type(BulletType::SYMBOL);
    bullet.set_char("-");

    conformance::Package pkg(save_to(loaded, path_for("bulleted.pptx")));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p/a:pPr/a:buChar",
                                           {{"char", "-"}}));
}

/// The text-frame half of the same defect.
TEST_F(TextBodyConformance, TextFrameFormattingSetOnALoadedDeckReachesTheFile) {
    Presentation pres;
    shape_with_text(pres, "A line of text");
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto* shape = dynamic_cast<AutoShape*>(&loaded.slides()[0].shapes()[0]);
    ASSERT_NE(shape, nullptr);
    auto& fmt = shape->text_frame()->text_frame_format();
    fmt.set_anchoring_type(TextAnchorType::TOP);
    fmt.set_margin_left(10); // 10 pt -> 127000 EMU
    fmt.set_margin_right(10);
    fmt.set_wrap_text(NullableBool::FALSE);

    conformance::Package pkg(save_to(loaded, path_for("anchored.pptx")));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:txBody/a:bodyPr",
                                           {{"anchor", "t"},
                                            {"lIns", "127000"},
                                            {"rIns", "127000"},
                                            {"wrap", "none"}}))
        << "text-frame formatting set on a loaded deck never reached a:bodyPr";
}

// -- Portions ---------------------------------------------------------------

/// A bold word inside a sentence is one paragraph with two differently
/// formatted runs. It is the most common rich-text operation there is.
///
/// Adding portions to a paragraph that is already attached works. Building the
/// paragraph first and then attaching it does not: `ParagraphCollection::add`
/// takes its argument by value, so every paragraph attached this way is moved
/// on the way in.
TEST_F(TextBodyConformance, ADetachedParagraphKeepsEveryPortionWhenItIsAdded) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "First paragraph");

    Paragraph para("plain ");
    Portion bold("bold");
    bold.portion_format().set_font_bold(NullableBool::TRUE);
    para.portions().add(std::move(bold));
    ASSERT_EQ(para.portions().size(), 2u);

    auto& attached = shape.text_frame()->paragraphs().add(std::move(para));
    EXPECT_EQ(attached.portions().size(), 2u)
        << "attaching the paragraph discarded a portion, so a differently "
           "formatted span inside a paragraph cannot be produced at all";

    auto pkg = save_and_inspect(pres);
    EXPECT_EQ(conformance::CountMatches(pkg, kSlide, "//a:p[2]/a:r"), 2u);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p[2]/a:r/a:rPr",
                                           {{"b", "1"}}));
}

/// The already-attached route works today and must keep working.
TEST_F(TextBodyConformance, TwoRunsAddedToAnAttachedParagraphBothReachTheFile) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "plain ");
    auto& para = shape.text_frame()->paragraphs()[0];

    Portion bold("bold");
    bold.portion_format().set_font_bold(NullableBool::TRUE);
    para.portions().add(std::move(bold));

    auto pkg = save_and_inspect(pres);
    EXPECT_EQ(conformance::CountMatches(pkg, kSlide, "//a:p/a:r"), 2u);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:p/a:r/a:rPr",
                                           {{"b", "1"}}));
}

/// `CT_RegularTextRun` is the sequence `rPr?` then `t`. A run whose properties
/// follow its text has those properties discarded by consumers that honour the
/// sequence.
TEST_F(TextBodyConformance, RunPropertiesArePlacedBeforeTheRunText) {
    Presentation pres;
    auto& shape = shape_with_text(pres, "Formatted");
    auto& fmt =
        shape.text_frame()->paragraphs()[0].portions()[0].portion_format();
    fmt.set_font_bold(NullableBool::TRUE);
    fmt.set_font_height(24);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ChildOrderIs(pkg, kSlide, "//a:p/a:r",
                                          {"a:rPr", "a:t"}));
}

} // namespace
