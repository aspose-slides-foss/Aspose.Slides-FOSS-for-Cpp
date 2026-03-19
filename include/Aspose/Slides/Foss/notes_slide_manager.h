// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <optional>
#include <string>

#include <Aspose/Slides/Foss/i_notes_slide_manager.h>
#include <Aspose/Slides/Foss/notes_slide.h>

namespace Aspose::Slides::Foss::Internal::pptx {
class SlidePart;
} // namespace Aspose::Slides::Foss::Internal::pptx

namespace Aspose::Slides::Foss {

class ISlide;

/// Manages the notes slide associated with a presentation slide.
///
/// Lazily loads the notes slide from OPC relationships when first accessed.
class NotesSlideManager final : public INotesSlideManager {
public:
    NotesSlideManager();
    /// Construct with a parent slide pointer.
    explicit NotesSlideManager(ISlide* slide);
    NotesSlideManager(const NotesSlideManager&) = delete;
    NotesSlideManager& operator=(const NotesSlideManager&) = delete;
    ~NotesSlideManager() override;

    NotesSlideManager(NotesSlideManager&&) noexcept;
    NotesSlideManager& operator=(NotesSlideManager&&) noexcept;

    /// Internal initialization with OPC package context.
    ///
    /// @param slide The parent Slide object.
    /// @param package The OPC package.
    /// @param slide_part The SlidePart for managing relationships.
    void init_internal(ISlide* slide,
                       Internal::opc::OpcPackage* package,
                       Internal::pptx::SlidePart* slide_part);

    /// Returns the notes slide, or nullptr if none exists. Read-only.
    [[nodiscard]] INotesSlide* notes_slide() const override;

    /// Creates and returns a new notes slide. If one already exists, returns it.
    INotesSlide* add_notes_slide() override;

    /// Removes the notes slide if one exists.
    void remove_notes_slide() override;

private:
    /// Resolve the notes slide part name from the slide's relationships.
    /// @return The part name, or nullopt if no notes slide relationship exists.
    [[nodiscard]] std::optional<std::string> get_notes_part_name() const;

    /// Load and cache a NotesSlide from the given part name.
    INotesSlide* load_notes_slide(const std::string& part_name);

    ISlide* slide_ = nullptr;
    Internal::opc::OpcPackage* package_ = nullptr;
    Internal::pptx::SlidePart* slide_part_ = nullptr;

    // Owned NotesSlidePart created during lazy loading.
    std::unique_ptr<Internal::pptx::NotesSlidePart> owned_notes_part_;
    // Cached notes slide.
    mutable std::unique_ptr<NotesSlide> notes_slide_cache_;
};

} // namespace Aspose::Slides::Foss
