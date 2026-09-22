// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file text_body_conformance_test.cpp
/// The text body of a deck built in memory: bullets, paragraph properties,
/// text-frame properties, and whether a paragraph keeps all of its portions.
///
/// A deck built in memory is the path every README sample takes, and it is
/// served by a different serialiser from a deck loaded off disk. The two
/// disagree about how much of the formatting model exists.

#include <filesystem>
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

/// The paragraphs of the last shape on the slide, which is where a shape added
/// to it goes.
const std::string kNewShapeParagraph = "//p:spTree/p:sp[last()]/p:txBody/a:p";

/// The text of every node the XPath selects in the slide, concatenated.
std::string saved_text(const conformance::Package& pkg,
                       const std::string& xpath) {
    std::string text;
    for (const auto& node : pkg.xml(kSlide).select_nodes(xpath.c_str())) {
        text += node.node().text().as_string();
    }
    return text;
}

/// An untouched new slide as PowerPoint saves it; see make_fixtures.py.
std::string new_slide_fixture() {
    return (conformance::test_data_dir() / "powerpoint_new_slide.pptx").string();
}

void set_character_bullet(ParagraphFormat& fmt) {
    fmt.bullet().set_type(BulletType::SYMBOL);
    fmt.bullet().set_char("\xE2\x80\xA2"); // U+2022 BULLET
    fmt.bullet().set_font_name("Arial");
}

void set_hanging_margins(ParagraphFormat& fmt) {
    fmt.set_margin_left(22.5); // 22.5 pt -> 285750 EMU
    fmt.set_indent(-22.5);
}

class TextBodyConformance : public conformance::SavedDeckTest {
protected:
    AutoShape& shape_with_text(Presentation& pres, const std::string& text) {
        pres.slides()[0].shapes().clear();
        auto& shape = pres.slides()[0].shapes().add_auto_shape(
            ShapeType::RECTANGLE, 50, 50, 400, 120);
        shape.text_frame()->set_text(text);
        return shape;
    }

    /// One paragraph carrying a character bullet and hanging margins is one
    /// `<a:pPr>`, ahead of the text, holding both.
    static void expect_one_bulleted_ppr(const conformance::Package& pkg,
                                        const std::string& paragraph) {
        EXPECT_EQ(conformance::CountMatches(pkg, kSlide, paragraph + "/a:pPr"),
                  1u)
            << "CT_TextParagraph allows one a:pPr; PowerPoint refuses a "
               "paragraph with two";
        auto children = conformance::ChildNames(
            pkg.xml(kSlide).select_node(paragraph.c_str()).node());
        ASSERT_FALSE(children.empty()) << "no paragraph at " << paragraph;
        EXPECT_EQ(children.front(), "a:pPr");
        EXPECT_TRUE(conformance::ElementExists(
            pkg, kSlide, paragraph + "/a:pPr",
            {{"marL", "285750"}, {"indent", "-285750"}}));
        EXPECT_TRUE(conformance::ChildOrderIs(pkg, kSlide, paragraph + "/a:pPr",
                                              {"a:buFont", "a:buChar"}));
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

/// `add_text_frame` on a shape added to a deck opened from a file built a text
/// frame that nothing wrote out. Its text read back from memory, and the shape
/// was saved holding one empty paragraph.
TEST_F(TextBodyConformance, TextGivenToANewShapeOnALoadedDeckReachesTheFile) {
    Presentation pres;
    auto base = save(pres, "base.pptx");

    Presentation loaded(base.string());
    auto& shape = loaded.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 400, 120);
    shape.add_text_frame("Added after loading");

    conformance::Package pkg(save_to(loaded, path_for("edited.pptx")));
    EXPECT_EQ(saved_text(pkg, kNewShapeParagraph + "/a:r/a:t"),
              "Added after loading")
        << "the new shape was saved with an empty text body";
}

/// The same, on a fixture shaped like a slide PowerPoint saves, with a line break in the text.
TEST_F(TextBodyConformance, TextGivenToANewShapeOnAPowerPointShapedDeckReachesTheFile) {
    Presentation loaded(new_slide_fixture());
    auto& shape = loaded.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 300, 400, 120);
    shape.add_text_frame("First line\nSecond line");

    auto pkg = save_and_inspect(loaded);
    EXPECT_EQ(conformance::CountMatches(pkg, kSlide, kNewShapeParagraph), 2u);
    EXPECT_EQ(saved_text(pkg, kNewShapeParagraph + "[1]/a:r/a:t"), "First line");
    EXPECT_EQ(saved_text(pkg, kNewShapeParagraph + "[2]/a:r/a:t"),
              "Second line");
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

/// A bullet on that new shape is lost with its text, and once the text is
/// written, setting the bullet before the margins must still give one a:pPr.
TEST_F(TextBodyConformance, ABulletOnANewShapeOfALoadedDeckReachesTheFile) {
    Presentation loaded(new_slide_fixture());
    auto& shape = loaded.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 300, 400, 120);
    auto& fmt =
        shape.add_text_frame("Bulleted line").paragraphs()[0].paragraph_format();
    set_character_bullet(fmt);
    set_hanging_margins(fmt);

    auto pkg = save_and_inspect(loaded);
    EXPECT_EQ(saved_text(pkg, kNewShapeParagraph + "/a:r/a:t"), "Bulleted line");
    expect_one_bulleted_ppr(pkg, kNewShapeParagraph);
}

/// A loaded paragraph with no `<a:pPr>`: the bullet created one that the
/// paragraph's own formatting did not know about, so the margins set next
/// created a second.
TEST_F(TextBodyConformance, BulletThenMarginsOnALoadedParagraphWriteOnePPr) {
    Presentation loaded(new_slide_fixture());
    auto* body = dynamic_cast<AutoShape*>(&loaded.slides()[0].shapes()[1]);
    ASSERT_NE(body, nullptr);
    auto& fmt = body->text_frame()->paragraphs()[0].paragraph_format();
    set_character_bullet(fmt);
    set_hanging_margins(fmt);

    auto pkg = save_and_inspect(loaded);
    expect_one_bulleted_ppr(pkg, "//p:spTree/p:sp[2]/p:txBody/a:p");
}

/// Regression guard: the other order was already right.
TEST_F(TextBodyConformance, MarginsThenBulletOnALoadedParagraphWriteOnePPr) {
    Presentation loaded(new_slide_fixture());
    auto* body = dynamic_cast<AutoShape*>(&loaded.slides()[0].shapes()[1]);
    ASSERT_NE(body, nullptr);
    auto& fmt = body->text_frame()->paragraphs()[0].paragraph_format();
    set_hanging_margins(fmt);
    set_character_bullet(fmt);

    auto pkg = save_and_inspect(loaded);
    expect_one_bulleted_ppr(pkg, "//p:spTree/p:sp[2]/p:txBody/a:p");
}

/// Regression guard: the same calls on a deck built in memory, which a
/// different serialiser writes and which was already right.
TEST_F(TextBodyConformance, TextAndBulletOnANewShapeOfAnInMemoryDeckReachTheFile) {
    Presentation pres;
    pres.slides()[0].shapes().clear();
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 400, 120);
    auto& fmt =
        shape.add_text_frame("Bulleted line").paragraphs()[0].paragraph_format();
    set_character_bullet(fmt);
    set_hanging_margins(fmt);

    auto pkg = save_and_inspect(pres);
    EXPECT_EQ(saved_text(pkg, kNewShapeParagraph + "/a:r/a:t"), "Bulleted line");
    expect_one_bulleted_ppr(pkg, kNewShapeParagraph);
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
