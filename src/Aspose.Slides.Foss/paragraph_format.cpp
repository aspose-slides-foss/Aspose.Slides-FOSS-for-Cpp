// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/paragraph_format.h>

#include <Aspose/Slides/Foss/_internal/pptx/text_serialization.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <string_view>
#include <unordered_map>


namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// pPr child element ordering (ECMA-376, CT_TextParagraphProperties)
// ---------------------------------------------------------------------------

// Flat tag -> group-index pairs for pPr child element ordering
// (ECMA-376, CT_TextParagraphProperties).
// The group index determines insertion order.
struct TagOrder { std::string_view tag; int group; };
static constexpr TagOrder kPprTagOrder[] = {
    {"a:lnSpc",    0},
    {"a:spcBef",   1},
    {"a:spcAft",   2},
    {"a:buClrTx",  3}, {"a:buClr",    3},
    {"a:buSzTx",   4}, {"a:buSzPct",  4}, {"a:buSzPts", 4},
    {"a:buFontTx", 5}, {"a:buFont",   5},
    {"a:buNone",   6}, {"a:buAutoNum",6}, {"a:buChar",  6}, {"a:buBlip", 6},
    {"a:tabLst",   7},
    {"a:defRPr",   8},
    {"a:extLst",   9},
};

/// Build a flat tag -> group-index map at first use.
static const std::unordered_map<std::string_view, int>& ppr_tag_index() {
    static const auto m = [] {
        std::unordered_map<std::string_view, int> result;
        for (const auto& entry : kPprTagOrder) {
            result[entry.tag] = entry.group;
        }
        return result;
    }();
    return m;
}

static int tag_position(std::string_view tag) {
    const auto& idx = ppr_tag_index();
    auto it = idx.find(tag);
    return (it != idx.end()) ? it->second : 999;
}

// ---------------------------------------------------------------------------
// ppr_insert_child — free function
// ---------------------------------------------------------------------------

pugi::xml_node Internal::pptx::ppr_insert_child(pugi::xml_node ppr,
                                                std::string_view tag) {
    const int target_pos = tag_position(tag);
    std::string tag_str{tag};

    for (auto child : ppr.children()) {
        if (tag_position(child.name()) > target_pos) {
            return ppr.insert_child_before(tag_str.c_str(), child);
        }
    }
    return ppr.append_child(tag_str.c_str());
}

// ---------------------------------------------------------------------------
// ParagraphFormat — XML-backed internal methods
// ---------------------------------------------------------------------------

static constexpr int kEmuPerPoint = 12700;

// ---------------------------------------------------------------------------
// OOXML alignment mappings
// ---------------------------------------------------------------------------

static TextAlignment ooxml_to_alignment(std::string_view s) {
    if (s == "l")        return TextAlignment::LEFT;
    if (s == "ctr")      return TextAlignment::CENTER;
    if (s == "r")        return TextAlignment::RIGHT;
    if (s == "just")     return TextAlignment::JUSTIFY;
    if (s == "justLow")  return TextAlignment::JUSTIFY_LOW;
    if (s == "dist")     return TextAlignment::DISTRIBUTED;
    return TextAlignment::NOT_DEFINED;
}

static const char* alignment_to_ooxml(TextAlignment a) {
    switch (a) {
        case TextAlignment::LEFT:        return "l";
        case TextAlignment::CENTER:      return "ctr";
        case TextAlignment::RIGHT:       return "r";
        case TextAlignment::JUSTIFY:     return "just";
        case TextAlignment::JUSTIFY_LOW: return "justLow";
        case TextAlignment::DISTRIBUTED: return "dist";
        default: return nullptr;
    }
}

// ---------------------------------------------------------------------------
// Alignment accessors
// ---------------------------------------------------------------------------

TextAlignment ParagraphFormat::alignment() const {
    if (ppr_element_) {
        auto attr = ppr_element_.attribute("algn");
        if (attr) return ooxml_to_alignment(attr.value());
    }
    return alignment_;
}

void ParagraphFormat::set_alignment(TextAlignment value) {
    alignment_ = value;
    if (auto ppr = ensure_ppr()) {
        if (value == TextAlignment::NOT_DEFINED) {
            ppr.remove_attribute("algn");
        } else {
            auto a = ppr.attribute("algn");
            if (!a) a = ppr.append_attribute("algn");
            a.set_value(alignment_to_ooxml(value));
        }
        save();
    }
}

void ParagraphFormat::init_internal(pugi::xml_node ppr_element,
                                    std::function<void()> save_callback,
                                    pugi::xml_node p_element) {
    ppr_element_ = ppr_element;
    p_element_ = p_element;
    save_callback_ = save_callback;
    // The bullet is part of the paragraph's formatting and lives in the same
    // element; binding it here is what makes a bullet set on a loaded deck
    // reach the file.
    bullet_.init_internal(ppr_element, std::move(save_callback), p_element);
}

