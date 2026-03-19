// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/drawing/size.h>

namespace Aspose::Slides::Foss {

/// Represents a raster or vector image.
class IImage {
public:
    virtual ~IImage() = default;

    /// Gets the size of the image in pixels.
    [[nodiscard]] virtual Drawing::Size size() const = 0;

    /// Gets the width of the image in pixels.
    [[nodiscard]] virtual int width() const = 0;

    /// Gets the height of the image in pixels.
    [[nodiscard]] virtual int height() const = 0;

    /// Saves the image to a file.
    virtual void save(std::string_view filename) const = 0;

    /// Saves the image to an output stream.
    virtual void save(std::ostream& stream) const = 0;

protected:
    IImage() = default;
};

} // namespace Aspose::Slides::Foss
