// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/notes_slide_header_footer_manager.h>

namespace Aspose::Slides::Foss {

NotesSlideHeaderFooterManager::NotesSlideHeaderFooterManager(
    NotesSlidePart* notes_part) noexcept
    : notes_part_(notes_part) {}

// -- IBaseHeaderFooterManager --

bool NotesSlideHeaderFooterManager::is_footer_visible() const {
    return notes_part_->has_placeholder("ftr");
}

bool NotesSlideHeaderFooterManager::is_date_time_visible() const {
    return notes_part_->has_placeholder("dt");
}

void NotesSlideHeaderFooterManager::set_footer_visibility(bool is_visible) {
    if (is_visible) {
        notes_part_->add_placeholder("ftr");
    } else {
        notes_part_->remove_placeholder("ftr");
    }
}

void NotesSlideHeaderFooterManager::set_date_time_visibility(bool is_visible) {
    if (is_visible) {
        notes_part_->add_placeholder("dt");
    } else {
        notes_part_->remove_placeholder("dt");
    }
}

void NotesSlideHeaderFooterManager::set_footer_text(std::string_view text) {
    notes_part_->set_placeholder_text("ftr", text);
}

void NotesSlideHeaderFooterManager::set_date_time_text(std::string_view text) {
    notes_part_->set_placeholder_text("dt", text);
}

// -- IBaseSlideHeaderFooterManager --

bool NotesSlideHeaderFooterManager::is_slide_number_visible() const {
    return notes_part_->has_placeholder("sldNum");
}

void NotesSlideHeaderFooterManager::set_slide_number_visibility(bool is_visible) {
    if (is_visible) {
        notes_part_->add_placeholder("sldNum");
    } else {
        notes_part_->remove_placeholder("sldNum");
    }
}

// -- IBaseHandoutNotesSlideHeaderFooterManager --

bool NotesSlideHeaderFooterManager::is_header_visible() const {
    return notes_part_->has_placeholder("hdr");
}

void NotesSlideHeaderFooterManager::set_header_visibility(bool is_visible) {
    if (is_visible) {
        notes_part_->add_placeholder("hdr");
    } else {
        notes_part_->remove_placeholder("hdr");
    }
}

void NotesSlideHeaderFooterManager::set_header_text(std::string_view text) {
    notes_part_->set_placeholder_text("hdr", text);
}

// -- INotesSlideHeaderFooterManager --

IBaseHandoutNotesSlideHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_handout_notes_slide_header_footer_manager() {
    return *this;
}

const IBaseHandoutNotesSlideHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_handout_notes_slide_header_footer_manager()
    const {
    return *this;
}

IBaseSlideHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_slide_header_footer_manager() {
    return *this;
}

const IBaseSlideHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_slide_header_footer_manager() const {
    return *this;
}

IBaseHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_header_footer_manager() {
    return *this;
}

const IBaseHeaderFooterManager&
NotesSlideHeaderFooterManager::as_i_base_header_footer_manager() const {
    return *this;
}

} // namespace Aspose::Slides::Foss
