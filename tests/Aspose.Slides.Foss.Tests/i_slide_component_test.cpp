// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/i_slide_component.h>

using namespace Aspose::Slides::Foss;

/// Verifies that ISlideComponent::slide() returns a non-null base slide.
TEST(ISlideComponentTest, SlideReturnsSelf) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    ISlideComponent& component = slide.as_i_slide_component();
    auto* base = component.slide();
    ASSERT_NE(base, nullptr);
    // The returned IBaseSlide should refer to the same presentation.
    EXPECT_EQ(base->presentation(), slide.presentation());
}

/// Verifies that const slide() works correctly.
TEST(ISlideComponentTest, SlideReturnsConstSelf) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    const ISlideComponent& component = slide.as_i_slide_component();
    const auto* base = component.slide();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->presentation(), slide.presentation());
}

/// Verifies that as_i_presentation_component() returns a valid component.
TEST(ISlideComponentTest, AsIPresentationComponent) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    ISlideComponent& component = slide.as_i_slide_component();
    auto* pres_component = component.as_i_presentation_component();
    ASSERT_NE(pres_component, nullptr);
    EXPECT_EQ(pres_component->presentation(), slide.presentation());
}

/// Verifies const as_i_presentation_component().
TEST(ISlideComponentTest, AsIPresentationComponentConst) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    const ISlideComponent& component = slide.as_i_slide_component();
    const auto* pres_component = component.as_i_presentation_component();
    ASSERT_NE(pres_component, nullptr);
    EXPECT_EQ(pres_component->presentation(), slide.presentation());
}

/// Verifies that ISlideComponent::slide() provides access to the parent presentation.
TEST(ISlideComponentTest, SlideHasCorrectPresentation) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    ISlideComponent& component = slide.as_i_slide_component();
    auto* base_slide = component.slide();
    ASSERT_NE(base_slide, nullptr);
    EXPECT_EQ(base_slide->presentation(), pres.presentation());
}

/// Verifies that multiple slides each return distinct base slides.
TEST(ISlideComponentTest, MultipleSlides) {
    Presentation pres;
    pres.slides().add_empty_slide(nullptr);
    ASSERT_EQ(pres.slides().size(), 2u);

    auto& slide0 = pres.slides()[0];
    auto& slide1 = pres.slides()[1];

    ISlideComponent& comp0 = slide0.as_i_slide_component();
    ISlideComponent& comp1 = slide1.as_i_slide_component();

    auto* base0 = comp0.slide();
    auto* base1 = comp1.slide();
    ASSERT_NE(base0, nullptr);
    ASSERT_NE(base1, nullptr);
    EXPECT_NE(base0, base1);
}
