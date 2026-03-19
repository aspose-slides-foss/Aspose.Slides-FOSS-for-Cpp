// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <utility>

namespace Aspose::Slides::Foss::image_utils {

/// Returns the width and height of an image from its raw bytes.
/// Supports PNG, JPEG, GIF, and BMP formats.
/// Returns {0, 0} if the format is not recognized.
std::pair<int, int> get_image_dimensions(std::span<const std::uint8_t> data);

/// Guesses the MIME content type from image magic bytes.
/// Returns "application/octet-stream" if unrecognized.
std::string guess_content_type(std::span<const std::uint8_t> data);

/// Guesses the file extension (without dot) from image magic bytes.
/// Returns "bin" if unrecognized.
std::string guess_extension(std::span<const std::uint8_t> data);

} // namespace Aspose::Slides::Foss::image_utils
