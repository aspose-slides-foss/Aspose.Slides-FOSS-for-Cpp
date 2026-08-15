// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/comments_part.h>

using namespace Aspose::Slides::Foss::Internal;
using namespace Aspose::Slides::Foss::Internal::pptx;

namespace {

/// Helper: create a minimal empty comments XML and store it in the package.
void seed_empty_comments(opc::InMemoryOpcPackage& pkg,
                         const std::string& part_name) {
    std::string xml =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<p:cmLst xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main"/>)";
    std::vector<uint8_t> data(xml.begin(), xml.end());
    pkg.set_part(part_name, std::move(data));
}

/// Helper: create a comments XML with two pre-existing comments.
void seed_two_comments(opc::InMemoryOpcPackage& pkg,
                       const std::string& part_name) {
    std::string xml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:cmLst xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cm authorId="0" dt="2024-03-15T10:30:00.000" idx="1">
    <p:pos x="360000" y="720000"/>
    <p:text>First comment</p:text>
  </p:cm>
  <p:cm authorId="1" dt="2024-03-15T11:00:00.000" idx="2">
    <p:pos x="0" y="0"/>
    <p:text>Second comment</p:text>
  </p:cm>
</p:cmLst>)";
    std::vector<uint8_t> data(xml.begin(), xml.end());
    pkg.set_part(part_name, std::move(data));
}

} // namespace

// ---------------------------------------------------------------------------
// dt_to_str / str_to_dt
// ---------------------------------------------------------------------------

TEST(CommentsPartHelperTest, DtToStrRoundTrip) {
    auto tp = str_to_dt("2024-03-15T10:30:00.123");
    ASSERT_TRUE(tp.has_value());
    auto s = dt_to_str(*tp);
    EXPECT_EQ(s, "2024-03-15T10:30:00.123");
}

TEST(CommentsPartHelperTest, StrToDtWithoutMs) {
    auto tp = str_to_dt("2024-03-15T10:30:00");
    ASSERT_TRUE(tp.has_value());
    auto s = dt_to_str(*tp);
    EXPECT_EQ(s, "2024-03-15T10:30:00.000");
}

TEST(CommentsPartHelperTest, StrToDtDateOnly) {
    auto tp = str_to_dt("2024-03-15");
    ASSERT_TRUE(tp.has_value());
    auto s = dt_to_str(*tp);
    EXPECT_EQ(s, "2024-03-15T00:00:00.000");
}

TEST(CommentsPartHelperTest, StrToDtEmpty) {
    EXPECT_FALSE(str_to_dt("").has_value());
}

// ---------------------------------------------------------------------------
// CommentData
// ---------------------------------------------------------------------------

TEST(CommentDataTest, ReadAttributes) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    ASSERT_EQ(comments.size(), 2);

    EXPECT_EQ(comments[0].author_id(), 0);
    EXPECT_EQ(comments[0].idx(), 1);
    EXPECT_EQ(comments[0].dt_str(), "2024-03-15T10:30:00.000");
    EXPECT_EQ(comments[0].text(), "First comment");
    EXPECT_DOUBLE_EQ(comments[0].pos_x(), 1.0);  // 360000 / 360000
    EXPECT_DOUBLE_EQ(comments[0].pos_y(), 2.0);  // 720000 / 360000
    EXPECT_FALSE(comments[0].parent_comment().has_value());

    EXPECT_EQ(comments[1].author_id(), 1);
    EXPECT_EQ(comments[1].idx(), 2);
    EXPECT_EQ(comments[1].text(), "Second comment");
}

TEST(CommentDataTest, SetText) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    comments[0].set_text("Updated text");
    EXPECT_EQ(comments[0].text(), "Updated text");
}

TEST(CommentDataTest, SetDtStr) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    comments[0].set_dt_str("2025-01-01T00:00:00.000");
    EXPECT_EQ(comments[0].dt_str(), "2025-01-01T00:00:00.000");
}

TEST(CommentDataTest, SetParentComment) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    EXPECT_FALSE(comments[0].parent_comment().has_value());

    comments[0].set_parent_comment(ParentCommentRef{1, 42});
    ASSERT_TRUE(comments[0].parent_comment().has_value());
    EXPECT_EQ(comments[0].parent_comment()->author_id, 1);
    EXPECT_EQ(comments[0].parent_comment()->idx, 42);

    comments[0].set_parent_comment(std::nullopt);
    EXPECT_FALSE(comments[0].parent_comment().has_value());
}

TEST(CommentDataTest, SetPosition) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    comments[0].set_pos_x(5.5);
    comments[0].set_pos_y(3.25);
    EXPECT_DOUBLE_EQ(comments[0].pos_x(), 5.5);
    EXPECT_DOUBLE_EQ(comments[0].pos_y(), 3.25);
}

// ---------------------------------------------------------------------------
// CommentsPart - basic operations
// ---------------------------------------------------------------------------

