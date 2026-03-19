// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_three_d_param_source.h>
#include <Aspose/Slides/Foss/material_preset_type.h>

namespace Aspose::Slides::Foss {

class Camera;
class ColorFormat;
class LightRig;
class ShapeBevel;

/// Interface representing 3-D properties.
class IThreeDFormat : public IThreeDParamSource {
public:
    ~IThreeDFormat() override = default;

    /// Returns or sets the width of a 3D contour.
    [[nodiscard]] virtual double contour_width() const = 0;
    virtual void set_contour_width(double value) = 0;

    /// Returns or sets the height of an extrusion effect.
    [[nodiscard]] virtual double extrusion_height() const = 0;
    virtual void set_extrusion_height(double value) = 0;

    /// Returns or sets the depth of a 3D shape.
    [[nodiscard]] virtual double depth() const = 0;
    virtual void set_depth(double value) = 0;

    /// Returns the top bevel properties. Read-only.
    [[nodiscard]] virtual ShapeBevel& bevel_top() = 0;

    /// Returns the bottom bevel properties. Read-only.
    [[nodiscard]] virtual ShapeBevel& bevel_bottom() = 0;

    /// Returns the contour color. Read-only.
    [[nodiscard]] virtual ColorFormat& contour_color() = 0;

    /// Returns the extrusion color. Read-only.
    [[nodiscard]] virtual ColorFormat& extrusion_color() = 0;

    /// Returns the camera properties. Read-only.
    [[nodiscard]] virtual Camera& camera() = 0;

    /// Returns the light rig properties. Read-only.
    [[nodiscard]] virtual LightRig& light_rig() = 0;

    /// Returns or sets the type of a material.
    [[nodiscard]] virtual MaterialPresetType material() const = 0;
    virtual void set_material(MaterialPresetType value) = 0;

protected:
    IThreeDFormat() = default;
};

} // namespace Aspose::Slides::Foss
