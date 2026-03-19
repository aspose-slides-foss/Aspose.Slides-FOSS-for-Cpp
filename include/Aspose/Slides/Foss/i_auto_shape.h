// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

#include <Aspose/Slides/Foss/i_geometry_shape.h>

namespace Aspose::Slides::Foss {

class GeometryShape;
class TextFrame;

/// Represents an AutoShape.
class IAutoShape : public virtual IGeometryShape {
public:
    ~IAutoShape() override = default;

    /// Returns the TextFrame for the AutoShape, or nullptr if none. Read-only.
    [[nodiscard]] virtual TextFrame* text_frame() = 0;
    [[nodiscard]] virtual const TextFrame* text_frame() const = 0;

    /// Specifies if the shape is a text box.
    [[nodiscard]] virtual bool is_text_box() const = 0;

    /// Returns this shape as a GeometryShape reference. Read-only.
    [[nodiscard]] virtual GeometryShape& as_i_geometry_shape() = 0;
    [[nodiscard]] virtual const GeometryShape& as_i_geometry_shape() const = 0;

    /// Adds a text frame with the given text, replacing any existing one.
    virtual TextFrame& add_text_frame(std::string_view text) = 0;

protected:
    IAutoShape() = default;
};

} // namespace Aspose::Slides::Foss
