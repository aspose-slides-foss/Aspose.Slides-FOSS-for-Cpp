// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file comments_test.cpp
/// Integration tests for Comments: authors, comments CRUD, slide comments.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Helper to create a deterministic time point.
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

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class CommentsIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("comments_integration_test_" +
                    std::to_string(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()));
        std::filesystem::create_directories(tmp_dir_);
    }

    void TearDown() override {
        std::filesystem::remove_all(tmp_dir_);
    }

    /// Saves a presentation to a temp file and reopens from that file.
    Presentation save_and_reopen(Presentation& pres) {
        auto path = (tmp_dir_ / "roundtrip.pptx").string();
        pres.save(path, SaveFormat::PPTX);
        return Presentation(path);
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(CommentsIntegrationTest, AddAuthor) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    EXPECT_EQ(author.name(), "Alice");
    EXPECT_EQ(author.initials(), "A");
    EXPECT_EQ(pres.comment_authors().size(), 1);

    // Round-trip: save, close, reopen.
    auto pres2 = save_and_reopen(pres);
    ASSERT_EQ(pres2.comment_authors().size(), 1);
    EXPECT_EQ(pres2.comment_authors()[0].name(), "Alice");
    EXPECT_EQ(pres2.comment_authors()[0].initials(), "A");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(CommentsIntegrationTest, AddComment) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = make_time(2026, 1, 15, 12, 0, 0);
    auto& comment =
        author.comments().add_comment("Review note", slide, PointF(2.0f, 3.0f), now);
    EXPECT_EQ(comment.text(), "Review note");
    EXPECT_EQ(comment.author()->name(), "Alice");

    // Round-trip: save, close, reopen.
    auto pres2 = save_and_reopen(pres);
    auto& a2 = pres2.comment_authors()[0];
    ASSERT_EQ(a2.comments().size(), 1);
    auto& c = a2.comments()[0];
    EXPECT_EQ(c.text(), "Review note");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST(CommentsIntegrationTestNoFixture, MultipleAuthors) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    EXPECT_EQ(pres.comment_authors().size(), 2);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST(CommentsIntegrationTestNoFixture, GetSlideComments) {
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

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(CommentsIntegrationTest, RemoveComment) {
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

    // Round-trip: save, close, reopen.
    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.comment_authors()[0].comments().size(), 2);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST(CommentsIntegrationTestNoFixture, InsertComment) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("First", slide, PointF(1, 1), now);
    author.comments().add_comment("Third", slide, PointF(1, 3), now);
    author.comments().insert_comment(1, "Second", slide, PointF(1, 2), now);

    ASSERT_EQ(author.comments().size(), 3);
    EXPECT_EQ(author.comments()[1].text(), "Second");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST(CommentsIntegrationTestNoFixture, ClearComments) {
    Presentation pres;
    auto& author = pres.comment_authors().add_author("Alice", "A");
    auto& slide = pres.slides()[0];
    auto now = std::chrono::system_clock::now();

    author.comments().add_comment("C1", slide, PointF(1, 1), now);
    author.comments().add_comment("C2", slide, PointF(2, 2), now);
    author.comments().clear();
    EXPECT_EQ(author.comments().size(), 0);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(CommentsIntegrationTest, RemoveAuthor) {
    Presentation pres;
    pres.comment_authors().add_author("Alice", "A");
    pres.comment_authors().add_author("Bob", "B");
    pres.comment_authors().remove(pres.comment_authors()[0]);
    ASSERT_EQ(pres.comment_authors().size(), 1);

    // Round-trip: save, close, reopen.
    auto pres2 = save_and_reopen(pres);
    ASSERT_EQ(pres2.comment_authors().size(), 1);
    EXPECT_EQ(pres2.comment_authors()[0].name(), "Bob");
}

} // namespace
