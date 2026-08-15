// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/camera.h>
#include <Aspose/Slides/Foss/light_rig.h>
#include <Aspose/Slides/Foss/material_preset_type.h>
#include <Aspose/Slides/Foss/shape_bevel.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents 3D formatting properties of a shape.
class ThreeDFormat final {
public:
    ThreeDFormat() = default;

    /// Initialize XML-backed 3D format.
    /// @param parent_element The XML element containing scene3d/sp3d (e.g., <p:spPr>).
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node parent_element,
                       std::function<void()> save_callback);

    /// Get the <a:sp3d> element if it exists.
    [[nodiscard]] pugi::xml_node get_sp3d() const;

    /// Get or create the <a:sp3d> element at the correct OOXML position.
    pugi::xml_node ensure_sp3d();

    /// Get the <a:scene3d> element if it exists.
    [[nodiscard]] pugi::xml_node get_scene3d() const;

    /// Get or create the <a:scene3d> element at the correct OOXML position.
    pugi::xml_node ensure_scene3d();

    /// Save changes via the save callback.
    void save();

    /// Returns true if any 3D properties have been set.
    [[nodiscard]] bool has_data() const noexcept;

    /// Serialize 3D formatting to an XML spPr node (for from-scratch save).
    void serialize_to_xml(pugi::xml_node sp_pr) const;

    /// Returns the top bevel properties (ensures sp3d element exists).
    [[nodiscard]] ShapeBevel& bevel_top();
    [[nodiscard]] const ShapeBevel& bevel_top() const noexcept { return bevel_top_; }

    /// Returns the bottom bevel properties (ensures sp3d element exists).
    [[nodiscard]] ShapeBevel& bevel_bottom();
    [[nodiscard]] const ShapeBevel& bevel_bottom() const noexcept { return bevel_bottom_; }

    /// Returns the camera properties (ensures scene3d element exists).
    [[nodiscard]] Camera& camera();
    [[nodiscard]] const Camera& camera() const noexcept { return camera_; }

    /// Returns the light rig properties (ensures scene3d element exists).
    [[nodiscard]] LightRig& light_rig();
    [[nodiscard]] const LightRig& light_rig() const noexcept { return light_rig_; }

    /// Returns the extrusion depth.
    [[nodiscard]] double depth() const noexcept { return depth_; }
    void set_depth(double value) noexcept;

    /// Returns the extrusion height. This is the same OOXML attribute as
    /// depth() - a:sp3d/@extrusionH - under its other name.
    [[nodiscard]] double extrusion_height() const noexcept { return extrusion_height_; }
    void set_extrusion_height(double value) noexcept;

    /// Returns the extrusion color, `a:sp3d/a:extrusionClr`.
    ///
    /// Mutating it writes the element straight into the backing XML when this
    /// object is bound to one, and is picked up by serialize_to_xml() when it
    /// is not.
    [[nodiscard]] SimpleColorFormat& extrusion_color() noexcept { return extrusion_color_; }
    [[nodiscard]] const SimpleColorFormat& extrusion_color() const noexcept { return extrusion_color_; }

    /// Returns the contour width.
    [[nodiscard]] double contour_width() const noexcept { return contour_width_; }
    void set_contour_width(double value) noexcept;

    /// Returns the contour color, `a:sp3d/a:contourClr`. See extrusion_color().
    [[nodiscard]] SimpleColorFormat& contour_color() noexcept { return contour_color_; }
    [[nodiscard]] const SimpleColorFormat& contour_color() const noexcept { return contour_color_; }

    /// Returns the material preset type.
    [[nodiscard]] MaterialPresetType material() const noexcept { return material_; }
    void set_material(MaterialPresetType value) noexcept;

private:
    /// Bind the camera and light rig to a scene3d element and make sure both
    /// of the children CT_Scene3D requires exist.
    void init_scene3d_children(pugi::xml_node scene3d);

    /// Rewrite `a:extrusionClr` and `a:contourClr` from the two colour models.
    void write_sp3d_colors();

    ShapeBevel bevel_top_;
    ShapeBevel bevel_bottom_;
    Camera camera_;
    LightRig light_rig_;
    double depth_ = 0.0;
    double extrusion_height_ = 0.0;
    SimpleColorFormat extrusion_color_;
    double contour_width_ = 0.0;
    SimpleColorFormat contour_color_;
    MaterialPresetType material_ = MaterialPresetType::NOT_DEFINED;

    pugi::xml_node parent_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
