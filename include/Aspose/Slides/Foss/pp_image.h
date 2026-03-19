// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include <Aspose/Slides/Foss/ipp_image.h>

namespace Aspose::Slides::Foss::Internal::opc { class OpcPackage; }

namespace Aspose::Slides::Foss {

class IImage;

/// Represents an image stored in a presentation.
class PPImage final : public IPPImage {
public:
    /// Constructs a PPImage from raw image bytes and content type.
    PPImage(std::vector<std::uint8_t> data, std::string content_type);

    /// Internal initialization with OPC package reference.
    ///
    /// @param package  The OPC package containing the image.
    /// @param part_name The part path (e.g., "ppt/media/image1.jpg").
    /// @param image_data Raw image bytes.
    /// @param content_type MIME type of the image.
    void init_internal(Internal::opc::OpcPackage* package,
                       std::string part_name,
                       std::vector<std::uint8_t> image_data,
                       std::string content_type);

    /// Returns a copy of the image's binary data.
    [[nodiscard]] std::vector<std::uint8_t> binary_data() const override;

    /// Returns a copy of the image as an IImage.
    [[nodiscard]] std::unique_ptr<IImage> image() const override;

    /// Returns the MIME content type.
    [[nodiscard]] const std::string& content_type() const override;

    /// Returns the width of the image in pixels.
    [[nodiscard]] int width() const override;

    /// Returns the height of the image in pixels.
    [[nodiscard]] int height() const override;

    /// Returns the X-offset of the image (always 0).
    [[nodiscard]] int x() const override;

    /// Returns the Y-offset of the image (always 0).
    [[nodiscard]] int y() const override;

    /// Replaces the image data with new raw bytes.
    void replace_image(std::span<const std::uint8_t> new_data) override;

    /// Returns a read-only view of the raw image data.
    [[nodiscard]] std::span<const std::uint8_t> raw_data() const noexcept;

    /// Returns the internal part name used for PPTX relationship tracking.
    [[nodiscard]] const std::string& part_name() const noexcept;

    /// Sets the internal part name used for PPTX relationship tracking.
    void set_part_name(std::string value);

    /// Returns the associated OPC package, or nullptr if not set.
    [[nodiscard]] Internal::opc::OpcPackage* package() const noexcept;

private:
    std::vector<std::uint8_t> data_;
    std::string content_type_;
    std::string part_name_;
    Internal::opc::OpcPackage* package_ = nullptr;
    int width_ = 0;
    int height_ = 0;
};

} // namespace Aspose::Slides::Foss
