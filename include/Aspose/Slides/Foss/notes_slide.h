// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/base_slide.h>
#include <Aspose/Slides/Foss/i_notes_slide.h>
#include <Aspose/Slides/Foss/notes_slide_header_footer_manager.h>
#include <Aspose/Slides/Foss/notes_slide_part.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/text_frame.h>

namespace Aspose::Slides::Foss::Internal::opc {
class OpcPackage;
} // namespace Aspose::Slides::Foss::Internal::opc

namespace Aspose::Slides::Foss::Internal::pptx {
class NotesSlidePart;
} // namespace Aspose::Slides::Foss::Internal::pptx

namespace Aspose::Slides::Foss {

class ISlide;

/// Represents a notes slide associated with a presentation slide.
class NotesSlide final : public BaseSlide, public INotesSlide {
public:
    NotesSlide() : header_footer_manager_(&notes_part_) {}

    /// Constructs a notes slide with a reference to its parent slide.
    explicit NotesSlide(ISlide* parent_slide)
        : parent_slide_(parent_slide), header_footer_manager_(&notes_part_) {}

    /// Internal initialization for a notes slide loaded from a package.
    ///
    /// @param presentation The parent Presentation object.
    /// @param package The OPC package containing the notes slide.
    /// @param part_name The OPC part name (e.g., "ppt/notesSlides/notesSlide1.xml").
    /// @param notes_part The parsed internal NotesSlidePart.
    /// @param parent_slide The slide that owns this notes slide.
    void init_internal(IPresentation* presentation,
                       Internal::opc::OpcPackage* package,
                       std::string part_name,
                       Internal::pptx::NotesSlidePart* notes_part,
                       ISlide* parent_slide);

    /// Returns the collection of shapes on this notes slide.
    [[nodiscard]] ShapeCollection& shapes() override { return shapes_; }
    [[nodiscard]] const ShapeCollection& shapes() const override { return shapes_; }

    /// Returns the HeaderFooter manager of the notes slide. Read-only.
    [[nodiscard]] INotesSlideHeaderFooterManager& header_footer_manager() override {
        return header_footer_manager_;
    }
    [[nodiscard]] const INotesSlideHeaderFooterManager& header_footer_manager() const override {
        return header_footer_manager_;
    }

    /// Returns the TextFrame with notes text. Read-only.
    [[nodiscard]] TextFrame& notes_text_frame() override { return text_frame_; }
    [[nodiscard]] const TextFrame& notes_text_frame() const override { return text_frame_; }

    /// Returns the parent slide. Read-only.
    [[nodiscard]] ISlide* parent_slide() override { return parent_slide_; }
    [[nodiscard]] const ISlide* parent_slide() const override { return parent_slide_; }

    /// Returns this as IBaseSlide. Read-only.
    [[nodiscard]] IBaseSlide& as_i_base_slide() override { return *this; }
    [[nodiscard]] const IBaseSlide& as_i_base_slide() const override { return *this; }

    /// Returns the OPC part name of this notes slide.
    [[nodiscard]] const std::string& part_name() const noexcept { return part_name_; }

    /// Returns the OPC package, or nullptr if not initialized.
    [[nodiscard]] Internal::opc::OpcPackage* package() const noexcept { return package_; }

    /// Returns the internal notes slide part, or nullptr if not initialized.
    [[nodiscard]] Internal::pptx::NotesSlidePart* internal_notes_part() const noexcept {
        return internal_notes_part_;
    }

protected:
    /// Returns the internal NotesSlidePart for BaseSlide shape access.
    [[nodiscard]] SlidePartVariant get_slide_part() override;

private:
    ISlide* parent_slide_ = nullptr;
    Internal::opc::OpcPackage* package_ = nullptr;
    Internal::pptx::NotesSlidePart* internal_notes_part_ = nullptr;
    std::string part_name_;
    ShapeCollection shapes_;
    NotesSlidePart notes_part_;
    NotesSlideHeaderFooterManager header_footer_manager_;
    TextFrame text_frame_;
};

} // namespace Aspose::Slides::Foss
