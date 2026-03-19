// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_font_data.h>

#include <ostream>
#include <string>
#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents font information used in a presentation.
class FontData final : public IFontData {
public:
    /// Constructs FontData with the given typeface name.
    explicit FontData(std::string_view font_name) : font_name_(font_name) {}

    /// Returns the font name (typeface).
    [[nodiscard]] const std::string& font_name() const override { return font_name_; }

    /// Returns the font name, resolving against the given theme.
    /// Currently ignores the theme and returns the stored name.
    [[nodiscard]] const std::string& get_font_name([[maybe_unused]] const void* theme) const override {
        return font_name_;
    }

    /// Sets the font name (typeface).
    void set_font_name(std::string value) override { font_name_ = std::move(value); }

    [[nodiscard]] bool operator==(const FontData& other) const {
        return font_name_ == other.font_name_;
    }

    friend std::ostream& operator<<(std::ostream& os, const FontData& fd) {
        return os << "FontData(\"" << fd.font_name_ << "\")";
    }

private:
    std::string font_name_;
};

} // namespace Aspose::Slides::Foss
