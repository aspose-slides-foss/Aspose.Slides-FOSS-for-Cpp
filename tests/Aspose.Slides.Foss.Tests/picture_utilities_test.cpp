// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/picture_utilities.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Minimal 1x1 white PNG for test images.
std::vector<std::uint8_t> create_test_png() {
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
        0xDE, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41,
        0x54, 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC,
        0x33, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E,
        0x44, 0xAE, 0x42, 0x60, 0x82};
}

} // namespace

/// flush resolves a pending part name to the matching PPImage.
TEST(PictureUtilitiesTest, ResolvesPendingPartName) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    auto& img = pres.images().add_image(create_test_png());
    img.set_part_name("/ppt/media/image1.png");

    auto& pf = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 0, 0, 100, 100, img);
    pf.set_pp_image(nullptr);
    pf.set_pending_part_name("/ppt/media/image1.png");

    picture::flush_pending_blip_images(slide);

    EXPECT_EQ(pf.pp_image(), &img);
    EXPECT_TRUE(pf.pending_part_name().empty());
}

/// flush does nothing when no pending part names exist.
TEST(PictureUtilitiesTest, NoPendingIsNoop) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    auto& img = pres.images().add_image(create_test_png());
    auto& pf = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 0, 0, 100, 100, img);

    picture::flush_pending_blip_images(slide);

    EXPECT_EQ(pf.pp_image(), &img);
    EXPECT_TRUE(pf.pending_part_name().empty());
}

/// flush clears pending part name even when no matching image is found.
TEST(PictureUtilitiesTest, UnmatchedPendingCleared) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    auto& img = pres.images().add_image(create_test_png());
    auto& pf = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 0, 0, 100, 100, img);
    pf.set_pp_image(nullptr);
    pf.set_pending_part_name("/ppt/media/nonexistent.png");

    picture::flush_pending_blip_images(slide);

    EXPECT_EQ(pf.pp_image(), nullptr);
    EXPECT_TRUE(pf.pending_part_name().empty());
}

/// flush skips non-PictureFrame shapes.
TEST(PictureUtilitiesTest, SkipsNonPictureFrameShapes) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 0, 0, 50, 50);

    // Should not crash or modify anything.
    picture::flush_pending_blip_images(slide);

    EXPECT_EQ(slide.shapes().size(), 1u);
}

/// flush resolves multiple pending frames on the same slide.
TEST(PictureUtilitiesTest, ResolvesMultiplePending) {
    Presentation pres;
    auto& slide = pres.slides()[0];

    auto& img1 = pres.images().add_image(create_test_png());
    img1.set_part_name("/ppt/media/image1.png");

    // Create a slightly different image to avoid dedup.
    auto png2 = create_test_png();
    png2.push_back(0x00);
    auto& img2 = pres.images().add_image(png2);
    img2.set_part_name("/ppt/media/image2.png");

    auto& pf1 = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 0, 0, 100, 100, img1);
    pf1.set_pp_image(nullptr);
    pf1.set_pending_part_name("/ppt/media/image1.png");

    auto& pf2 = slide.shapes().add_picture_frame(
        ShapeType::RECTANGLE, 100, 0, 100, 100, img2);
    pf2.set_pp_image(nullptr);
    pf2.set_pending_part_name("/ppt/media/image2.png");

    picture::flush_pending_blip_images(slide);

    EXPECT_EQ(pf1.pp_image(), &img1);
    EXPECT_EQ(pf2.pp_image(), &img2);
}
