// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file comments_conformance_test.cpp
/// Comments in the package: how many relationships, whether a reply is a
/// reply once it is written down, and where a comment is placed.

#include <chrono>
#include <cmath>
#include <filesystem>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

std::chrono::system_clock::time_point fixed_time() {
    std::tm tm{};
    tm.tm_year = 126; // 2026
    tm.tm_mon = 0;
    tm.tm_mday = 15;
    tm.tm_hour = 12;
    tm.tm_isdst = -1;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

class CommentsConformance : public conformance::SavedDeckTest {
protected:
    /// Writes a deck carrying one comment and returns the path.
    std::filesystem::path make_commented_deck(std::string_view name) {
        Presentation pres;
        auto& author = pres.comment_authors().add_author("Alice", "A");
        author.comments().add_comment("Review note", pres.slides()[0],
                                      PointF(2.0f, 3.0f), fixed_time());
        return save(pres, name);
    }

    /// Relationships of the given type declared by slide 1.
    std::size_t slide_relationships_of_type(const conformance::Package& pkg,
                                            std::string_view type_suffix) {
        std::size_t count = 0;
        const auto& rels = pkg.xml("ppt/slides/_rels/slide1.xml.rels");
        for (auto rel : rels.child("Relationships").children("Relationship")) {
            std::string type = rel.attribute("Type").value();
            if (type.size() >= type_suffix.size() &&
                type.compare(type.size() - type_suffix.size(),
                             type_suffix.size(), type_suffix) == 0)
                ++count;
        }
        return count;
    }
};

/// A slide may carry at most one comments part. Re-saving a deck that already
/// has comments must reuse the relationship it already has, not add a second
/// one: two comments relationships on one slide is a package PowerPoint
/// refuses outright.
TEST_F(CommentsConformance, ResavingACommentedDeckKeepsOneCommentsRelationship) {
    auto first = make_commented_deck("first.pptx");

    Presentation reloaded(first.string());
    auto second = save_to(reloaded, path_for("second.pptx"));

    conformance::Package pkg(second);
    EXPECT_EQ(slide_relationships_of_type(pkg, "/relationships/comments"), 1u)
        << "a slide with more than one comments relationship is refused by "
           "PowerPoint and by the Open XML SDK";
}

/// The first save is already correct; this pins that so the re-save fix cannot
/// be made by breaking the first write instead.
TEST_F(CommentsConformance, AFreshCommentedDeckHasOneCommentsRelationship) {
    conformance::Package pkg(make_commented_deck("first.pptx"));
    EXPECT_EQ(slide_relationships_of_type(pkg, "/relationships/comments"), 1u);
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

/// Re-saving must also not accumulate comment parts.
TEST_F(CommentsConformance, ResavingACommentedDeckDoesNotDuplicateTheComment) {
    auto first = make_commented_deck("first.pptx");
    Presentation reloaded(first.string());
    auto second = save_to(reloaded, path_for("second.pptx"));

    conformance::Package pkg(second);
    EXPECT_EQ(pkg.entries_matching("^ppt/comments/").size(), 1u);
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

/// A reply is modelled in the API and reported back in memory, and the README
/// says replies are written into the classic comment list, so a reply has to
/// survive being written down.
///
/// `CT_Comment` has no attribute for a parent. A thread on a classic comment
/// is expressed in the extension list, under the `p:ext` whose `@uri` is
/// `{C676402C-5697-4E1C-873F-D02D1690AC5C}`: a `<p15:threadingInfo>` holding a
/// `<p15:parentCm>` that names the parent by author and index. A `parentCmId`
/// attribute on `p:cm` is not in the schema and no consumer reads it.
///
/// If the project instead decides not to implement threading, the honest
/// change is to drop the claim from the README and make `set_parent_comment`
/// say it is an in-memory convenience — and then to replace this test with one
/// asserting that. It must not be weakened into asserting that the reply is
/// silently discarded.
TEST_F(CommentsConformance, AReplyToACommentIsWrittenAsAThread) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& parent = author.comments().add_comment(
        "Review note", pres.slides()[0], PointF(2.0f, 3.0f), fixed_time());
    auto& reply = author.comments().add_comment(
        "Agreed", pres.slides()[0], PointF(2.0f, 3.5f), fixed_time());
    reply.set_parent_comment(&parent);

    auto pkg = save_and_inspect(pres);
    const auto& xml = pkg.xml("ppt/comments/slide1.xml");

    // The reply names its parent, and the parent names nobody.
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/comments/slide1.xml",
                                        "//p15:parentCm"),
              1u)
        << "the package carries two independent flat comments; the reply "
           "relationship the caller expressed is not in the file";

    auto parent_cm = xml.select_node("//p15:parentCm").node();
    ASSERT_TRUE(parent_cm);
    EXPECT_STREQ(parent_cm.attribute("idx").value(), "1");

    // p:cm has no parentCmId attribute in any version of the schema.
    for (auto cm : xml.select_nodes("//p:cm")) {
        EXPECT_FALSE(cm.node().attribute("parentCmId"))
            << "parentCmId is not a declared attribute of p:cm";
    }
}

