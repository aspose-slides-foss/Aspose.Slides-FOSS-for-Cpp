// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/shape_bevel.h>

#include <cmath>
#include <string>
#include <string_view>
#include <utility>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::kEmuPerPoint;

// ---------------------------------------------------------------------------
// Tag constants (prefixed names for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kBevelT = "a:bevelT";
static constexpr std::string_view kBevelB = "a:bevelB";

// ---------------------------------------------------------------------------
// ShapeBevel – construction and XML-backed internal methods
// ---------------------------------------------------------------------------

ShapeBevel::ShapeBevel(bool is_top_bevel)
    : is_top_(is_top_bevel) {}

void ShapeBevel::init_internal(pugi::xml_node sp3d_element,
                               std::function<void()> save_callback) {
    sp3d_element_ = sp3d_element;
    save_callback_ = std::move(save_callback);

    // Read existing bevel element.
    auto tag = is_top_ ? kBevelT : kBevelB;
    auto bevel = sp3d_element_.child(std::string(tag).c_str());
    if (bevel) {
        auto prst = bevel.attribute("prst");
        if (prst) {
            bevel_type_ = bevel_preset_type_from_ooxml(prst.as_string());
        }
        auto w = bevel.attribute("w");
        if (w) {
            width_ = static_cast<double>(w.as_llong(0)) / kEmuPerPoint;
        }
        auto h = bevel.attribute("h");
        if (h) {
            height_ = static_cast<double>(h.as_llong(0)) / kEmuPerPoint;
        }
    }
}

pugi::xml_node ShapeBevel::ensure_bevel() {
    auto tag = is_top_ ? kBevelT : kBevelB;
    auto bevel = sp3d_element_.child(std::string(tag).c_str());
    if (bevel) return bevel;
    return sp3d_element_.append_child(std::string(tag).c_str());
}

void ShapeBevel::set_bevel_type(BevelPresetType value) noexcept {
    bevel_type_ = value;
    if (sp3d_element_) {
        auto bevel = ensure_bevel();
        auto ooxml = bevel_preset_type_to_ooxml(value);
        auto attr = bevel.attribute("prst");
        if (attr) {
            attr.set_value(std::string(ooxml).c_str());
        } else if (!ooxml.empty()) {
            bevel.append_attribute("prst") = std::string(ooxml).c_str();
        }
        save();
    }
}

void ShapeBevel::set_width(double value) noexcept {
    width_ = value;
    if (sp3d_element_) {
        auto bevel = ensure_bevel();
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        auto attr = bevel.attribute("w");
        if (attr) {
            attr.set_value(std::to_string(emu).c_str());
        } else {
            bevel.append_attribute("w") = std::to_string(emu).c_str();
        }
        save();
    }
}

void ShapeBevel::set_height(double value) noexcept {
    height_ = value;
    if (sp3d_element_) {
        auto bevel = ensure_bevel();
        auto emu = static_cast<long long>(std::round(value * kEmuPerPoint));
        auto attr = bevel.attribute("h");
        if (attr) {
            attr.set_value(std::to_string(emu).c_str());
        } else {
            bevel.append_attribute("h") = std::to_string(emu).c_str();
        }
        save();
    }
}

void ShapeBevel::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
