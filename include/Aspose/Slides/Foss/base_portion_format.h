// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cmath>
#include <limits>
#include <optional>
#include <string>
#include <string_view>

#include <memory>

#include <Aspose/Slides/Foss/color_format.h>
#include <Aspose/Slides/Foss/effect_format.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/font_data.h>
#include <Aspose/Slides/Foss/i_base_portion_format.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/text_cap_type.h>
#include <Aspose/Slides/Foss/text_strikethrough_type.h>
#include <Aspose/Slides/Foss/text_underline_type.h>

namespace Aspose::Slides::Foss {

/// Common text portion formatting properties.
///
/// Provides getters and setters for font style, underline, capitalization,
/// strikethrough, font metrics, font references, and language identifiers.
/// Properties that are not explicitly set return a "not defined" sentinel
/// (NullableBool::NOT_DEFINED, enum NOT_DEFINED, NaN for floats, std::nullopt
/// for optional values).
class BasePortionFormat : public virtual IBasePortionFormat {
public:
    BasePortionFormat() = default;
    ~BasePortionFormat() override = default;

    // -- NullableBool attribute properties ------------------------------------

    [[nodiscard]] NullableBool font_bold() const override { return font_bold_; }
    void set_font_bold(NullableBool value) override { font_bold_ = value; on_property_changed(); }

    [[nodiscard]] NullableBool font_italic() const override { return font_italic_; }
    void set_font_italic(NullableBool value) override { font_italic_ = value; on_property_changed(); }

    [[nodiscard]] NullableBool kumimoji() const override { return kumimoji_; }
    void set_kumimoji(NullableBool value) override { kumimoji_ = value; on_property_changed(); }

    [[nodiscard]] NullableBool normalise_height() const override { return normalise_height_; }
    void set_normalise_height(NullableBool value) override { normalise_height_ = value; on_property_changed(); }

    [[nodiscard]] NullableBool proof_disabled() const override { return proof_disabled_; }
    void set_proof_disabled(NullableBool value) override { proof_disabled_ = value; on_property_changed(); }

    // -- Enum attribute properties --------------------------------------------

    [[nodiscard]] TextUnderlineType font_underline() const override { return font_underline_; }
    void set_font_underline(TextUnderlineType value) override { font_underline_ = value; on_property_changed(); }

    [[nodiscard]] TextCapType text_cap_type() const override { return text_cap_type_; }
    void set_text_cap_type(TextCapType value) override { text_cap_type_ = value; on_property_changed(); }

    [[nodiscard]] TextStrikethroughType strikethrough_type() const override { return strikethrough_type_; }
    void set_strikethrough_type(TextStrikethroughType value) override { strikethrough_type_ = value; on_property_changed(); }

    // -- Underline hard/soft properties ---------------------------------------

    [[nodiscard]] NullableBool is_hard_underline_line() const override { return is_hard_underline_line_; }
    void set_is_hard_underline_line(NullableBool value) override { is_hard_underline_line_ = value; on_property_changed(); }

    [[nodiscard]] NullableBool is_hard_underline_fill() const override { return is_hard_underline_fill_; }
    void set_is_hard_underline_fill(NullableBool value) override { is_hard_underline_fill_ = value; on_property_changed(); }

    // -- Float attribute properties (NaN = undefined) -------------------------

    [[nodiscard]] double font_height() const override { return font_height_; }
    void set_font_height(double value) override { font_height_ = value; on_property_changed(); }

    [[nodiscard]] double escapement() const override { return escapement_; }
    void set_escapement(double value) override { escapement_ = value; on_property_changed(); }

    [[nodiscard]] double kerning_minimal_size() const override { return kerning_minimal_size_; }
    void set_kerning_minimal_size(double value) override { kerning_minimal_size_ = value; on_property_changed(); }

    [[nodiscard]] double spacing() const override { return spacing_; }
    void set_spacing(double value) override { spacing_ = value; on_property_changed(); }

    // -- Font properties (nullopt = undefined) --------------------------------

    [[nodiscard]] const std::optional<FontData>& latin_font() const override { return latin_font_; }
    void set_latin_font(std::optional<FontData> value) override { latin_font_ = std::move(value); on_property_changed(); }

    [[nodiscard]] const std::optional<FontData>& east_asian_font() const override { return east_asian_font_; }
    void set_east_asian_font(std::optional<FontData> value) override { east_asian_font_ = std::move(value); on_property_changed(); }

