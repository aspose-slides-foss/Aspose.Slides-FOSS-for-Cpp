// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <chrono>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

// Helper to create a fixed time point for deterministic tests.
auto make_time(int year, int month, int day, int hour = 0, int min = 0,
               int sec = 0) {
    std::tm tm{};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    tm.tm_isdst = -1;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

} // namespace

TEST(CommentTest, AddAuthor) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    EXPECT_EQ(author.name(), "Alice");
    EXPECT_EQ(author.initials(), "A");
    EXPECT_EQ(pres.comment_authors().size(), 1);

    // Verify the author is accessible through the collection.
    EXPECT_EQ(pres.comment_authors()[0].name(), "Alice");
    EXPECT_EQ(pres.comment_authors()[0].initials(), "A");
}

TEST(CommentTest, AddComment) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = make_time(2026, 1, 15, 12, 0, 0);
    auto& comment =
        author.comments().add_comment("Review note", slide, PointF(2.0f, 3.0f), now);

    EXPECT_EQ(comment.text(), "Review note");
    EXPECT_EQ(comment.author()->name(), "Alice");
    EXPECT_EQ(comment.position(), PointF(2.0f, 3.0f));
    EXPECT_EQ(comment.created_time(), now);
    EXPECT_EQ(comment.slide(), &slide);

    // Verify accessible through collection.
    EXPECT_EQ(author.comments().size(), 1);
    EXPECT_EQ(author.comments()[0].text(), "Review note");
}

TEST(CommentTest, MultipleAuthors) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    EXPECT_EQ(pres.comment_authors().size(), 2);
}

TEST(CommentTest, GetSlideComments) {
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

TEST(CommentTest, RemoveComment) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("C1", slide, PointF(1, 1), now);
    author.comments().add_comment("C2", slide, PointF(2, 2), now);
    author.comments().add_comment("C3", slide, PointF(3, 3), now);
    ASSERT_EQ(author.comments().size(), 3);

    author.comments().remove_at(1);
    ASSERT_EQ(author.comments().size(), 2);
    EXPECT_EQ(author.comments()[0].text(), "C1");
    EXPECT_EQ(author.comments()[1].text(), "C3");
}

TEST(CommentTest, InsertComment) {
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

TEST(CommentTest, ClearComments) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("C1", slide, PointF(1, 1), now);
    author.comments().add_comment("C2", slide, PointF(2, 2), now);
    author.comments().clear();
    EXPECT_EQ(author.comments().size(), 0);
}

TEST(CommentTest, RemoveAuthor) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");

    pres.comment_authors().remove(pres.comment_authors()[0]);
    ASSERT_EQ(pres.comment_authors().size(), 1);
    EXPECT_EQ(pres.comment_authors()[0].name(), "Bob");
}

TEST(CommentTest, AuthorRemoveSelf) {
    Presentation pres;
    auto& alice = pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();
    alice.comments().add_comment("C1", slide, PointF(1, 1), now);
    alice.comments().add_comment("C2", slide, PointF(2, 2), now);

    alice.remove();
    ASSERT_EQ(pres.comment_authors().size(), 1);
    EXPECT_EQ(pres.comment_authors()[0].name(), "Bob");
}

// Additional: test Comment::remove() removes self and replies.
TEST(CommentTest, CommentRemoveWithReplies) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    auto& parent = author.comments().add_comment("Parent", slide, PointF(1, 1), now);
    auto& reply = author.comments().add_comment("Reply", slide, PointF(2, 2), now);
    reply.set_parent_comment(&parent);

    ASSERT_EQ(author.comments().size(), 2);
    parent.remove();
    EXPECT_EQ(author.comments().size(), 0);
}

TEST(CommentTest, ToArray) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");

    auto arr = pres.comment_authors().to_array();
    ASSERT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0]->name(), "Alice");
    EXPECT_EQ(arr[1]->name(), "Bob");
}

TEST(CommentTest, FindByName) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    pres.comment_authors().add_author("Alice", "A2");

    auto found = pres.comment_authors().find_by_name("Alice");
    ASSERT_EQ(found.size(), 2);
    EXPECT_EQ(found[0]->initials(), "A");
    EXPECT_EQ(found[1]->initials(), "A2");

    auto none = pres.comment_authors().find_by_name("Charlie");
    EXPECT_EQ(none.size(), 0);
}

