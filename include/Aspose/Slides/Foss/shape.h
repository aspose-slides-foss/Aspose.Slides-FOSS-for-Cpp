// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/effect_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/i_shape.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/shape_frame.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/three_d_format.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class IBaseSlide;
class IPresentation;

/// Base class for all shapes on a slide.
class Shape : public IShape {
public:
    ~Shape() override = default;

    // -- IShape implementation ------------------------------------------------

    /// Returns the shape type.
    [[nodiscard]] ShapeType shape_type() const override { return shape_type_; }
    /// Sets the shape type.
    void set_shape_type(ShapeType value) override { shape_type_ = value; }

    /// Returns the x-coordinate of the shape.
    [[nodiscard]] double x() const override { return x_; }
    void set_x(double value) override;

    /// Returns the y-coordinate of the shape.
    [[nodiscard]] double y() const override { return y_; }
    void set_y(double value) override;

    /// Returns the width of the shape.
    [[nodiscard]] double width() const override { return width_; }
    void set_width(double value) override;

    /// Returns the height of the shape.
    [[nodiscard]] double height() const override { return height_; }
    void set_height(double value) override;

    /// Returns the rotation angle in degrees.
    [[nodiscard]] double rotation() const override { return rotation_; }
    void set_rotation(double value) override;

    /// Returns the shape name.
    [[nodiscard]] const std::string& name() const override { return name_; }
    void set_name(std::string value) override { name_ = std::move(value); }

    /// Returns the effect format for this shape.
    [[nodiscard]] EffectFormat& effect_format() override { return effect_format_; }
    [[nodiscard]] const EffectFormat& effect_format() const { return effect_format_; }

    /// Returns the fill format for this shape.
    [[nodiscard]] FillFormat& fill_format() override { return fill_format_; }
    [[nodiscard]] const FillFormat& fill_format() const { return fill_format_; }

    /// Returns the line format for this shape.
    [[nodiscard]] LineFormat& line_format() override { return line_format_; }
    [[nodiscard]] const LineFormat& line_format() const { return line_format_; }

    /// Returns the 3D format for this shape.
    [[nodiscard]] ThreeDFormat& three_d_format() override { return three_d_format_; }
    [[nodiscard]] const ThreeDFormat& three_d_format() const { return three_d_format_; }

    /// Determines whether the shape is a TextHolder. Default: false.
    [[nodiscard]] bool is_text_holder() const override { return false; }

    /// Returns the placeholder. Default: nullptr.
    [[nodiscard]] void* placeholder() const override { return nullptr; }

    /// Returns the custom data. Default: nullptr.
    [[nodiscard]] void* custom_data() const override { return nullptr; }

    /// Returns the raw shape frame.
    [[nodiscard]] const ShapeFrame& raw_frame() const override { return frame_; }
    void set_raw_frame(const ShapeFrame& value) override { frame_ = value; sync_from_frame(); }

    /// Returns the shape frame.
    [[nodiscard]] const ShapeFrame& frame() const override { return frame_; }
    void set_frame(const ShapeFrame& value) override { frame_ = value; sync_from_frame(); }

    /// Determines whether the shape is hidden.
    [[nodiscard]] bool hidden() const override { return hidden_; }
    void set_hidden(bool value) override { hidden_ = value; }

    /// Returns the z-order position.
    [[nodiscard]] std::int32_t z_order_position() const override { return z_order_position_; }

    /// Returns the number of connection sites (default 4).
    [[nodiscard]] std::int32_t connection_site_count() const override { return 4; }

    /// Returns the alternative text.
    [[nodiscard]] const std::string& alternative_text() const override { return alternative_text_; }
    void set_alternative_text(std::string value) override { alternative_text_ = std::move(value); }

    /// Returns the alternative text title.
    [[nodiscard]] const std::string& alternative_text_title() const override { return alternative_text_title_; }
    void set_alternative_text_title(std::string value) override { alternative_text_title_ = std::move(value); }

    /// Gets the 'Mark as decorative' option.
    [[nodiscard]] bool is_decorative() const override { return is_decorative_; }
    void set_is_decorative(bool value) override { is_decorative_ = value; }

    /// Returns the presentation-scoped unique identifier.
    [[nodiscard]] std::uint32_t unique_id() const override { return unique_id_; }

    /// Returns the slide-scoped shape identifier.
    [[nodiscard]] std::uint32_t office_interop_shape_id() const override { return office_interop_shape_id_; }

    /// Determines whether the shape is grouped.
    [[nodiscard]] bool is_grouped() const override { return false; }

