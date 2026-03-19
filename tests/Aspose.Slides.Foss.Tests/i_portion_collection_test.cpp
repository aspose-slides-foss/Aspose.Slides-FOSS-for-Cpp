// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_portion_collection.h>
#include <Aspose/Slides/Foss/portion.h>
#include <Aspose/Slides/Foss/portion_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture providing a PortionCollection accessed through IPortionCollection.
class IPortionCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection_ = &concrete_;
    }

    PortionCollection concrete_;
    IPortionCollection* collection_ = nullptr;
};

} // namespace

TEST_F(IPortionCollectionTest, Add) {
    auto& p1 = collection_->add(Portion("Hello "));
    EXPECT_EQ(p1.text(), "Hello ");
    EXPECT_EQ(collection_->size(), 1);

    auto& p2 = collection_->add(Portion("World!"));
    EXPECT_EQ(p2.text(), "World!");
    EXPECT_EQ(collection_->size(), 2);
    EXPECT_EQ((*collection_)[1].text(), "World!");
}

TEST_F(IPortionCollectionTest, RemoveAt) {
    collection_->add(Portion("C1"));
    collection_->add(Portion("C2"));
    collection_->add(Portion("C3"));
    ASSERT_EQ(collection_->size(), 3);

    collection_->remove_at(1);
    ASSERT_EQ(collection_->size(), 2);
    EXPECT_EQ((*collection_)[0].text(), "C1");
    EXPECT_EQ((*collection_)[1].text(), "C3");
}

TEST_F(IPortionCollectionTest, RemoveAtFirst) {
    collection_->add(Portion("First"));
    collection_->add(Portion("Second"));
    collection_->remove_at(0);
    ASSERT_EQ(collection_->size(), 1);
    EXPECT_EQ((*collection_)[0].text(), "Second");
}

TEST_F(IPortionCollectionTest, IndexOf) {
    auto& p0 = collection_->add(Portion("Alpha"));
    auto& p1 = collection_->add(Portion("Beta"));

    auto idx0 = collection_->index_of(p0);
    auto idx1 = collection_->index_of(p1);
    ASSERT_TRUE(idx0.has_value());
    ASSERT_TRUE(idx1.has_value());
    EXPECT_EQ(*idx0, 0);
    EXPECT_EQ(*idx1, 1);
}

TEST_F(IPortionCollectionTest, RemoveAtReducesCount) {
    collection_->add(Portion("A"));
    collection_->add(Portion("B"));
    ASSERT_EQ(collection_->size(), 2);

    collection_->remove_at(1);
    EXPECT_EQ(collection_->size(), 1);
}

TEST_F(IPortionCollectionTest, AddMultiple) {
    collection_->add(Portion("Stop0"));
    collection_->add(Portion("Stop1"));
    EXPECT_GE(collection_->size(), 2);
    EXPECT_EQ((*collection_)[0].text(), "Stop0");
    EXPECT_EQ((*collection_)[1].text(), "Stop1");
}

// Additional: verify contains, remove by reference, insert, clear, as_i_enumerable
TEST_F(IPortionCollectionTest, Contains) {
    auto& p = collection_->add(Portion("X"));
    EXPECT_TRUE(collection_->contains(p));

    Portion detached("Y");
    EXPECT_FALSE(collection_->contains(detached));
}

TEST_F(IPortionCollectionTest, RemoveByReference) {
    collection_->add(Portion("A"));
    auto& b = collection_->add(Portion("B"));
    collection_->add(Portion("C"));

    EXPECT_TRUE(collection_->remove(b));
    ASSERT_EQ(collection_->size(), 2);
    EXPECT_EQ((*collection_)[0].text(), "A");
    EXPECT_EQ((*collection_)[1].text(), "C");
}

TEST_F(IPortionCollectionTest, Insert) {
    collection_->add(Portion("First"));
    collection_->add(Portion("Third"));
    collection_->insert(1, Portion("Second"));

    ASSERT_EQ(collection_->size(), 3);
    EXPECT_EQ((*collection_)[0].text(), "First");
    EXPECT_EQ((*collection_)[1].text(), "Second");
    EXPECT_EQ((*collection_)[2].text(), "Third");
}

TEST_F(IPortionCollectionTest, Clear) {
    collection_->add(Portion("A"));
    collection_->add(Portion("B"));
    collection_->clear();
    EXPECT_EQ(collection_->size(), 0);
}

TEST_F(IPortionCollectionTest, AsIEnumerable) {
    auto& enum_ref = collection_->as_i_enumerable();
    EXPECT_EQ(&enum_ref, collection_);

    const auto* const_coll = collection_;
    auto& const_enum_ref = const_coll->as_i_enumerable();
    EXPECT_EQ(&const_enum_ref, const_coll);
}

TEST_F(IPortionCollectionTest, IndexOfNotFound) {
    collection_->add(Portion("A"));
    Portion detached("B");
    auto idx = collection_->index_of(detached);
    EXPECT_FALSE(idx.has_value());
}

TEST_F(IPortionCollectionTest, RemoveAtOutOfRange) {
    collection_->add(Portion("A"));
    EXPECT_THROW(collection_->remove_at(5), std::out_of_range);
}

TEST_F(IPortionCollectionTest, Count) {
    EXPECT_EQ(collection_->count(), 0);
    collection_->add(Portion("A"));
    EXPECT_EQ(collection_->count(), 1);
    EXPECT_EQ(collection_->count(), collection_->size());
}

TEST_F(IPortionCollectionTest, IsReadOnly) {
    EXPECT_FALSE(collection_->is_read_only());
}