TEST(CommentTest, FindByNameAndInitials) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Alice", "A2");
    pres.comment_authors().add_author("Bob", "B");

    auto found = pres.comment_authors().find_by_name_and_initials("Alice", "A2");
    ASSERT_EQ(found.size(), 1);
    EXPECT_EQ(found[0]->initials(), "A2");

    auto none = pres.comment_authors().find_by_name_and_initials("Alice", "X");
    EXPECT_EQ(none.size(), 0);
}

TEST(CommentTest, RemoveAt) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    pres.comment_authors().add_author("Charlie", "C");

    pres.comment_authors().remove_at(1);
    ASSERT_EQ(pres.comment_authors().size(), 2);
    EXPECT_EQ(pres.comment_authors()[0].name(), "Alice");
    EXPECT_EQ(pres.comment_authors()[1].name(), "Charlie");
}

TEST(CommentTest, ClearAuthors) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();
    pres.comment_authors()[0].comments().add_comment("C1", slide, PointF(1, 1), now);

    pres.comment_authors().clear();
    EXPECT_EQ(pres.comment_authors().size(), 0);
}

// Additional: test Comment text setter.
TEST(CommentTest, SetText) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    auto& comment = author.comments().add_comment("Original", slide, PointF(1, 1), now);
    comment.set_text("Updated");
    EXPECT_EQ(comment.text(), "Updated");
}

// Additional: test Comment position setter.
TEST(CommentTest, SetPosition) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    auto& comment = author.comments().add_comment("Test", slide, PointF(1, 1), now);
    comment.set_position(PointF(5, 10));
    EXPECT_EQ(comment.position(), PointF(5, 10));
}

TEST(CommentTest, ToArrayComments) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("C1", slide, PointF(1, 1), now);
    author.comments().add_comment("C2", slide, PointF(2, 2), now);
    author.comments().add_comment("C3", slide, PointF(3, 3), now);

    auto all = author.comments().to_array();
    ASSERT_EQ(all.size(), 3);
    EXPECT_EQ(all[0]->text(), "C1");
    EXPECT_EQ(all[1]->text(), "C2");
    EXPECT_EQ(all[2]->text(), "C3");

    // Ranged overload.
    auto sub = author.comments().to_array(1, 2);
    ASSERT_EQ(sub.size(), 2);
    EXPECT_EQ(sub[0]->text(), "C2");
    EXPECT_EQ(sub[1]->text(), "C3");
}

TEST(CommentTest, FindCommentByIdx) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    auto& c1 = author.comments().add_comment("First", slide, PointF(1, 1), now);
    auto& c2 = author.comments().add_comment("Second", slide, PointF(2, 2), now);

    auto* found = author.comments().find_comment_by_idx(c1.idx());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->text(), "First");

    found = author.comments().find_comment_by_idx(c2.idx());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->text(), "Second");

    // Non-existent idx returns nullptr.
    EXPECT_EQ(author.comments().find_comment_by_idx(999), nullptr);
}

TEST(CommentTest, RemoveByReference) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("C1", slide, PointF(1, 1), now);
    auto& c2 = author.comments().add_comment("C2", slide, PointF(2, 2), now);
    author.comments().add_comment("C3", slide, PointF(3, 3), now);
    ASSERT_EQ(author.comments().size(), 3);

    author.comments().remove(c2);
    ASSERT_EQ(author.comments().size(), 2);
    EXPECT_EQ(author.comments()[0].text(), "C1");
    EXPECT_EQ(author.comments()[1].text(), "C3");
}

// Additional: test parent_comment getter/setter.
TEST(CommentTest, ParentComment) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    auto& parent = author.comments().add_comment("Parent", slide, PointF(1, 1), now);
    auto& child = author.comments().add_comment("Child", slide, PointF(2, 2), now);

    EXPECT_EQ(child.parent_comment(), nullptr);
    child.set_parent_comment(&parent);
    EXPECT_EQ(child.parent_comment(), &parent);
    EXPECT_EQ(child.parent_comment()->text(), "Parent");

    child.set_parent_comment(nullptr);
    EXPECT_EQ(child.parent_comment(), nullptr);
}
