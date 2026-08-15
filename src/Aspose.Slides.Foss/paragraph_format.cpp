// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/paragraph_format.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/i_color_format.h>

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

pugi::xml_node ppr_insert_child(pugi::xml_node ppr, std::string_view tag) {
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
    if (ppr_element_) {
        if (value == TextAlignment::NOT_DEFINED) {
            ppr_element_.remove_attribute("algn");
        } else {
            auto a = ppr_element_.attribute("algn");
            if (!a) a = ppr_element_.append_attribute("algn");
            a.set_value(alignment_to_ooxml(value));
        }
        save();
    }
}

void ParagraphFormat::init_internal(pugi::xml_node ppr_element,
                                    std::function<void()> save_callback) {
    ppr_element_ = ppr_element;
    save_callback_ = std::move(save_callback);
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
            el = ppr_insert_child(ppr_element_, tag);
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

/// ST_TextAutonumberScheme token. These are not the display names
/// to_string_view() returns; an invented token makes PowerPoint refuse
/// the file.
const char* numbered_bullet_style_to_ooxml(NumberedBulletStyle value) {
    switch (value) {
        case NumberedBulletStyle::BULLET_ALPHA_LC_PERIOD:         return "alphaLcPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PERIOD:         return "alphaUcPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_RIGHT:      return "arabicParenR";
        case NumberedBulletStyle::BULLET_ARABIC_PERIOD:           return "arabicPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_BOTH:     return "romanLcParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PAREN_RIGHT:    return "romanLcParenR";
        case NumberedBulletStyle::BULLET_ROMAN_LC_PERIOD:         return "romanLcPeriod";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PERIOD:         return "romanUcPeriod";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_BOTH:     return "alphaLcParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_LC_PAREN_RIGHT:    return "alphaLcParenR";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_BOTH:     return "alphaUcParenBoth";
        case NumberedBulletStyle::BULLET_ALPHA_UC_PAREN_RIGHT:    return "alphaUcParenR";
        case NumberedBulletStyle::BULLET_ARABIC_PAREN_BOTH:       return "arabicParenBoth";
        case NumberedBulletStyle::BULLET_ARABIC_PLAIN:            return "arabicPlain";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_BOTH:     return "romanUcParenBoth";
        case NumberedBulletStyle::BULLET_ROMAN_UC_PAREN_RIGHT:    return "romanUcParenR";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PLAIN:         return "ea1ChsPlain";
        case NumberedBulletStyle::BULLET_SIMP_CHIN_PERIOD:        return "ea1ChsPeriod";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_DB_PLAIN:     return "circleNumDbPlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_WHITE_PLAIN: return "circleNumWdWhitePlain";
        case NumberedBulletStyle::BULLET_CIRCLE_NUM_WD_BLACK_PLAIN: return "circleNumWdBlackPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PLAIN:         return "ea1ChtPlain";
        case NumberedBulletStyle::BULLET_TRAD_CHIN_PERIOD:        return "ea1ChtPeriod";
        // ST_TextAutonumberScheme spells the three dash schemes with a
        // "Minus" suffix, not with the language name they carry here.
        case NumberedBulletStyle::BULLET_ARABIC_ALPHA_DASH:       return "arabic1Minus";
        case NumberedBulletStyle::BULLET_ARABIC_ABJAD_DASH:       return "arabic2Minus";
        case NumberedBulletStyle::BULLET_HEBREW_ALPHA_DASH:       return "hebrew2Minus";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PLAIN:      return "ea1JpnKorPlain";
        case NumberedBulletStyle::BULLET_KANJI_KOREAN_PERIOD:     return "ea1JpnKorPeriod";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PLAIN:         return "arabicDbPlain";
        case NumberedBulletStyle::BULLET_ARABIC_DB_PERIOD:        return "arabicDbPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PERIOD:       return "thaiAlphaPeriod";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_RIGHT:  return "thaiAlphaParenR";
        case NumberedBulletStyle::BULLET_THAI_ALPHA_PAREN_BOTH:   return "thaiAlphaParenBoth";
        case NumberedBulletStyle::BULLET_THAI_NUM_PERIOD:         return "thaiNumPeriod";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_RIGHT:    return "thaiNumParenR";
        case NumberedBulletStyle::BULLET_THAI_NUM_PAREN_BOTH:     return "thaiNumParenBoth";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA_PERIOD:      return "hindiAlphaPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PERIOD:        return "hindiNumPeriod";
        case NumberedBulletStyle::BULLET_KANJI_SIMP_CHIN_DB_PERIOD: return "ea1JpnChsDbPeriod";
        case NumberedBulletStyle::BULLET_HINDI_NUM_PAREN_RIGHT:   return "hindiNumParenR";
        case NumberedBulletStyle::BULLET_HINDI_ALPHA1_PERIOD:     return "hindiAlpha1Period";
        case NumberedBulletStyle::NOT_DEFINED:                    return nullptr;
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
    auto el = ppr_insert_child(ppr, tag);
    if (value >= 0) {
        el.append_child("a:spcPct").append_attribute("val") =
            static_cast<int>(std::round(value * 1000));
    } else {
        el.append_child("a:spcPts").append_attribute("val") =
            static_cast<int>(std::round(-value * 100));
    }
}

void append_srgb_color(pugi::xml_node parent, const IColorFormat& cf) {
    auto c = cf.color();
    char hex[7];
    std::snprintf(hex, sizeof(hex), "%02X%02X%02X", static_cast<int>(c.r()),
                  static_cast<int>(c.g()), static_cast<int>(c.b()));
    parent.append_child("a:srgbClr").append_attribute("val") = hex;
}

} // namespace

bool ppr_has_content(const IParagraphFormat& format) {
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

void serialize_ppr(pugi::xml_node ppr, const IParagraphFormat& format) {
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

    const auto& bullet = format.bullet();
    if (bullet.type() == BulletType::NOT_DEFINED) return;

    if (bullet.is_bullet_hard_color() == NullableBool::TRUE) {
        append_srgb_color(ppr_insert_child(ppr, "a:buClr"), bullet.color());
    }
    if (!std::isnan(bullet.height())) {
        ppr_insert_child(ppr, "a:buSzPct").append_attribute("val") =
            static_cast<int>(std::round(bullet.height() * 1000.0f));
    }
    if (!bullet.font_name().empty()) {
        ppr_insert_child(ppr, "a:buFont").append_attribute("typeface") =
            bullet.font_name().c_str();
    }

    switch (bullet.type()) {
        case BulletType::NONE:
            ppr_insert_child(ppr, "a:buNone");
            break;
        case BulletType::SYMBOL: {
            // @char is required by CT_TextCharBullet. A symbol bullet with no
            // character set falls back to the same glyph PowerPoint uses.
            auto node = ppr_insert_child(ppr, "a:buChar");
            node.append_attribute("char") =
                bullet.get_char().empty() ? "\xE2\x80\xA2"
                                          : bullet.get_char().c_str();
            break;
        }
        case BulletType::NUMBERED: {
            auto node = ppr_insert_child(ppr, "a:buAutoNum");
            // @type is required by CT_TextAutonumberBullet.
            const char* scheme =
                numbered_bullet_style_to_ooxml(bullet.numbered_bullet_style());
            node.append_attribute("type") = scheme ? scheme : "arabicPeriod";
            if (bullet.numbered_bullet_start_with() != 1) {
                node.append_attribute("startAt") =
                    bullet.numbered_bullet_start_with();
            }
            break;
        }
        case BulletType::PICTURE:
            // a:buBlip needs an r:embed to an image part, which this
            // serialiser has no relationship table to allocate one in. Writing
            // a:buBlip with no a:blip would produce a package that does not
            // validate, so the bullet is left to be inherited instead.
            break;
        case BulletType::NOT_DEFINED:
            break;
    }
}

} // namespace Aspose::Slides::Foss
