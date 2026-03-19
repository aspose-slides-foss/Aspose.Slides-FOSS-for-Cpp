// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/paragraph_collection.h>
#include <Aspose/Slides/Foss/shape_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Minimal IBaseSlide stub for testing parent slide back-references.
class StubSlide : public IBaseSlide {
public:
    explicit StubSlide(IPresentation* pres = nullptr) : pres_(pres) {}

    [[nodiscard]] ShapeCollection& shapes() override { return shapes_; }
    [[nodiscard]] const ShapeCollection& shapes() const override { return shapes_; }
    [[nodiscard]] const std::string& name() const override {
        static const std::string n;
        return n;
    }
    void set_name(std::string) override {}
    [[nodiscard]] uint32_t slide_id() const override { return 0; }

    [[nodiscard]] IPresentation* presentation() override { return pres_; }
    [[nodiscard]] const IPresentation* presentation() const override { return pres_; }

private:
    IPresentation* pres_;
    ShapeCollection shapes_;
};

} // namespace

/// Default-constructed collection is empty.
TEST(IParagraphCollectionTest, DefaultEmpty) {
    ParagraphCollection coll;
    EXPECT_EQ(coll.size(), 0u);
}

/// Adding paragraphs increases size.
TEST(IParagraphCollectionTest, AddParagraphs) {
    ParagraphCollection coll;
    auto& p1 = coll.add(Paragraph("First"));
    auto& p2 = coll.add(Paragraph("Second"));

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_EQ(coll[0].text(), "First");
    EXPECT_EQ(coll[1].text(), "Second");
    EXPECT_EQ(p1.text(), "First");
    EXPECT_EQ(p2.text(), "Second");
}

/// remove_at removes a paragraph by index, remaining items shift down.
TEST(IParagraphCollectionTest, RemoveAt) {
    ParagraphCollection coll;
    coll.add(Paragraph("C1"));
    coll.add(Paragraph("C2"));
    coll.add(Paragraph("C3"));
    ASSERT_EQ(coll.size(), 3u);

    coll.remove_at(1);
    ASSERT_EQ(coll.size(), 2u);
    EXPECT_EQ(coll[0].text(), "C1");
    EXPECT_EQ(coll[1].text(), "C3");
}

/// remove_at on shapes collection — removing first element.
TEST(IParagraphCollectionTest, RemoveAtFirstElement) {
    ParagraphCollection coll;
    coll.add(Paragraph("First"));
    coll.add(Paragraph("Second"));
    coll.remove_at(0);

    ASSERT_EQ(coll.size(), 1u);
    EXPECT_EQ(coll[0].text(), "Second");
}

/// remove_at on slides — remove_at last index.
TEST(IParagraphCollectionTest, RemoveAtLastElement) {
    ParagraphCollection coll;
    coll.add(Paragraph("First"));
    coll.add(Paragraph("Second"));
    coll.remove_at(1);

    ASSERT_EQ(coll.size(), 1u);
    EXPECT_EQ(coll[0].text(), "First");
}

/// remove_at throws on out-of-range index.
TEST(IParagraphCollectionTest, RemoveAtOutOfRange) {
    ParagraphCollection coll;
    coll.add(Paragraph("Only"));
    EXPECT_THROW(coll.remove_at(1), std::out_of_range);
    EXPECT_THROW(coll.remove_at(100), std::out_of_range);
}

/// remove() removes a paragraph by reference.
TEST(IParagraphCollectionTest, RemoveByReference) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    auto& b = coll.add(Paragraph("B"));
    coll.add(Paragraph("C"));
    ASSERT_EQ(coll.size(), 3u);

    bool removed = coll.remove(b);
    EXPECT_TRUE(removed);
    ASSERT_EQ(coll.size(), 2u);
    EXPECT_EQ(coll[0].text(), "A");
    EXPECT_EQ(coll[1].text(), "C");
}

/// remove() returns false when the paragraph is not in the collection.
TEST(IParagraphCollectionTest, RemoveNotFound) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    Paragraph other("B");
    EXPECT_FALSE(coll.remove(other));
    EXPECT_EQ(coll.size(), 1u);
}

/// insert places a paragraph at the given index.
TEST(IParagraphCollectionTest, InsertAtIndex) {
    ParagraphCollection coll;
    coll.add(Paragraph("First"));
    coll.add(Paragraph("Third"));
    coll.insert(1, Paragraph("Second"));

    ASSERT_EQ(coll.size(), 3u);
    EXPECT_EQ(coll[0].text(), "First");
    EXPECT_EQ(coll[1].text(), "Second");
    EXPECT_EQ(coll[2].text(), "Third");
}

/// insert at beginning.
TEST(IParagraphCollectionTest, InsertAtBeginning) {
    ParagraphCollection coll;
    coll.add(Paragraph("Second"));
    coll.insert(0, Paragraph("First"));

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_EQ(coll[0].text(), "First");
    EXPECT_EQ(coll[1].text(), "Second");
}