pugi::xml_node ParagraphFormat::ensure_ppr() {
    if (ppr_element_) return ppr_element_;
    if (!p_element_) return {};
    // CT_TextParagraph is (pPr?, (r|br|fld)*, endParaRPr?), so the properties
    // element goes first.
    ppr_element_ = p_element_.prepend_child("a:pPr");
    bullet_.init_internal(ppr_element_, save_callback_, p_element_);
    return ppr_element_;
}

void ParagraphFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// --- NullableBool attribute helpers ---

NullableBool ParagraphFormat::get_nullable_bool_attr(std::string_view attr) const {
    if (!ppr_element_) {
        return NullableBool::NOT_DEFINED;
    }
    auto val = ppr_element_.attribute(std::string(attr).c_str());
    if (!val) {
        return NullableBool::NOT_DEFINED;
    }
    return (std::string_view{val.value()} == "1")
               ? NullableBool::TRUE
               : NullableBool::FALSE;
}

void ParagraphFormat::set_nullable_bool_attr(std::string_view attr,
                                             NullableBool value) {
    if (!ppr_element_) {
        return;
    }
    std::string attr_str{attr};
    if (value == NullableBool::NOT_DEFINED) {
        ppr_element_.remove_attribute(attr_str.c_str());
    } else {
        auto a = ppr_element_.attribute(attr_str.c_str());
        if (!a) {
            a = ppr_element_.append_attribute(attr_str.c_str());
        }
        a.set_value((value == NullableBool::TRUE) ? "1" : "0");
    }
    save();
}

// --- Spacing helpers ---

double ParagraphFormat::get_spacing(std::string_view tag) const {
    if (!ppr_element_) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    auto el = ppr_element_.child(std::string(tag).c_str());
    if (!el) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Check for percentage-based spacing first.
    auto pct = el.child("a:spcPct");
    if (pct) {
        auto val = pct.attribute("val");
        if (val) {
            return std::stoi(val.value()) / 1000.0;
        }
    }

    // Check for point-based spacing.
    auto pts = el.child("a:spcPts");
    if (pts) {
        auto val = pts.attribute("val");
        if (val) {
            return -(std::stoi(val.value()) / 100.0);
        }
    }

    return std::numeric_limits<double>::quiet_NaN();
}

void ParagraphFormat::set_spacing(std::string_view tag, double value) {
    if (!ppr_element_) {
        return;
    }
    std::string tag_str{tag};
    auto el = ppr_element_.child(tag_str.c_str());

    if (std::isnan(value)) {
        if (el) {
            ppr_element_.remove_child(el);
        }
    } else {
        if (!el) {
            el = Internal::pptx::ppr_insert_child(ppr_element_, tag);
        }
        // Remove existing children.
        while (auto child = el.first_child()) {
            el.remove_child(child);
        }
        if (value >= 0) {
            auto pct = el.append_child("a:spcPct");
            pct.append_attribute("val").set_value(
                std::to_string(static_cast<int>(std::round(value * 1000))).c_str());
        } else {
            auto pts = el.append_child("a:spcPts");
            pts.append_attribute("val").set_value(
                std::to_string(static_cast<int>(std::round(-value * 100))).c_str());
        }
    }
    save();
}

// --- EMU-based attribute helpers ---

double ParagraphFormat::get_emu_attr(std::string_view attr) const {
    if (!ppr_element_) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    auto val = ppr_element_.attribute(std::string(attr).c_str());
    if (!val) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return std::stoi(val.value()) / static_cast<double>(kEmuPerPoint);
}

void ParagraphFormat::set_emu_attr(std::string_view attr, double value) {
    if (!ppr_element_) {
        return;
    }
    std::string attr_str{attr};
    if (std::isnan(value)) {
        ppr_element_.remove_attribute(attr_str.c_str());
    } else {
        auto a = ppr_element_.attribute(attr_str.c_str());
        if (!a) {
            a = ppr_element_.append_attribute(attr_str.c_str());
        }
        a.set_value(
            std::to_string(
                static_cast<int>(std::round(value * kEmuPerPoint)))
                .c_str());
    }
    save();
}

// ---------------------------------------------------------------------------
// serialize_ppr — write the in-memory model into a fresh <a:pPr>
// ---------------------------------------------------------------------------

