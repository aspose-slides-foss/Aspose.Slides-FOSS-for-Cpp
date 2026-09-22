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
    slide_part_ = slide_part;

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
    text_frame_->set_parent_shape(this);

    // A shape on a deck opened from a file is saved from its XML, so the new
    // frame has to be a new <p:txBody> there. Left detached, it read its text
    // back from memory while the file kept the old body.
    if (auto sp = xml_element()) {
        // CT_Shape is (nvSpPr, spPr, style?, txBody?, extLst?).
        auto old_body = sp.child("p:txBody");
        auto next = old_body ? old_body : sp.child("p:extLst");
        auto body = next ? sp.insert_child_before("p:txBody", next)
                         : sp.append_child("p:txBody");
        if (old_body) sp.remove_child(old_body);

        // The same empty body add_auto_shape() gives a new shape.
        auto body_pr = body.append_child("a:bodyPr");
        body_pr.append_attribute("rtlCol") = "0";
        body_pr.append_attribute("anchor") = "ctr";
        body.append_child("a:lstStyle");
        text_frame_->init_internal(body, slide_part_, slide(), this);
    }

    text_frame_->set_text(std::string(text));
    return *text_frame_;
}

} // namespace Aspose::Slides::Foss
