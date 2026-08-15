// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file line_format_conformance_test.cpp
/// Everything `LineFormat` accepts, checked against what `<a:ln>` carries.
///
/// `CT_LineProperties` has four attributes — `w`, `cap`, `cmpd`, `algn` — and
/// its children come in sequence: fill, dash, join, `headEnd`, `tailEnd`.
/// Three of those are written today. The rest are accepted by the setters,
/// read back correctly by the getters, and absent from the file.

#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/line_alignment.h>
#include <Aspose/Slides/Foss/line_arrowhead_length.h>
#include <Aspose/Slides/Foss/line_arrowhead_style.h>
#include <Aspose/Slides/Foss/line_arrowhead_width.h>
#include <Aspose/Slides/Foss/line_cap_style.h>
#include <Aspose/Slides/Foss/line_dash_style.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/line_join_style.h>
#include <Aspose/Slides/Foss/line_style.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

constexpr const char* kSlide = "ppt/slides/slide1.xml";

class LineFormatConformance : public conformance::SavedDeckTest {
protected:
    LineFormat& fresh_line(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        auto& shape = pres.slides()[0].shapes().add_auto_shape(
            ShapeType::RECTANGLE, 50, 50, 200, 100);
        auto& line = shape.line_format();
        line.set_width(6); // 6 pt -> 76200 EMU
        line.fill_format().set_fill_type(FillType::SOLID);
        line.fill_format().solid_fill_color().set_color(Color::black);
        return line;
    }
};

/// Width, fill and dash are written today. Regression guard for the rest of
/// the line repair.
TEST_F(LineFormatConformance, WidthFillAndDashStyleReachTheFile) {
    Presentation pres;
    auto& line = fresh_line(pres);
    line.set_dash_style(LineDashStyle::DASH_DOT);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:spPr/a:ln",
                                           {{"w", "76200"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:solidFill/a:srgbClr",
                                           {{"val", "000000"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:prstDash",
                                           {{"val", "dashDot"}}));
}

TEST_F(LineFormatConformance, ABeginArrowheadReachesTheFile) {
    Presentation pres;
    auto& line = fresh_line(pres);
    line.set_begin_arrowhead_style(LineArrowheadStyle::TRIANGLE);
    line.set_begin_arrowhead_width(LineArrowheadWidth::MEDIUM);
    line.set_begin_arrowhead_length(LineArrowheadLength::MEDIUM);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//a:ln/a:headEnd",
        {{"type", "triangle"}, {"w", "med"}, {"len", "med"}}))
        << "the arrowhead the caller asked for is not on the line";
}

TEST_F(LineFormatConformance, AnEndArrowheadReachesTheFile) {
    Presentation pres;
    auto& line = fresh_line(pres);
    line.set_end_arrowhead_style(LineArrowheadStyle::STEALTH);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:tailEnd",
                                           {{"type", "stealth"}}));
}

TEST_F(LineFormatConformance, TheCapStyleReachesTheFile) {
    Presentation pres;
    fresh_line(pres).set_cap_style(LineCapStyle::ROUND);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:spPr/a:ln",
                                           {{"cap", "rnd"}}));
}

TEST_F(LineFormatConformance, TheCompoundStyleReachesTheFile) {
    Presentation pres;
    fresh_line(pres).set_style(LineStyle::THIN_THICK);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:spPr/a:ln",
                                           {{"cmpd", "thinThick"}}));
}

TEST_F(LineFormatConformance, TheLineAlignmentReachesTheFile) {
    Presentation pres;
    fresh_line(pres).set_alignment(LineAlignment::CENTER);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:spPr/a:ln",
                                           {{"algn", "ctr"}}));
}

TEST_F(LineFormatConformance, TheJoinStyleReachesTheFile) {
    Presentation pres;
    fresh_line(pres).set_join_style(LineJoinStyle::ROUND);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:round"));
}

/// Child order inside `<a:ln>` is a sequence, not a set: fill, then dash, then
/// join, then the two ends.
TEST_F(LineFormatConformance, LineChildrenAreWrittenInSchemaOrder) {
    Presentation pres;
    auto& line = fresh_line(pres);
    line.set_dash_style(LineDashStyle::DASH_DOT);
    line.set_join_style(LineJoinStyle::ROUND);
    line.set_begin_arrowhead_style(LineArrowheadStyle::TRIANGLE);
    line.set_end_arrowhead_style(LineArrowheadStyle::NONE);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ChildOrderIs(
        pkg, kSlide, "//p:spPr/a:ln",
        {"a:solidFill", "a:prstDash", "a:round", "a:headEnd", "a:tailEnd"}));
}

/// A deck opened from a file takes the XML-backed path, where the shape's
/// `<a:ln>` already exists. None of `LineFormat`'s setters touched it: they
/// were defined inline in the header and only ever assigned a member, so on a
/// loaded deck every line property was accepted, read back, and dropped.
TEST_F(LineFormatConformance, LinePropertiesSetOnALoadedDeckReachTheFile) {
    Presentation pres;
    pres.slides()[0].shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200,
                                             100);
    auto first = save(pres, "plain.pptx");

    Presentation loaded(first.string());
    auto& line = loaded.slides()[0].shapes()[0].line_format();
    line.set_width(6); // 6 pt -> 76200 EMU
    line.set_dash_style(LineDashStyle::DASH_DOT);
    line.set_cap_style(LineCapStyle::ROUND);
    line.set_begin_arrowhead_style(LineArrowheadStyle::TRIANGLE);

    conformance::Package pkg(save_to(loaded, path_for("outlined.pptx")));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//p:spPr/a:ln",
                                           {{"w", "76200"}, {"cap", "rnd"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:prstDash",
                                           {{"val", "dashDot"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:ln/a:headEnd",
                                           {{"type", "triangle"}}));
}

} // namespace
