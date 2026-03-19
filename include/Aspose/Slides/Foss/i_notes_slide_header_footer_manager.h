// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_base_handout_notes_slide_header_footer_manager.h>

namespace Aspose::Slides::Foss {

/// Interface for notes slide header/footer management.
class INotesSlideHeaderFooterManager
    : public IBaseHandoutNotesSlideHeaderFooterManager {
public:
    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager.
    [[nodiscard]] IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() override = 0;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager (const).
    [[nodiscard]] const IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() const override = 0;
};

} // namespace Aspose::Slides::Foss
