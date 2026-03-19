// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

#include <Aspose/Slides/Foss/i_base_slide_header_footer_manager.h>

namespace Aspose::Slides::Foss {

/// Interface for handout/notes slide header/footer management, adding header support.
class IBaseHandoutNotesSlideHeaderFooterManager : public IBaseSlideHeaderFooterManager {
public:
    /// Gets whether the header placeholder is present.
    [[nodiscard]] virtual bool is_header_visible() const = 0;

    /// Sets header placeholder visibility.
    virtual void set_header_visibility(bool is_visible) = 0;

    /// Sets header placeholder text content.
    virtual void set_header_text(std::string_view text) = 0;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager.
    [[nodiscard]] virtual IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() = 0;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager (const).
    [[nodiscard]] virtual const IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() const = 0;
};

} // namespace Aspose::Slides::Foss
