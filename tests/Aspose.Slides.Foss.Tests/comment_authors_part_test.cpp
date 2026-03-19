// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/comment_authors_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Minimal valid ppt/commentAuthors.xml for testing.
static const std::string kSampleAuthorsXml =
    R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:cmAuthorLst xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cmAuthor id="0" name="Alice" initials="A" lastIdx="3" clrIdx="0"/>
  <p:cmAuthor id="1" name="Bob" initials="B" lastIdx="5" clrIdx="1"/>
</p:cmAuthorLst>)";

class CommentAuthorsPartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_authors_xml(const std::string& xml) {
        package_.set_part(pptx::kCommentAuthorsPartName, xml);
    }
};

// ---------------------------------------------------------------------------
// Parsing tests
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, ParseExistingAuthors) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    auto authors = part.get_authors();
    ASSERT_EQ(authors.size(), 2u);
    EXPECT_EQ(authors[0].id(), 0);
    EXPECT_EQ(authors[0].name(), "Alice");
    EXPECT_EQ(authors[0].initials(), "A");
    EXPECT_EQ(authors[0].last_idx(), 3);
    EXPECT_EQ(authors[0].clr_idx(), 0);
    EXPECT_EQ(authors[1].id(), 1);
    EXPECT_EQ(authors[1].name(), "Bob");
    EXPECT_EQ(authors[1].initials(), "B");
    EXPECT_EQ(authors[1].last_idx(), 5);
    EXPECT_EQ(authors[1].clr_idx(), 1);
}

TEST_F(CommentAuthorsPartTest, EmptyPackageCreatesEmptyRoot) {
    pptx::CommentAuthorsPart part(package_);
    auto authors = part.get_authors();
    EXPECT_TRUE(authors.empty());
}

// ---------------------------------------------------------------------------
// find_author_by_id
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, FindAuthorById) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    auto alice = part.find_author_by_id(0);
    ASSERT_TRUE(alice.has_value());
    EXPECT_EQ(alice->name(), "Alice");

    auto bob = part.find_author_by_id(1);
    ASSERT_TRUE(bob.has_value());
    EXPECT_EQ(bob->name(), "Bob");

    auto missing = part.find_author_by_id(99);
    EXPECT_FALSE(missing.has_value());
}

// ---------------------------------------------------------------------------
// add_author
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, AddAuthor) {
    pptx::CommentAuthorsPart part(package_);

    auto a = part.add_author("Charlie", "C");
    EXPECT_EQ(a.id(), 0);
    EXPECT_EQ(a.name(), "Charlie");
    EXPECT_EQ(a.initials(), "C");
    EXPECT_EQ(a.last_idx(), 0);
    EXPECT_EQ(a.clr_idx(), 0);

    auto b = part.add_author("Diana", "D");
    EXPECT_EQ(b.id(), 1);
    EXPECT_EQ(b.clr_idx(), 1);

    EXPECT_EQ(part.get_authors().size(), 2u);
}

TEST_F(CommentAuthorsPartTest, AddAuthorColorCycles) {
    pptx::CommentAuthorsPart part(package_);
    // Add 11 authors — the 11th should have clrIdx 0 (cycle).
    for (int i = 0; i < 11; ++i) {
        part.add_author("Author" + std::to_string(i), "X");
    }
    auto authors = part.get_authors();
    ASSERT_EQ(authors.size(), 11u);
    EXPECT_EQ(authors[10].clr_idx(), 0); // 10 % 10 == 0
}

// ---------------------------------------------------------------------------
// remove_author
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, RemoveAuthor) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    part.remove_author(0);
    EXPECT_EQ(part.get_authors().size(), 1u);
    EXPECT_FALSE(part.find_author_by_id(0).has_value());
    EXPECT_TRUE(part.find_author_by_id(1).has_value());
}

TEST_F(CommentAuthorsPartTest, RemoveNonexistentAuthorIsNoOp) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    part.remove_author(99);
    EXPECT_EQ(part.get_authors().size(), 2u);
}

// ---------------------------------------------------------------------------
// clear
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, Clear) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    part.clear();
    EXPECT_TRUE(part.get_authors().empty());
}

