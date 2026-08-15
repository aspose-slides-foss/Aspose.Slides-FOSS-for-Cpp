// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/text_frame_format.h>

#include <Aspose/Slides/Foss/_internal/pptx/text_serialization.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <string_view>

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
    if (!txbody_element_) {
        return {};
    }
    // CT_TextBody is (bodyPr, lstStyle?, p+): the element goes first, not
    // last. Appending it after the paragraphs produces a body a consumer is
    // entitled to reject.
    return txbody_element_.prepend_child("a:bodyPr");
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

void Internal::pptx::serialize_body_pr(pugi::xml_node body_pr,
                                       const ITextFrameFormat& format) {
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


// ---------------------------------------------------------------------------
// Property accessors
//
// Backed by `<a:bodyPr>` when this object is bound to a `<a:txBody>`, and by
// the members when it is not. The two cases are the two serialisers: a deck
// opened from a file is edited in place through the XML, and a deck built in
// memory is written out by serialize_body_pr() at save time.
//
// A getter falls back to its member when the attribute is absent, so a
// property nobody set still reads as undefined and stays inheritable.
// ---------------------------------------------------------------------------

namespace {

TextAnchorType ooxml_to_anchor(std::string_view s) {
    if (s == "t")    return TextAnchorType::TOP;
    if (s == "ctr")  return TextAnchorType::CENTER;
    if (s == "b")    return TextAnchorType::BOTTOM;
    if (s == "just") return TextAnchorType::JUSTIFIED;
    if (s == "dist") return TextAnchorType::DISTRIBUTED;
    return TextAnchorType::NOT_DEFINED;
}

TextVerticalType ooxml_to_vertical(std::string_view s) {
    if (s == "horz")           return TextVerticalType::HORIZONTAL;
    if (s == "vert")           return TextVerticalType::VERTICAL;
    if (s == "vert270")        return TextVerticalType::VERTICAL270;
    if (s == "wordArtVert")    return TextVerticalType::WORD_ART_VERTICAL;
    if (s == "eaVert")         return TextVerticalType::EAST_ASIAN_VERTICAL;
    if (s == "mongolianVert")  return TextVerticalType::MONGOLIAN_VERTICAL;
    if (s == "wordArtVertRtl")
        return TextVerticalType::WORD_ART_VERTICAL_RIGHT_TO_LEFT;
    return TextVerticalType::NOT_DEFINED;
}

} // namespace

double TextFrameFormat::margin_left() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("lIns"))
        return bp.attribute("lIns").as_llong(0) / static_cast<double>(kEmuPerPoint);
    return margin_left_;
}

void TextFrameFormat::set_margin_left(double value) {
    margin_left_ = value;
    if (txbody_element_) set_margin("lIns", value);
}

double TextFrameFormat::margin_right() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("rIns"))
        return bp.attribute("rIns").as_llong(0) / static_cast<double>(kEmuPerPoint);
    return margin_right_;
}

void TextFrameFormat::set_margin_right(double value) {
    margin_right_ = value;
    if (txbody_element_) set_margin("rIns", value);
}

double TextFrameFormat::margin_top() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("tIns"))
        return bp.attribute("tIns").as_llong(0) / static_cast<double>(kEmuPerPoint);
    return margin_top_;
}

void TextFrameFormat::set_margin_top(double value) {
    margin_top_ = value;
    if (txbody_element_) set_margin("tIns", value);
}

double TextFrameFormat::margin_bottom() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("bIns"))
        return bp.attribute("bIns").as_llong(0) / static_cast<double>(kEmuPerPoint);
    return margin_bottom_;
}

void TextFrameFormat::set_margin_bottom(double value) {
    margin_bottom_ = value;
    if (txbody_element_) set_margin("bIns", value);
}

NullableBool TextFrameFormat::wrap_text() const {
    if (auto bp = get_body_pr(); bp) {
        if (auto attr = bp.attribute("wrap")) {
            return std::string_view(attr.as_string("")) == "none"
                       ? NullableBool::FALSE
                       : NullableBool::TRUE;
        }
    }
    return wrap_text_;
}

void TextFrameFormat::set_wrap_text(NullableBool value) {
    wrap_text_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    // ST_TextWrappingType is "square" or "none"; there is no boolean form.
    if (value == NullableBool::NOT_DEFINED) {
        bp.remove_attribute("wrap");
    } else {
        set_attr(bp, "wrap", value == NullableBool::TRUE ? "square" : "none");
    }
    save();
}

