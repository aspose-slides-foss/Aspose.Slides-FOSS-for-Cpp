// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/paragraph.h>
#include <Aspose/Slides/Foss/shape_collection.h>

#include <string>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Minimal stub implementing IBaseSlide for testing Paragraph.slide().
// ---------------------------------------------------------------------------
namespace {

class StubSlide : public IBaseSlide {
public:
    explicit StubSlide(std::string name = "") : name_(std::move(name)) {}

    ShapeCollection& shapes() override { return shapes_; }
    const ShapeCollection& shapes() const override { return shapes_; }
    const std::string& name() const override { return name_; }
    void set_name(std::string value) override { name_ = std::move(value); }
    uint32_t slide_id() const override { return 1; }
    IPresentation* presentation() override { return nullptr; }
    const IPresentation* presentation() const override { return nullptr; }

private:
    std::string name_;
    ShapeCollection shapes_;
};

} // namespace

// ---------------------------------------------------------------------------
// parent slide after being associated with one.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, SlideReturnsNullWhenNotSet) {
    Paragraph para;
    EXPECT_EQ(para.slide(), nullptr);

    const auto* cpara = &para;
    EXPECT_EQ(cpara->slide(), nullptr);
}

// ---------------------------------------------------------------------------
// should return that slide from their slide() accessor.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, SlideReturnsParentAfterSet) {
    StubSlide stub("Slide1");
    Paragraph para("Review note");
    para.set_slide(&stub);

    EXPECT_EQ(para.slide(), &stub);
    EXPECT_EQ(para.slide()->name(), "Slide1");
}

// ---------------------------------------------------------------------------
// nullptr) should revert slide() to null.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, SlideCanBeCleared) {
    StubSlide stub;
    Paragraph para;
    para.set_slide(&stub);
    ASSERT_NE(para.slide(), nullptr);

    para.set_slide(nullptr);
    EXPECT_EQ(para.slide(), nullptr);
}

// ---------------------------------------------------------------------------
// reference different slides.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, MultipleParagraphsDifferentSlides) {
    StubSlide slide1("First");
    StubSlide slide2("Second");

    Paragraph p1("Alice's");
    Paragraph p2("Bob's");
    p1.set_slide(&slide1);
    p2.set_slide(&slide2);

    EXPECT_EQ(p1.slide()->name(), "First");
    EXPECT_EQ(p2.slide()->name(), "Second");
    EXPECT_NE(p1.slide(), p2.slide());
}

// ---------------------------------------------------------------------------
// slide updates the reference correctly.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, SlideCanBeReassigned) {
    StubSlide slide1("Original");
    StubSlide slide2("New");

    Paragraph para;
    para.set_slide(&slide1);
    EXPECT_EQ(para.slide()->name(), "Original");

    para.set_slide(&slide2);
    EXPECT_EQ(para.slide()->name(), "New");
}

// ---------------------------------------------------------------------------
// ISlideComponent interface.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, SlideAccessThroughInterface) {
    StubSlide stub("ViaInterface");
    Paragraph para;
    para.set_slide(&stub);

    ISlideComponent* sc = para.as_i_slide_component();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->slide(), &stub);
    EXPECT_EQ(sc->slide()->name(), "ViaInterface");
}

// ---------------------------------------------------------------------------
// Presentation access delegates through slide.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, PresentationReturnsNullWithNoSlide) {
    Paragraph para;
    EXPECT_EQ(para.presentation(), nullptr);
}

TEST(ParagraphSlideTest, PresentationDelegatesViaSlide) {
    StubSlide stub;
    Paragraph para;
    para.set_slide(&stub);

    // StubSlide::presentation() returns nullptr, so paragraph's should too.
    EXPECT_EQ(para.presentation(), nullptr);
}

// ---------------------------------------------------------------------------
// Const correctness for slide access.
// ---------------------------------------------------------------------------
TEST(ParagraphSlideTest, ConstSlideAccess) {
    StubSlide stub("ConstTest");
    Paragraph para;
    para.set_slide(&stub);

    const Paragraph& cpara = para;
    EXPECT_EQ(cpara.slide(), &stub);
    EXPECT_EQ(cpara.slide()->name(), "ConstTest");
    EXPECT_EQ(cpara.presentation(), nullptr);
}
