// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <Aspose/Slides/Foss/i_line_format.h>
#include <Aspose/Slides/Foss/line_fill_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents the line (outline) formatting properties.
class LineFormat final : public ILineFormat {
public:
    LineFormat() = default;
    ~LineFormat() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed line format.
    /// @param parent_element Any XML element that may contain <a:ln>
    ///        (e.g., <p:spPr>, <a:rPr>).
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    /// @param ln_tag Optional custom tag to use instead of "a:ln"
    ///        (e.g., "a:uLn" for underline).
    void init_internal(pugi::xml_node parent_element,
                       std::function<void()> save_callback,
                       std::string_view ln_tag = "");

    /// Get the <a:ln> element if it exists.
    /// @return The ln element node, or an empty node if not found.
    [[nodiscard]] pugi::xml_node get_ln() const;

    /// Get or create the <a:ln> element at the correct OOXML position.
    /// For spPr children: xfrm, geometry, fill, ln, effects.
    /// For tcPr children: lnL, lnR, lnT, lnB, lnTlToBr, lnBlToTr.
    /// @return The ln element node.
    pugi::xml_node ensure_ln();

    /// Insert a child element into <a:ln> at the correct OOXML position.
    /// @param ln The ln element to insert into.
    /// @param tag The qualified child element tag.
    /// @return The newly inserted element.
    pugi::xml_node insert_ln_child(pugi::xml_node ln, std::string_view tag);

    /// Save changes via the save callback.
    void save();

    /// Serialize the in-memory line format state to XML under the given spPr node.
    /// Used during Presentation::save() for shapes without XML backing.
    void serialize_to_xml(pugi::xml_node sp_pr) const;

    /// Get an arrowhead attribute value.
    /// @param end_tag The arrowhead element tag (e.g., "a:headEnd", "a:tailEnd").
    /// @param attr The attribute name.
    /// @return The attribute value, or std::nullopt if not found.
    [[nodiscard]] std::optional<std::string> get_arrow_attr(
        std::string_view end_tag, std::string_view attr) const;

    /// Set an arrowhead attribute value.
    /// @param end_tag The arrowhead element tag (e.g., "a:headEnd", "a:tailEnd").
    /// @param attr The attribute name.
    /// @param value The value to set, or std::nullopt to remove the attribute.
    void set_arrow_attr(std::string_view end_tag, std::string_view attr,
                        const std::optional<std::string>& value);

    // -- Public property API ----------------------------------------------

    /// Returns true if line format is not defined (all defaults). Read-only.
    [[nodiscard]] bool is_format_not_defined() const noexcept override {
        return width_ == 0.0
            && dash_style_ == LineDashStyle::NOT_DEFINED
            && custom_dash_pattern_.empty()
            && cap_style_ == LineCapStyle::NOT_DEFINED
            && join_style_ == LineJoinStyle::NOT_DEFINED
            && style_ == LineStyle::NOT_DEFINED
            && alignment_ == LineAlignment::NOT_DEFINED
            && miter_limit_ == 0.0
            && begin_arrow_style_ == LineArrowheadStyle::NOT_DEFINED
            && begin_arrow_width_ == LineArrowheadWidth::NOT_DEFINED
            && begin_arrow_length_ == LineArrowheadLength::NOT_DEFINED
            && end_arrow_style_ == LineArrowheadStyle::NOT_DEFINED
            && end_arrow_width_ == LineArrowheadWidth::NOT_DEFINED
            && end_arrow_length_ == LineArrowheadLength::NOT_DEFINED;
    }

    /// Returns the fill format of a line.
    [[nodiscard]] LineFillFormat& fill_format() noexcept override { return fill_format_; }
    [[nodiscard]] const LineFillFormat& fill_format() const noexcept override { return fill_format_; }

    /// Returns the line width in points.
    [[nodiscard]] double width() const noexcept override { return width_; }
    void set_width(double value) noexcept override { width_ = value; }

    /// Returns the line dash style.
    [[nodiscard]] LineDashStyle dash_style() const noexcept override { return dash_style_; }
    void set_dash_style(LineDashStyle value) noexcept override { dash_style_ = value; }

    /// Returns the custom dash pattern.
    [[nodiscard]] std::vector<float> custom_dash_pattern() const override { return custom_dash_pattern_; }
    void set_custom_dash_pattern(std::vector<float> value) override { custom_dash_pattern_ = std::move(value); }

