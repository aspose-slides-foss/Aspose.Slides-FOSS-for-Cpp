// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/adjust_value_collection.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void AdjustValueCollection::init_internal(
    pugi::xml_node av_lst_element,
    Internal::pptx::SlidePart* slide_part) {
    av_lst_ = av_lst_element;
    slide_part_ = slide_part;

    // Populate the values vector from XML child <a:gd> elements.
    values_.clear();
    for (auto gd : get_gd_elements()) {
        AdjustValue av;
        av.init_internal(gd, slide_part_);
        values_.push_back(std::move(av));
    }
}

// ---------------------------------------------------------------------------
// get_gd_elements
// ---------------------------------------------------------------------------

std::vector<pugi::xml_node> AdjustValueCollection::get_gd_elements() const {
    std::vector<pugi::xml_node> result;
    if (!av_lst_) {
        return result;
    }

    // Find all child elements whose name matches "gd" in the DrawingML namespace.
    for (auto child : av_lst_.children()) {
        std::string_view name = child.name();
        // Match both prefixed ("a:gd") and local ("gd") forms.
        if (name == "a:gd" || name == "gd") {
            result.push_back(child);
        }
    }
    return result;
}

} // namespace Aspose::Slides::Foss
