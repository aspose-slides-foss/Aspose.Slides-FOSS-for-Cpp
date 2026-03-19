// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <string>

#include <Aspose/Slides/Foss/i_hyperlink_container.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/i_slide_component.h>
#include <Aspose/Slides/Foss/shape_type.h>

namespace Aspose::Slides::Foss {

class EffectFormat;
class FillFormat;
class IShapeFrame;
class LineFormat;
class ShapeFrame;
class ThreeDFormat;

/// Represents a shape on a slide.
class IShape : public virtual ISlideComponent,
               public virtual IPresentationComponent,
               public virtual IHyperlinkContainer {
public:
    ~IShape() override = default;

    /// Determines whether the shape is a TextHolder. Read-only.
    [[nodiscard]] virtual bool is_text_holder() const = 0;

    /// Returns the placeholder for a shape, or nullptr. Read-only.
    [[nodiscard]] virtual void* placeholder() const = 0;

    /// Returns the shape's custom data, or nullptr. Read-only.
    [[nodiscard]] virtual void* custom_data() const = 0;

    /// Returns the raw shape frame's properties. Read-only.
    [[nodiscard]] virtual const ShapeFrame& raw_frame() const = 0;
    /// Sets the raw shape frame's properties.
    virtual void set_raw_frame(const ShapeFrame& value) = 0;

    /// Returns the shape frame's properties. Read-only.
    [[nodiscard]] virtual const ShapeFrame& frame() const = 0;
    /// Sets the shape frame's properties.
    virtual void set_frame(const ShapeFrame& value) = 0;

    /// Returns the LineFormat object. Read-only.
    [[nodiscard]] virtual LineFormat& line_format() = 0;

    /// Returns the ThreeDFormat object. Read-only.
    [[nodiscard]] virtual ThreeDFormat& three_d_format() = 0;

    /// Returns the EffectFormat object. Read-only.
    [[nodiscard]] virtual EffectFormat& effect_format() = 0;

    /// Returns the FillFormat object. Read-only.
    [[nodiscard]] virtual FillFormat& fill_format() = 0;

    /// Determines whether the shape is hidden. Read-only.
    [[nodiscard]] virtual bool hidden() const = 0;
    /// Sets whether the shape is hidden.
    virtual void set_hidden(bool value) = 0;

    /// Returns the position of a shape in the z-order. Read-only.
    [[nodiscard]] virtual std::int32_t z_order_position() const = 0;

    /// Returns the number of connection sites on the shape. Read-only.
    [[nodiscard]] virtual std::int32_t connection_site_count() const = 0;

    /// Returns the rotation angle in degrees. Read-only.
    [[nodiscard]] virtual double rotation() const = 0;
    /// Sets the rotation angle in degrees.
    virtual void set_rotation(double value) = 0;

    /// Returns the x-coordinate of the upper-left corner. Read-only.
    [[nodiscard]] virtual double x() const = 0;
    /// Sets the x-coordinate of the upper-left corner.
    virtual void set_x(double value) = 0;

    /// Returns the y-coordinate of the upper-left corner. Read-only.
    [[nodiscard]] virtual double y() const = 0;
    /// Sets the y-coordinate of the upper-left corner.
    virtual void set_y(double value) = 0;

    /// Returns the width of the shape. Read-only.
    [[nodiscard]] virtual double width() const = 0;
    /// Sets the width of the shape.
    virtual void set_width(double value) = 0;

    /// Returns the height of the shape. Read-only.
    [[nodiscard]] virtual double height() const = 0;
    /// Sets the height of the shape.
    virtual void set_height(double value) = 0;

    /// Returns the alternative text associated with a shape. Read-only.
    [[nodiscard]] virtual const std::string& alternative_text() const = 0;
    /// Sets the alternative text associated with a shape.
    virtual void set_alternative_text(std::string value) = 0;

    /// Returns the title of alternative text. Read-only.
    [[nodiscard]] virtual const std::string& alternative_text_title() const = 0;
    /// Sets the title of alternative text.
    virtual void set_alternative_text_title(std::string value) = 0;

    /// Returns the shape name. Read-only.
    [[nodiscard]] virtual const std::string& name() const = 0;
    /// Sets the shape name.
    virtual void set_name(std::string value) = 0;

    /// Gets the 'Mark as decorative' option. Read-only.
    [[nodiscard]] virtual bool is_decorative() const = 0;
    /// Sets the 'Mark as decorative' option.
    virtual void set_is_decorative(bool value) = 0;

    /// Returns a presentation-scoped unique identifier. Read-only.
    [[nodiscard]] virtual std::uint32_t unique_id() const = 0;

    /// Returns a slide-scoped shape identifier. Read-only.
    [[nodiscard]] virtual std::uint32_t office_interop_shape_id() const = 0;

    /// Determines whether the shape is grouped. Read-only.
    [[nodiscard]] virtual bool is_grouped() const = 0;

    /// Returns the shape type.
    [[nodiscard]] virtual ShapeType shape_type() const = 0;
    /// Sets the shape type.
    virtual void set_shape_type(ShapeType value) = 0;

    /// Returns the base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;

protected:
    IShape() = default;
};

} // namespace Aspose::Slides::Foss
