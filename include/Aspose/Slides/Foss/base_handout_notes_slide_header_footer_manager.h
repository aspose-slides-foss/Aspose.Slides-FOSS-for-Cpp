// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_base_handout_notes_slide_header_footer_manager.h>

namespace Aspose::Slides::Foss {

/// Base class for handout and notes slide header/footer managers.
class BaseHandoutNotesSlideHeaderFooterManager final
    : public IBaseHandoutNotesSlideHeaderFooterManager {
public:
    ~BaseHandoutNotesSlideHeaderFooterManager() override = default;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager.
    [[nodiscard]] IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() override;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager (const).
    [[nodiscard]] const IBaseHandoutNotesSlideHeaderFooterManager&
    [[nodiscard]] as_i_base_handout_notes_slide_header_footer_manager() const override;

protected:
    BaseHandoutNotesSlideHeaderFooterManager() = default;
};

} // namespace Aspose::Slides::Foss