/// Re-saving a deck that was opened from a file must keep the thread. The
/// reader has to understand the extension the writer produces, or one
/// round trip flattens every reply back into a top-level comment.
TEST_F(CommentsConformance, AThreadSurvivesBeingReopenedAndSavedAgain) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& parent = author.comments().add_comment(
        "Review note", pres.slides()[0], PointF(2.0f, 3.0f), fixed_time());
    auto& reply = author.comments().add_comment(
        "Agreed", pres.slides()[0], PointF(2.0f, 3.5f), fixed_time());
    reply.set_parent_comment(&parent);
    auto first = save(pres, "first.pptx");

    Presentation reloaded(first.string());
    conformance::Package pkg(save_to(reloaded, path_for("second.pptx")));

    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/comments/slide1.xml",
                                        "//p15:parentCm"),
              1u);
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

// ---------------------------------------------------------------------------
// Where a comment is placed
// ---------------------------------------------------------------------------
//
// The schema types `p:cm/p:pos` as a point in EMU, but PowerPoint writes and
// reads it in its own unit, an eighth of a point (576 to the inch): a comment
// PowerPoint places 10 pt from the top-left corner is saved as
// `<p:pos x="80" y="80"/>`. A position written in EMU is 1587.5 times too large
// and puts the comment far outside the slide.
//
// A comment's position in this API is in centimetres from the top-left corner
// of the slide; that is what the library has always converted from.

/// PowerPoint's comment-position units per centimetre.
constexpr double kPosUnitsPerCm = 576.0 / 2.54;

/// EMU per comment-position unit: 12 700 EMU per point, eight units a point.
constexpr double kEmuPerPosUnit = 12700.0 / 8.0;

/// PowerPoint's own deck: one comment at 10 pt by 10 pt and a reply to it at
/// 10 pt by 22 pt, in the markup PowerPoint writes. See make_fixtures.py.
std::string powerpoint_comment_fixture() {
    return (conformance::test_data_dir() / "powerpoint_comment_reply.pptx")
        .string();
}

/// The comments part slide 1 points at, resolved through its relationships.
std::string comments_part_of_slide1(const conformance::Package& pkg) {
    const auto& rels = pkg.xml("ppt/slides/_rels/slide1.xml.rels");
    for (auto rel : rels.child("Relationships").children("Relationship")) {
        std::string type = rel.attribute("Type").value();
        const std::string suffix = "/relationships/comments";
        if (type.size() < suffix.size() ||
            type.compare(type.size() - suffix.size(), suffix.size(), suffix) != 0)
            continue;
        std::string target = rel.attribute("Target").value();
        if (target.rfind("../", 0) == 0) return "ppt/" + target.substr(3);
        return "ppt/slides/" + target;
    }
    return {};
}

/// The `p:cm` whose text is `text`, or an empty node.
pugi::xml_node comment_with_text(const conformance::Package& pkg,
                                 const std::string& part,
                                 std::string_view text) {
    for (auto cm : pkg.xml(part).select_nodes("//p:cm")) {
        if (std::string_view(cm.node().child("p:text").child_value()) == text)
            return cm.node();
    }
    return {};
}

/// One inch across and two down must be written as PowerPoint writes 72 pt
/// and 144 pt.
TEST_F(CommentsConformance, ACommentIsWrittenInTheUnitPowerPointReads) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    author.comments().add_comment("One inch in", pres.slides()[0],
                                  PointF(2.54f, 5.08f), fixed_time());

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/comments/slide1.xml",
                                           "//p:cm/p:pos",
                                           {{"x", "576"}, {"y", "1152"}}))
        << "p:pos is in eighths of a point; a value in EMU places the comment "
           "1587.5 times further from the corner, off the slide";
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

