// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <chrono>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/i_comment_collection.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;
using namespace Aspose::Slides::Foss::Drawing;

namespace {

/// Fixture that provides a Presentation with one author and access to the
/// author's comment collection through the ICommentCollection interface.
class ICommentCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        author_ = &pres_.comment_authors().add_author("Alice", "A");
        slide_ = &pres_.slides()[0];
        now_ = std::chrono::system_clock::now();
        collection_ = &author_->comments();
    }

    Presentation pres_;
    CommentAuthor* author_ = nullptr;
    Slide* slide_ = nullptr;
    std::chrono::system_clock::time_point now_;
    ICommentCollection* collection_ = nullptr;
};

} // namespace

TEST_F(ICommentCollectionTest, AddComment) {
    auto& comment = collection_->add_comment("Review note", *slide_,
                                              PointF(2.0f, 3.0f), now_);
    EXPECT_EQ(comment.text(), "Review note");
    EXPECT_EQ(comment.author()->name(), "Alice");
    EXPECT_EQ(collection_->size(), 1);
    EXPECT_EQ((*collection_)[0].text(), "Review note");
}

TEST_F(ICommentCollectionTest, InsertComment) {
    collection_->add_comment("First", *slide_, PointF(1, 1), now_);
    collection_->add_comment("Third", *slide_, PointF(1, 3), now_);
    collection_->insert_comment(1, "Second", *slide_, PointF(1, 2), now_);

    ASSERT_EQ(collection_->size(), 3);
    EXPECT_EQ((*collection_)[0].text(), "First");
    EXPECT_EQ((*collection_)[1].text(), "Second");
    EXPECT_EQ((*collection_)[2].text(), "Third");
}

TEST_F(ICommentCollectionTest, RemoveAt) {
    collection_->add_comment("C1", *slide_, PointF(1, 1), now_);
    collection_->add_comment("C2", *slide_, PointF(2, 2), now_);
    collection_->add_comment("C3", *slide_, PointF(3, 3), now_);
    ASSERT_EQ(collection_->size(), 3);

    collection_->remove_at(1);
    ASSERT_EQ(collection_->size(), 2);
    EXPECT_EQ((*collection_)[0].text(), "C1");
    EXPECT_EQ((*collection_)[1].text(), "C3");
}

TEST_F(ICommentCollectionTest, Clear) {
    collection_->add_comment("C1", *slide_, PointF(1, 1), now_);
    collection_->add_comment("C2", *slide_, PointF(2, 2), now_);
    collection_->clear();
    EXPECT_EQ(collection_->size(), 0);
}

// then verifies slide-level filtering)
TEST_F(ICommentCollectionTest, GetSlideComments) {
    auto& bob = pres_.comment_authors().add_author("Bob", "B");
    ICommentCollection* bob_coll = &bob.comments();

    collection_->add_comment("Alice's", *slide_, PointF(1, 1), now_);
    bob_coll->add_comment("Bob's", *slide_, PointF(2, 2), now_);

    auto all_c = slide_->get_slide_comments(nullptr);
    EXPECT_EQ(all_c.size(), 2);

    auto bob_c = slide_->get_slide_comments(&bob);
    ASSERT_EQ(bob_c.size(), 1);
    EXPECT_EQ(bob_c[0]->text(), "Bob's");
}

// Verify to_array via the interface.
TEST_F(ICommentCollectionTest, ToArray) {
    collection_->add_comment("C1", *slide_, PointF(1, 1), now_);
    collection_->add_comment("C2", *slide_, PointF(2, 2), now_);
    collection_->add_comment("C3", *slide_, PointF(3, 3), now_);

    auto all = collection_->to_array();
    ASSERT_EQ(all.size(), 3);
    EXPECT_EQ(all[0]->text(), "C1");
    EXPECT_EQ(all[2]->text(), "C3");

    auto sub = collection_->to_array(1, 2);
    ASSERT_EQ(sub.size(), 2);
    EXPECT_EQ(sub[0]->text(), "C2");
}

// Verify remove(Comment&) via the interface.
TEST_F(ICommentCollectionTest, RemoveByReference) {
    collection_->add_comment("C1", *slide_, PointF(1, 1), now_);
    auto& c2 = collection_->add_comment("C2", *slide_, PointF(2, 2), now_);
    collection_->add_comment("C3", *slide_, PointF(3, 3), now_);

    collection_->remove(c2);
    ASSERT_EQ(collection_->size(), 2);
    EXPECT_EQ((*collection_)[0].text(), "C1");
    EXPECT_EQ((*collection_)[1].text(), "C3");
}

// Verify as_i_collection and as_i_enumerable return the same interface.
TEST_F(ICommentCollectionTest, AsICollectionAndEnumerable) {
    auto& coll_ref = collection_->as_i_collection();
    auto& enum_ref = collection_->as_i_enumerable();
    EXPECT_EQ(&coll_ref, collection_);
    EXPECT_EQ(&enum_ref, collection_);
}
