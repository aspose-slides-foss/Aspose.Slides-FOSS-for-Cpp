// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file test_png.cpp
/// @brief Minimal PNG encoder for image tests: one pixel, stored DEFLATE.

#include "conformance/test_png.h"

namespace conformance {

namespace {

std::uint32_t crc32_of(const std::vector<std::uint8_t>& data) {
    std::uint32_t crc = 0xFFFFFFFFu;
    for (auto byte : data) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i)
            crc = (crc >> 1) ^ (0xEDB88320u & (~(crc & 1u) + 1u));
    }
    return crc ^ 0xFFFFFFFFu;
}

void push_be32(std::vector<std::uint8_t>& out, std::uint32_t value) {
    out.push_back(static_cast<std::uint8_t>((value >> 24) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((value >> 16) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((value >> 8) & 0xFF));
    out.push_back(static_cast<std::uint8_t>(value & 0xFF));
}

std::vector<std::uint8_t> chunk(const char (&type)[5],
                                const std::vector<std::uint8_t>& data) {
    std::vector<std::uint8_t> body;
    for (int i = 0; i < 4; ++i)
        body.push_back(static_cast<std::uint8_t>(type[i]));
    body.insert(body.end(), data.begin(), data.end());

    std::vector<std::uint8_t> out;
    push_be32(out, static_cast<std::uint32_t>(data.size()));
    out.insert(out.end(), body.begin(), body.end());
    push_be32(out, crc32_of(body));
    return out;
}

/// zlib stream holding a single stored (uncompressed) DEFLATE block.
std::vector<std::uint8_t> zlib_stored(const std::vector<std::uint8_t>& raw) {
    std::vector<std::uint8_t> out{0x78, 0x01, 0x01};
    auto len = static_cast<std::uint16_t>(raw.size());
    auto nlen = static_cast<std::uint16_t>(~len);
    out.push_back(static_cast<std::uint8_t>(len & 0xFF));
    out.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
    out.push_back(static_cast<std::uint8_t>(nlen & 0xFF));
    out.push_back(static_cast<std::uint8_t>((nlen >> 8) & 0xFF));
    out.insert(out.end(), raw.begin(), raw.end());

    std::uint32_t a = 1, b = 0;
    for (auto byte : raw) {
        a = (a + byte) % 65521u;
        b = (b + a) % 65521u;
    }
    push_be32(out, (b << 16) | a);
    return out;
}

} // namespace

std::vector<std::uint8_t> one_pixel_png(std::uint8_t r, std::uint8_t g,
                                        std::uint8_t b) {
    std::vector<std::uint8_t> png = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};

    std::vector<std::uint8_t> ihdr;
    push_be32(ihdr, 1); // width
    push_be32(ihdr, 1); // height
    ihdr.push_back(8);  // bit depth
    ihdr.push_back(2);  // colour type: truecolour
    ihdr.push_back(0);  // compression
    ihdr.push_back(0);  // filter
    ihdr.push_back(0);  // interlace
    auto ihdr_chunk = chunk("IHDR", ihdr);
    png.insert(png.end(), ihdr_chunk.begin(), ihdr_chunk.end());

    auto idat_chunk = chunk("IDAT", zlib_stored({0, r, g, b}));
    png.insert(png.end(), idat_chunk.begin(), idat_chunk.end());

    auto iend_chunk = chunk("IEND", {});
    png.insert(png.end(), iend_chunk.begin(), iend_chunk.end());
    return png;
}

} // namespace conformance
