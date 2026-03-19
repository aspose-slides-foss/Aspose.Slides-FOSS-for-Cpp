// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/portion_format.h>

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Aspose/Slides/Foss/drawing/color.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// OOXML underline type mappings
// ---------------------------------------------------------------------------

static const char* underline_to_ooxml(TextUnderlineType t) {
    switch (t) {
        case TextUnderlineType::NONE:             return "none";
        case TextUnderlineType::WORDS:            return "words";
        case TextUnderlineType::SINGLE:           return "sng";
        case TextUnderlineType::DOUBLE:           return "dbl";
        case TextUnderlineType::HEAVY:            return "heavy";
        case TextUnderlineType::DOTTED:           return "dotted";
        case TextUnderlineType::HEAVY_DOTTED:     return "dottedHeavy";
        case TextUnderlineType::DASHED:           return "dash";
        case TextUnderlineType::HEAVY_DASHED:     return "dashHeavy";
        case TextUnderlineType::LONG_DASHED:      return "dashLong";
        case TextUnderlineType::HEAVY_LONG_DASHED:return "dashLongHeavy";
        case TextUnderlineType::DOT_DASH:         return "dotDash";
        case TextUnderlineType::HEAVY_DOT_DASH:   return "dotDashHeavy";
        case TextUnderlineType::DOT_DOT_DASH:     return "dotDotDash";
        case TextUnderlineType::HEAVY_DOT_DOT_DASH: return "dotDotDashHeavy";
        case TextUnderlineType::WAVY:             return "wavy";
        case TextUnderlineType::HEAVY_WAVY:       return "wavyHeavy";
        case TextUnderlineType::DOUBLE_WAVY:      return "wavyDbl";
        default: return nullptr;
    }
}

static TextUnderlineType ooxml_to_underline(std::string_view s) {
    static const std::unordered_map<std::string_view, TextUnderlineType> m = {
        {"none",           TextUnderlineType::NONE},
        {"words",          TextUnderlineType::WORDS},
        {"sng",            TextUnderlineType::SINGLE},
        {"dbl",            TextUnderlineType::DOUBLE},
        {"heavy",          TextUnderlineType::HEAVY},
        {"dotted",         TextUnderlineType::DOTTED},
        {"dottedHeavy",    TextUnderlineType::HEAVY_DOTTED},
        {"dash",           TextUnderlineType::DASHED},
        {"dashHeavy",      TextUnderlineType::HEAVY_DASHED},
        {"dashLong",       TextUnderlineType::LONG_DASHED},
        {"dashLongHeavy",  TextUnderlineType::HEAVY_LONG_DASHED},
        {"dotDash",        TextUnderlineType::DOT_DASH},
        {"dotDashHeavy",   TextUnderlineType::HEAVY_DOT_DASH},
        {"dotDotDash",     TextUnderlineType::DOT_DOT_DASH},
        {"dotDotDashHeavy",TextUnderlineType::HEAVY_DOT_DOT_DASH},
        {"wavy",           TextUnderlineType::WAVY},
        {"wavyHeavy",      TextUnderlineType::HEAVY_WAVY},
        {"wavyDbl",        TextUnderlineType::DOUBLE_WAVY},
    };
    auto it = m.find(s);
    return it != m.end() ? it->second : TextUnderlineType::NOT_DEFINED;
}

// ---------------------------------------------------------------------------
// OOXML strikethrough type mappings
// ---------------------------------------------------------------------------

static const char* strike_to_ooxml(TextStrikethroughType t) {
    switch (t) {
        case TextStrikethroughType::NONE:   return "noStrike";
        case TextStrikethroughType::SINGLE: return "sngStrike";
        case TextStrikethroughType::DOUBLE: return "dblStrike";
        default: return nullptr;
    }
}

static TextStrikethroughType ooxml_to_strike(std::string_view s) {
    if (s == "noStrike")  return TextStrikethroughType::NONE;
    if (s == "sngStrike") return TextStrikethroughType::SINGLE;
    if (s == "dblStrike") return TextStrikethroughType::DOUBLE;
    return TextStrikethroughType::NOT_DEFINED;
}

// ---------------------------------------------------------------------------
// NullableBool attribute helpers
// ---------------------------------------------------------------------------

static NullableBool read_bool_attr(pugi::xml_node node, const char* attr) {
    auto a = node.attribute(attr);
    if (!a) return NullableBool::NOT_DEFINED;
    return (std::string_view{a.value()} == "1") ? NullableBool::TRUE
                                                 : NullableBool::FALSE;
}

static void write_bool_attr(pugi::xml_node node, const char* attr, NullableBool v) {
    if (v == NullableBool::NOT_DEFINED) {
        node.remove_attribute(attr);
    } else {
        auto a = node.attribute(attr);
        if (!a) a = node.append_attribute(attr);
        a.set_value((v == NullableBool::TRUE) ? "1" : "0");
    }
}

// ---------------------------------------------------------------------------
// Color helpers
// ---------------------------------------------------------------------------

static std::string color_to_hex(const Drawing::Color& c) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0')
        << std::setw(2) << static_cast<int>(c.r())
        << std::setw(2) << static_cast<int>(c.g())
        << std::setw(2) << static_cast<int>(c.b());
    return oss.str();
}

static Drawing::Color hex_to_color(std::string_view hex) {
    if (hex.size() < 6) return {};
    auto parse = [](char hi, char lo) -> uint8_t {
        auto digit = [](char c) -> int {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            return 0;
        };
        return static_cast<uint8_t>(digit(hi) * 16 + digit(lo));
    };
    return Drawing::Color::from_argb(
        255, parse(hex[0], hex[1]), parse(hex[2], hex[3]), parse(hex[4], hex[5]));
}

