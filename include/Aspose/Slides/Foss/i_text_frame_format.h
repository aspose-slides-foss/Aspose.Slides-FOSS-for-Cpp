// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>
#include <Aspose/Slides/Foss/text_autofit_type.h>
#include <Aspose/Slides/Foss/text_shape_type.h>
#include <Aspose/Slides/Foss/text_vertical_type.h>

namespace Aspose::Slides::Foss {

class ThreeDFormat;

/// Contains the TextFrame's formatting properties.
class ITextFrameFormat {
public:
    virtual ~ITextFrameFormat() = default;

    /// Returns the left margin (points) in a TextFrame.
    [[nodiscard]] virtual double margin_left() const = 0;
    /// Sets the left margin (points) in a TextFrame.
    virtual void set_margin_left(double value) = 0;

    /// Returns the right margin (points) in a TextFrame.
    [[nodiscard]] virtual double margin_right() const = 0;
    /// Sets the right margin (points) in a TextFrame.
    virtual void set_margin_right(double value) = 0;

    /// Returns the top margin (points) in a TextFrame.
    [[nodiscard]] virtual double margin_top() const = 0;
    /// Sets the top margin (points) in a TextFrame.
    virtual void set_margin_top(double value) = 0;

    /// Returns the bottom margin (points) in a TextFrame.
    [[nodiscard]] virtual double margin_bottom() const = 0;
    /// Sets the bottom margin (points) in a TextFrame.
    virtual void set_margin_bottom(double value) = 0;

    /// Returns whether text is wrapped at TextFrame's margins.
    [[nodiscard]] virtual NullableBool wrap_text() const = 0;
    /// Sets whether text is wrapped at TextFrame's margins.
    virtual void set_wrap_text(NullableBool value) = 0;

    /// Returns the vertical anchor text in a TextFrame.
    [[nodiscard]] virtual TextAnchorType anchoring_type() const = 0;
    /// Sets the vertical anchor text in a TextFrame.
    virtual void set_anchoring_type(TextAnchorType value) = 0;

    /// Returns whether text should be centered in box horizontally.
    [[nodiscard]] virtual NullableBool center_text() const = 0;
    /// Sets whether text should be centered in box horizontally.
    virtual void set_center_text(NullableBool value) = 0;

    /// Returns the text orientation.
    [[nodiscard]] virtual TextVerticalType text_vertical_type() const = 0;
    /// Sets the text orientation.
    virtual void set_text_vertical_type(TextVerticalType value) = 0;

    /// Returns text's autofit mode.
    [[nodiscard]] virtual TextAutofitType autofit_type() const = 0;
    /// Sets text's autofit mode.
    virtual void set_autofit_type(TextAutofitType value) = 0;

    /// Returns the number of columns in the text area.
    [[nodiscard]] virtual int column_count() const = 0;
    /// Sets the number of columns in the text area.
    virtual void set_column_count(int value) = 0;

    /// Returns the space between text columns in points.
    [[nodiscard]] virtual double column_spacing() const = 0;
    /// Sets the space between text columns in points.
    virtual void set_column_spacing(double value) = 0;

    /// Returns the ThreeDFormat object for 3D effect properties. Read-only.
    [[nodiscard]] virtual ThreeDFormat& three_d_format() = 0;
    /// Returns the ThreeDFormat object for 3D effect properties. Read-only.
    [[nodiscard]] virtual const ThreeDFormat& three_d_format() const = 0;

    /// Returns whether text is kept flat (no 3D rotation).
    [[nodiscard]] virtual bool keep_text_flat() const = 0;
    /// Sets whether text is kept flat (no 3D rotation).
    virtual void set_keep_text_flat(bool value) = 0;

    /// Returns the custom rotation applied to text within the bounding box.
    [[nodiscard]] virtual double rotation_angle() const = 0;
    /// Sets the custom rotation applied to text within the bounding box.
    virtual void set_rotation_angle(double value) = 0;

    /// Returns the text wrapping shape.
    [[nodiscard]] virtual TextShapeType transform() const = 0;
    /// Sets the text wrapping shape.
    virtual void set_transform(TextShapeType value) = 0;

protected:
    ITextFrameFormat() = default;
};

} // namespace Aspose::Slides::Foss
