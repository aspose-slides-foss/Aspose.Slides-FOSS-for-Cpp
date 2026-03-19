// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/image.h>

#include <fstream>
#include <stdexcept>

#include <Aspose/Slides/Foss/image_utils.h>

namespace Aspose::Slides::Foss {

Image::Image(std::vector<std::uint8_t> data, std::string content_type)
    : data_(std::move(data)), content_type_(std::move(content_type)) {
    auto [w, h] = image_utils::get_image_dimensions(data_);
    width_ = w;
    height_ = h;
}

Drawing::Size Image::size() const { return {width_, height_}; }
int Image::width() const { return width_; }
int Image::height() const { return height_; }

void Image::save(std::string_view filename) const {
    std::ofstream f(std::string(filename), std::ios::binary);
    if (!f) {
        throw std::runtime_error("Cannot open file for writing: " +
                                 std::string(filename));
    }
    f.write(reinterpret_cast<const char*>(data_.data()),
            static_cast<std::streamsize>(data_.size()));
}

void Image::save(std::ostream& stream) const {
    stream.write(reinterpret_cast<const char*>(data_.data()),
                 static_cast<std::streamsize>(data_.size()));
}

std::span<const std::uint8_t> Image::data() const noexcept { return data_; }

const std::string& Image::content_type() const noexcept {
    return content_type_;
}

} // namespace Aspose::Slides::Foss
