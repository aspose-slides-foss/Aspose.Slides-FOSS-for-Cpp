// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <optional>
#include <string>

#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/text_cap_type.h>
#include <Aspose/Slides/Foss/text_strikethrough_type.h>
#include <Aspose/Slides/Foss/text_underline_type.h>

namespace Aspose::Slides::Foss {

class ColorFormat;
class EffectFormat;
class FillFormat;
class FontData;
class LineFormat;

/// Interface for text portion formatting properties.
///
/// Unlike read-only portion format interfaces, all properties of this
/// interface are writeable. Properties that are not explicitly set return
/// a "not defined" sentinel (NullableBool::NOT_DEFINED, enum NOT_DEFINED,
/// NaN for floats, std::nullopt for optional values).
class IBasePortionFormat {
public:
    virtual ~IBasePortionFormat() = default;

    // -- Format object properties (read-only references) ----------------------

    /// Returns the LineFormat properties for text outlining. No inheritance applied.
    [[nodiscard]] virtual LineFormat& line_format() = 0;

    /// Returns the text FillFormat properties. No inheritance applied.
    [[nodiscard]] virtual FillFormat& fill_format() = 0;

    /// Returns the text EffectFormat properties. No inheritance applied.
    [[nodiscard]] virtual EffectFormat& effect_format() = 0;

    /// Returns the color used to highlight a text. No inheritance applied.
    [[nodiscard]] virtual ColorFormat& highlight_color() = 0;

    /// Returns the LineFormat properties used to outline underline line. No inheritance applied.
    [[nodiscard]] virtual LineFormat& underline_line_format() = 0;

    /// Returns the underline line FillFormat properties. No inheritance applied.
    [[nodiscard]] virtual FillFormat& underline_fill_format() = 0;

    // -- NullableBool properties (read/write) ---------------------------------

    /// Determines whether the font is bold. No inheritance applied.
    [[nodiscard]] virtual NullableBool font_bold() const = 0;
    /// Sets whether the font is bold.
    virtual void set_font_bold(NullableBool value) = 0;

    /// Determines whether the font is italic. No inheritance applied.
    [[nodiscard]] virtual NullableBool font_italic() const = 0;
    /// Sets whether the font is italic.
    virtual void set_font_italic(NullableBool value) = 0;

    /// Determines whether numbers should ignore eastern language vertical layout.
    [[nodiscard]] virtual NullableBool kumimoji() const = 0;
    /// Sets kumimoji.
    virtual void set_kumimoji(NullableBool value) = 0;

    /// Determines whether the height of a text should be normalized.
    [[nodiscard]] virtual NullableBool normalise_height() const = 0;
    /// Sets normalise_height.
    virtual void set_normalise_height(NullableBool value) = 0;

    /// Determines whether the text shouldn't be proofed.
    [[nodiscard]] virtual NullableBool proof_disabled() const = 0;
    /// Sets proof_disabled.
    virtual void set_proof_disabled(NullableBool value) = 0;

    // -- Enum properties (read/write) -----------------------------------------

    /// Returns the text underline type. No inheritance applied.
    [[nodiscard]] virtual TextUnderlineType font_underline() const = 0;
    /// Sets the text underline type.
    virtual void set_font_underline(TextUnderlineType value) = 0;

    /// Returns the type of text capitalisation. No inheritance applied.
    [[nodiscard]] virtual TextCapType text_cap_type() const = 0;
    /// Sets the type of text capitalisation.
    virtual void set_text_cap_type(TextCapType value) = 0;

    /// Returns the strikethrough type of a text. No inheritance applied.
    [[nodiscard]] virtual TextStrikethroughType strikethrough_type() const = 0;
    /// Sets the strikethrough type.
    virtual void set_strikethrough_type(TextStrikethroughType value) = 0;

    // -- Underline hard/soft properties (read/write) --------------------------

    /// Determines whether the underline style has its own LineFormat or inherits.
    [[nodiscard]] virtual NullableBool is_hard_underline_line() const = 0;
    /// Sets is_hard_underline_line.
    virtual void set_is_hard_underline_line(NullableBool value) = 0;

    /// Determines whether the underline style has its own FillFormat or inherits.
    [[nodiscard]] virtual NullableBool is_hard_underline_fill() const = 0;
    /// Sets is_hard_underline_fill.
    virtual void set_is_hard_underline_fill(NullableBool value) = 0;

    // -- Float properties (NaN = undefined, read/write) -----------------------

    /// Returns the font height in points. NaN means undefined.
    [[nodiscard]] virtual double font_height() const = 0;
    /// Sets the font height in points. Pass NaN to clear.
    virtual void set_font_height(double value) = 0;

    /// Returns superscript/subscript offset (-100% to 100%). NaN = undefined.
    [[nodiscard]] virtual double escapement() const = 0;
    /// Sets the escapement value. Pass NaN to clear.
    virtual void set_escapement(double value) = 0;

    /// Returns the minimal font size for which kerning is active. NaN = undefined.
    [[nodiscard]] virtual double kerning_minimal_size() const = 0;
    /// Sets the kerning minimal size. Pass NaN to clear.
    virtual void set_kerning_minimal_size(double value) = 0;

    /// Returns the intercharacter spacing increment. NaN = undefined.
    [[nodiscard]] virtual double spacing() const = 0;
    /// Sets the spacing. Pass NaN to clear.
    virtual void set_spacing(double value) = 0;

    // -- Font properties (nullopt = undefined, read/write) --------------------

    /// Returns the Latin font info. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<FontData>& latin_font() const = 0;
    /// Sets the Latin font info. Pass std::nullopt to clear.
    virtual void set_latin_font(std::optional<FontData> value) = 0;

    /// Returns the East Asian font info. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<FontData>& east_asian_font() const = 0;
    /// Sets the East Asian font info. Pass std::nullopt to clear.
    virtual void set_east_asian_font(std::optional<FontData> value) = 0;

    /// Returns the complex script font info. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<FontData>& complex_script_font() const = 0;
    /// Sets the complex script font info. Pass std::nullopt to clear.
    virtual void set_complex_script_font(std::optional<FontData> value) = 0;

    /// Returns the symbolic font info. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<FontData>& symbol_font() const = 0;
    /// Sets the symbolic font info. Pass std::nullopt to clear.
    virtual void set_symbol_font(std::optional<FontData> value) = 0;

    // -- String properties (nullopt = undefined, read/write) ------------------

    /// Returns the proofing language id. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<std::string>& language_id() const = 0;
    /// Sets the proofing language id. Pass std::nullopt to clear.
    virtual void set_language_id(std::optional<std::string> value) = 0;

    /// Returns the alternative language id. std::nullopt means undefined.
    [[nodiscard]] virtual const std::optional<std::string>& alternative_language_id() const = 0;
    /// Sets the alternative language id. Pass std::nullopt to clear.
    virtual void set_alternative_language_id(std::optional<std::string> value) = 0;

    // -- spell_check property -------------------------------------------------

    /// Returns whether spell checking is enabled for the text portion.
    [[nodiscard]] virtual bool spell_check() const = 0;
    /// Sets whether spell checking is enabled.
    virtual void set_spell_check(bool value) = 0;

protected:
    IBasePortionFormat() = default;
};

} // namespace Aspose::Slides::Foss
