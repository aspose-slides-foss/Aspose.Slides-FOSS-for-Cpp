// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/pattern_style.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents a pattern fill format.
class PatternFormat final {
public:
    PatternFormat() = default;
    virtual ~PatternFormat() = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed pattern format.
    /// @param patt_fill_element The \c a:pattFill XML element.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node patt_fill_element,
                       std::function<void()> save_callback);

    /// Save changes via the save callback.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns the pattern style.
    [[nodiscard]] PatternStyle pattern_style() const noexcept { return pattern_style_; }
    void set_pattern_style(PatternStyle value) noexcept { pattern_style_ = value; }

    /// Returns the foreground color of the pattern.
    [[nodiscard]] SimpleColorFormat& fore_color() noexcept { return fore_color_; }
    [[nodiscard]] const SimpleColorFormat& fore_color() const noexcept { return fore_color_; }

    /// Returns the background color of the pattern.
    [[nodiscard]] SimpleColorFormat& back_color() noexcept { return back_color_; }
    [[nodiscard]] const SimpleColorFormat& back_color() const noexcept { return back_color_; }

private:
    PatternStyle pattern_style_ = PatternStyle::NOT_DEFINED;
    SimpleColorFormat fore_color_;
    SimpleColorFormat back_color_;

    pugi::xml_node patt_fill_element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
