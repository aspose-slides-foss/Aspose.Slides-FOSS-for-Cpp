// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effects/fill_overlay.h>
#include <Aspose/Slides/Foss/_internal/pptx/xml_attribute_utils.h>

#include <string_view>

namespace Aspose::Slides::Foss::Effects {

namespace {

// ST_BlendMode token <-> FillBlendMode. The tokens are not the display names
// carried by to_string_view(); "mult" and "over" in particular are abbreviated.
const char* blend_to_ooxml(FillBlendMode value) {
    switch (value) {
        case FillBlendMode::DARKEN:   return "darken";
        case FillBlendMode::LIGHTEN:  return "lighten";
        case FillBlendMode::MULTIPLY: return "mult";
        case FillBlendMode::OVERLAY:  return "over";
        case FillBlendMode::SCREEN:   return "screen";
    }
    return "over";
}

FillBlendMode blend_from_ooxml(std::string_view val) {
    if (val == "darken") return FillBlendMode::DARKEN;
    if (val == "lighten") return FillBlendMode::LIGHTEN;
    if (val == "mult") return FillBlendMode::MULTIPLY;
    if (val == "screen") return FillBlendMode::SCREEN;
    return FillBlendMode::OVERLAY;
}

} // namespace

const char* fill_blend_mode_to_ooxml(FillBlendMode value) {
    return blend_to_ooxml(value);
}

void FillOverlay::init_internal(pugi::xml_node element,
                                std::function<void()> save_callback,
                                IBaseSlide* parent_slide) {
    element_ = element;
    save_callback_ = save_callback;
    set_parent_slide(parent_slide);

    if (auto attr = element_.attribute("blend")) {
        blend_ = blend_from_ooxml(attr.as_string());
    }

    // CT_FillOverlayEffect requires @blend and exactly one fill child. A newly
    // created element carries neither, so establish both here rather than
    // leaving an element the schema rejects.
    if (element_) {
        Internal::pptx::set_attribute(element_, "blend", blend_to_ooxml(blend_));
        fill_format_.init_internal(element_, save_callback_);
        if (!fill_format_.find_fill_element()) {
            fill_format_.get_or_create_fill("a:noFill");
        }
    }
}

void FillOverlay::set_blend(FillBlendMode value) noexcept {
    blend_ = value;
    if (element_) {
        Internal::pptx::set_attribute(element_, "blend", blend_to_ooxml(value));
    }
    if (save_callback_) {
        save_callback_();
    }
}

void FillOverlay::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss::Effects
