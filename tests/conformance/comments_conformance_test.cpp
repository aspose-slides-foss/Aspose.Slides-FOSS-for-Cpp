// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file comments_conformance_test.cpp
/// Comments in the package: how many relationships, and whether a reply is a
/// reply once it is written down.

#include <chrono>
#include <string>

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

/// A reply is modelled in the API and reported back in memory. The README
/// advertises threaded comments, so a reply has to survive being written down:
/// modern threading is a `ppt/threadedComments/` part relating replies to
/// their parent, and nothing else in the format expresses a thread.
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
    EXPECT_FALSE(pkg.entries_matching("^ppt/threadedComments/").empty())
        << "the package carries two independent flat comments; the reply "
           "relationship the caller expressed is not in the file";
}

} // namespace
