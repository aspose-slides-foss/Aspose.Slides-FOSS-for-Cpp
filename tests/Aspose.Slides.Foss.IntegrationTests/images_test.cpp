// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file images_test.cpp
/// Integration tests for ImageCollection and PictureFrame.

#include <chrono>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/picture_frame.h>
#include <Aspose/Slides/Foss/pp_image.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

using namespace Aspose::Slides::Foss;

namespace {

// ---------------------------------------------------------------------------
// Helper: generate a minimal valid 1x1 PNG with the given RGB colour.
// ---------------------------------------------------------------------------

/// Compute CRC32 of a byte span (zlib / PNG CRC).
static std::uint32_t crc32(const std::vector<std::uint8_t>& data) {
    // Standard CRC-32 used by PNG (polynomial 0xEDB88320).
    std::uint32_t crc = 0xFFFFFFFF;
    for (auto b : data) {
        crc ^= b;
        for (int i = 0; i < 8; ++i)
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
    }
    return crc ^ 0xFFFFFFFF;
}

/// Write a big-endian 32-bit unsigned int into a vector.
static void push_be32(std::vector<std::uint8_t>& out, std::uint32_t v) {
    out.push_back(static_cast<std::uint8_t>((v >> 24) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((v >> 16) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((v >>  8) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((v >>  0) & 0xFF));
}

/// Build a PNG chunk: length(4) + type(4) + data + crc(4).
static std::vector<std::uint8_t> png_chunk(const char* type,
                                           const std::vector<std::uint8_t>& data) {
    std::vector<std::uint8_t> out;
    push_be32(out, static_cast<std::uint32_t>(data.size()));
    // type bytes
    for (int i = 0; i < 4; ++i) out.push_back(static_cast<std::uint8_t>(type[i]));
    // data bytes
    out.insert(out.end(), data.begin(), data.end());
    // crc over type+data
    std::vector<std::uint8_t> crc_input;
    for (int i = 0; i < 4; ++i) crc_input.push_back(static_cast<std::uint8_t>(type[i]));
    crc_input.insert(crc_input.end(), data.begin(), data.end());
    push_be32(out, crc32(crc_input));
    return out;
}

/// Deflate (zlib compress) raw bytes — minimal implementation using raw
/// DEFLATE stored blocks wrapped in a zlib container.
static std::vector<std::uint8_t> zlib_compress(const std::vector<std::uint8_t>& raw) {
    std::vector<std::uint8_t> out;
    // zlib header: CMF=0x78 (deflate, window=32K), FLG=0x01 (check bits)
    out.push_back(0x78);
    out.push_back(0x01);
    // DEFLATE stored block (BFINAL=1, BTYPE=00)
    out.push_back(0x01); // BFINAL=1, BTYPE=00
    auto len = static_cast<std::uint16_t>(raw.size());
    auto nlen = static_cast<std::uint16_t>(~len);
    out.push_back(static_cast<std::uint8_t>(len & 0xFF));
    out.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
    out.push_back(static_cast<std::uint8_t>(nlen & 0xFF));
    out.push_back(static_cast<std::uint8_t>((nlen >> 8) & 0xFF));
    out.insert(out.end(), raw.begin(), raw.end());
    // Adler-32 checksum
    std::uint32_t a = 1, b = 0;
    for (auto byte : raw) {
        a = (a + byte) % 65521;
        b = (b + a) % 65521;
    }
    std::uint32_t adler = (b << 16) | a;
    push_be32(out, adler);
    return out;
}

/// Create a minimal 1x1 PNG with the given RGB colour.
static std::vector<std::uint8_t> create_test_png(std::uint8_t r = 255,
                                                  std::uint8_t g = 0,
                                                  std::uint8_t b = 0) {
    std::vector<std::uint8_t> png;
    // PNG signature
    const std::uint8_t sig[] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};
    png.insert(png.end(), std::begin(sig), std::end(sig));

    // IHDR: width=1, height=1, bit_depth=8, colour_type=2 (RGB), rest=0
    std::vector<std::uint8_t> ihdr;
    push_be32(ihdr, 1); // width
    push_be32(ihdr, 1); // height
    ihdr.push_back(8);  // bit depth
    ihdr.push_back(2);  // colour type (RGB)
    ihdr.push_back(0);  // compression method
    ihdr.push_back(0);  // filter method
    ihdr.push_back(0);  // interlace method
    auto ihdr_chunk = png_chunk("IHDR", ihdr);
    png.insert(png.end(), ihdr_chunk.begin(), ihdr_chunk.end());

    // IDAT: filter byte 0 + RGB
    std::vector<std::uint8_t> raw_scanline = {0, r, g, b};
    auto compressed = zlib_compress(raw_scanline);
    auto idat_chunk = png_chunk("IDAT", compressed);
    png.insert(png.end(), idat_chunk.begin(), idat_chunk.end());

    // IEND
    auto iend_chunk = png_chunk("IEND", {});
    png.insert(png.end(), iend_chunk.begin(), iend_chunk.end());

    return png;
}

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class ImagesIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("images_integration_test_" +
                    std::to_string(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()));
        std::filesystem::create_directories(tmp_dir_);
    }

    void TearDown() override {
        std::filesystem::remove_all(tmp_dir_);
    }

    /// Saves a presentation to a temp file and reopens from that file.
    Presentation save_and_reopen(Presentation& pres) {
        auto path = (tmp_dir_ / "roundtrip.pptx").string();
        pres.save(path, SaveFormat::PPTX);
        return Presentation(path);
    }

    std::filesystem::path tmp_dir_;
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

/// Adding an image increases collection count.
TEST_F(ImagesIntegrationTest, AddImage) {
    Presentation pres;
    auto png = create_test_png(255, 0, 0);
    pres.images().add_image(std::span<const std::uint8_t>(png));
    EXPECT_GE(pres.images().size(), 1u);
}

/// Multiple images can be added and iterated.
TEST_F(ImagesIntegrationTest, MultipleImages) {
    Presentation pres;
    struct RGB { std::uint8_t r, g, b; };
    RGB colours[] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
    for (auto [r, g, b] : colours) {
        auto png = create_test_png(r, g, b);
        pres.images().add_image(std::span<const std::uint8_t>(png));
    }
    EXPECT_GE(pres.images().size(), 3u);

    // Iterate to verify we can enumerate them.
    std::size_t count = 0;
    for ([[maybe_unused]] auto& img : pres.images()) {
        ++count;
    }
    EXPECT_GE(count, 3u);
}

/// Picture frame with image persists after save/reload.
TEST_F(ImagesIntegrationTest, PictureFrame) {
    Presentation pres;
    auto png = create_test_png(0, 0, 255);
    auto& img = pres.images().add_image(std::span<const std::uint8_t>(png));
    pres.slides()[0].shapes().add_picture_frame(
        ShapeType::RECTANGLE, 50, 50, 100, 100, img);
    EXPECT_GE(pres.slides()[0].shapes().size(), 1u);

    auto pres2 = save_and_reopen(pres);
    EXPECT_GE(pres2.slides()[0].shapes().size(), 1u);
}

/// Load an image from the test_data directory (skipped if file missing).
TEST_F(ImagesIntegrationTest, ImageFromFile) {
    // Determine path to test_data/lotus.png relative to the test binary.
    auto test_data = std::filesystem::path(__FILE__).parent_path().parent_path() / "test_data";
    auto img_path = test_data / "lotus.png";
    if (!std::filesystem::exists(img_path)) {
        GTEST_SKIP() << "lotus.png not in test_data";
    }

    // Read the file into a byte vector.
    std::ifstream file(img_path, std::ios::binary);
    ASSERT_TRUE(file.is_open());
    std::vector<std::uint8_t> file_data(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    Presentation pres;
    auto& pp_img = pres.images().add_image(
        std::span<const std::uint8_t>(file_data));
    pres.slides()[0].shapes().add_picture_frame(
        ShapeType::RECTANGLE, 50, 50, 200, 200, pp_img);
    EXPECT_GE(pres.slides()[0].shapes().size(), 1u);
}

} // namespace
