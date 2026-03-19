// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/images.h>

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/image.h>
#include <Aspose/Slides/Foss/image_utils.h>

namespace Aspose::Slides::Foss {

std::unique_ptr<Image> Images::from_file(std::string_view filename) {
    std::ifstream f(std::string(filename), std::ios::binary);
    if (!f) {
        throw std::runtime_error("Cannot open file: " + std::string(filename));
    }
    std::vector<std::uint8_t> data(
        (std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>());
    auto content_type = image_utils::guess_content_type(data);
    return std::make_unique<Image>(std::move(data), std::move(content_type));
}

std::unique_ptr<Image> Images::from_stream(std::istream& stream) {
    std::vector<std::uint8_t> data(
        (std::istreambuf_iterator<char>(stream)),
        std::istreambuf_iterator<char>());
    auto content_type = image_utils::guess_content_type(data);
    return std::make_unique<Image>(std::move(data), std::move(content_type));
}

} // namespace Aspose::Slides::Foss
