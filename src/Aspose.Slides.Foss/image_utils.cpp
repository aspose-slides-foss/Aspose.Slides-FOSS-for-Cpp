// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/image_utils.h>

#include <algorithm>
#include <cstring>

namespace Aspose::Slides::Foss::image_utils {

namespace {

bool starts_with(std::span<const std::uint8_t> data,
                 std::initializer_list<std::uint8_t> magic) {
    if (data.size() < magic.size()) return false;
    return std::equal(magic.begin(), magic.end(), data.begin());
}

std::uint16_t read_be16(const std::uint8_t* p) {
    return static_cast<std::uint16_t>((p[0] << 8) | p[1]);
}

std::uint32_t read_be32(const std::uint8_t* p) {
    return (static_cast<std::uint32_t>(p[0]) << 24) |
           (static_cast<std::uint32_t>(p[1]) << 16) |
           (static_cast<std::uint32_t>(p[2]) << 8) |
           static_cast<std::uint32_t>(p[3]);
}

std::uint32_t read_le32(const std::uint8_t* p) {
    return static_cast<std::uint32_t>(p[0]) |
           (static_cast<std::uint32_t>(p[1]) << 8) |
           (static_cast<std::uint32_t>(p[2]) << 16) |
           (static_cast<std::uint32_t>(p[3]) << 24);
}

std::uint16_t read_le16(const std::uint8_t* p) {
    return static_cast<std::uint16_t>(p[0] | (p[1] << 8));
}

enum class ImageFormat { PNG, JPEG, GIF, BMP, TIFF, EMF, WMF, UNKNOWN };

ImageFormat detect_format(std::span<const std::uint8_t> data) {
    if (starts_with(data, {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}))
        return ImageFormat::PNG;
    if (starts_with(data, {0xFF, 0xD8, 0xFF}))
        return ImageFormat::JPEG;
    if (starts_with(data, {0x47, 0x49, 0x46, 0x38}))  // GIF8
        return ImageFormat::GIF;
    if (starts_with(data, {0x42, 0x4D}))  // BM
        return ImageFormat::BMP;
    if (starts_with(data, {0x49, 0x49, 0x2A, 0x00}) ||
        starts_with(data, {0x4D, 0x4D, 0x00, 0x2A}))
        return ImageFormat::TIFF;
    if (data.size() >= 4 && data[0] == 0x01 && data[1] == 0x00 &&
        data[2] == 0x00 && data[3] == 0x00)
        return ImageFormat::EMF;
    if (starts_with(data, {0xD7, 0xCD, 0xC6, 0x9A}))
        return ImageFormat::WMF;
    return ImageFormat::UNKNOWN;
}

std::pair<int, int> png_dimensions(std::span<const std::uint8_t> data) {
    // IHDR chunk starts at offset 8 (after signature), chunk length at 8,
    // chunk type at 12, width at 16, height at 20
    if (data.size() < 24) return {0, 0};
    auto w = static_cast<int>(read_be32(data.data() + 16));
    auto h = static_cast<int>(read_be32(data.data() + 20));
    return {w, h};
}

std::pair<int, int> jpeg_dimensions(std::span<const std::uint8_t> data) {
    // Scan for SOF0/SOF2 markers (0xFF 0xC0 or 0xFF 0xC2)
    std::size_t i = 2;
    while (i + 1 < data.size()) {
        if (data[i] != 0xFF) break;
        auto marker = data[i + 1];
        if (marker == 0xC0 || marker == 0xC2) {
            if (i + 9 < data.size()) {
                auto h = static_cast<int>(read_be16(data.data() + i + 5));
                auto w = static_cast<int>(read_be16(data.data() + i + 7));
                return {w, h};
            }
            break;
        }
        if (marker == 0xD9 || marker == 0xDA) break;  // EOI or SOS
        if (i + 3 < data.size()) {
            auto len = read_be16(data.data() + i + 2);
            i += 2 + len;
        } else {
            break;
        }
    }
    return {0, 0};
}

std::pair<int, int> gif_dimensions(std::span<const std::uint8_t> data) {
    if (data.size() < 10) return {0, 0};
    auto w = static_cast<int>(read_le16(data.data() + 6));
    auto h = static_cast<int>(read_le16(data.data() + 8));
    return {w, h};
}

std::pair<int, int> bmp_dimensions(std::span<const std::uint8_t> data) {
    if (data.size() < 26) return {0, 0};
    auto w = static_cast<int>(read_le32(data.data() + 18));
    auto h = static_cast<int>(read_le32(data.data() + 22));
    if (h < 0) h = -h;  // bottom-up BMP
    return {w, h};
}

}  // namespace

std::pair<int, int> get_image_dimensions(std::span<const std::uint8_t> data) {
    switch (detect_format(data)) {
        case ImageFormat::PNG:  return png_dimensions(data);
        case ImageFormat::JPEG: return jpeg_dimensions(data);
        case ImageFormat::GIF:  return gif_dimensions(data);
        case ImageFormat::BMP:  return bmp_dimensions(data);
        default:                return {0, 0};
    }
}

std::string guess_content_type(std::span<const std::uint8_t> data) {
    switch (detect_format(data)) {
        case ImageFormat::PNG:  return "image/png";
        case ImageFormat::JPEG: return "image/jpeg";
        case ImageFormat::GIF:  return "image/gif";
        case ImageFormat::BMP:  return "image/bmp";
        case ImageFormat::TIFF: return "image/tiff";
        case ImageFormat::EMF:  return "image/x-emf";
        case ImageFormat::WMF:  return "image/x-wmf";
        default:                return "application/octet-stream";
    }
}

std::string guess_extension(std::span<const std::uint8_t> data) {
    switch (detect_format(data)) {
        case ImageFormat::PNG:  return "png";
        case ImageFormat::JPEG: return "jpeg";
        case ImageFormat::GIF:  return "gif";
        case ImageFormat::BMP:  return "bmp";
        case ImageFormat::TIFF: return "tiff";
        case ImageFormat::EMF:  return "emf";
        case ImageFormat::WMF:  return "wmf";
        default:                return "bin";
    }
}

} // namespace Aspose::Slides::Foss::image_utils
