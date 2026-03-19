// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_geometry_shape.h>

namespace Aspose::Slides::Foss {

class IPictureFillFormat;
class IPictureFrameLock;

/// Represents a frame with a picture inside.
class IPictureFrame : public IGeometryShape {
public:
    ~IPictureFrame() override = default;

    /// Returns PictureFrame's locks. Read-only.
    /// @return Pointer to the picture frame lock, or nullptr if not available.
    [[nodiscard]] virtual IPictureFrameLock* picture_frame_lock() const = 0;

    /// Returns the PictureFillFormat object for a picture frame. Read-only.
    /// @return Pointer to the picture fill format, or nullptr if not set.
    [[nodiscard]] virtual IPictureFillFormat* picture_format() = 0;

    /// Returns the scale of height relative to original picture size.
    /// Value 1.0 corresponds to 100%. Read/write.
    [[nodiscard]] virtual double relative_scale_height() const = 0;

    /// Sets the scale of height relative to original picture size.
    virtual void set_relative_scale_height(double value) = 0;

    /// Returns the scale of width relative to original picture size.
    /// Value 1.0 corresponds to 100%. Read/write.
    [[nodiscard]] virtual double relative_scale_width() const = 0;

    /// Sets the scale of width relative to original picture size.
    virtual void set_relative_scale_width(double value) = 0;

protected:
    IPictureFrame() = default;
};

} // namespace Aspose::Slides::Foss
