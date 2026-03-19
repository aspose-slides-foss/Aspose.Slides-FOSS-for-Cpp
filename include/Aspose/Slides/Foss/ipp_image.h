// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <vector>

namespace Aspose::Slides::Foss {

class IImage;

/// Represents an image in a presentation.
class IPPImage {
public:
    virtual ~IPPImage() = default;

    /// Returns a copy of the image's binary data.
    [[nodiscard]] virtual std::vector<std::uint8_t> binary_data() const = 0;

    /// Returns a copy of the image as an IImage.
    [[nodiscard]] virtual std::unique_ptr<IImage> image() const = 0;

    /// Returns the MIME content type.
    [[nodiscard]] virtual const std::string& content_type() const = 0;

    /// Returns the width of the image in pixels.
    [[nodiscard]] virtual int width() const = 0;

    /// Returns the height of the image in pixels.
    [[nodiscard]] virtual int height() const = 0;

    /// Returns the X-offset of the image.
    [[nodiscard]] virtual int x() const = 0;

    /// Returns the Y-offset of the image.
    [[nodiscard]] virtual int y() const = 0;

    /// Replaces the image data with new raw bytes.
    virtual void replace_image(std::span<const std::uint8_t> new_data) = 0;

protected:
    IPPImage() = default;
};

} // namespace Aspose::Slides::Foss
