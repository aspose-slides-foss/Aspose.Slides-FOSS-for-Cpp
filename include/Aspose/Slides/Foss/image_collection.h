// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>
#include <vector>

#include <Aspose/Slides/Foss/i_image_collection.h>
#include <Aspose/Slides/Foss/pp_image.h>

namespace Aspose::Slides::Foss {

/// Manages the collection of images in a presentation.
class ImageCollection final : public IImageCollection {
public:
    ImageCollection() = default;
    ImageCollection(const ImageCollection&) = delete;
    ImageCollection& operator=(const ImageCollection&) = delete;
    ~ImageCollection() override;
    ImageCollection(ImageCollection&&) noexcept;
    ImageCollection& operator=(ImageCollection&&) noexcept;

    /// Returns the number of images in the collection.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Adds an image from raw bytes. Deduplicates by content.
    PPImage& add_image(std::span<const std::uint8_t> data) override;

    /// Returns the image at the given index.
    [[nodiscard]] PPImage& operator[](std::size_t index) override;
    [[nodiscard]] const PPImage& operator[](std::size_t index) const override;

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<PPImage>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<PPImage>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;
    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;

private:
    std::vector<std::unique_ptr<PPImage>> images_;
};

} // namespace Aspose::Slides::Foss
