// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <Aspose/Slides/Foss/i_image.h>

namespace Aspose::Slides::Foss {

/// Represents a raster or vector image backed by in-memory data.
class Image final : public IImage {
public:
    /// Constructs an Image from raw bytes and content type.
    Image(std::vector<std::uint8_t> data, std::string content_type);

    /// Gets the size of the image in pixels.
    [[nodiscard]] Drawing::Size size() const override;

    /// Gets the width of the image in pixels.
    [[nodiscard]] int width() const override;

    /// Gets the height of the image in pixels.
    [[nodiscard]] int height() const override;

    /// Saves the image to a file.
    void save(std::string_view filename) const override;

    /// Saves the image to an output stream.
    void save(std::ostream& stream) const override;

    /// Returns a read-only view of the raw image data.
    [[nodiscard]] std::span<const std::uint8_t> data() const noexcept;

    /// Returns the MIME content type of the image.
    [[nodiscard]] const std::string& content_type() const noexcept;

private:
    std::vector<std::uint8_t> data_;
    std::string content_type_;
    int width_ = 0;
    int height_ = 0;
};

} // namespace Aspose::Slides::Foss
