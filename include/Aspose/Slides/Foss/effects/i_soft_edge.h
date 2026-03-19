// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing a Soft Edge effect.
/// The edges of the shape are blurred, while the fill is not affected.
class ISoftEdge {
public:
    virtual ~ISoftEdge() = default;

    /// Returns the radius of blur applied to the edges, in points. Default 0.
    [[nodiscard]] virtual double radius() const = 0;
    /// Sets the radius of blur applied to the edges, in points.
    virtual void set_radius(double value) = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
