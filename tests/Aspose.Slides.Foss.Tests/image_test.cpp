// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/image.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/images.h>
#include <Aspose/Slides/Foss/picture_fill_format.h>
#include <Aspose/Slides/Foss/picture_fill_mode.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/connector.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Creates a minimal valid 1x1 PNG with the given RGB color.
/// The image data is a valid PNG that can be parsed for dimensions.
std::vector<std::uint8_t> create_test_png(std::uint8_t r, std::uint8_t g,
                                          std::uint8_t b) {
    // Minimal 1x1 RGBA PNG
    // PNG signature
    std::vector<std::uint8_t> png = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  // PNG signature
        // IHDR chunk
        0x00, 0x00, 0x00, 0x0D,  // chunk length = 13
        0x49, 0x48, 0x44, 0x52,  // "IHDR"
        0x00, 0x00, 0x00, 0x01,  // width = 1
        0x00, 0x00, 0x00, 0x01,  // height = 1
        0x08,                    // bit depth = 8
        0x02,                    // color type = 2 (RGB)
        0x00, 0x00, 0x00,        // compression, filter, interlace
        0x00, 0x00, 0x00, 0x00,  // CRC (placeholder)
        // IDAT chunk (compressed pixel data: filter=0, r, g, b)
        0x00, 0x00, 0x00, 0x0C,  // chunk length = 12
        0x49, 0x44, 0x41, 0x54,  // "IDAT"
        0x08, 0xD7,              // zlib header
        0x63, 0xF8, 0xCF, 0xC0, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,  // CRC (placeholder)
        // IEND chunk
        0x00, 0x00, 0x00, 0x00,  // chunk length = 0
        0x49, 0x45, 0x4E, 0x44,  // "IEND"
        0xAE, 0x42, 0x60, 0x82,  // CRC
    };

    // Make each color produce slightly different data so dedup works correctly
    // by appending color bytes as a tEXt chunk-like suffix (still valid-ish PNG
    // for our dimension parser which only reads IHDR).
    png.push_back(r);
    png.push_back(g);
    png.push_back(b);

    return png;
}

/// Helper: return a slide with all shapes cleared.
Slide& blank_slide(Presentation& pres) {
    auto& slide = pres.slides()[0];
    slide.shapes().clear();
    return slide;
}

} // namespace


TEST(ImageCollectionTest, AddImage) {
    Presentation pres;
    auto png = create_test_png(255, 0, 0);
    pres.images().add_image(png);
    EXPECT_GE(pres.images().size(), 1);
}

TEST(ImageCollectionTest, MultipleImages) {
    Presentation pres;
    pres.images().add_image(create_test_png(255, 0, 0));
    pres.images().add_image(create_test_png(0, 255, 0));
    pres.images().add_image(create_test_png(0, 0, 255));
    EXPECT_GE(pres.images().size(), 3);

    // Verify iteration works
    std::size_t count = 0;
    for ([[maybe_unused]] auto& img : pres.images()) {
        ++count;
    }
    EXPECT_GE(count, 3);
}

// Since there is no PPTX serialization yet, we verify that the picture frame
// properties are correctly retained in memory after creation.
TEST(ImageCollectionTest, PictureFrame) {
    Presentation pres;
    auto& img = pres.images().add_image(create_test_png(0, 0, 255));
    pres.slides()[0].shapes().add_picture_frame(
        ShapeType::RECTANGLE, 50, 50, 100, 100, img);
    EXPECT_GE(pres.slides()[0].shapes().size(), 1);

    // Verify the picture frame retains its image reference
    auto& shape = pres.slides()[0].shapes()[0];
    auto* pf = dynamic_cast<PictureFrame*>(&shape);
    ASSERT_NE(pf, nullptr);
    EXPECT_EQ(pf->pp_image(), &img);
}

TEST(ImageCollectionTest, ImageFromFile) {
    // Create a temporary PNG file
    auto png_data = create_test_png(128, 64, 32);
    auto temp_path = std::string("test_image_temp.png");
    {
        std::ofstream f(temp_path, std::ios::binary);
        ASSERT_TRUE(f.is_open());
        f.write(reinterpret_cast<const char*>(png_data.data()),
                static_cast<std::streamsize>(png_data.size()));
    }

    Presentation pres;
    // Read file and add as image
    {
        std::ifstream f(temp_path, std::ios::binary);
        ASSERT_TRUE(f.is_open());
        std::vector<std::uint8_t> data(
            (std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
        auto& pp_img = pres.images().add_image(data);
        pres.slides()[0].shapes().add_picture_frame(
            ShapeType::RECTANGLE, 50, 50, 200, 200, pp_img);
    }
    EXPECT_GE(pres.slides()[0].shapes().size(), 1);

    // Clean up temp file
    std::remove(temp_path.c_str());
}


// Since there is no PPTX serialization yet, we verify in-memory state.
TEST(FillFormatTest, PictureFill) {
    Presentation pres;
    auto& slide = blank_slide(pres);
    auto& shape = slide.shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200, 200);
    shape.fill_format().set_fill_type(FillType::PICTURE);
    auto& pff = shape.fill_format().picture_fill_format();
    pff.set_picture_fill_mode(PictureFillMode::STRETCH);
    auto& img = pres.images().add_image(create_test_png(0, 255, 0));
    pff.set_image(&img);

    // Verify fill type is retained
    EXPECT_EQ(shape.fill_format().fill_type(), FillType::PICTURE);
    EXPECT_EQ(pff.picture_fill_mode(), PictureFillMode::STRETCH);
    EXPECT_EQ(pff.image(), &img);
}
