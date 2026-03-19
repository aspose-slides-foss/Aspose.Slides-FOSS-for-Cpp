// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/picture.h>

#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/slide.h>

namespace Aspose::Slides::Foss {

Picture::Picture(Slide* parent_slide) noexcept
    : parent_slide_(parent_slide) {}

void Picture::init_internal(pugi::xml_node blip_element,
                            Internal::pptx::SlidePart* slide_part,
                            Slide* parent_slide) {
    blip_ = blip_element;
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;
}

IPPImage* Picture::image() const noexcept {
    return image_;
}

void Picture::set_image(IPPImage* value) {
    image_ = value;
}

const std::string& Picture::link_path_long() const noexcept {
    return link_path_long_;
}

void Picture::set_link_path_long(std::string value) {
    link_path_long_ = std::move(value);
}

IPresentation* Picture::presentation() {
    return parent_slide_->presentation();
}

const IPresentation* Picture::presentation() const {
    return parent_slide_->presentation();
}

IBaseSlide* Picture::slide() {
    return nullptr;
}

const IBaseSlide* Picture::slide() const {
    return nullptr;
}

IPresentationComponent* Picture::as_i_presentation_component() {
    return this;
}

const IPresentationComponent* Picture::as_i_presentation_component() const {
    return this;
}

ISlideComponent& Picture::as_i_slide_component() noexcept {
    return *this;
}

const ISlideComponent& Picture::as_i_slide_component() const noexcept {
    return *this;
}

} // namespace Aspose::Slides::Foss