/// Every position on the slide must be written as a position on the slide,
/// rounded to PowerPoint's unit.
TEST_F(CommentsConformance, ACommentPlacedOnTheSlideIsWrittenOnTheSlide) {
    // The new-deck slide is 25.4 cm by 19.05 cm; the last point is its far corner.
    const PointF positions[] = {{0.0f, 0.0f},   {1.0f, 1.0f},
                                {2.0f, 3.0f},   {12.7f, 9.525f},
                                {24.0f, 18.0f}, {25.4f, 19.05f}};
    int n = 0;
    for (const auto& at : positions) {
        SCOPED_TRACE(::testing::Message()
                     << "comment at (" << at.x << " cm, " << at.y << " cm)");
        Presentation pres;
        auto& author = pres.comment_authors().add_author("Alice", "A");
        author.comments().add_comment("Here", pres.slides()[0], at,
                                      fixed_time());
        auto pkg = save_and_inspect(pres, "at" + std::to_string(n++) + ".pptx");

        auto sld_sz = pkg.xml("ppt/presentation.xml")
                          .select_node("/p:presentation/p:sldSz")
                          .node();
        ASSERT_TRUE(sld_sz);
        const double width = sld_sz.attribute("cx").as_llong() / kEmuPerPosUnit;
        const double height = sld_sz.attribute("cy").as_llong() / kEmuPerPosUnit;

        auto pos = pkg.xml("ppt/comments/slide1.xml")
                       .select_node("//p:cm/p:pos")
                       .node();
        ASSERT_TRUE(pos);
        const long long x = pos.attribute("x").as_llong(-1);
        const long long y = pos.attribute("y").as_llong(-1);
        EXPECT_EQ(x, std::llround(at.x * kPosUnitsPerCm));
        EXPECT_EQ(y, std::llround(at.y * kPosUnitsPerCm));
        EXPECT_GE(x, 0);
        EXPECT_LE(x, std::llround(width)) << "off the right of the slide";
        EXPECT_GE(y, 0);
        EXPECT_LE(y, std::llround(height)) << "off the bottom of the slide";
    }
}

/// A comment PowerPoint placed must read back where PowerPoint shows it.
///
/// A reader test, so it goes through the API: the input is a deck this library
/// did not write, with PowerPoint's own `x="80" y="80"` for a comment it shows
/// at 10 pt by 10 pt, which is 10 / 72 x 2.54 cm.
TEST_F(CommentsConformance, ACommentPowerPointPlacedReadsBackWherePowerPointShowsIt) {
    ASSERT_TRUE(std::filesystem::exists(powerpoint_comment_fixture()))
        << "missing fixture; regenerate with tests/conformance/make_fixtures.py";
    Presentation pres(powerpoint_comment_fixture());
    ASSERT_EQ(pres.comment_authors().size(), 1u);
    auto& comments = pres.comment_authors()[0].comments();
    ASSERT_EQ(comments.size(), 2u);

    const double ten_pt = 10.0 / 72.0 * 2.54;
    const double twenty_two_pt = 22.0 / 72.0 * 2.54;
    EXPECT_EQ(comments[0].text(), "Parent comment");
    EXPECT_NEAR(comments[0].position().x, ten_pt, 1e-4)
        << "PowerPoint shows this comment 10 pt from the left of the slide";
    EXPECT_NEAR(comments[0].position().y, ten_pt, 1e-4)
        << "PowerPoint shows this comment 10 pt from the top of the slide";
    EXPECT_EQ(comments[1].text(), "Reply to parent");
    EXPECT_NEAR(comments[1].position().x, ten_pt, 1e-4);
    EXPECT_NEAR(comments[1].position().y, twenty_two_pt, 1e-4);

    // Regression guard: PowerPoint's reply is read as a reply.
    EXPECT_EQ(comments[1].parent_comment(), &comments[0]);
}

/// Regression guard: opening PowerPoint's deck and saving it must leave its
/// comments where PowerPoint put them, and its reply a reply. A reader and a
/// writer that disagree about the unit would move every comment on each save.
TEST_F(CommentsConformance, ACommentPowerPointPlacedStaysWherePowerPointPutIt) {
    Presentation pres(powerpoint_comment_fixture());
    conformance::Package pkg(save_to(pres, path_for("resaved.pptx")));

    auto part = comments_part_of_slide1(pkg);
    ASSERT_FALSE(part.empty()) << "slide 1 lost its comments relationship";
    auto parent = comment_with_text(pkg, part, "Parent comment");
    auto reply = comment_with_text(pkg, part, "Reply to parent");
    ASSERT_TRUE(parent);
    ASSERT_TRUE(reply);

    EXPECT_STREQ(parent.child("p:pos").attribute("x").value(), "80");
    EXPECT_STREQ(parent.child("p:pos").attribute("y").value(), "80");
    EXPECT_STREQ(reply.child("p:pos").attribute("x").value(), "80");
    EXPECT_STREQ(reply.child("p:pos").attribute("y").value(), "176");

    auto parent_cm = reply.select_node(".//p15:parentCm").node();
    ASSERT_TRUE(parent_cm) << "the reply was saved as a top-level comment";
    EXPECT_STREQ(parent_cm.attribute("authorId").value(),
                 parent.attribute("authorId").value());
    EXPECT_STREQ(parent_cm.attribute("idx").value(),
                 parent.attribute("idx").value());
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

} // namespace