TEST(CommentsPartTest, ConstructAndCount) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    EXPECT_EQ(part.count(), 2);
    EXPECT_FALSE(part.is_empty());
    EXPECT_EQ(part.part_name(), "ppt/comments/slide1.xml");
}

TEST(CommentsPartTest, ConstructThrowsOnMissing) {
    opc::InMemoryOpcPackage pkg;
    EXPECT_THROW(CommentsPart(pkg, "nonexistent.xml"), std::runtime_error);
}

TEST(CommentsPartTest, GetCommentsByAuthor) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto a0 = part.get_comments_by_author(0);
    ASSERT_EQ(a0.size(), 1);
    EXPECT_EQ(a0[0].text(), "First comment");

    auto a1 = part.get_comments_by_author(1);
    ASSERT_EQ(a1.size(), 1);
    EXPECT_EQ(a1[0].text(), "Second comment");

    auto a99 = part.get_comments_by_author(99);
    EXPECT_TRUE(a99.empty());
}

TEST(CommentsPartTest, FindCommentByIdx) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto found = part.find_comment_by_idx(0, 1);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->text(), "First comment");

    EXPECT_FALSE(part.find_comment_by_idx(0, 999).has_value());
}

TEST(CommentsPartTest, FindCommentByIdxAll) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto found = part.find_comment_by_idx_all(2);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->text(), "Second comment");

    EXPECT_FALSE(part.find_comment_by_idx_all(999).has_value());
}

TEST(CommentsPartTest, AddComment) {
    opc::InMemoryOpcPackage pkg;
    seed_empty_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    EXPECT_TRUE(part.is_empty());

    auto cd = part.add_comment(0, 1, "New comment", 2.5, 3.0,
                               "2024-06-01T12:00:00.000");
    EXPECT_EQ(part.count(), 1);
    EXPECT_EQ(cd.text(), "New comment");
    EXPECT_EQ(cd.author_id(), 0);
    EXPECT_EQ(cd.idx(), 1);
    EXPECT_DOUBLE_EQ(cd.pos_x(), 2.5);
    EXPECT_DOUBLE_EQ(cd.pos_y(), 3.0);
    EXPECT_FALSE(cd.parent_comment().has_value());
}

TEST(CommentsPartTest, AddCommentWithParent) {
    opc::InMemoryOpcPackage pkg;
    seed_empty_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.add_comment(0, 1, "Parent", 1.0, 1.0, "2024-06-01T12:00:00.000");
    auto reply = part.add_comment(0, 2, "Reply", 1.0, 1.0,
                                  "2024-06-01T12:01:00.000",
                                  ParentCommentRef{0, 1});
    EXPECT_EQ(part.count(), 2);
    ASSERT_TRUE(reply.parent_comment().has_value());
    EXPECT_EQ(reply.parent_comment()->author_id, 0);
    EXPECT_EQ(reply.parent_comment()->idx, 1);
}

TEST(CommentsPartTest, InsertComment) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.insert_comment(1, 0, 3, "Inserted", 0.0, 0.0,
                        "2024-06-01T12:00:00.000");
    EXPECT_EQ(part.count(), 3);

    auto all = part.get_comments();
    EXPECT_EQ(all[0].text(), "First comment");
    EXPECT_EQ(all[1].text(), "Inserted");
    EXPECT_EQ(all[2].text(), "Second comment");
}

TEST(CommentsPartTest, InsertCommentAtEnd) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.insert_comment(99, 0, 3, "Appended", 0.0, 0.0,
                        "2024-06-01T12:00:00.000");
    EXPECT_EQ(part.count(), 3);

    auto all = part.get_comments();
    EXPECT_EQ(all[2].text(), "Appended");
}

TEST(CommentsPartTest, RemoveComment) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.remove_comment(0, 1);
    EXPECT_EQ(part.count(), 1);
    EXPECT_EQ(part.get_comments()[0].text(), "Second comment");
}

TEST(CommentsPartTest, RemoveCommentElem) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    auto comments = part.get_comments();
    part.remove_comment_elem(comments[0].node());
    EXPECT_EQ(part.count(), 1);
    EXPECT_EQ(part.get_comments()[0].text(), "Second comment");
}

TEST(CommentsPartTest, RemoveCommentsAt) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.remove_comments_at(0);
    EXPECT_EQ(part.count(), 1);
    EXPECT_EQ(part.get_comments()[0].text(), "Second comment");
}

TEST(CommentsPartTest, RemoveCommentsAtOutOfRange) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.remove_comments_at(99);  // no-op
    EXPECT_EQ(part.count(), 2);
}

TEST(CommentsPartTest, Clear) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.clear();
    EXPECT_TRUE(part.is_empty());
    EXPECT_EQ(part.count(), 0);
}

