// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cmath>
#include <functional>
#include <limits>
#include <string_view>

#include <Aspose/Slides/Foss/bullet_format.h>
#include <Aspose/Slides/Foss/font_alignment.h>
#include <Aspose/Slides/Foss/i_paragraph_format.h>
#include <Aspose/Slides/Foss/nullable_bool.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/text_alignment.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents paragraph formatting properties.
class ParagraphFormat final : public IParagraphFormat {
public:
    ParagraphFormat() = default;

    /// Returns bullet format of the paragraph. Read-only.
    [[nodiscard]] IBulletFormat& bullet() override { return bullet_; }
    [[nodiscard]] const IBulletFormat& bullet() const override { return bullet_; }

    // Every property below is backed by `<a:pPr>` once this object is bound to
    // one: the getter reads the element and the setter writes it, so a deck
    // opened from a file records what the caller asked for. An unbound object
    // — the from-scratch path, which serialises through serialize_ppr() at
    // save time — answers from its members instead.

    /// Returns the paragraph depth (`<a:pPr>` @lvl).
    [[nodiscard]] int depth() const override;
    /// Sets the paragraph depth.
    void set_depth(int value) override;

    /// Returns the text alignment.
    [[nodiscard]] TextAlignment alignment() const override;
    /// Sets the text alignment.
    void set_alignment(TextAlignment value) override;

    /// Returns the space within the paragraph (positive=%, negative=points).
    [[nodiscard]] double space_within() const override;
    void set_space_within(double value) override;

    /// Returns the space before the paragraph.
    [[nodiscard]] double space_before() const override;
    void set_space_before(double value) override;

    /// Returns the space after the paragraph.
    [[nodiscard]] double space_after() const override;
    void set_space_after(double value) override;

    /// Returns whether east asian line break is enabled.
    [[nodiscard]] NullableBool east_asian_line_break() const override;
    void set_east_asian_line_break(NullableBool value) override;

    /// Returns whether text is right-to-left.
    [[nodiscard]] NullableBool right_to_left() const override;
    void set_right_to_left(NullableBool value) override;

    /// Returns whether latin line break is enabled.
    [[nodiscard]] NullableBool latin_line_break() const override;
    void set_latin_line_break(NullableBool value) override;

    /// Returns whether hanging punctuation is enabled.
    [[nodiscard]] NullableBool hanging_punctuation() const override;
    void set_hanging_punctuation(NullableBool value) override;

    /// Returns the left margin in points. NaN = undefined.
    [[nodiscard]] double margin_left() const override;
    void set_margin_left(double value) override;

    /// Returns the right margin in points. NaN = undefined.
    [[nodiscard]] double margin_right() const override;
    void set_margin_right(double value) override;

    /// Returns the indent in points. NaN = undefined.
    [[nodiscard]] double indent() const override;
    void set_indent(double value) override;

    /// Returns the default tab size in points. NaN = undefined.
    [[nodiscard]] double default_tab_size() const override;
    void set_default_tab_size(double value) override;

    /// Returns the font alignment.
    [[nodiscard]] FontAlignment font_alignment() const override;
    void set_font_alignment(FontAlignment value) override;

    /// Returns default portion format of a paragraph. Read-only.
    [[nodiscard]] PortionFormat& default_portion_format() override { return default_portion_format_; }
    [[nodiscard]] const PortionFormat& default_portion_format() const override { return default_portion_format_; }

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an existing `<a:pPr>` XML node.
    /// @param ppr_element The `<a:pPr>` pugixml node, which may be empty.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    /// @param p_element The owning `<a:p>`. Most paragraphs in a real deck
    ///        carry no `<a:pPr>` at all, so without the parent there is
    ///        nowhere to put the first property that gets set, and every
    ///        setter is a silent no-op. Given it, the element is created on
    ///        the first write and not before — an empty `<a:pPr>` added to
    ///        every paragraph on load would change files nobody edited.
    void init_internal(pugi::xml_node ppr_element,
                       std::function<void()> save_callback,
                       pugi::xml_node p_element = {});

    /// Persist changes via the save callback.
    void save();

    /// Read a NullableBool from a pPr attribute.
    [[nodiscard]] NullableBool get_nullable_bool_attr(std::string_view attr) const;

    /// Write a NullableBool to a pPr attribute.
    void set_nullable_bool_attr(std::string_view attr, NullableBool value);

    /// Read spacing from a child element (lnSpc, spcBef, spcAft).
    /// Positive return = percentage, negative return = points. NaN = undefined.
    [[nodiscard]] double get_spacing(std::string_view tag) const;

    /// Write spacing to a child element.
    /// Positive value = percentage (spcPct), negative = points (spcPts). NaN removes.
    void set_spacing(std::string_view tag, double value);

    /// Read an EMU-based attribute and convert to points. NaN = undefined.
    [[nodiscard]] double get_emu_attr(std::string_view attr) const;

    /// Write a point value as an EMU attribute. NaN removes the attribute.
    void set_emu_attr(std::string_view attr, double value);

private:
    /// The backing `<a:pPr>`, created under the owning `<a:p>` if it is not
    /// there yet. Empty when this object has no XML behind it at all.
    pugi::xml_node ensure_ppr();

    BulletFormat bullet_;
    TextAlignment alignment_ = TextAlignment::NOT_DEFINED;
    double space_within_ = std::numeric_limits<double>::quiet_NaN();
    double space_before_ = std::numeric_limits<double>::quiet_NaN();
    double space_after_ = std::numeric_limits<double>::quiet_NaN();
    NullableBool east_asian_line_break_ = NullableBool::NOT_DEFINED;
    NullableBool right_to_left_ = NullableBool::NOT_DEFINED;
    NullableBool latin_line_break_ = NullableBool::NOT_DEFINED;
    NullableBool hanging_punctuation_ = NullableBool::NOT_DEFINED;
    double margin_left_ = std::numeric_limits<double>::quiet_NaN();
    double margin_right_ = std::numeric_limits<double>::quiet_NaN();
    double indent_ = std::numeric_limits<double>::quiet_NaN();
    double default_tab_size_ = std::numeric_limits<double>::quiet_NaN();
    FontAlignment font_alignment_ = FontAlignment::DEFAULT;
    int depth_ = 0;
    PortionFormat default_portion_format_;

    pugi::xml_node ppr_element_;
    pugi::xml_node p_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