namespace {

/// ST_TextFontAlignType token, or nullptr when the value is not to be written.
const char* font_alignment_to_ooxml(FontAlignment value) {
    switch (value) {
        case FontAlignment::AUTOMATIC: return "auto";
        case FontAlignment::TOP:       return "t";
        case FontAlignment::CENTER:    return "ctr";
        case FontAlignment::BOTTOM:    return "b";
        case FontAlignment::BASELINE:  return "base";
        case FontAlignment::DEFAULT:   return nullptr;
    }
    return nullptr;
}

void append_emu_attr(pugi::xml_node node, const char* name, double points) {
    if (std::isnan(points)) return;
    node.append_attribute(name) =
        static_cast<long long>(std::round(points * kEmuPerPoint));
}

void append_bool_attr(pugi::xml_node node, const char* name, NullableBool value) {
    if (value == NullableBool::NOT_DEFINED) return;
    node.append_attribute(name) = (value == NullableBool::TRUE) ? "1" : "0";
}

/// spcBef / spcAft / lnSpc: a positive value is a percentage, a negative one is
/// a point size — the sign convention get_spacing()/set_spacing() already use.
void append_spacing(pugi::xml_node ppr, const char* tag, double value) {
    if (std::isnan(value)) return;
    auto el = Internal::pptx::ppr_insert_child(ppr, tag);
    if (value >= 0) {
        el.append_child("a:spcPct").append_attribute("val") =
            static_cast<int>(std::round(value * 1000));
    } else {
        el.append_child("a:spcPts").append_attribute("val") =
            static_cast<int>(std::round(-value * 100));
    }
}

} // namespace

bool Internal::pptx::ppr_has_content(const IParagraphFormat& format) {
    const auto& bullet = format.bullet();
    return format.alignment() != TextAlignment::NOT_DEFINED ||
           format.depth() != 0 ||
           !std::isnan(format.margin_left()) ||
           !std::isnan(format.margin_right()) ||
           !std::isnan(format.indent()) ||
           !std::isnan(format.default_tab_size()) ||
           !std::isnan(format.space_within()) ||
           !std::isnan(format.space_before()) ||
           !std::isnan(format.space_after()) ||
           format.right_to_left() != NullableBool::NOT_DEFINED ||
           format.east_asian_line_break() != NullableBool::NOT_DEFINED ||
           format.latin_line_break() != NullableBool::NOT_DEFINED ||
           format.hanging_punctuation() != NullableBool::NOT_DEFINED ||
           format.font_alignment() != FontAlignment::DEFAULT ||
           bullet.type() != BulletType::NOT_DEFINED;
}

void Internal::pptx::serialize_ppr(pugi::xml_node ppr,
                                   const IParagraphFormat& format) {
    // -- Attributes ---------------------------------------------------------
    append_emu_attr(ppr, "marL", format.margin_left());
    append_emu_attr(ppr, "marR", format.margin_right());
    if (format.depth() != 0) {
        ppr.append_attribute("lvl") = format.depth();
    }
    append_emu_attr(ppr, "indent", format.indent());
    if (const char* algn = alignment_to_ooxml(format.alignment())) {
        ppr.append_attribute("algn") = algn;
    }
    append_emu_attr(ppr, "defTabSz", format.default_tab_size());
    append_bool_attr(ppr, "rtl", format.right_to_left());
    append_bool_attr(ppr, "eaLnBrk", format.east_asian_line_break());
    if (const char* fa = font_alignment_to_ooxml(format.font_alignment())) {
        ppr.append_attribute("fontAlgn") = fa;
    }
    append_bool_attr(ppr, "latinLnBrk", format.latin_line_break());
    append_bool_attr(ppr, "hangingPunct", format.hanging_punctuation());

    // -- Children, in CT_TextParagraphProperties sequence order -------------
    append_spacing(ppr, "a:lnSpc", format.space_within());
    append_spacing(ppr, "a:spcBef", format.space_before());
    append_spacing(ppr, "a:spcAft", format.space_after());

    Internal::pptx::write_bullet(ppr, format.bullet());
}



// ---------------------------------------------------------------------------
// Property accessors
//
// Each one is backed by the `<a:pPr>` element when this object is bound to
// one, and answers from its member when it is not. The two cases are the two
// serialisers: a deck opened from a file is edited in place through the XML,
// and a deck built in memory is written out by serialize_ppr() at save time.
//
// Writing is surgical — one attribute or one child per property — so a
// property the caller never mentions is left exactly as the file had it.
// ---------------------------------------------------------------------------

namespace {

/// The reverse of font_alignment_to_ooxml.
FontAlignment ooxml_to_font_alignment(std::string_view s) {
    if (s == "auto") return FontAlignment::AUTOMATIC;
    if (s == "t")    return FontAlignment::TOP;
    if (s == "ctr")  return FontAlignment::CENTER;
    if (s == "b")    return FontAlignment::BOTTOM;
    if (s == "base") return FontAlignment::BASELINE;
    return FontAlignment::DEFAULT;
}

} // namespace

int ParagraphFormat::depth() const {
    if (ppr_element_) {
        if (auto attr = ppr_element_.attribute("lvl")) return attr.as_int(0);
    }
    return depth_;
}

