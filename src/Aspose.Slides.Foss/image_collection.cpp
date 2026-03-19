// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/image_collection.h>

#include <algorithm>
#include <stdexcept>

#include <Aspose/Slides/Foss/image_utils.h>
#include <Aspose/Slides/Foss/pp_image.h>

namespace Aspose::Slides::Foss {

ImageCollection::~ImageCollection() = default;
ImageCollection::ImageCollection(ImageCollection&&) noexcept = default;
ImageCollection& ImageCollection::operator=(ImageCollection&&) noexcept = default;

std::size_t ImageCollection::size() const noexcept { return images_.size(); }

PPImage& ImageCollection::add_image(std::span<const std::uint8_t> data) {
    // Check for duplicate images (same binary data)
    for (auto& existing : images_) {
        auto existing_data = existing->raw_data();
        if (existing_data.size() == data.size() &&
            std::equal(data.begin(), data.end(), existing_data.begin())) {
            return *existing;
        }
    }

    auto content_type = image_utils::guess_content_type(data);
    auto img = std::make_unique<PPImage>(
        std::vector<std::uint8_t>(data.begin(), data.end()),
        std::move(content_type));
    auto& ref = *img;
    images_.push_back(std::move(img));
    return ref;
}

PPImage& ImageCollection::operator[](std::size_t index) {
    return *images_.at(index);
}

const PPImage& ImageCollection::operator[](std::size_t index) const {
    return *images_.at(index);
}

ImageCollection::iterator ImageCollection::begin() noexcept { return images_.begin(); }
ImageCollection::iterator ImageCollection::end() noexcept { return images_.end(); }
ImageCollection::const_iterator ImageCollection::begin() const noexcept { return images_.begin(); }
ImageCollection::const_iterator ImageCollection::end() const noexcept { return images_.end(); }

} // namespace Aspose::Slides::Foss
