// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/source_format.h>

namespace Aspose::Slides::Foss {

class CommentAuthorCollection;
class DocumentProperties;
class GlobalLayoutSlideCollection;
class ImageCollection;
class MasterSlideCollection;
class NotesSize;
class SlideCollection;

/// Presentation document interface.
class IPresentation : public IPresentationComponent {
public:
    ~IPresentation() override = default;

    /// Returns date and time which will substitute content of datetime fields.
    [[nodiscard]] virtual std::chrono::system_clock::time_point current_date_time() const = 0;
    /// Sets date and time which will substitute content of datetime fields.
    virtual void set_current_date_time(std::chrono::system_clock::time_point value) = 0;

    /// Returns the collection of slides. Read-only.
    [[nodiscard]] virtual SlideCollection& slides() = 0;
    [[nodiscard]] virtual const SlideCollection& slides() const = 0;

    /// Returns the collection of comment authors. Read-only.
    [[nodiscard]] virtual CommentAuthorCollection& comment_authors() = 0;
    [[nodiscard]] virtual const CommentAuthorCollection& comment_authors() const = 0;

    /// Returns the collection of images. Read-only.
    [[nodiscard]] virtual ImageCollection& images() = 0;
    [[nodiscard]] virtual const ImageCollection& images() const = 0;

    /// Returns the document properties. Read-only.
    [[nodiscard]] virtual DocumentProperties& document_properties() = 0;
    [[nodiscard]] virtual const DocumentProperties& document_properties() const = 0;

    /// Returns the collection of layout slides. Read-only.
    [[nodiscard]] virtual GlobalLayoutSlideCollection& layout_slides() = 0;
    [[nodiscard]] virtual const GlobalLayoutSlideCollection& layout_slides() const = 0;

    /// Returns the collection of master slides. Read-only.
    [[nodiscard]] virtual MasterSlideCollection& masters() = 0;
    [[nodiscard]] virtual const MasterSlideCollection& masters() const = 0;

    /// Returns the notes slide size. Read-only.
    [[nodiscard]] virtual NotesSize& notes_size() = 0;
    [[nodiscard]] virtual const NotesSize& notes_size() const = 0;

    /// Returns source format information. Read-only.
    [[nodiscard]] virtual SourceFormat source_format() const = 0;

    /// Returns the first slide number in the presentation.
    [[nodiscard]] virtual int first_slide_number() const = 0;
    /// Sets the first slide number in the presentation.
    virtual void set_first_slide_number(int value) = 0;

    /// Returns a pointer to this as IPresentationComponent.
    [[nodiscard]] virtual IPresentationComponent* as_i_presentation_component() = 0;
    [[nodiscard]] virtual const IPresentationComponent* as_i_presentation_component() const = 0;

    /// Saves the presentation to a file path with the given format.
    virtual void save(std::string_view path, SaveFormat format) = 0;

    /// Releases all resources used by this Presentation.
    virtual void dispose() = 0;
};

} // namespace Aspose::Slides::Foss
