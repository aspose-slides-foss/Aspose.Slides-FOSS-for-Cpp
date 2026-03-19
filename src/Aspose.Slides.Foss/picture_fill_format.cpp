// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/picture_fill_format.h>

#include <cmath>
#include <string>
#include <string_view>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// Tag constants (prefixed names for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kBlip     = "a:blip";
static constexpr std::string_view kSrcRect  = "a:srcRect";
static constexpr std::string_view kStretch  = "a:stretch";
static constexpr std::string_view kFillRect = "a:fillRect";
static constexpr std::string_view kTile     = "a:tile";

// ---------------------------------------------------------------------------
// PictureFillFormat – XML-backed internal methods
// ---------------------------------------------------------------------------

void PictureFillFormat::init_internal(pugi::xml_node blip_fill_element,
                                      std::function<void()> save_callback) {
    blip_fill_ = blip_fill_element;
    save_callback_ = std::move(save_callback);
}

pugi::xml_node PictureFillFormat::get_blip() const {
    return blip_fill_.child(std::string(kBlip).c_str());
}

pugi::xml_node PictureFillFormat::get_or_create_src_rect() {
    auto src_rect = blip_fill_.child(std::string(kSrcRect).c_str());
    if (src_rect) return src_rect;
    return blip_fill_.append_child(std::string(kSrcRect).c_str());
}

pugi::xml_node PictureFillFormat::get_stretch() const {
    return blip_fill_.child(std::string(kStretch).c_str());
}

pugi::xml_node PictureFillFormat::get_or_create_fill_rect() {
    auto stretch = get_stretch();
    if (!stretch) {
        stretch = blip_fill_.append_child(std::string(kStretch).c_str());
    }
    auto fill_rect = stretch.child(std::string(kFillRect).c_str());
    if (!fill_rect) {
        fill_rect = stretch.append_child(std::string(kFillRect).c_str());
    }
    return fill_rect;
}

float PictureFillFormat::get_crop_value(std::string_view attr) const {
    auto src_rect = blip_fill_.child(std::string(kSrcRect).c_str());
    if (!src_rect) return 0.0f;
    auto val = src_rect.attribute(std::string(attr).c_str());
    if (!val) return 0.0f;
    return static_cast<float>(val.as_int(0)) / 1000.0f;
}

void PictureFillFormat::set_crop_value(std::string_view attr, float value) {
    auto src_rect = get_or_create_src_rect();
    std::string attr_str{attr};
    auto existing = src_rect.attribute(attr_str.c_str());
    int int_val = static_cast<int>(value * 1000.0f);
    std::string val_str = std::to_string(int_val);
    if (existing) {
        existing.set_value(val_str.c_str());
    } else {
        src_rect.append_attribute(attr_str.c_str()) = val_str.c_str();
    }
}

float PictureFillFormat::get_stretch_offset(std::string_view attr) const {
    auto stretch = get_stretch();
    if (!stretch) return 0.0f;
    auto fill_rect = stretch.child(std::string(kFillRect).c_str());
    if (!fill_rect) return 0.0f;
    auto val = fill_rect.attribute(std::string(attr).c_str());
    if (!val) return 0.0f;
    return static_cast<float>(val.as_int(0)) / 1000.0f;
}

void PictureFillFormat::set_stretch_offset(std::string_view attr, float value) {
    auto fill_rect = get_or_create_fill_rect();
    std::string attr_str{attr};
    auto existing = fill_rect.attribute(attr_str.c_str());
    int int_val = static_cast<int>(value * 1000.0f);
    std::string val_str = std::to_string(int_val);
    if (existing) {
        existing.set_value(val_str.c_str());
    } else {
        fill_rect.append_attribute(attr_str.c_str()) = val_str.c_str();
    }
}

pugi::xml_node PictureFillFormat::get_tile() const {
    return blip_fill_.child(std::string(kTile).c_str());
}

pugi::xml_node PictureFillFormat::ensure_tile() {
    auto tile = get_tile();
    if (tile) return tile;

    // Remove stretch if present (switching to tile mode).
    auto stretch = blip_fill_.child(std::string(kStretch).c_str());
    if (stretch) {
        blip_fill_.remove_child(stretch);
    }

    return blip_fill_.append_child(std::string(kTile).c_str());
}

void PictureFillFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

} // namespace Aspose::Slides::Foss
