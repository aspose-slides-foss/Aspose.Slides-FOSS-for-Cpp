// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/cell_collection.h>
#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/shape_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Minimal IBaseSlide stub for testing CellCollection's slide/presentation
/// back-references.
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
TEST(CellCollectionTest, DefaultEmpty) {
    CellCollection coll;
    EXPECT_EQ(coll.size(), 0u);
}

/// Adding cells increases size and stores them.
TEST(CellCollectionTest, AddCells) {
    CellCollection coll;
    auto& c1 = coll.add();
    c1.set_width(100.0);
    auto& c2 = coll.add();
    c2.set_width(200.0);

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_DOUBLE_EQ(coll[0].width(), 100.0);
    EXPECT_DOUBLE_EQ(coll[1].width(), 200.0);
}

/// clear() removes all cells.
TEST(CellCollectionTest, Clear) {
    CellCollection coll;
    coll.add();
    coll.add();
    coll.add();
    ASSERT_EQ(coll.size(), 3u);

    coll.clear();
    EXPECT_EQ(coll.size(), 0u);
}

/// operator[] throws on out-of-range index.
TEST(CellCollectionTest, IndexOutOfRangeThrows) {
    CellCollection coll;
    coll.add();
    EXPECT_THROW((void)coll[1], std::out_of_range);
    EXPECT_THROW((void)coll[100], std::out_of_range);
}

/// Empty collection throws on any index access.
TEST(CellCollectionTest, EmptyCollectionThrows) {
    CellCollection coll;
    EXPECT_THROW((void)coll[0], std::out_of_range);
}

/// Range-based for loop iterates all cells.
TEST(CellCollectionTest, Iteration) {
    CellCollection coll;
    coll.add();
    coll.add();
    coll.add();

    std::size_t count = 0;
    for ([[maybe_unused]] const auto& cell : coll) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

/// slide() returns nullptr when no parent slide is set.
TEST(CellCollectionTest, SlideDefaultsToNull) {
    CellCollection coll;
    EXPECT_EQ(coll.slide(), nullptr);
}

/// slide() returns the parent slide after set_slide.
TEST(CellCollectionTest, SlideReturnsParentSlide) {
    StubSlide stub;
    CellCollection coll;
    coll.set_slide(&stub);
    EXPECT_EQ(coll.slide(), &stub);
}

/// presentation() returns nullptr when no parent slide is set.
TEST(CellCollectionTest, PresentationDefaultsToNull) {
    CellCollection coll;
    EXPECT_EQ(coll.presentation(), nullptr);
}

/// presentation() traverses through parent slide.
TEST(CellCollectionTest, PresentationViaSlideLookup) {
    // StubSlide with a non-null presentation pointer (cast is safe for
    // identity comparison only).
    int fake_pres = 0;
    auto* fake_pres_ptr = reinterpret_cast<IPresentation*>(&fake_pres);
    StubSlide stub(fake_pres_ptr);

    CellCollection coll;
    coll.set_slide(&stub);
    EXPECT_EQ(coll.presentation(), fake_pres_ptr);
}

/// presentation() returns nullptr when slide has no presentation.
TEST(CellCollectionTest, PresentationNullWhenSlideHasNoPresentation) {
    StubSlide stub(nullptr);
    CellCollection coll;
    coll.set_slide(&stub);
    EXPECT_EQ(coll.presentation(), nullptr);
}

/// as_i_slide_component returns self.
TEST(CellCollectionTest, AsISlideComponent) {
    CellCollection coll;
    EXPECT_EQ(coll.as_i_slide_component(), static_cast<ISlideComponent*>(&coll));
}

/// as_i_presentation_component returns self.
TEST(CellCollectionTest, AsIPresentationComponent) {
    CellCollection coll;
    EXPECT_EQ(coll.as_i_presentation_component(), static_cast<IPresentationComponent*>(&coll));
}

/// as_i_collection returns a snapshot of all cells.
TEST(CellCollectionTest, AsICollection) {
    CellCollection coll;
    auto& c1 = coll.add();
    auto& c2 = coll.add();

    auto snapshot = coll.as_i_collection();
    ASSERT_EQ(snapshot.size(), 2u);
    EXPECT_EQ(snapshot[0], &c1);
    EXPECT_EQ(snapshot[1], &c2);
}

/// as_i_enumerable returns same data as as_i_collection.
TEST(CellCollectionTest, AsIEnumerable) {
    CellCollection coll;
    coll.add();

    auto snapshot = coll.as_i_enumerable();
    ASSERT_EQ(snapshot.size(), 1u);
}

/// init_internal sets cells and parent slide.
TEST(CellCollectionTest, InitInternal) {
    StubSlide stub;

    std::vector<std::unique_ptr<Cell>> cells;
    cells.push_back(std::make_unique<Cell>());
    cells.push_back(std::make_unique<Cell>());
    cells[0]->set_width(50.0);
    cells[1]->set_width(75.0);

    CellCollection coll;
    coll.init_internal(std::move(cells), &stub);

    ASSERT_EQ(coll.size(), 2u);
    EXPECT_DOUBLE_EQ(coll[0].width(), 50.0);
    EXPECT_DOUBLE_EQ(coll[1].width(), 75.0);
    EXPECT_EQ(coll.slide(), &stub);
}

/// Removing cells by clearing after add persists.
TEST(CellCollectionTest, AddThenClear) {
    CellCollection coll;
    coll.add();
    coll.add();
    ASSERT_EQ(coll.size(), 2u);

    coll.clear();
    EXPECT_EQ(coll.size(), 0u);

    // Can add again after clearing.
    coll.add();
    EXPECT_EQ(coll.size(), 1u);
}