    /// Returns the line cap style.
    [[nodiscard]] LineCapStyle cap_style() const noexcept override { return cap_style_; }
    void set_cap_style(LineCapStyle value) noexcept override { cap_style_ = value; }

    /// Returns the line style (single, double, etc.).
    [[nodiscard]] LineStyle style() const noexcept override { return style_; }
    void set_style(LineStyle value) noexcept override { style_ = value; }

    /// Returns the line alignment.
    [[nodiscard]] LineAlignment alignment() const noexcept override { return alignment_; }
    void set_alignment(LineAlignment value) noexcept override { alignment_ = value; }

    /// Returns the line join style.
    [[nodiscard]] LineJoinStyle join_style() const noexcept override { return join_style_; }
    void set_join_style(LineJoinStyle value) noexcept override { join_style_ = value; }

    /// Returns the miter limit of a line.
    [[nodiscard]] double miter_limit() const noexcept override { return miter_limit_; }
    void set_miter_limit(double value) noexcept override { miter_limit_ = value; }

    /// Returns the begin arrowhead style.
    [[nodiscard]] LineArrowheadStyle begin_arrowhead_style() const noexcept override { return begin_arrow_style_; }
    void set_begin_arrowhead_style(LineArrowheadStyle value) noexcept override { begin_arrow_style_ = value; }

    /// Returns the begin arrowhead width.
    [[nodiscard]] LineArrowheadWidth begin_arrowhead_width() const noexcept override { return begin_arrow_width_; }
    void set_begin_arrowhead_width(LineArrowheadWidth value) noexcept override { begin_arrow_width_ = value; }

    /// Returns the begin arrowhead length.
    [[nodiscard]] LineArrowheadLength begin_arrowhead_length() const noexcept override { return begin_arrow_length_; }
    void set_begin_arrowhead_length(LineArrowheadLength value) noexcept override { begin_arrow_length_ = value; }

    /// Returns the end arrowhead style.
    [[nodiscard]] LineArrowheadStyle end_arrowhead_style() const noexcept override { return end_arrow_style_; }
    void set_end_arrowhead_style(LineArrowheadStyle value) noexcept override { end_arrow_style_ = value; }

    /// Returns the end arrowhead width.
    [[nodiscard]] LineArrowheadWidth end_arrowhead_width() const noexcept override { return end_arrow_width_; }
    void set_end_arrowhead_width(LineArrowheadWidth value) noexcept override { end_arrow_width_ = value; }

    /// Returns the end arrowhead length.
    [[nodiscard]] LineArrowheadLength end_arrowhead_length() const noexcept override { return end_arrow_length_; }
    void set_end_arrowhead_length(LineArrowheadLength value) noexcept override { end_arrow_length_ = value; }

private:
    double width_ = 0.0;
    LineDashStyle dash_style_ = LineDashStyle::NOT_DEFINED;
    std::vector<float> custom_dash_pattern_;
    LineCapStyle cap_style_ = LineCapStyle::NOT_DEFINED;
    LineJoinStyle join_style_ = LineJoinStyle::NOT_DEFINED;
    LineStyle style_ = LineStyle::NOT_DEFINED;
    LineAlignment alignment_ = LineAlignment::NOT_DEFINED;
    double miter_limit_ = 0.0;
    LineArrowheadStyle begin_arrow_style_ = LineArrowheadStyle::NOT_DEFINED;
    LineArrowheadWidth begin_arrow_width_ = LineArrowheadWidth::NOT_DEFINED;
    LineArrowheadLength begin_arrow_length_ = LineArrowheadLength::NOT_DEFINED;
    LineArrowheadStyle end_arrow_style_ = LineArrowheadStyle::NOT_DEFINED;
    LineArrowheadWidth end_arrow_width_ = LineArrowheadWidth::NOT_DEFINED;
    LineArrowheadLength end_arrow_length_ = LineArrowheadLength::NOT_DEFINED;
    LineFillFormat fill_format_;

    pugi::xml_node parent_element_;
    std::function<void()> save_callback_;
    std::string ln_tag_;  ///< Resolved tag for the ln element (default: "a:ln").
};

} // namespace Aspose::Slides::Foss
