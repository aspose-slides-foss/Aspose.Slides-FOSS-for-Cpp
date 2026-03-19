// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class INotesSlide;

/// Interface for managing the notes slide associated with a slide.
class INotesSlideManager {
public:
    virtual ~INotesSlideManager() = default;

    /// Returns the notes slide, or nullptr if none exists.
    [[nodiscard]] virtual INotesSlide* notes_slide() const = 0;

    /// Creates and returns a new notes slide. If one already exists, returns it.
    virtual INotesSlide* add_notes_slide() = 0;

    /// Removes the notes slide if one exists.
    virtual void remove_notes_slide() = 0;

protected:
    INotesSlideManager() = default;
};

} // namespace Aspose::Slides::Foss
