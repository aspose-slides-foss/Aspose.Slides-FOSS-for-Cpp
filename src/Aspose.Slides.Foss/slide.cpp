// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/slide.h>

#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/comment.h>
#include <Aspose/Slides/Foss/comment_author.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide_collection.h>

namespace Aspose::Slides::Foss {

Slide::Slide(Presentation* presentation) noexcept
    : BaseSlide(presentation),
      presentation_(presentation),
      notes_slide_manager_(this) {}

IPresentation* Slide::presentation() { return presentation_; }
const IPresentation* Slide::presentation() const { return presentation_; }

IBaseSlide* Slide::slide() { return this; }
const IBaseSlide* Slide::slide() const { return this; }

IPresentationComponent* Slide::as_i_presentation_component() { return this; }
const IPresentationComponent* Slide::as_i_presentation_component() const { return this; }

ISlideComponent& Slide::as_i_slide_component() { return *this; }
const ISlideComponent& Slide::as_i_slide_component() const { return *this; }

std::vector<Comment*> Slide::get_slide_comments(
    CommentAuthor* author) const {
    std::vector<Comment*> result;
    if (!presentation_) return result;

    auto& authors = presentation_->comment_authors();
    for (std::size_t a = 0; a < authors.size(); ++a) {
        auto& ca = authors[a];
        if (author != nullptr && &ca != author) continue;

        for (std::size_t c = 0; c < ca.comments().size(); ++c) {
            auto& comment = ca.comments()[c];
            if (comment.slide() == this) {
                result.push_back(const_cast<Comment*>(&comment));
            }
        }
    }
    return result;
}

void Slide::remove() {
    if (presentation_) {
        presentation_->slides().remove(*this);
    }
}

// ---------------------------------------------------------------------------
// OPC-level initialization
// ---------------------------------------------------------------------------

void Slide::init_internal(Presentation* presentation,
                          Internal::opc::OpcPackage* package,
                          std::string_view part_name,
                          const SlideReference& slide_ref,
                          Internal::pptx::SlidePart* slide_part,
                          LayoutResolver layout_resolver) {
    // Reset base class state.
    set_presentation(presentation);
    set_slide_id(static_cast<uint32_t>(slide_ref.slide_id));

    // Store presentation reference.
    presentation_ = presentation;

    // Store OPC-level state.
    package_ = package;
    part_name_ = std::string(part_name);
    slide_part_ = slide_part;
    layout_resolver_ = std::move(layout_resolver);

    // Clear cached layout and notes slide manager state.
    layout_slide_ = nullptr;
    notes_slide_manager_.init_internal(this, package, slide_part);
}

SlidePartVariant Slide::get_slide_part() {
    if (slide_part_) {
        return slide_part_;
    }
    return std::monostate{};
}

} // namespace Aspose::Slides::Foss