// ---------------------------------------------------------------------------
// next_comment_idx
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, NextCommentIdxUsesGlobalMax) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);
    // Alice lastIdx=3, Bob lastIdx=5. Global max = 5.

    int32_t idx = part.next_comment_idx(0); // target: Alice
    EXPECT_EQ(idx, 6); // 5 + 1

    // Alice's lastIdx should now be 6.
    auto alice = part.find_author_by_id(0);
    ASSERT_TRUE(alice.has_value());
    EXPECT_EQ(alice->last_idx(), 6);

    // Bob's lastIdx should be unchanged.
    auto bob = part.find_author_by_id(1);
    ASSERT_TRUE(bob.has_value());
    EXPECT_EQ(bob->last_idx(), 5);
}

TEST_F(CommentAuthorsPartTest, NextCommentIdxSequential) {
    pptx::CommentAuthorsPart part(package_);
    auto a = part.add_author("Author", "A");

    EXPECT_EQ(part.next_comment_idx(0), 1);
    EXPECT_EQ(part.next_comment_idx(0), 2);
    EXPECT_EQ(part.next_comment_idx(0), 3);
}

TEST_F(CommentAuthorsPartTest, NextCommentIdxNonexistentAuthor) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    // Still returns the next index even for non-existent author.
    int32_t idx = part.next_comment_idx(99);
    EXPECT_EQ(idx, 6);
}

// ---------------------------------------------------------------------------
// AuthorData setters
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, AuthorDataSetters) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);

    auto alice = part.find_author_by_id(0);
    ASSERT_TRUE(alice.has_value());

    alice->set_name("Alicia");
    alice->set_initials("AL");
    alice->set_last_idx(10);

    // Re-fetch and verify.
    auto alicia = part.find_author_by_id(0);
    ASSERT_TRUE(alicia.has_value());
    EXPECT_EQ(alicia->name(), "Alicia");
    EXPECT_EQ(alicia->initials(), "AL");
    EXPECT_EQ(alicia->last_idx(), 10);
}

// ---------------------------------------------------------------------------
// Save / round-trip
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, SaveAndReload) {
    pptx::CommentAuthorsPart part(package_);
    part.add_author("Eve", "E");
    part.add_author("Frank", "F");
    part.save();

    pptx::CommentAuthorsPart reloaded(package_);
    auto authors = reloaded.get_authors();
    ASSERT_EQ(authors.size(), 2u);
    EXPECT_EQ(authors[0].name(), "Eve");
    EXPECT_EQ(authors[1].name(), "Frank");
}

TEST_F(CommentAuthorsPartTest, SaveExistingRoundTrip) {
    set_authors_xml(kSampleAuthorsXml);
    pptx::CommentAuthorsPart part(package_);
    part.add_author("Charlie", "C");
    part.save();

    pptx::CommentAuthorsPart reloaded(package_);
    EXPECT_EQ(reloaded.get_authors().size(), 3u);
}

// ---------------------------------------------------------------------------
// ensure_registered
// ---------------------------------------------------------------------------

TEST_F(CommentAuthorsPartTest, EnsureRegisteredAddsContentTypeAndRel) {
    pptx::CommentAuthorsPart::ensure_registered(
        package_, "ppt/presentation.xml");

    // Verify content type was added.
    opc::ContentTypesManager ct(package_);
    EXPECT_EQ(ct.get_content_type(pptx::kCommentAuthorsPartName),
              opc::content_types::kCommentAuthors);

    // Verify relationship was added.
    opc::RelationshipsManager rels(package_, "ppt/presentation.xml");
    auto rel_list = rels.get_relationships_by_type(
        opc::rel_types::kCommentAuthors);
    ASSERT_EQ(rel_list.size(), 1u);
    EXPECT_EQ(rel_list[0].target, "commentAuthors.xml");
}

TEST_F(CommentAuthorsPartTest, EnsureRegisteredIdempotent) {
    pptx::CommentAuthorsPart::ensure_registered(
        package_, "ppt/presentation.xml");
    pptx::CommentAuthorsPart::ensure_registered(
        package_, "ppt/presentation.xml");

    opc::RelationshipsManager rels(package_, "ppt/presentation.xml");
    auto rel_list = rels.get_relationships_by_type(
        opc::rel_types::kCommentAuthors);
    EXPECT_EQ(rel_list.size(), 1u);
}
