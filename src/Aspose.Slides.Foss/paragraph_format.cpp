// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/paragraph_format.h>

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

} // namespace Aspose::Slides::Foss
