// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss::Effects {

class IImageTransformOperation;

/// Interface representing a blur effect that is applied to the entire shape,
/// including its fill. All color channels, including alpha, are affected.
class IBlur {
public:
    virtual ~IBlur() = default;

    /// Returns the blur radius in points. Default 0.
    [[nodiscard]] virtual double radius() const = 0;
    /// Sets the blur radius in points.
    virtual void set_radius(double value) = 0;

    /// Returns whether the bounds of the object should be grown as a result
    /// of the blurring. Default true.
    [[nodiscard]] virtual bool grow() const = 0;
    /// Sets whether the bounds grow with the blur.
    virtual void set_grow(bool value) = 0;

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] virtual IImageTransformOperation& as_i_image_transform_operation() = 0;
};

} // namespace Aspose::Slides::Foss::Effects
