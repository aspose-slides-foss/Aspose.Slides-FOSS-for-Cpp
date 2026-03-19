// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/shape_type.h>

namespace Aspose::Slides::Foss {

class AdjustValueCollection;
class IShapeStyle;

/// Represents the parent class for all geometric shapes.
class IGeometryShape {
public:
    virtual ~IGeometryShape() = default;

    /// Returns the shape's style object. Read-only.
    [[nodiscard]] virtual IShapeStyle* shape_style() = 0;
    [[nodiscard]] virtual const IShapeStyle* shape_style() const = 0;

    /// Returns the geometry preset type.
    /// Note: on value changing all adjustment values will reset to their default values.
    /// Read/write.
    [[nodiscard]] virtual ShapeType shape_type() const = 0;

    /// Sets the geometry preset type.
    virtual void set_shape_type(ShapeType value) = 0;

    /// Returns the collection of shape's adjustment values. Read-only.
    [[nodiscard]] virtual AdjustValueCollection& adjustments() = 0;
    [[nodiscard]] virtual const AdjustValueCollection& adjustments() const = 0;
};

} // namespace Aspose::Slides::Foss