    /// Returns the base ISlideComponent interface.
    [[nodiscard]] ISlideComponent* as_i_slide_component() override { return nullptr; }

    // -- IPresentationComponent -----------------------------------------------
    [[nodiscard]] IPresentation* presentation() override { return nullptr; }
    [[nodiscard]] const IPresentation* presentation() const override { return nullptr; }

    // -- ISlideComponent ------------------------------------------------------
    [[nodiscard]] IBaseSlide* slide() override { return parent_slide_; }
    [[nodiscard]] const IBaseSlide* slide() const override { return parent_slide_; }
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override { return nullptr; }
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override { return nullptr; }

    /// Sets the z-order position (used internally by ShapeCollection).
    void set_z_order_position(std::int32_t value) { z_order_position_ = value; }

    /// Sets the unique id (used internally).
    void set_unique_id(std::uint32_t value) { unique_id_ = value; }

    /// Sets the office interop shape id (used internally).
    void set_office_interop_shape_id(std::uint32_t value) { office_interop_shape_id_ = value; }

    // -- XML-backed internal API ------------------------------------------------

    /// Initialize this shape from an XML element within a slide part.
    /// @param xml_element The XML node representing this shape (e.g., <p:sp>).
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node xml_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Build a ShapeFrame from the current xfrm element.
    [[nodiscard]] ShapeFrame build_frame() const;

    /// Apply a ShapeFrame's values to the xfrm element.
    void apply_frame(const IShapeFrame& value);

    /// Get the spPr (or grpSpPr) element for this shape.
    /// @return The element node, or an empty node if not found.
    [[nodiscard]] pugi::xml_node get_sp_pr() const;

    /// Get or create the spPr element.
    /// @throws std::runtime_error if the shape has no XML element.
    [[nodiscard]] pugi::xml_node ensure_sp_pr();

    /// Get the cNvPr element from the shape XML.
    /// @return The element node, or an empty node if not found.
    [[nodiscard]] pugi::xml_node get_c_nv_pr() const;

    /// Find the a:xfrm element directly within a shape XML element.
    [[nodiscard]] static pugi::xml_node find_xfrm_in_element(pugi::xml_node xml_element);

    /// Get (type, idx) from <p:ph> element if this shape is a placeholder.
    /// @return A pair of (optional type, idx), or nullopt if not a placeholder.
    [[nodiscard]] std::optional<std::pair<std::optional<std::string>, std::string>>
    get_placeholder_info() const;

    /// Find the xfrm for a matching placeholder in a layout/master XML root.
    [[nodiscard]] static pugi::xml_node find_placeholder_xfrm_in_xml(
        pugi::xml_node root,
        const std::optional<std::string>& ph_type,
        std::string_view ph_idx);

    /// Returns the XML element backing this shape.
    [[nodiscard]] pugi::xml_node xml_element() const { return xml_element_; }

    /// Walk the layout -> master chain to find inherited xfrm for placeholders.
    [[nodiscard]] pugi::xml_node get_inherited_xfrm() const;

    /// Get the a:xfrm element from the shape XML, with placeholder inheritance.
    [[nodiscard]] pugi::xml_node get_xfrm() const;

    /// Get or create the a:xfrm element.
    /// @throws std::runtime_error if the shape has no XML element.
    [[nodiscard]] pugi::xml_node ensure_xfrm();

protected:
    Shape() = default;
    Shape(ShapeType type, double x, double y, double w, double h)
        : shape_type_(type), x_(x), y_(y), width_(w), height_(h),
          frame_(x, y, w, h) {}

private:
    /// Synchronizes x/y/width/height/rotation from the frame object.
    void sync_from_frame() {
        x_ = frame_.x();
        y_ = frame_.y();
        width_ = frame_.width();
        height_ = frame_.height();
        rotation_ = frame_.rotation();
    }

    ShapeType shape_type_ = ShapeType::NOT_DEFINED;
    double x_ = 0;
    double y_ = 0;
    double width_ = 0;
    double height_ = 0;
    double rotation_ = 0;
    std::string name_;
    std::string alternative_text_;
    std::string alternative_text_title_;
    bool hidden_ = false;
    bool is_decorative_ = false;
    std::int32_t z_order_position_ = 0;
    std::uint32_t unique_id_ = 0;
    std::uint32_t office_interop_shape_id_ = 0;
    ShapeFrame frame_;
    EffectFormat effect_format_;
    FillFormat fill_format_;
    LineFormat line_format_;
    ThreeDFormat three_d_format_;

    // XML-backed state
    pugi::xml_node xml_element_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;
};

} // namespace Aspose::Slides::Foss