void ParagraphFormat::set_depth(int value) {
    depth_ = value;
    auto ppr = ensure_ppr();
    if (!ppr) return;
    // @lvl defaults to 0, so level zero is written by leaving it off.
    if (value == 0) {
        ppr.remove_attribute("lvl");
    } else {
        auto attr = ppr.attribute("lvl");
        if (!attr) attr = ppr.append_attribute("lvl");
        attr.set_value(value);
    }
    save();
}

double ParagraphFormat::space_within() const {
    return ppr_element_ ? get_spacing("a:lnSpc") : space_within_;
}

void ParagraphFormat::set_space_within(double value) {
    space_within_ = value;
    if (ensure_ppr()) set_spacing("a:lnSpc", value);
}

double ParagraphFormat::space_before() const {
    return ppr_element_ ? get_spacing("a:spcBef") : space_before_;
}

void ParagraphFormat::set_space_before(double value) {
    space_before_ = value;
    if (ensure_ppr()) set_spacing("a:spcBef", value);
}

double ParagraphFormat::space_after() const {
    return ppr_element_ ? get_spacing("a:spcAft") : space_after_;
}

void ParagraphFormat::set_space_after(double value) {
    space_after_ = value;
    if (ensure_ppr()) set_spacing("a:spcAft", value);
}

NullableBool ParagraphFormat::east_asian_line_break() const {
    return ppr_element_ ? get_nullable_bool_attr("eaLnBrk")
                        : east_asian_line_break_;
}

void ParagraphFormat::set_east_asian_line_break(NullableBool value) {
    east_asian_line_break_ = value;
    if (ensure_ppr()) set_nullable_bool_attr("eaLnBrk", value);
}

NullableBool ParagraphFormat::right_to_left() const {
    return ppr_element_ ? get_nullable_bool_attr("rtl") : right_to_left_;
}

void ParagraphFormat::set_right_to_left(NullableBool value) {
    right_to_left_ = value;
    if (ensure_ppr()) set_nullable_bool_attr("rtl", value);
}

NullableBool ParagraphFormat::latin_line_break() const {
    return ppr_element_ ? get_nullable_bool_attr("latinLnBrk")
                        : latin_line_break_;
}

void ParagraphFormat::set_latin_line_break(NullableBool value) {
    latin_line_break_ = value;
    if (ensure_ppr()) set_nullable_bool_attr("latinLnBrk", value);
}

NullableBool ParagraphFormat::hanging_punctuation() const {
    return ppr_element_ ? get_nullable_bool_attr("hangingPunct")
                        : hanging_punctuation_;
}

void ParagraphFormat::set_hanging_punctuation(NullableBool value) {
    hanging_punctuation_ = value;
    if (ensure_ppr()) set_nullable_bool_attr("hangingPunct", value);
}

double ParagraphFormat::margin_left() const {
    return ppr_element_ ? get_emu_attr("marL") : margin_left_;
}

void ParagraphFormat::set_margin_left(double value) {
    margin_left_ = value;
    if (ensure_ppr()) set_emu_attr("marL", value);
}

double ParagraphFormat::margin_right() const {
    return ppr_element_ ? get_emu_attr("marR") : margin_right_;
}

void ParagraphFormat::set_margin_right(double value) {
    margin_right_ = value;
    if (ensure_ppr()) set_emu_attr("marR", value);
}

double ParagraphFormat::indent() const {
    return ppr_element_ ? get_emu_attr("indent") : indent_;
}

void ParagraphFormat::set_indent(double value) {
    indent_ = value;
    if (ensure_ppr()) set_emu_attr("indent", value);
}

double ParagraphFormat::default_tab_size() const {
    return ppr_element_ ? get_emu_attr("defTabSz") : default_tab_size_;
}

void ParagraphFormat::set_default_tab_size(double value) {
    default_tab_size_ = value;
    if (ensure_ppr()) set_emu_attr("defTabSz", value);
}

FontAlignment ParagraphFormat::font_alignment() const {
    if (ppr_element_) {
        if (auto attr = ppr_element_.attribute("fontAlgn"))
            return ooxml_to_font_alignment(attr.as_string(""));
    }
    return font_alignment_;
}

void ParagraphFormat::set_font_alignment(FontAlignment value) {
    font_alignment_ = value;
    auto ppr = ensure_ppr();
    if (!ppr) return;
    if (const char* token = font_alignment_to_ooxml(value)) {
        auto attr = ppr.attribute("fontAlgn");
        if (!attr) attr = ppr.append_attribute("fontAlgn");
        attr.set_value(token);
    } else {
        ppr.remove_attribute("fontAlgn");
    }
    save();
}

} // namespace Aspose::Slides::Foss