    [[nodiscard]] const std::optional<FontData>& complex_script_font() const override { return complex_script_font_; }
    void set_complex_script_font(std::optional<FontData> value) override { complex_script_font_ = std::move(value); on_property_changed(); }

    [[nodiscard]] const std::optional<FontData>& symbol_font() const override { return symbol_font_; }
    void set_symbol_font(std::optional<FontData> value) override { symbol_font_ = std::move(value); on_property_changed(); }

    // -- String attribute properties ------------------------------------------

    [[nodiscard]] const std::optional<std::string>& language_id() const override { return language_id_; }
    void set_language_id(std::optional<std::string> value) override { language_id_ = std::move(value); on_property_changed(); }

    [[nodiscard]] const std::optional<std::string>& alternative_language_id() const override { return alternative_language_id_; }
    void set_alternative_language_id(std::optional<std::string> value) override { alternative_language_id_ = std::move(value); on_property_changed(); }

    // -- spell_check property -------------------------------------------------

    [[nodiscard]] bool spell_check() const override {
        return proof_disabled_ == NullableBool::FALSE;
    }

    void set_spell_check(bool value) override {
        proof_disabled_ = value ? NullableBool::NOT_DEFINED : NullableBool::TRUE;
        on_property_changed();
    }

    // -- Format object properties ---------------------------------------------

    [[nodiscard]] LineFormat& line_format() override {
        if (!line_format_) line_format_ = std::make_unique<LineFormat>();
        return *line_format_;
    }

    [[nodiscard]] FillFormat& fill_format() override {
        if (!fill_format_) fill_format_ = std::make_unique<FillFormat>();
        return *fill_format_;
    }

    [[nodiscard]] EffectFormat& effect_format() override {
        if (!effect_format_) effect_format_ = std::make_unique<EffectFormat>();
        return *effect_format_;
    }

    [[nodiscard]] ColorFormat& highlight_color() override {
        if (!highlight_color_) highlight_color_ = std::make_unique<SimpleColorFormat>();
        return *highlight_color_;
    }

    [[nodiscard]] LineFormat& underline_line_format() override {
        if (!underline_line_format_) underline_line_format_ = std::make_unique<LineFormat>();
        return *underline_line_format_;
    }

    [[nodiscard]] FillFormat& underline_fill_format() override {
        if (!underline_fill_format_) underline_fill_format_ = std::make_unique<FillFormat>();
        return *underline_fill_format_;
    }

protected:
    /// Called after any property is changed. Subclasses can override to
    /// persist changes (e.g. write to XML).
    virtual void on_property_changed() {}

private:
    NullableBool font_bold_ = NullableBool::NOT_DEFINED;
    NullableBool font_italic_ = NullableBool::NOT_DEFINED;
    NullableBool kumimoji_ = NullableBool::NOT_DEFINED;
    NullableBool normalise_height_ = NullableBool::NOT_DEFINED;
    NullableBool proof_disabled_ = NullableBool::NOT_DEFINED;

    TextUnderlineType font_underline_ = TextUnderlineType::NOT_DEFINED;
    TextCapType text_cap_type_ = TextCapType::NOT_DEFINED;
    TextStrikethroughType strikethrough_type_ = TextStrikethroughType::NOT_DEFINED;

    NullableBool is_hard_underline_line_ = NullableBool::NOT_DEFINED;
    NullableBool is_hard_underline_fill_ = NullableBool::NOT_DEFINED;

    double font_height_ = std::numeric_limits<double>::quiet_NaN();
    double escapement_ = std::numeric_limits<double>::quiet_NaN();
    double kerning_minimal_size_ = std::numeric_limits<double>::quiet_NaN();
    double spacing_ = std::numeric_limits<double>::quiet_NaN();

    std::optional<FontData> latin_font_;
    std::optional<FontData> east_asian_font_;
    std::optional<FontData> complex_script_font_;
    std::optional<FontData> symbol_font_;

    std::optional<std::string> language_id_;
    std::optional<std::string> alternative_language_id_;

    std::unique_ptr<LineFormat> line_format_;
    std::unique_ptr<FillFormat> fill_format_;
    std::unique_ptr<EffectFormat> effect_format_;
    std::unique_ptr<SimpleColorFormat> highlight_color_;
    std::unique_ptr<LineFormat> underline_line_format_;
    std::unique_ptr<FillFormat> underline_fill_format_;
};

} // namespace Aspose::Slides::Foss
