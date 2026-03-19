// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_notes_slide_header_footer_manager.h>
#include <Aspose/Slides/Foss/notes_slide_part.h>

namespace Aspose::Slides::Foss {

/// Manages the behavior of notes slide placeholders including header, footer,
/// date-time, and slide number.
class NotesSlideHeaderFooterManager final : public INotesSlideHeaderFooterManager {
public:
    /// Constructs a manager backed by the given notes slide part.
    explicit NotesSlideHeaderFooterManager(NotesSlidePart* notes_part) noexcept;

    // -- IBaseHeaderFooterManager --

    /// Gets whether the footer placeholder is present.
    [[nodiscard]] bool is_footer_visible() const override;

    /// Gets whether the date-time placeholder is present.
    [[nodiscard]] bool is_date_time_visible() const override;

    /// Sets footer placeholder visibility.
    void set_footer_visibility(bool is_visible) override;

    /// Sets date-time placeholder visibility.
    void set_date_time_visibility(bool is_visible) override;

    /// Sets footer placeholder text content.
    void set_footer_text(std::string_view text) override;

    /// Sets date-time placeholder text content.
    void set_date_time_text(std::string_view text) override;

    // -- IBaseSlideHeaderFooterManager --

    /// Gets whether the slide number placeholder is present.
    [[nodiscard]] bool is_slide_number_visible() const override;

    /// Sets slide number placeholder visibility.
    void set_slide_number_visibility(bool is_visible) override;

    // -- IBaseHandoutNotesSlideHeaderFooterManager --

    /// Gets whether the header placeholder is present.
    [[nodiscard]] bool is_header_visible() const override;

    /// Sets header placeholder visibility.
    void set_header_visibility(bool is_visible) override;

    /// Sets header placeholder text content.
    void set_header_text(std::string_view text) override;

    // -- INotesSlideHeaderFooterManager --

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager.
    [[nodiscard]] IBaseHandoutNotesSlideHeaderFooterManager&
    as_i_base_handout_notes_slide_header_footer_manager() override;

    /// Returns this as IBaseHandoutNotesSlideHeaderFooterManager (const).
    [[nodiscard]] const IBaseHandoutNotesSlideHeaderFooterManager&
    [[nodiscard]] as_i_base_handout_notes_slide_header_footer_manager() const override;

    /// Returns this as IBaseSlideHeaderFooterManager.
    [[nodiscard]] IBaseSlideHeaderFooterManager&
    as_i_base_slide_header_footer_manager();

    /// Returns this as IBaseSlideHeaderFooterManager (const).
    [[nodiscard]] const IBaseSlideHeaderFooterManager&
    as_i_base_slide_header_footer_manager() const;

    /// Returns this as IBaseHeaderFooterManager.
    [[nodiscard]] IBaseHeaderFooterManager& as_i_base_header_footer_manager();

    /// Returns this as IBaseHeaderFooterManager (const).
    [[nodiscard]] const IBaseHeaderFooterManager&
    as_i_base_header_footer_manager() const;

private:
    NotesSlidePart* notes_part_;
};

} // namespace Aspose::Slides::Foss