// ---------------------------------------------------------------------------
// PortionFormat implementation
// ---------------------------------------------------------------------------

void PortionFormat::init_from_rpr(pugi::xml_node r_element,
                                   std::function<void()> save_callback) {
    r_element_ = r_element;
    save_callback_ = save_callback;
    read_from_xml();

    // Initialize the FillFormat with the <a:rPr> element as parent,
    // so fill changes write directly to XML.
    auto rpr = r_element_.child("a:rPr");
    if (rpr) {
        fill_format().init_internal(rpr, save_callback);
    }
}

void PortionFormat::on_property_changed() {
    if (suppress_change_) return;
    if (!r_element_) return;
    flush_to_xml();
    if (save_callback_) save_callback_();
}

pugi::xml_node PortionFormat::ensure_rpr() {
    auto rpr = r_element_.child("a:rPr");
    if (!rpr) {
        // Insert rPr as first child of <a:r> (before <a:t>).
        auto first = r_element_.first_child();
        if (first) {
            rpr = r_element_.insert_child_before("a:rPr", first);
        } else {
            rpr = r_element_.append_child("a:rPr");
        }
    }
    return rpr;
}

void PortionFormat::read_from_xml() {
    if (!r_element_) return;
    auto rpr = r_element_.child("a:rPr");
    if (!rpr) return;

    suppress_change_ = true;

    // Boolean attributes.
    set_font_bold(read_bool_attr(rpr, "b"));
    set_font_italic(read_bool_attr(rpr, "i"));

    // Underline.
    auto u_attr = rpr.attribute("u");
    if (u_attr) {
        set_font_underline(ooxml_to_underline(u_attr.value()));
    }

    // Strikethrough.
    auto strike_attr = rpr.attribute("strike");
    if (strike_attr) {
        set_strikethrough_type(ooxml_to_strike(strike_attr.value()));
    }

    // Font size (stored in hundredths of a point, e.g., 2800 = 28pt).
    auto sz_attr = rpr.attribute("sz");
    if (sz_attr) {
        set_font_height(sz_attr.as_int() / 100.0);
    }

    // Latin font.
    auto latin = rpr.child("a:latin");
    if (latin) {
        auto typeface = latin.attribute("typeface");
        if (typeface) {
            set_latin_font(FontData(typeface.value()));
        }
    }

    // East Asian font.
    auto ea = rpr.child("a:ea");
    if (ea) {
        auto typeface = ea.attribute("typeface");
        if (typeface) {
            set_east_asian_font(FontData(typeface.value()));
        }
    }

    // Complex script font.
    auto cs = rpr.child("a:cs");
    if (cs) {
        auto typeface = cs.attribute("typeface");
        if (typeface) {
            set_complex_script_font(FontData(typeface.value()));
        }
    }

    // Fill format — read solid fill color.
    auto solid_fill = rpr.child("a:solidFill");
    if (solid_fill) {
        fill_format().set_fill_type(FillType::SOLID);
        auto srgb = solid_fill.child("a:srgbClr");
        if (srgb) {
            auto c = hex_to_color(srgb.attribute("val").as_string(""));
            fill_format().solid_fill_color().set_color(c);
        }
    }

    suppress_change_ = false;
}

void PortionFormat::flush_to_xml() {
    if (!r_element_) return;
    auto rpr = ensure_rpr();

    // Boolean attributes.
    write_bool_attr(rpr, "b", font_bold());
    write_bool_attr(rpr, "i", font_italic());

    // Underline.
    if (font_underline() != TextUnderlineType::NOT_DEFINED) {
        auto val = underline_to_ooxml(font_underline());
        if (val) {
            auto a = rpr.attribute("u");
            if (!a) a = rpr.append_attribute("u");
            a.set_value(val);
        }
    } else {
        rpr.remove_attribute("u");
    }

    // Strikethrough.
    if (strikethrough_type() != TextStrikethroughType::NOT_DEFINED) {
        auto val = strike_to_ooxml(strikethrough_type());
        if (val) {
            auto a = rpr.attribute("strike");
            if (!a) a = rpr.append_attribute("strike");
            a.set_value(val);
        }
    } else {
        rpr.remove_attribute("strike");
    }

    // Font size (hundredths of a point).
    if (!std::isnan(font_height())) {
        auto a = rpr.attribute("sz");
        if (!a) a = rpr.append_attribute("sz");
        a.set_value(std::to_string(static_cast<int>(std::round(font_height() * 100))).c_str());
    } else {
        rpr.remove_attribute("sz");
    }

    // Latin font.
    rpr.remove_child("a:latin");
    if (latin_font().has_value()) {
        auto node = rpr.append_child("a:latin");
        node.append_attribute("typeface") = latin_font()->font_name().c_str();
    }

    // East Asian font.
    rpr.remove_child("a:ea");
    if (east_asian_font().has_value()) {
        auto node = rpr.append_child("a:ea");
        node.append_attribute("typeface") = east_asian_font()->font_name().c_str();
    }

    // Complex script font.
    rpr.remove_child("a:cs");
    if (complex_script_font().has_value()) {
        auto node = rpr.append_child("a:cs");
        node.append_attribute("typeface") = complex_script_font()->font_name().c_str();
    }

    // Fill format — write solid fill.
    rpr.remove_child("a:solidFill");
    rpr.remove_child("a:noFill");
    if (fill_format().fill_type() == FillType::SOLID) {
        auto sf = rpr.append_child("a:solidFill");
        auto clr = fill_format().solid_fill_color().color();
        auto srgb = sf.append_child("a:srgbClr");
        srgb.append_attribute("val") = color_to_hex(clr).c_str();
    } else if (fill_format().fill_type() == FillType::NO_FILL) {
        rpr.append_child("a:noFill");
    }
}

} // namespace Aspose::Slides::Foss
