// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/portion.h>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/portion_format.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

namespace Aspose::Slides::Foss {

struct Portion::Impl {
    std::string text;
    PortionFormat format;
    pugi::xml_node r_element;
    pugi::xml_node p_element;
    pugi::xml_node txbody_element;
    Internal::pptx::SlidePart* slide_part = nullptr;
    IBaseSlide* parent_slide = nullptr;
};

Portion::Portion() : impl_(std::make_unique<Impl>()) {}

Portion::Portion(std::string text) : impl_(std::make_unique<Impl>()) {
    impl_->text = std::move(text);
}

Portion::~Portion() = default;
Portion::Portion(Portion&&) noexcept = default;
Portion& Portion::operator=(Portion&&) noexcept = default;

const std::string& Portion::text() const {
    return impl_->text;
}

void Portion::set_text(std::string value) {
    impl_->text = std::move(value);
}

PortionFormat& Portion::portion_format() {
    return impl_->format;
}

const PortionFormat& Portion::portion_format() const {
    return impl_->format;
}

ISlideComponent* Portion::as_i_slide_component() {
    return static_cast<ISlideComponent*>(this);
}

const ISlideComponent* Portion::as_i_slide_component() const {
    return static_cast<const ISlideComponent*>(this);
}

IBaseSlide* Portion::slide() {
    return impl_->parent_slide;
}

const IBaseSlide* Portion::slide() const {
    return impl_->parent_slide;
}

IPresentationComponent* Portion::as_i_presentation_component() {
    return static_cast<IPresentationComponent*>(this);
}

const IPresentationComponent* Portion::as_i_presentation_component() const {
    return static_cast<const IPresentationComponent*>(this);
}

IPresentation* Portion::presentation() {
    return impl_->parent_slide ? impl_->parent_slide->presentation() : nullptr;
}

const IPresentation* Portion::presentation() const {
    return impl_->parent_slide ? impl_->parent_slide->presentation() : nullptr;
}

void Portion::init_internal(pugi::xml_node r_element,
                            pugi::xml_node p_element,
                            pugi::xml_node txbody_element,
                            Internal::pptx::SlidePart* slide_part,
                            IBaseSlide* parent_slide) {
    impl_->r_element = r_element;
    impl_->p_element = p_element;
    impl_->txbody_element = txbody_element;
    impl_->slide_part = slide_part;
    impl_->parent_slide = parent_slide;

    // Initialize portion format from the <a:rPr> element so that text
    // formatting properties (bold, italic, underline, etc.) are loaded.
    impl_->format.init_from_rpr(r_element, [slide_part]() {
        if (slide_part) slide_part->save();
    });
}

pugi::xml_node Portion::r_element() const {
    return impl_->r_element;
}

pugi::xml_node Portion::p_element() const {
    return impl_->p_element;
}

pugi::xml_node Portion::txbody_element() const {
    return impl_->txbody_element;
}

Internal::pptx::SlidePart* Portion::slide_part() const {
    return impl_->slide_part;
}

void Portion::set_slide(IBaseSlide* slide) {
    impl_->parent_slide = slide;
}

} // namespace Aspose::Slides::Foss
