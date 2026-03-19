// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/geometry_shape.h>
#include <Aspose/Slides/Foss/i_auto_shape.h>
#include <Aspose/Slides/Foss/text_frame.h>

namespace Aspose::Slides::Foss {

/// Represents an AutoShape.
class AutoShape final : public GeometryShape, public IAutoShape {
public:
    AutoShape() = default;
    AutoShape(ShapeType type, double x, double y, double w, double h)
        : GeometryShape(type, x, y, w, h) {}

    /// Returns the TextFrame for the AutoShape, or nullptr if none.
    [[nodiscard]] TextFrame* text_frame() noexcept override { return text_frame_.get(); }
    [[nodiscard]] const TextFrame* text_frame() const noexcept override { return text_frame_.get(); }

    /// Specifies if the shape is a text box.
    [[nodiscard]] bool is_text_box() const noexcept override { return text_frame_ != nullptr; }

    /// Returns this shape as a GeometryShape reference.
    [[nodiscard]] GeometryShape& as_i_geometry_shape() noexcept override { return *this; }
    [[nodiscard]] const GeometryShape& as_i_geometry_shape() const noexcept override { return *this; }

    /// Adds a text frame with the given text, replacing any existing one.
    /// Lines separated by \\r\\n, \\r, or \\n create separate paragraphs.
    TextFrame& add_text_frame(std::string_view text) override;

    /// Initializes the AutoShape from an XML element, including text frame detection.
    void init_internal(pugi::xml_node xml_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

private:
    std::unique_ptr<TextFrame> text_frame_;
};

} // namespace Aspose::Slides::Foss
