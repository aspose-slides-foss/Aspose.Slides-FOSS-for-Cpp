// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

namespace Aspose::Slides::Foss {

class PPImage;

/// Represents a collection of presentation images.
class IImageCollection {
public:
    virtual ~IImageCollection() = default;

    /// Returns the number of images in the collection.
    [[nodiscard]] virtual std::size_t size() const noexcept = 0;

    /// Adds an image from raw bytes and returns a reference to the PPImage.
    /// Deduplicates: if the same binary data already exists, returns the existing image.
    virtual PPImage& add_image(std::span<const std::uint8_t> data) = 0;

    /// Returns the image at the given index.
    [[nodiscard]] virtual PPImage& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const PPImage& operator[](std::size_t index) const = 0;

protected:
    IImageCollection() = default;
};

} // namespace Aspose::Slides::Foss