TEST(CommentsPartTest, Save) {
    opc::InMemoryOpcPackage pkg;
    seed_empty_comments(pkg, "ppt/comments/slide1.xml");
    CommentsPart part(pkg, "ppt/comments/slide1.xml");

    part.add_comment(0, 1, "Saved comment", 1.0, 2.0,
                     "2024-06-01T12:00:00.000");
    part.save();

    // Reload and verify
    CommentsPart reloaded(pkg, "ppt/comments/slide1.xml");
    EXPECT_EQ(reloaded.count(), 1);
    auto comments = reloaded.get_comments();
    EXPECT_EQ(comments[0].text(), "Saved comment");
    EXPECT_DOUBLE_EQ(comments[0].pos_x(), 1.0);
    EXPECT_DOUBLE_EQ(comments[0].pos_y(), 2.0);
}

// ---------------------------------------------------------------------------
// Static factory methods
// ---------------------------------------------------------------------------

TEST(CommentsPartTest, CreateForSlide) {
    opc::InMemoryOpcPackage pkg;
    auto part = CommentsPart::create_for_slide(pkg, "ppt/slides/slide1.xml");

    EXPECT_EQ(part.part_name(), "ppt/comments/slide1.xml");
    EXPECT_TRUE(part.is_empty());
    EXPECT_TRUE(pkg.has_part("ppt/comments/slide1.xml"));
}

TEST(CommentsPartTest, CreateForSlideUniqueName) {
    opc::InMemoryOpcPackage pkg;
    // Pre-create slide1 comments
    seed_empty_comments(pkg, "ppt/comments/slide1.xml");

    auto part = CommentsPart::create_for_slide(pkg, "ppt/slides/slide2.xml");
    EXPECT_EQ(part.part_name(), "ppt/comments/slide2.xml");
}

TEST(CommentsPartTest, LoadForSlide) {
    opc::InMemoryOpcPackage pkg;
    seed_two_comments(pkg, "ppt/comments/slide1.xml");

    // Set up the relationship from slide to comments
    opc::RelationshipsManager slide_rels(pkg, "ppt/slides/slide1.xml");
    slide_rels.add_relationship(opc::rel_types::kComments,
                                "../comments/slide1.xml");
    slide_rels.save();

    auto result = CommentsPart::load_for_slide(pkg, "ppt/slides/slide1.xml");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->count(), 2);
}

TEST(CommentsPartTest, LoadForSlideNotFound) {
    opc::InMemoryOpcPackage pkg;
    auto result = CommentsPart::load_for_slide(pkg, "ppt/slides/slide1.xml");
    EXPECT_FALSE(result.has_value());
}

TEST(CommentsPartTest, DeleteForSlide) {
    opc::InMemoryOpcPackage pkg;

    // Create comments part with relationship
    seed_two_comments(pkg, "ppt/comments/slide1.xml");
    opc::RelationshipsManager slide_rels(pkg, "ppt/slides/slide1.xml");
    slide_rels.add_relationship(opc::rel_types::kComments,
                                "../comments/slide1.xml");
    slide_rels.save();

    EXPECT_TRUE(pkg.has_part("ppt/comments/slide1.xml"));

    CommentsPart::delete_for_slide(pkg, "ppt/slides/slide1.xml");
    EXPECT_FALSE(pkg.has_part("ppt/comments/slide1.xml"));
}

// ---------------------------------------------------------------------------
// Path resolution helpers
// ---------------------------------------------------------------------------

TEST(CommentsPartTest, ResolveTargetRelative) {
    auto result = CommentsPart::resolve_target(
        "ppt/slides/slide1.xml", "../comments/slide1.xml");
    EXPECT_EQ(result, "ppt/comments/slide1.xml");
}

TEST(CommentsPartTest, ResolveTargetAbsolute) {
    auto result = CommentsPart::resolve_target(
        "ppt/slides/slide1.xml", "/ppt/comments/slide1.xml");
    EXPECT_EQ(result, "ppt/comments/slide1.xml");
}

TEST(CommentsPartTest, ResolveTargetSameDir) {
    auto result = CommentsPart::resolve_target(
        "ppt/slides/slide1.xml", "slide2.xml");
    EXPECT_EQ(result, "ppt/slides/slide2.xml");
}

TEST(CommentsPartTest, ComputeRelativeTargetDifferentDir) {
    auto result = CommentsPart::compute_relative_target(
        "ppt/slides/slide1.xml", "ppt/comments/slide1.xml");
    EXPECT_EQ(result, "../comments/slide1.xml");
}

TEST(CommentsPartTest, ComputeRelativeTargetSameDir) {
    auto result = CommentsPart::compute_relative_target(
        "ppt/slides/slide1.xml", "ppt/slides/slide2.xml");
    EXPECT_EQ(result, "slide2.xml");
}

TEST(CommentsPartTest, ComputeRelativeTargetDeep) {
    auto result = CommentsPart::compute_relative_target(
        "a/b/c/file1.xml", "a/d/e/file2.xml");
    EXPECT_EQ(result, "../../d/e/file2.xml");
}
