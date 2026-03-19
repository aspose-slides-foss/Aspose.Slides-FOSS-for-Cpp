// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <istream>
#include <memory>
#include <string_view>

#include <Aspose/Slides/Foss/i_image.h>

namespace Aspose::Slides::Foss {

class Image;

/// Factory methods to create IImage instances.
class Images final {
public:
    Images() = delete;

    /// Creates an IImage from a file path.
    [[nodiscard]] static std::unique_ptr<Image> from_file(std::string_view filename);

    /// Creates an IImage from an input stream.
    [[nodiscard]] static std::unique_ptr<Image> from_stream(std::istream& stream);
};

} // namespace Aspose::Slides::Foss
