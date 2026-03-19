// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/pvi_object.h>
#include <Aspose/Slides/Foss/i_base_slide.h>

namespace Aspose::Slides::Foss {

IPresentationComponent* PVIObject::as_i_presentation_component() {
    return this;
}

const IPresentationComponent* PVIObject::as_i_presentation_component() const {
    return this;
}

IBaseSlide* PVIObject::slide() {
    return parent_slide_;
}

const IBaseSlide* PVIObject::slide() const {
    return parent_slide_;
}

IPresentation* PVIObject::presentation() {
    if (parent_slide_ != nullptr) {
        return parent_slide_->presentation();
    }
    return nullptr;
}

const IPresentation* PVIObject::presentation() const {
    if (parent_slide_ != nullptr) {
        return parent_slide_->presentation();
    }
    return nullptr;
}

void PVIObject::set_parent_slide(IBaseSlide* slide) {
    parent_slide_ = slide;
}

} // namespace Aspose::Slides::Foss
