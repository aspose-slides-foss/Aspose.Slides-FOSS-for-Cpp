// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/auto_shape.h>

#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

namespace Aspose::Slides::Foss {

void AutoShape::init_internal(pugi::xml_node xml_element,
                              Internal::pptx::SlidePart* slide_part,
                              IBaseSlide* parent_slide) {
    // Delegate to Shape (handles frame, fill, line, effect formats, etc.)
    Shape::init_internal(xml_element, slide_part, parent_slide);

    // Parse text frame from <p:txBody>.
    auto txbody = xml_element.child("p:txBody");
    if (txbody) {
        text_frame_ = std::make_unique<TextFrame>();
        text_frame_->set_parent_shape(this);
        text_frame_->init_internal(txbody, slide_part, parent_slide, nullptr);
    }
}

TextFrame& AutoShape::add_text_frame(std::string_view text) {
    text_frame_ = std::make_unique<TextFrame>();
    text_frame_->set_text(std::string(text));
    text_frame_->set_parent_shape(this);
    return *text_frame_;
}

} // namespace Aspose::Slides::Foss
