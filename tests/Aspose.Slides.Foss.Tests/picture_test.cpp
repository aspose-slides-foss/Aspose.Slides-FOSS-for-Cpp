// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/picture.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Helper: create minimal valid PNG data for constructing a PPImage.
std::vector<std::uint8_t> create_test_png() {
    // Minimal 1x1 white PNG.
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, // PNG signature
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, // IHDR chunk
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, // 1x1
        0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53, // 8-bit RGB
        0xDE, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41, // IDAT chunk
        0x54, 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC,
        0x33, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, // IEND chunk
        0x44, 0xAE, 0x42, 0x60, 0x82};
}

} // namespace

/// Picture belongs to its parent slide and presentation.
TEST(PictureTest, SlideAndPresentation) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Picture pic(&slide);

    EXPECT_EQ(pic.presentation(), slide.presentation());
}

/// image() is null by default, can be set and retrieved.
TEST(PictureTest, ImageGetSet) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Picture pic(&slide);

    EXPECT_EQ(pic.image(), nullptr);

    PPImage img(create_test_png(), "image/png");
    pic.set_image(&img);
    EXPECT_EQ(pic.image(), &img);
}

/// link_path_long() is empty by default, can be set and retrieved.
TEST(PictureTest, LinkPathLongGetSet) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Picture pic(&slide);

    EXPECT_EQ(pic.link_path_long(), "");

    pic.set_link_path_long("https://example.com/image.png");
    EXPECT_EQ(pic.link_path_long(), "https://example.com/image.png");

    pic.set_link_path_long("");
    EXPECT_EQ(pic.link_path_long(), "");
}

/// as_i_presentation_component returns the same object.
TEST(PictureTest, AsIPresentationComponent) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Picture pic(&slide);

    auto* comp = pic.as_i_presentation_component();
    EXPECT_EQ(comp->presentation(), &pres);
}

/// as_i_slide_component returns the same object.
TEST(PictureTest, AsISlideComponent) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    Picture pic(&slide);

    auto& comp = pic.as_i_slide_component();
    EXPECT_EQ(comp.presentation(), &pres);
}
