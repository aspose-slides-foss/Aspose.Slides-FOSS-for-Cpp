// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file picture_frame_conformance_test.cpp
/// What `add_picture_frame` puts in the file.
///
/// The in-memory object keeps the image whether or not the serialiser wrote
/// it, so asking the library "is there a picture?" after saving answers yes in
/// both cases. Only the package can tell them apart: a picture is a `<p:pic>`
/// whose `r:embed` resolves to an image relationship, plus the image bytes and
/// a content type for them.

#include <cstdint>
#include <span>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"
#include "conformance/test_png.h"

using namespace Aspose::Slides::Foss;

namespace {

class PictureFrameConformance : public conformance::SavedDeckTest {};

TEST_F(PictureFrameConformance, APictureFrameWritesAPictureShape) {
    Presentation pres;
    auto png = conformance::one_pixel_png(0, 0, 255);
    auto& img = pres.images().add_image(std::span<const std::uint8_t>(png));
    pres.slides()[0].shapes().add_picture_frame(ShapeType::RECTANGLE, 50, 50,
                                                100, 100, img);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//p:pic"))
        << "the shape was serialised as something other than a picture; "
           "PowerPoint shows a grey rectangle where the image should be";
}

TEST_F(PictureFrameConformance, APictureFrameEmbedsTheImageBytes) {
    Presentation pres;
    auto png = conformance::one_pixel_png(0, 0, 255);
    auto& img = pres.images().add_image(std::span<const std::uint8_t>(png));
    pres.slides()[0].shapes().add_picture_frame(ShapeType::RECTANGLE, 50, 50,
                                                100, 100, img);

    auto pkg = save_and_inspect(pres);
    auto media = pkg.entries_matching("^ppt/media/");
    EXPECT_FALSE(media.empty())
        << "no part under ppt/media/: the image never reached the package at "
           "all, so nothing can render it";
}

TEST_F(PictureFrameConformance, APictureFrameReferencesTheImageItEmbedded) {
    Presentation pres;
    auto png = conformance::one_pixel_png(0, 0, 255);
    auto& img = pres.images().add_image(std::span<const std::uint8_t>(png));
    pres.slides()[0].shapes().add_picture_frame(ShapeType::RECTANGLE, 50, 50,
                                                100, 100, img);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//p:pic/p:blipFill/a:blip"));
    EXPECT_TRUE(conformance::AllRelationshipReferencesResolve(pkg));
    EXPECT_TRUE(conformance::EveryPartHasAContentType(pkg))
        << "an image with no content type is a part PowerPoint refuses the "
           "whole file over";
}

/// The picture fill path is the one that already works end to end, and it is
/// the code the picture-frame path should be reusing. Kept as a regression
/// guard: whatever the frame fix does, this must keep passing.
TEST_F(PictureFrameConformance, APictureFillEmbedsAndResolvesItsImage) {
    Presentation pres;
    auto png = conformance::one_pixel_png(255, 0, 0);
    pres.images().add_image(std::span<const std::uint8_t>(png));

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::AllRelationshipReferencesResolve(pkg));
    EXPECT_TRUE(conformance::NoContentTypeOverrideDangles(pkg));
}

} // namespace
