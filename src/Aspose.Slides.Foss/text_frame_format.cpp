// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/text_frame_format.h>

#include <algorithm>
#include <cmath>
#include <string>

namespace Aspose::Slides::Foss {

static constexpr int kEmuPerPoint = 12700;

// ---------------------------------------------------------------------------
// TextFrameFormat — XML-backed internal methods
// ---------------------------------------------------------------------------

void TextFrameFormat::init_internal(pugi::xml_node txbody_element,
                                    std::function<void()> save_callback) {
    txbody_element_ = txbody_element;
    save_callback_ = std::move(save_callback);
}

pugi::xml_node TextFrameFormat::get_body_pr() const {
    if (!txbody_element_) {
        return {};
    }
    return txbody_element_.child("a:bodyPr");
}

pugi::xml_node TextFrameFormat::ensure_body_pr() {
    auto body_pr = get_body_pr();
    if (body_pr) {
        return body_pr;
    }
    return txbody_element_.append_child("a:bodyPr");
}

void TextFrameFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// ---------------------------------------------------------------------------
// Margin helpers (EMU <-> points)
// ---------------------------------------------------------------------------

double TextFrameFormat::get_margin(std::string_view attr, int default_emu) const {
    auto body_pr = get_body_pr();
    if (!body_pr) {
        return default_emu / static_cast<double>(kEmuPerPoint);
    }
    auto val = body_pr.attribute(std::string(attr).c_str());
    if (!val) {
        return default_emu / static_cast<double>(kEmuPerPoint);
    }
    return std::stoi(val.value()) / static_cast<double>(kEmuPerPoint);
}

void TextFrameFormat::set_margin(std::string_view attr, double value) {
    auto body_pr = ensure_body_pr();
    std::string attr_str{attr};
    auto a = body_pr.attribute(attr_str.c_str());
    if (!a) {
        a = body_pr.append_attribute(attr_str.c_str());
    }
    a.set_value(
        std::to_string(static_cast<int>(std::round(value * kEmuPerPoint))).c_str());
    save();
}

// ---------------------------------------------------------------------------
// resize_shape_to_fit_text
// ---------------------------------------------------------------------------

void TextFrameFormat::resize_shape_to_fit_text(pugi::xml_node body_pr) {
    if (!txbody_element_) {
        return;
    }

    auto sp_element = txbody_element_.parent();
    if (!sp_element) {
        return;
    }

    auto sp_pr = sp_element.child("p:spPr");
    if (!sp_pr) {
        return;
    }

    auto xfrm = sp_pr.child("a:xfrm");
    if (!xfrm) {
        return;
    }

    auto ext = xfrm.child("a:ext");
    auto off = xfrm.child("a:off");
    if (!ext || !off) {
        return;
    }

    // Count paragraphs
    int num_paragraphs = 0;
    for (auto child : txbody_element_.children("a:p")) {
        (void)child;
        ++num_paragraphs;
    }
    num_paragraphs = std::max(1, num_paragraphs);

    // Default font size 18pt, single line spacing = 120% of font size
    constexpr int kDefaultFontSizeEmu = static_cast<int>(18.0 * kEmuPerPoint);
    constexpr int kLineHeightEmu = static_cast<int>(kDefaultFontSizeEmu * 1.2);
    int text_height_emu = num_paragraphs * kLineHeightEmu;

    // Top and bottom margins (default 45720 EMU = 3.6pt each)
    auto t_attr = body_pr.attribute("tIns");
    int top_margin = t_attr ? std::stoi(t_attr.value()) : 45720;
    auto b_attr = body_pr.attribute("bIns");
    int bottom_margin = b_attr ? std::stoi(b_attr.value()) : 45720;

    int required_height = text_height_emu + top_margin + bottom_margin;

    // Resize preserving vertical center
    auto y_attr = off.attribute("y");
    int current_y = y_attr ? std::stoi(y_attr.value()) : 0;
    auto cy_attr = ext.attribute("cy");
    int current_cy = cy_attr ? std::stoi(cy_attr.value()) : 0;

    int center_y = current_y + current_cy / 2;
    int new_y = center_y - required_height / 2;

    // Update ext cy
    if (!cy_attr) {
        cy_attr = ext.append_attribute("cy");
    }
    cy_attr.set_value(std::to_string(required_height).c_str());

    // Update off y
    if (!y_attr) {
        y_attr = off.append_attribute("y");
    }
    y_attr.set_value(std::to_string(new_y).c_str());
}

// ---------------------------------------------------------------------------
// serialize_body_pr — write the in-memory model onto an <a:bodyPr>
// ---------------------------------------------------------------------------

namespace {

constexpr int kRotationUnit = 60000; // 60000ths of a degree

/// ST_TextAnchoringType token, or nullptr when nothing is to be written.
const char* anchor_to_ooxml(TextAnchorType value) {
    switch (value) {
        case TextAnchorType::TOP:         return "t";
        case TextAnchorType::CENTER:      return "ctr";
        case TextAnchorType::BOTTOM:      return "b";
        case TextAnchorType::JUSTIFIED:   return "just";
        case TextAnchorType::DISTRIBUTED: return "dist";
        case TextAnchorType::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// ST_TextVerticalType token, or nullptr when nothing is to be written.
const char* vertical_to_ooxml(TextVerticalType value) {
    switch (value) {
        case TextVerticalType::HORIZONTAL:          return "horz";
        case TextVerticalType::VERTICAL:            return "vert";
        case TextVerticalType::VERTICAL270:         return "vert270";
        case TextVerticalType::WORD_ART_VERTICAL:   return "wordArtVert";
        case TextVerticalType::EAST_ASIAN_VERTICAL: return "eaVert";
        case TextVerticalType::MONGOLIAN_VERTICAL:  return "mongolianVert";
        case TextVerticalType::WORD_ART_VERTICAL_RIGHT_TO_LEFT:
            return "wordArtVertRtl";
        case TextVerticalType::NOT_DEFINED:         return nullptr;
    }
    return nullptr;
}

/// The autofit choice is an element, not an attribute.
const char* autofit_to_ooxml(TextAutofitType value) {
    switch (value) {
        case TextAutofitType::NONE:        return "a:noAutofit";
        case TextAutofitType::NORMAL:      return "a:normAutofit";
        case TextAutofitType::SHAPE:       return "a:spAutoFit";
        case TextAutofitType::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

void set_attr(pugi::xml_node node, const char* name, const char* value) {
    auto attr = node.attribute(name);
    if (!attr) attr = node.append_attribute(name);
    attr.set_value(value);
}

void set_emu_attr(pugi::xml_node node, const char* name, double points) {
    if (std::isnan(points)) return;
    auto attr = node.attribute(name);
    if (!attr) attr = node.append_attribute(name);
    attr.set_value(static_cast<long long>(std::round(points * kEmuPerPoint)));
}

} // namespace

void serialize_body_pr(pugi::xml_node body_pr, const ITextFrameFormat& format) {
    if (format.rotation_angle() != 0.0) {
        auto attr = body_pr.attribute("rot");
        if (!attr) attr = body_pr.append_attribute("rot");
        attr.set_value(
            static_cast<long long>(std::round(format.rotation_angle() * kRotationUnit)));
    }
    if (const char* vert = vertical_to_ooxml(format.text_vertical_type())) {
        set_attr(body_pr, "vert", vert);
    }
    // ST_TextWrappingType is "square" or "none"; there is no boolean form.
    if (format.wrap_text() != NullableBool::NOT_DEFINED) {
        set_attr(body_pr, "wrap",
                 format.wrap_text() == NullableBool::TRUE ? "square" : "none");
    }
    set_emu_attr(body_pr, "lIns", format.margin_left());
    set_emu_attr(body_pr, "tIns", format.margin_top());
    set_emu_attr(body_pr, "rIns", format.margin_right());
    set_emu_attr(body_pr, "bIns", format.margin_bottom());
    if (format.column_count() > 1) {
        auto attr = body_pr.attribute("numCol");
        if (!attr) attr = body_pr.append_attribute("numCol");
        attr.set_value(format.column_count());
    }
    if (format.column_spacing() > 0.0) {
        set_emu_attr(body_pr, "spcCol", format.column_spacing());
    }
    if (const char* anchor = anchor_to_ooxml(format.anchoring_type())) {
        set_attr(body_pr, "anchor", anchor);
    }
    if (format.center_text() != NullableBool::NOT_DEFINED) {
        set_attr(body_pr, "anchorCtr",
                 format.center_text() == NullableBool::TRUE ? "1" : "0");
    }

    // The autofit choice is a child element. Replace whichever one is there so
    // that re-serialising cannot leave two of the three behind.
    for (const char* tag : {"a:noAutofit", "a:normAutofit", "a:spAutoFit"}) {
        if (auto existing = body_pr.child(tag)) body_pr.remove_child(existing);
    }
    if (const char* autofit = autofit_to_ooxml(format.autofit_type())) {
        // CT_TextBodyProperties puts the autofit choice after a:prstTxWarp.
        if (auto warp = body_pr.child("a:prstTxWarp")) {
            body_pr.insert_child_after(autofit, warp);
        } else {
            body_pr.prepend_child(autofit);
        }
    }
}

} // namespace Aspose::Slides::Foss