TextAnchorType TextFrameFormat::anchoring_type() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("anchor"))
        return ooxml_to_anchor(bp.attribute("anchor").as_string(""));
    return anchoring_type_;
}

void TextFrameFormat::set_anchoring_type(TextAnchorType value) {
    anchoring_type_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    if (const char* token = anchor_to_ooxml(value)) {
        set_attr(bp, "anchor", token);
    } else {
        bp.remove_attribute("anchor");
    }
    save();
}

NullableBool TextFrameFormat::center_text() const {
    if (auto bp = get_body_pr(); bp) {
        if (auto attr = bp.attribute("anchorCtr")) {
            return std::string_view(attr.as_string("")) == "1"
                       ? NullableBool::TRUE
                       : NullableBool::FALSE;
        }
    }
    return center_text_;
}

void TextFrameFormat::set_center_text(NullableBool value) {
    center_text_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    if (value == NullableBool::NOT_DEFINED) {
        bp.remove_attribute("anchorCtr");
    } else {
        set_attr(bp, "anchorCtr", value == NullableBool::TRUE ? "1" : "0");
    }
    save();
}

TextVerticalType TextFrameFormat::text_vertical_type() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("vert"))
        return ooxml_to_vertical(bp.attribute("vert").as_string(""));
    return text_vertical_type_;
}

void TextFrameFormat::set_text_vertical_type(TextVerticalType value) {
    text_vertical_type_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    if (const char* token = vertical_to_ooxml(value)) {
        set_attr(bp, "vert", token);
    } else {
        bp.remove_attribute("vert");
    }
    save();
}

TextAutofitType TextFrameFormat::autofit_type() const {
    if (auto bp = get_body_pr(); bp) {
        if (bp.child("a:noAutofit"))   return TextAutofitType::NONE;
        if (bp.child("a:normAutofit")) return TextAutofitType::NORMAL;
        if (bp.child("a:spAutoFit"))   return TextAutofitType::SHAPE;
    }
    return autofit_type_;
}

void TextFrameFormat::set_autofit_type(TextAutofitType value) {
    autofit_type_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    // The autofit choice is one element out of three; replace whichever is
    // there so the body cannot end up carrying two of them.
    for (const char* tag : {"a:noAutofit", "a:normAutofit", "a:spAutoFit"}) {
        if (auto existing = bp.child(tag)) bp.remove_child(existing);
    }
    if (const char* tag = autofit_to_ooxml(value)) {
        // CT_TextBodyProperties puts the autofit choice after a:prstTxWarp.
        if (auto warp = bp.child("a:prstTxWarp")) {
            bp.insert_child_after(tag, warp);
        } else {
            bp.prepend_child(tag);
        }
    }
    save();
}

int TextFrameFormat::column_count() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("numCol"))
        return bp.attribute("numCol").as_int(1);
    return column_count_;
}

void TextFrameFormat::set_column_count(int value) {
    column_count_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    // @numCol defaults to 1, so a single column is written by leaving it off.
    if (value <= 1) {
        bp.remove_attribute("numCol");
    } else {
        auto attr = bp.attribute("numCol");
        if (!attr) attr = bp.append_attribute("numCol");
        attr.set_value(value);
    }
    save();
}

double TextFrameFormat::column_spacing() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("spcCol"))
        return bp.attribute("spcCol").as_llong(0) / static_cast<double>(kEmuPerPoint);
    return column_spacing_;
}

void TextFrameFormat::set_column_spacing(double value) {
    column_spacing_ = value;
    if (txbody_element_) set_margin("spcCol", value);
}

double TextFrameFormat::rotation_angle() const {
    if (auto bp = get_body_pr(); bp && bp.attribute("rot"))
        return bp.attribute("rot").as_llong(0) / static_cast<double>(kRotationUnit);
    return rotation_angle_;
}

void TextFrameFormat::set_rotation_angle(double value) {
    rotation_angle_ = value;
    if (!txbody_element_) return;
    auto bp = ensure_body_pr();
    if (!bp) return;
    if (value == 0.0) {
        bp.remove_attribute("rot");
    } else {
        auto attr = bp.attribute("rot");
        if (!attr) attr = bp.append_attribute("rot");
        attr.set_value(static_cast<long long>(std::round(value * kRotationUnit)));
    }
    save();
}

} // namespace Aspose::Slides::Foss
