// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/notes_slide.h>

#include <string_view>
#include <utility>

#include <Aspose/Slides/Foss/_internal/pptx/notes_slide_part.h>

namespace Aspose::Slides::Foss {

void NotesSlide::init_internal(IPresentation* presentation,
                               Internal::opc::OpcPackage* package,
                               std::string part_name,
                               Internal::pptx::NotesSlidePart* notes_part,
                               ISlide* parent_slide) {
    set_presentation(presentation);
    package_ = package;
    part_name_ = std::move(part_name);
    internal_notes_part_ = notes_part;
    parent_slide_ = parent_slide;

    // Initialize the text frame from the notes body txBody element.
    if (internal_notes_part_) {
        auto txbody = internal_notes_part_->get_notes_txbody();
        if (txbody) {
            text_frame_.init_internal(txbody, nullptr, this, nullptr);
        }

        // Populate the in-memory NotesSlidePart from XML placeholder state.
        using namespace Internal::pptx;
        constexpr std::string_view ph_types[] = {"ftr", "dt", "sldNum", "hdr"};
        for (auto type : ph_types) {
            if (internal_notes_part_->has_placeholder(type)) {
                notes_part_.add_placeholder(type);
            }
        }
    }
}

SlidePartVariant NotesSlide::get_slide_part() {
    if (internal_notes_part_ != nullptr) {
        return internal_notes_part_;
    }
    return std::monostate{};
}

} // namespace Aspose::Slides::Foss
