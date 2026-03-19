// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/adjust_value.h>

#include <charconv>
#include <string_view>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void AdjustValue::init_internal(pugi::xml_node gd_element,
                                Internal::pptx::SlidePart* slide_part) {
    gd_element_ = gd_element;
    slide_part_ = slide_part;

    if (gd_element_) {
        // Read name from the "name" attribute of <a:gd name="adj1" fmla="val 50000"/>
        name_ = gd_element_.attribute("name").as_string("");

        // Parse raw value from the "fmla" attribute: "val NNNNN"
        std::string_view fmla = gd_element_.attribute("fmla").as_string("");
        constexpr std::string_view kValPrefix = "val ";
        if (fmla.starts_with(kValPrefix)) {
            auto num_str = fmla.substr(kValPrefix.size());
            int parsed = 0;
            std::from_chars(num_str.data(), num_str.data() + num_str.size(), parsed);
            raw_value_ = parsed;
        } else {
            raw_value_ = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// set_raw_value
// ---------------------------------------------------------------------------

void AdjustValue::set_raw_value(int value) noexcept {
    raw_value_ = value;

    // Sync back to XML if backed by an element.
    if (gd_element_) {
        auto fmla_str = "val " + std::to_string(value);
        gd_element_.attribute("fmla").set_value(fmla_str.c_str());
    }
}

} // namespace Aspose::Slides::Foss