/// insert throws on out-of-range index.
TEST(IParagraphCollectionTest, InsertOutOfRange) {
    ParagraphCollection coll;
    EXPECT_THROW(coll.insert(1, Paragraph("X")), std::out_of_range);
}

/// clear() removes all paragraphs.
TEST(IParagraphCollectionTest, Clear) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    coll.add(Paragraph("B"));
    coll.add(Paragraph("C"));
    ASSERT_EQ(coll.size(), 3u);

    coll.clear();
    EXPECT_EQ(coll.size(), 0u);
}

/// Can add again after clear.
TEST(IParagraphCollectionTest, AddAfterClear) {
    ParagraphCollection coll;
    coll.add(Paragraph("Before"));
    coll.clear();
    coll.add(Paragraph("After"));

    ASSERT_EQ(coll.size(), 1u);
    EXPECT_EQ(coll[0].text(), "After");
}

/// operator[] throws on out-of-range index.
TEST(IParagraphCollectionTest, IndexOutOfRange) {
    ParagraphCollection coll;
    coll.add(Paragraph("Only"));
    EXPECT_THROW((void)coll[1], std::out_of_range);
    EXPECT_THROW((void)coll[100], std::out_of_range);
}

/// Empty collection throws on any index access.
TEST(IParagraphCollectionTest, EmptyCollectionThrows) {
    ParagraphCollection coll;
    EXPECT_THROW((void)coll[0], std::out_of_range);
}

/// Range-based for loop iterates all paragraphs.
TEST(IParagraphCollectionTest, Iteration) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    coll.add(Paragraph("B"));
    coll.add(Paragraph("C"));

    std::size_t count = 0;
    for ([[maybe_unused]] const auto& para : coll) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

/// as_i_slide_component returns self.
TEST(IParagraphCollectionTest, AsISlideComponent) {
    ParagraphCollection coll;
    EXPECT_EQ(coll.as_i_slide_component(), static_cast<ISlideComponent*>(&coll));
}

/// as_i_enumerable returns self.
TEST(IParagraphCollectionTest, AsIEnumerable) {
    ParagraphCollection coll;
    EXPECT_EQ(&coll.as_i_enumerable(), &coll);
}

/// slide() defaults to nullptr.
TEST(IParagraphCollectionTest, SlideDefaultsToNull) {
    ParagraphCollection coll;
    EXPECT_EQ(coll.slide(), nullptr);
}

/// slide() returns the parent after set_slide.
TEST(IParagraphCollectionTest, SlideReturnsParent) {
    StubSlide stub;
    ParagraphCollection coll;
    coll.set_slide(&stub);
    EXPECT_EQ(coll.slide(), &stub);
}

/// presentation() defaults to nullptr.
TEST(IParagraphCollectionTest, PresentationDefaultsToNull) {
    ParagraphCollection coll;
    EXPECT_EQ(coll.presentation(), nullptr);
}

/// presentation() traverses through parent slide.
TEST(IParagraphCollectionTest, PresentationViaSlideLookup) {
    int fake_pres = 0;
    auto* fake_pres_ptr = reinterpret_cast<IPresentation*>(&fake_pres);
    StubSlide stub(fake_pres_ptr);

    ParagraphCollection coll;
    coll.set_slide(&stub);
    EXPECT_EQ(coll.presentation(), fake_pres_ptr);
}

/// as_i_presentation_component returns self.
TEST(IParagraphCollectionTest, AsIPresentationComponent) {
    ParagraphCollection coll;
    EXPECT_EQ(coll.as_i_presentation_component(), static_cast<IPresentationComponent*>(&coll));
}

/// is_read_only always returns false.
TEST(IParagraphCollectionTest, IsReadOnly) {
    ParagraphCollection coll;
    EXPECT_FALSE(coll.is_read_only());
    coll.add(Paragraph("A"));
    EXPECT_FALSE(coll.is_read_only());
}

/// index_of returns the index of a paragraph found by identity.
TEST(IParagraphCollectionTest, IndexOfFound) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    auto& b = coll.add(Paragraph("B"));
    coll.add(Paragraph("C"));

    auto idx = coll.index_of(b);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 1u);
}

/// index_of returns nullopt when the paragraph is not in the collection.
TEST(IParagraphCollectionTest, IndexOfNotFound) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    Paragraph other("B");
    EXPECT_FALSE(coll.index_of(other).has_value());
}

/// contains returns true for a paragraph in the collection.
TEST(IParagraphCollectionTest, ContainsFound) {
    ParagraphCollection coll;
    auto& a = coll.add(Paragraph("A"));
    EXPECT_TRUE(coll.contains(a));
}

/// contains returns false for a paragraph not in the collection.
TEST(IParagraphCollectionTest, ContainsNotFound) {
    ParagraphCollection coll;
    coll.add(Paragraph("A"));
    Paragraph other("B");
    EXPECT_FALSE(coll.contains(other));
}
