// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/adjust_value_collection.h>
#include <Aspose/Slides/Foss/i_geometry_shape.h>
#include <Aspose/Slides/Foss/shape.h>

namespace Aspose::Slides::Foss {

/// Represents the parent class for all geometric shapes.
class GeometryShape : public Shape, public virtual IGeometryShape {
public:
    ~GeometryShape() override = default;

    /// Returns nullptr — shape style is not yet implemented.
    [[nodiscard]] IShapeStyle* shape_style() override { return nullptr; }
    [[nodiscard]] const IShapeStyle* shape_style() const override { return nullptr; }

    /// Returns the geometry preset type.
    [[nodiscard]] ShapeType shape_type() const override { return Shape::shape_type(); }

    /// Sets the geometry preset type.
    void set_shape_type(ShapeType value) override { Shape::set_shape_type(value); }

    /// Returns the collection of shape's adjustment values.
    [[nodiscard]] AdjustValueCollection& adjustments() noexcept override { return adjustments_; }
    [[nodiscard]] const AdjustValueCollection& adjustments() const noexcept override { return adjustments_; }

protected:
    GeometryShape() = default;
    GeometryShape(ShapeType type, double x, double y, double w, double h)
        : Shape(type, x, y, w, h) {}

private:
    AdjustValueCollection adjustments_;
};

} // namespace Aspose::Slides::Foss
