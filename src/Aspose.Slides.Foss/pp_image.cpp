// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/pp_image.h>

#include <Aspose/Slides/Foss/image.h>
#include <Aspose/Slides/Foss/image_utils.h>

namespace Aspose::Slides::Foss {

PPImage::PPImage(std::vector<std::uint8_t> data, std::string content_type)
    : data_(std::move(data)), content_type_(std::move(content_type)) {
    auto [w, h] = image_utils::get_image_dimensions(data_);
    width_ = w;
    height_ = h;
}

void PPImage::init_internal(Internal::opc::OpcPackage* package,
                            std::string part_name,
                            std::vector<std::uint8_t> image_data,
                            std::string content_type) {
    package_ = package;
    part_name_ = std::move(part_name);
    data_ = std::move(image_data);
    content_type_ = std::move(content_type);
    auto [w, h] = image_utils::get_image_dimensions(data_);
    width_ = w;
    height_ = h;
}

std::vector<std::uint8_t> PPImage::binary_data() const { return data_; }

std::unique_ptr<IImage> PPImage::image() const {
    return std::make_unique<Image>(data_, content_type_);
}

const std::string& PPImage::content_type() const { return content_type_; }
int PPImage::width() const { return width_; }
int PPImage::height() const { return height_; }
int PPImage::x() const { return 0; }
int PPImage::y() const { return 0; }

void PPImage::replace_image(std::span<const std::uint8_t> new_data) {
    data_.assign(new_data.begin(), new_data.end());
    content_type_ = image_utils::guess_content_type(data_);
    auto [w, h] = image_utils::get_image_dimensions(data_);
    width_ = w;
    height_ = h;
}

std::span<const std::uint8_t> PPImage::raw_data() const noexcept {
    return data_;
}

const std::string& PPImage::part_name() const noexcept {
    return part_name_;
}

void PPImage::set_part_name(std::string value) {
    part_name_ = std::move(value);
}

Internal::opc::OpcPackage* PPImage::package() const noexcept {
    return package_;
}

} // namespace Aspose::Slides::Foss
