// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cmath>
#include <functional>
#include <limits>
#include <string_view>

#include <Aspose/Slides/Foss/i_text_frame_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>
#include <Aspose/Slides/Foss/text_autofit_type.h>
#include <Aspose/Slides/Foss/text_shape_type.h>
#include <Aspose/Slides/Foss/text_vertical_type.h>
#include <Aspose/Slides/Foss/three_d_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents text frame formatting properties.
class TextFrameFormat final : public ITextFrameFormat {
public:
    TextFrameFormat() = default;

    // Every property below is backed by `<a:bodyPr>` once this object is bound
    // to a `<a:txBody>`: the setter writes the element, so an edit to a deck
    // opened from a file reaches the package. An unbound object — the
    // from-scratch path, written out by serialize_body_pr() at save time —
    // keeps its members instead. A getter prefers what the element says and
    // falls back to the member when the attribute is absent, so an unset
    // property still reads as undefined and stays inheritable.

    /// Returns the left margin in points. NaN = undefined.
    [[nodiscard]] double margin_left() const override;
    /// Sets the left margin in points.
    void set_margin_left(double value) override;

    /// Returns the right margin in points. NaN = undefined.
    [[nodiscard]] double margin_right() const override;
    /// Sets the right margin in points.
    void set_margin_right(double value) override;

    /// Returns the top margin in points. NaN = undefined.
    [[nodiscard]] double margin_top() const override;
    /// Sets the top margin in points.
    void set_margin_top(double value) override;

    /// Returns the bottom margin in points. NaN = undefined.
    [[nodiscard]] double margin_bottom() const override;
    /// Sets the bottom margin in points.
    void set_margin_bottom(double value) override;

    /// Returns whether text wraps.
    [[nodiscard]] NullableBool wrap_text() const override;
    /// Sets whether text wraps.
    void set_wrap_text(NullableBool value) override;

    /// Returns the text anchor type.
    [[nodiscard]] TextAnchorType anchoring_type() const override;
    /// Sets the text anchor type.
    void set_anchoring_type(TextAnchorType value) override;

    /// Returns whether text is centered.
    [[nodiscard]] NullableBool center_text() const override;
    /// Sets whether text is centered.
    void set_center_text(NullableBool value) override;

    /// Returns the text vertical type.
    [[nodiscard]] TextVerticalType text_vertical_type() const override;
    /// Sets the text vertical type.
    void set_text_vertical_type(TextVerticalType value) override;

    /// Returns the autofit type.
    [[nodiscard]] TextAutofitType autofit_type() const override;
    /// Sets the autofit type.
    void set_autofit_type(TextAutofitType value) override;

    /// Returns the number of columns.
    [[nodiscard]] int column_count() const override;
    /// Sets the number of columns.
    void set_column_count(int value) override;

    /// Returns the column spacing in points.
    [[nodiscard]] double column_spacing() const override;
    /// Sets the column spacing in points.
    void set_column_spacing(double value) override;

    /// Returns the ThreeDFormat object that represents 3D effect properties for text. Read-only.
    [[nodiscard]] ThreeDFormat& three_d_format() noexcept override { return three_d_format_; }
    /// Returns the ThreeDFormat object that represents 3D effect properties for text. Read-only.
    [[nodiscard]] const ThreeDFormat& three_d_format() const noexcept override { return three_d_format_; }

    /// Returns whether text is kept flat (no 3D rotation).
    [[nodiscard]] bool keep_text_flat() const override { return keep_text_flat_; }
    /// Sets whether text is kept flat (no 3D rotation).
    void set_keep_text_flat(bool value) override { keep_text_flat_ = value; }

    /// Returns the rotation angle in degrees.
    [[nodiscard]] double rotation_angle() const override;
    /// Sets the rotation angle in degrees.
    void set_rotation_angle(double value) override;

    /// Returns the text shape type (transform).
    [[nodiscard]] TextShapeType transform() const override { return transform_; }
    /// Sets the text shape type (transform).
    void set_transform(TextShapeType value) override { transform_ = value; }

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an existing `<a:txBody>` XML node.
    /// @param txbody_element The `<a:txBody>` pugixml node.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node txbody_element,
                       std::function<void()> save_callback);

    /// Find the `<a:bodyPr>` child of the txBody element.
    /// @return The bodyPr node, or an empty node if not found.
    [[nodiscard]] pugi::xml_node get_body_pr() const;

    /// Find or create the `<a:bodyPr>` child of the txBody element.
    /// @return The existing or newly created bodyPr node.
    pugi::xml_node ensure_body_pr();

    /// Persist changes via the save callback.
    void save();

    /// Read a margin attribute from bodyPr and convert EMU to points.
    /// @param attr The attribute name (e.g., "lIns", "rIns", "tIns", "bIns").
    /// @param default_emu Default value in EMUs when the attribute is absent (default: 91440).
    /// @return Margin in points.
    [[nodiscard]] double get_margin(std::string_view attr, int default_emu = 91440) const;

    /// Write a margin value (in points) to bodyPr as an EMU attribute.
    /// @param attr The attribute name (e.g., "lIns", "rIns", "tIns", "bIns").
    /// @param value Margin in points.
    void set_margin(std::string_view attr, double value);

    /// Resize the parent shape to fit text content, preserving vertical center.
    /// @param body_pr The `<a:bodyPr>` XML node.
    void resize_shape_to_fit_text(pugi::xml_node body_pr);

private:
    TextAnchorType anchoring_type_ = TextAnchorType::NOT_DEFINED;
    TextAutofitType autofit_type_ = TextAutofitType::NOT_DEFINED;
    TextVerticalType text_vertical_type_ = TextVerticalType::NOT_DEFINED;
    NullableBool wrap_text_ = NullableBool::NOT_DEFINED;
    NullableBool center_text_ = NullableBool::NOT_DEFINED;
    double margin_left_ = std::numeric_limits<double>::quiet_NaN();
    double margin_right_ = std::numeric_limits<double>::quiet_NaN();
    double margin_top_ = std::numeric_limits<double>::quiet_NaN();
    double margin_bottom_ = std::numeric_limits<double>::quiet_NaN();
    int column_count_ = 1;
    double column_spacing_ = 0.0;
    double rotation_angle_ = 0.0;
    TextShapeType transform_ = TextShapeType::NOT_DEFINED;
    bool keep_text_flat_ = true;
    ThreeDFormat three_d_format_;

    pugi::xml_node txbody_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
