// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/notes_slide_manager.h>

#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/i_presentation_component.h>
#include <Aspose/Slides/Foss/i_slide.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/pptx/notes_slide_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

namespace Aspose::Slides::Foss {

NotesSlideManager::NotesSlideManager() = default;
NotesSlideManager::NotesSlideManager(ISlide* slide) : slide_(slide) {}
NotesSlideManager::~NotesSlideManager() = default;
NotesSlideManager::NotesSlideManager(NotesSlideManager&&) noexcept = default;
NotesSlideManager& NotesSlideManager::operator=(NotesSlideManager&&) noexcept = default;

void NotesSlideManager::init_internal(ISlide* slide,
                                       Internal::opc::OpcPackage* package,
                                       Internal::pptx::SlidePart* slide_part) {
    slide_ = slide;
    package_ = package;
    slide_part_ = slide_part;
    notes_slide_cache_.reset();
    owned_notes_part_.reset();
}

INotesSlide* NotesSlideManager::notes_slide() const {
    if (notes_slide_cache_) {
        return notes_slide_cache_.get();
    }

    // When no OPC context is set, there are no relationships to resolve.
    if (!slide_part_) {
        return nullptr;
    }

    auto part_name = get_notes_part_name();
    if (!part_name) {
        return nullptr;
    }

    return const_cast<NotesSlideManager*>(this)->load_notes_slide(*part_name);
}

INotesSlide* NotesSlideManager::add_notes_slide() {
    auto* existing = notes_slide();
    if (existing) {
        return existing;
    }

    // Simple creation path (no OPC package context).
    // Creates a basic NotesSlide attached to the parent slide.
    auto ns = std::make_unique<NotesSlide>(slide_);
    notes_slide_cache_ = std::move(ns);
    return notes_slide_cache_.get();
}

void NotesSlideManager::remove_notes_slide() {
    notes_slide_cache_.reset();
    owned_notes_part_.reset();
}

std::optional<std::string> NotesSlideManager::get_notes_part_name() const {
    if (!slide_part_) {
        return std::nullopt;
    }

    auto rels = slide_part_->rels_manager().get_relationships_by_type(
        Internal::opc::rel_types::kNotesSlide);

    if (rels.empty()) {
        return std::nullopt;
    }

    return slide_part_->resolve_target(rels[0].target);
}

INotesSlide* NotesSlideManager::load_notes_slide(const std::string& part_name) {
    if (!package_) {
        return nullptr;
    }

    owned_notes_part_ = std::make_unique<Internal::pptx::NotesSlidePart>(
        *package_, part_name);

    auto notes_slide = std::make_unique<NotesSlide>();

    // Retrieve the presentation pointer from the parent slide if available.
    IPresentation* presentation = nullptr;
    if (slide_) {
        auto* component = dynamic_cast<IPresentationComponent*>(slide_);
        if (component) {
            presentation = component->presentation();
        }
    }

    notes_slide->init_internal(
        presentation,
        package_,
        part_name,
        owned_notes_part_.get(),
        slide_);

    notes_slide_cache_ = std::move(notes_slide);
    return notes_slide_cache_.get();
}

} // namespace Aspose::Slides::Foss
