// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Base interface for header/footer management on slides.
class IBaseHeaderFooterManager {
public:
    virtual ~IBaseHeaderFooterManager() = default;

    /// Gets whether the footer placeholder is present.
    [[nodiscard]] virtual bool is_footer_visible() const = 0;

    /// Gets whether the date-time placeholder is present.
    [[nodiscard]] virtual bool is_date_time_visible() const = 0;

    /// Sets footer placeholder visibility.
    virtual void set_footer_visibility(bool is_visible) = 0;

    /// Sets date-time placeholder visibility.
    virtual void set_date_time_visibility(bool is_visible) = 0;

    /// Sets footer placeholder text content.
    virtual void set_footer_text(std::string_view text) = 0;

    /// Sets date-time placeholder text content.
    virtual void set_date_time_text(std::string_view text) = 0;
};

} // namespace Aspose::Slides::Foss
