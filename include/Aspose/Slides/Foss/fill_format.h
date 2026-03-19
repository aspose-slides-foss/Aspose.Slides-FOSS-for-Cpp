// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <string_view>

#include <Aspose/Slides/Foss/fill_type.h>
#include <Aspose/Slides/Foss/gradient_format.h>
#include <Aspose/Slides/Foss/i_fill_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/pattern_format.h>
#include <Aspose/Slides/Foss/picture_fill_format.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents the fill formatting properties of a shape.
class FillFormat final : public IFillFormat {
public:
    FillFormat() = default;
    ~FillFormat() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed fill format.
    /// @param parent_element Any XML element that contains fill children
    ///        (e.g., <p:spPr>, <p:bgPr>, <a:tcPr>, <a:rPr>).
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node parent_element,
                       std::function<void()> save_callback);

    /// Find the first fill child element in the parent.
    /// @return The fill element node, or an empty node if none found.
    [[nodiscard]] pugi::xml_node find_fill_element() const;

    /// Remove all existing fill child elements from parent.
    void remove_fill_elements();

    /// Insert a fill element at the correct OOXML position in the parent.
    /// Fill elements must appear after geometry and before <a:ln>.
    /// @param tag The qualified fill element tag (e.g., "a:solidFill").
    /// @return The newly inserted element.
    pugi::xml_node insert_fill_element(std::string_view tag);

    /// Get existing fill element of given tag, or create it (removing others).
    /// Adds default children for gradient and picture fills.
    /// @param tag The qualified fill element tag.
    /// @return The fill element node.
    pugi::xml_node get_or_create_fill(std::string_view tag);

    /// Save changes via the save callback.
    void save();

    /// Serialize the in-memory fill format state to XML under the given spPr node.
    /// Used during Presentation::save() for shapes without XML backing.
    void serialize_to_xml(pugi::xml_node sp_pr) const;

    // -- Public property API ----------------------------------------------

    /// Returns the fill type.
    [[nodiscard]] FillType fill_type() const noexcept override { return fill_type_; }
    void set_fill_type(FillType value) noexcept override { fill_type_ = value; }

    /// Returns the solid fill color format.
    [[nodiscard]] SimpleColorFormat& solid_fill_color() noexcept override { return solid_fill_color_; }
    [[nodiscard]] const SimpleColorFormat& solid_fill_color() const noexcept override { return solid_fill_color_; }

    /// Returns the gradient fill format.
    [[nodiscard]] GradientFormat& gradient_format() noexcept override { return gradient_format_; }
    [[nodiscard]] const GradientFormat& gradient_format() const noexcept override { return gradient_format_; }

    /// Returns the pattern fill format.
    [[nodiscard]] PatternFormat& pattern_format() noexcept override { return pattern_format_; }
    [[nodiscard]] const PatternFormat& pattern_format() const noexcept override { return pattern_format_; }

    /// Returns the picture fill format.
    [[nodiscard]] PictureFillFormat& picture_fill_format() noexcept override {
        return picture_fill_;
    }
    [[nodiscard]] const PictureFillFormat& picture_fill_format() const noexcept override {
        return picture_fill_;
    }

    /// Determines whether the fill should be rotated with shape.
    [[nodiscard]] NullableBool rotate_with_shape() const noexcept override { return rotate_with_shape_; }
    void set_rotate_with_shape(NullableBool value) noexcept override { rotate_with_shape_ = value; }

private:
    FillType fill_type_ = FillType::NOT_DEFINED;
    SimpleColorFormat solid_fill_color_;
    GradientFormat gradient_format_;
    PatternFormat pattern_format_;
    PictureFillFormat picture_fill_;
    NullableBool rotate_with_shape_ = NullableBool::NOT_DEFINED;

    pugi::xml_node parent_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
