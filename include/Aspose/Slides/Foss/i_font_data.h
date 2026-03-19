// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

namespace Aspose::Slides::Foss {

/// Interface representing a font definition.
///
/// Provides access to the font name and theme-aware font resolution.
class IFontData {
public:
    virtual ~IFontData() = default;

    /// Returns the font name (typeface). Read-only.
    [[nodiscard]] virtual const std::string& font_name() const = 0;

    /// Sets the font name (typeface).
    virtual void set_font_name(std::string value) = 0;

    /// Returns the font name, optionally resolved against a theme.
    /// @param theme  Pointer to a theme object (may be nullptr).
    /// @return The resolved font name.
    [[nodiscard]] virtual const std::string& get_font_name(const void* theme) const = 0;
};

} // namespace Aspose::Slides::Foss
