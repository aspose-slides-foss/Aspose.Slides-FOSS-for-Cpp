// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/bevel_preset_type.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents the bevel properties of a shape's 3D surface.
class ShapeBevel final {
public:
    /// @param is_top_bevel If true, this represents <a:bevelT>; otherwise <a:bevelB>.
    explicit ShapeBevel(bool is_top_bevel = true);

    /// Initialize XML-backed bevel.
    /// @param sp3d_element The <a:sp3d> XML element that contains the bevel child.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node sp3d_element,
                       std::function<void()> save_callback);

    /// Save changes via the save callback.
    void save();

    /// Returns the bevel preset type.
    [[nodiscard]] BevelPresetType bevel_type() const noexcept { return bevel_type_; }
    void set_bevel_type(BevelPresetType value) noexcept;

    /// Returns the bevel width.
    [[nodiscard]] double width() const noexcept { return width_; }
    void set_width(double value) noexcept;

    /// Returns the bevel height.
    [[nodiscard]] double height() const noexcept { return height_; }
    void set_height(double value) noexcept;

    /// Get or create the bevel child element within sp3d.
    pugi::xml_node ensure_bevel();

    /// Returns true if this bevel has been initialized with a parent XML element.
    [[nodiscard]] bool has_parent() const noexcept { return static_cast<bool>(sp3d_element_); }

private:
    bool is_top_;
    BevelPresetType bevel_type_ = BevelPresetType::NOT_DEFINED;
    double width_ = 0.0;
    double height_ = 0.0;

    pugi::xml_node sp3d_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
