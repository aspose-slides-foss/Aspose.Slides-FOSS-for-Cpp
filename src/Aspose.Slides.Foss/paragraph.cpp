// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/paragraph.h>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/paragraph_format.h>
#include <Aspose/Slides/Foss/picture_utilities.h>
#include <Aspose/Slides/Foss/portion_collection.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

namespace Aspose::Slides::Foss {

struct Paragraph::Impl {
    std::string text;
    ParagraphFormat format;
    PortionCollection portions;
    pugi::xml_node p_element;
    pugi::xml_node txbody_element;
    Internal::pptx::SlidePart* slide_part = nullptr;
    IBaseSlide* parent_slide = nullptr;
};

Paragraph::Paragraph() : impl_(std::make_unique<Impl>()) {}

Paragraph::Paragraph(std::string text) : impl_(std::make_unique<Impl>()) {
    impl_->text = text;
    impl_->portions.add(Portion(std::move(text)));
}

Paragraph::~Paragraph() = default;

Paragraph::Paragraph(Paragraph&& other) noexcept = default;

Paragraph& Paragraph::operator=(Paragraph&&) noexcept = default;

std::string Paragraph::text() const {
    if (impl_->portions.size() > 0) {
        std::string result;
        for (std::size_t i = 0; i < impl_->portions.size(); ++i) {
            result += impl_->portions[i].text();
        }
        return result;
    }
    return impl_->text;
}

void Paragraph::set_text(std::string value) {
    impl_->text = value;
    impl_->portions.clear();
    impl_->portions.add(Portion(std::move(value)));
}

ParagraphFormat& Paragraph::paragraph_format() {
    return impl_->format;
}

const ParagraphFormat& Paragraph::paragraph_format() const {
    return impl_->format;
}

PortionCollection& Paragraph::portions() {
    return impl_->portions;
}

const PortionCollection& Paragraph::portions() const {
    return impl_->portions;
}

ISlideComponent* Paragraph::as_i_slide_component() {
    return static_cast<ISlideComponent*>(this);
}

const ISlideComponent* Paragraph::as_i_slide_component() const {
    return static_cast<const ISlideComponent*>(this);
}

IBaseSlide* Paragraph::slide() {
    return impl_->parent_slide;
}

const IBaseSlide* Paragraph::slide() const {
    return impl_->parent_slide;
}

IPresentationComponent* Paragraph::as_i_presentation_component() {
    return static_cast<IPresentationComponent*>(this);
}

const IPresentationComponent* Paragraph::as_i_presentation_component() const {
    return static_cast<const IPresentationComponent*>(this);
}

IPresentation* Paragraph::presentation() {
    return impl_->parent_slide ? impl_->parent_slide->presentation() : nullptr;
}

const IPresentation* Paragraph::presentation() const {
    return impl_->parent_slide ? impl_->parent_slide->presentation() : nullptr;
}

void Paragraph::init_internal(pugi::xml_node p_element,
                              pugi::xml_node txbody_element,
                              Internal::pptx::SlidePart* slide_part,
                              IBaseSlide* parent_slide) {
    impl_->p_element = p_element;
    impl_->txbody_element = txbody_element;
    impl_->slide_part = slide_part;
    impl_->parent_slide = parent_slide;

    // Extract text from <a:r>/<a:t> children (supports both prefix and Clark notation).
    std::string text;
    for (auto child = p_element.first_child(); child; child = child.next_sibling()) {
        std::string_view name = child.name();
        if (name == "a:r" || name == Internal::pptx::Elements::kAR) {
            for (auto sub = child.first_child(); sub; sub = sub.next_sibling()) {
                std::string_view sub_name = sub.name();
                if (sub_name == "a:t" || sub_name == Internal::pptx::Elements::kAT) {
                    text += sub.text().as_string("");
                }
            }
        }
    }
    impl_->text = std::move(text);

    // Initialize the portion collection so portions can be lazily loaded from XML.
    impl_->portions.init_internal(p_element, txbody_element, slide_part, parent_slide);

    // Initialize paragraph format from <a:pPr> element.
    auto ppr = p_element.child("a:pPr");
    if (!ppr) ppr = p_element.child(Internal::pptx::Elements::kAPPr.c_str());
    // The <a:p> goes with it: most paragraphs in a real deck carry no
    // <a:pPr>, and without the parent the format has nowhere to write the
    // first property that gets set.
    impl_->format.init_internal(ppr, [slide_part]() {
        if (slide_part) slide_part->save();
    }, p_element);

    if (slide_part && parent_slide) {
        if (auto* slide = dynamic_cast<Slide*>(parent_slide)) {
            picture::flush_pending_blip_images(*slide);
        }
    }
}

pugi::xml_node Paragraph::p_element() const {
    return impl_->p_element;
}

pugi::xml_node Paragraph::txbody_element() const {
    return impl_->txbody_element;
}

Internal::pptx::SlidePart* Paragraph::slide_part() const {
    return impl_->slide_part;
}

void Paragraph::set_slide(IBaseSlide* slide) {
    impl_->parent_slide = slide;
}

} // namespace Aspose::Slides::Foss
