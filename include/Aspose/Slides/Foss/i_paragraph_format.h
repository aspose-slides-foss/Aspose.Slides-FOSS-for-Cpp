// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/font_alignment.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/text_alignment.h>

namespace Aspose::Slides::Foss {

class IBulletFormat;
class PortionFormat;

/// Interface for paragraph formatting properties.
/// Unlike read-only effective formats, all properties of this class are writeable.
class IParagraphFormat {
public:
    virtual ~IParagraphFormat() = default;

    /// Returns bullet format of the paragraph. Read-only.
    [[nodiscard]] virtual IBulletFormat& bullet() = 0;
    /// @copydoc bullet()
    [[nodiscard]] virtual const IBulletFormat& bullet() const = 0;

    /// Returns the paragraph depth. Value 0 means undefined.
    [[nodiscard]] virtual int depth() const = 0;
    /// Sets the paragraph depth.
    virtual void set_depth(int value) = 0;

    /// Returns the text alignment.
    [[nodiscard]] virtual TextAlignment alignment() const = 0;
    /// Sets the text alignment.
    virtual void set_alignment(TextAlignment value) = 0;

    /// Returns the space within the paragraph (positive=%, negative=points).
    [[nodiscard]] virtual double space_within() const = 0;
    /// Sets the space within the paragraph.
    virtual void set_space_within(double value) = 0;

    /// Returns the space before the paragraph (positive=%, negative=points).
    [[nodiscard]] virtual double space_before() const = 0;
    /// Sets the space before the paragraph.
    virtual void set_space_before(double value) = 0;

    /// Returns the space after the paragraph (positive=%, negative=points).
    [[nodiscard]] virtual double space_after() const = 0;
    /// Sets the space after the paragraph.
    virtual void set_space_after(double value) = 0;

    /// Returns whether east asian line break is enabled.
    [[nodiscard]] virtual NullableBool east_asian_line_break() const = 0;
    /// Sets whether east asian line break is enabled.
    virtual void set_east_asian_line_break(NullableBool value) = 0;

    /// Returns whether text is right-to-left.
    [[nodiscard]] virtual NullableBool right_to_left() const = 0;
    /// Sets whether text is right-to-left.
    virtual void set_right_to_left(NullableBool value) = 0;

    /// Returns whether latin line break is enabled.
    [[nodiscard]] virtual NullableBool latin_line_break() const = 0;
    /// Sets whether latin line break is enabled.
    virtual void set_latin_line_break(NullableBool value) = 0;

    /// Returns whether hanging punctuation is enabled.
    [[nodiscard]] virtual NullableBool hanging_punctuation() const = 0;
    /// Sets whether hanging punctuation is enabled.
    virtual void set_hanging_punctuation(NullableBool value) = 0;

    /// Returns the left margin in points. NaN = undefined.
    [[nodiscard]] virtual double margin_left() const = 0;
    /// Sets the left margin.
    virtual void set_margin_left(double value) = 0;

    /// Returns the right margin in points. NaN = undefined.
    [[nodiscard]] virtual double margin_right() const = 0;
    /// Sets the right margin.
    virtual void set_margin_right(double value) = 0;

    /// Returns the indent in points. Negative = hanging indent. NaN = undefined.
    [[nodiscard]] virtual double indent() const = 0;
    /// Sets the indent.
    virtual void set_indent(double value) = 0;

    /// Returns the default tab size in points. NaN = undefined.
    [[nodiscard]] virtual double default_tab_size() const = 0;
    /// Sets the default tab size.
    virtual void set_default_tab_size(double value) = 0;

    /// Returns the font alignment.
    [[nodiscard]] virtual FontAlignment font_alignment() const = 0;
    /// Sets the font alignment.
    virtual void set_font_alignment(FontAlignment value) = 0;

    /// Returns default portion format of a paragraph. Read-only.
    [[nodiscard]] virtual PortionFormat& default_portion_format() = 0;
    /// @copydoc default_portion_format()
    [[nodiscard]] virtual const PortionFormat& default_portion_format() const = 0;

protected:
    IParagraphFormat() = default;
};

} // namespace Aspose::Slides::Foss
