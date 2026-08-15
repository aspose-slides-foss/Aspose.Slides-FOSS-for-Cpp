// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/line_format.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/drawing/color.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::kEmuPerPoint;

// ---------------------------------------------------------------------------
// Tag constants (prefix notation for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kDefaultLnTag = "a:ln";

/// OOXML CT_TableCellProperties child order for border lines within <a:tcPr>.
static constexpr std::array kTcPrChildOrder = {
    std::string_view{"a:lnL"},
    std::string_view{"a:lnR"},
    std::string_view{"a:lnT"},
    std::string_view{"a:lnB"},
    std::string_view{"a:lnTlToBr"},
    std::string_view{"a:lnBlToTr"},
};

/// Tags that must appear after <a:ln> in OOXML spPr ordering.
static constexpr std::array kPostLnTags = {
    std::string_view{"a:effectLst"},
    std::string_view{"a:effectDag"},
    std::string_view{"a:scene3d"},
    std::string_view{"a:sp3d"},
    std::string_view{"a:extLst"},
};

/// OOXML CT_LineProperties child order within <a:ln>.
static constexpr std::array kLnChildOrder = {
    std::string_view{"a:noFill"},
    std::string_view{"a:solidFill"},
    std::string_view{"a:gradFill"},
    std::string_view{"a:pattFill"},
    std::string_view{"a:prstDash"},
    std::string_view{"a:custDash"},
    std::string_view{"a:round"},
    std::string_view{"a:bevel"},
    std::string_view{"a:miter"},
    std::string_view{"a:headEnd"},
    std::string_view{"a:tailEnd"},
    std::string_view{"a:extLst"},
};

/// Return the rank of a tag in an ordered array, or -1 if not found.
template <std::size_t N>
static int rank_of(std::string_view tag,
                   const std::array<std::string_view, N>& order) {
    auto it = std::ranges::find(order, tag);
    if (it == order.end()) return -1;
    return static_cast<int>(it - order.begin());
}

/// Check whether a tag is a tcPr border element.
static bool is_tc_pr_border(std::string_view tag) {
    return std::ranges::find(kTcPrChildOrder, tag) != kTcPrChildOrder.end();
}

/// Check whether a tag is a post-ln element.
static bool is_post_ln_tag(std::string_view tag) {
    return std::ranges::find(kPostLnTags, tag) != kPostLnTags.end();
}

// ---------------------------------------------------------------------------
// LineFormat – XML-backed internal methods
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Dash style OOXML name mappings
// ---------------------------------------------------------------------------

namespace {

const char* dash_style_to_ooxml(LineDashStyle style) {
    switch (style) {
        case LineDashStyle::SOLID:               return "solid";
        case LineDashStyle::DOT:                 return "dot";
        case LineDashStyle::DASH:                return "dash";
        case LineDashStyle::LARGE_DASH:          return "lgDash";
        case LineDashStyle::DASH_DOT:            return "dashDot";
        case LineDashStyle::LARGE_DASH_DOT:      return "lgDashDot";
        case LineDashStyle::LARGE_DASH_DOT_DOT:  return "lgDashDotDot";
        case LineDashStyle::SYSTEM_DASH:         return "sysDash";
        case LineDashStyle::SYSTEM_DOT:          return "sysDot";
        case LineDashStyle::SYSTEM_DASH_DOT:     return "sysDashDot";
        case LineDashStyle::SYSTEM_DASH_DOT_DOT: return "sysDashDotDot";
        default:                                 return nullptr;
    }
}

LineDashStyle ooxml_to_dash_style(std::string_view val) {
    static const std::unordered_map<std::string_view, LineDashStyle> map = {
        {"solid",         LineDashStyle::SOLID},
        {"dot",           LineDashStyle::DOT},
        {"dash",          LineDashStyle::DASH},
        {"lgDash",        LineDashStyle::LARGE_DASH},
        {"dashDot",       LineDashStyle::DASH_DOT},
        {"lgDashDot",     LineDashStyle::LARGE_DASH_DOT},
        {"lgDashDotDot",  LineDashStyle::LARGE_DASH_DOT_DOT},
        {"sysDash",       LineDashStyle::SYSTEM_DASH},
        {"sysDot",        LineDashStyle::SYSTEM_DOT},
        {"sysDashDot",    LineDashStyle::SYSTEM_DASH_DOT},
        {"sysDashDotDot", LineDashStyle::SYSTEM_DASH_DOT_DOT},
    };
    auto it = map.find(val);
    return it != map.end() ? it->second : LineDashStyle::NOT_DEFINED;
}

/// ST_LineCap token, or nullptr when nothing is to be written.
const char* cap_style_to_ooxml(LineCapStyle style) {
    switch (style) {
        case LineCapStyle::ROUND:       return "rnd";
        case LineCapStyle::SQUARE:      return "sq";
        case LineCapStyle::FLAT:        return "flat";
        case LineCapStyle::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// ST_CompoundLine token, or nullptr when nothing is to be written.
///
/// LineStyle names the visual arrangement of the strokes; the schema names the
/// count for the symmetric cases, so THIN_THIN is "dbl" and
/// THICK_BETWEEN_THIN is "tri".
const char* line_style_to_ooxml(LineStyle style) {
    switch (style) {
        case LineStyle::SINGLE:             return "sng";
        case LineStyle::THIN_THIN:          return "dbl";
        case LineStyle::THICK_THIN:         return "thickThin";
        case LineStyle::THIN_THICK:         return "thinThick";
        case LineStyle::THICK_BETWEEN_THIN: return "tri";
        case LineStyle::NOT_DEFINED:        return nullptr;
    }
    return nullptr;
}

/// ST_PenAlignment token, or nullptr when nothing is to be written.
const char* alignment_to_ooxml(LineAlignment alignment) {
    switch (alignment) {
        case LineAlignment::CENTER:      return "ctr";
        case LineAlignment::INSET:       return "in";
        case LineAlignment::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// The join is a child element, not an attribute.
const char* join_style_to_element(LineJoinStyle style) {
    switch (style) {
        case LineJoinStyle::ROUND:       return "a:round";
        case LineJoinStyle::BEVEL:       return "a:bevel";
        case LineJoinStyle::MITER:       return "a:miter";
        case LineJoinStyle::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// ST_LineEndType token, or nullptr when nothing is to be written.
///
/// OPEN has no same-named token: the open arrowhead in ST_LineEndType is
/// "arrow".
const char* arrowhead_style_to_ooxml(LineArrowheadStyle style) {
    switch (style) {
        case LineArrowheadStyle::NONE:        return "none";
        case LineArrowheadStyle::TRIANGLE:    return "triangle";
        case LineArrowheadStyle::STEALTH:     return "stealth";
        case LineArrowheadStyle::DIAMOND:     return "diamond";
        case LineArrowheadStyle::OVAL:        return "oval";
        case LineArrowheadStyle::OPEN:        return "arrow";
        case LineArrowheadStyle::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// ST_LineEndWidth token, or nullptr when nothing is to be written.
const char* arrowhead_width_to_ooxml(LineArrowheadWidth width) {
    switch (width) {
        case LineArrowheadWidth::NARROW:      return "sm";
        case LineArrowheadWidth::MEDIUM:      return "med";
        case LineArrowheadWidth::WIDE:        return "lg";
        case LineArrowheadWidth::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// ST_LineEndLength token, or nullptr when nothing is to be written.
const char* arrowhead_length_to_ooxml(LineArrowheadLength length) {
    switch (length) {
        case LineArrowheadLength::SHORT:       return "sm";
        case LineArrowheadLength::MEDIUM:      return "med";
        case LineArrowheadLength::LONG:        return "lg";
        case LineArrowheadLength::NOT_DEFINED: return nullptr;
    }
    return nullptr;
}

/// Set an attribute, adding it when absent; remove it when @p value is null.
void set_or_remove_attribute(pugi::xml_node node, const char* name,
                             const char* value) {
    if (!value) {
        node.remove_attribute(name);
        return;
    }
    auto attr = node.attribute(name);
    if (!attr) attr = node.append_attribute(name);
    attr.set_value(value);
}

void remove_children(pugi::xml_node node,
                     std::initializer_list<const char*> tags) {
    for (const char* tag : tags) {
        while (auto child = node.child(tag)) node.remove_child(child);
    }
}

/// Convert a Color to a 6-character hex string (RRGGBB).
std::string color_to_hex(const Drawing::Color& c) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0')
        << std::setw(2) << static_cast<int>(c.r())
        << std::setw(2) << static_cast<int>(c.g())
        << std::setw(2) << static_cast<int>(c.b());
    return oss.str();
}

/// Parse a 6-character hex color string to a Color.
Drawing::Color hex_to_color(std::string_view hex) {
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

/// Read a color from the first srgbClr child of the given element.
Drawing::Color read_color_element(pugi::xml_node parent) {
    auto srgb = parent.child("a:srgbClr");
    if (srgb) {
        return hex_to_color(srgb.attribute("val").as_string(""));
    }
    return {};
}

/// Write a color child element (a:srgbClr with optional a:alpha) under parent.
void write_color_element(pugi::xml_node parent, const Drawing::Color& clr) {
    auto srgb = parent.append_child("a:srgbClr");
    srgb.append_attribute("val") = color_to_hex(clr).c_str();
    if (clr.a() < 255) {
        auto alpha_node = srgb.append_child("a:alpha");
        auto alpha_pct = static_cast<int>(std::round(
            static_cast<double>(clr.a()) / 255.0 * 100000.0));
        alpha_node.append_attribute("val") = std::to_string(alpha_pct).c_str();
    }
}

} // anonymous namespace

void LineFormat::init_internal(pugi::xml_node parent_element,
                               std::function<void()> save_callback,
                               std::string_view ln_tag) {
    parent_element_ = parent_element;
    save_callback_ = std::move(save_callback);
    ln_tag_ = ln_tag.empty() ? std::string(kDefaultLnTag) : std::string(ln_tag);

    // Parse existing <a:ln> element if present.
    auto ln = get_ln();
    if (!ln) return;

    // Width: stored in EMU as the "w" attribute.
    auto w_attr = ln.attribute("w");
    if (w_attr) {
        width_ = w_attr.as_int(0) / static_cast<double>(kEmuPerPoint);
    }

    // Dash style: from <a:prstDash val="..."/> child.
    auto prst_dash = ln.child("a:prstDash");
    if (prst_dash) {
        auto val = prst_dash.attribute("val");
        if (val) {
            dash_style_ = ooxml_to_dash_style(val.as_string(""));
        }
    }

    // Fill: <a:solidFill>, <a:noFill>, etc.
    auto solid_fill = ln.child("a:solidFill");
    if (solid_fill) {
        fill_format_.set_fill_type(FillType::SOLID);
        fill_format_.solid_fill_color().set_color(read_color_element(solid_fill));
    } else if (ln.child("a:noFill")) {
        fill_format_.set_fill_type(FillType::NO_FILL);
    }
}

pugi::xml_node LineFormat::get_ln() const {
    return parent_element_.child(ln_tag_.empty() ? kDefaultLnTag.data()
                                                 : ln_tag_.c_str());
}

pugi::xml_node LineFormat::ensure_ln() {
    auto ln = get_ln();
    if (ln) return ln;

    const std::string& tag = ln_tag_.empty() ? (ln_tag_ = std::string(kDefaultLnTag))
                                             : ln_tag_;

    // For table cell border elements, use the tcPr child ordering.
    if (is_tc_pr_border(tag)) {
        int new_rank = rank_of(tag, kTcPrChildOrder);
        for (auto child : parent_element_.children()) {
            int child_rank = rank_of(child.name(), kTcPrChildOrder);
            if (child_rank < 0) {
                // Non-border child (fill, cell3D, extLst) comes after all borders.
                return parent_element_.insert_child_before(tag.c_str(), child);
            }
            if (child_rank > new_rank) {
                return parent_element_.insert_child_before(tag.c_str(), child);
            }
        }
        return parent_element_.append_child(tag.c_str());
    }

    // Default: insert before effect/3D/extension elements.
    for (auto child : parent_element_.children()) {
        if (is_post_ln_tag(child.name())) {
            return parent_element_.insert_child_before(tag.c_str(), child);
        }
    }
    return parent_element_.append_child(tag.c_str());
}

pugi::xml_node LineFormat::insert_ln_child(pugi::xml_node ln,
                                           std::string_view tag) const {
    std::string tag_str{tag};
    int new_rank = rank_of(tag, kLnChildOrder);

    if (new_rank < 0) {
        // Unknown tag — append at end.
        return ln.append_child(tag_str.c_str());
    }

    for (auto child : ln.children()) {
        int child_rank = rank_of(child.name(), kLnChildOrder);
        if (child_rank < 0) continue;
        if (child_rank > new_rank) {
            return ln.insert_child_before(tag_str.c_str(), child);
        }
    }
    return ln.append_child(tag_str.c_str());
}

void LineFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

std::optional<std::string> LineFormat::get_arrow_attr(
    std::string_view end_tag, std::string_view attr) const {
    auto ln = get_ln();
    if (!ln) return std::nullopt;

    auto end_elem = ln.child(std::string(end_tag).c_str());
    if (!end_elem) return std::nullopt;

    auto attr_val = end_elem.attribute(std::string(attr).c_str());
    if (!attr_val) return std::nullopt;

    return std::string(attr_val.value());
}

void LineFormat::set_arrow_attr(std::string_view end_tag, std::string_view attr,
                                const std::optional<std::string>& value) {
    auto ln = ensure_ln();

    std::string end_tag_str{end_tag};
    auto end_elem = ln.child(end_tag_str.c_str());
    if (!end_elem) {
        end_elem = insert_ln_child(ln, end_tag);
    }

    std::string attr_str{attr};
    if (!value.has_value()) {
        end_elem.remove_attribute(attr_str.c_str());
    } else {
        auto existing = end_elem.attribute(attr_str.c_str());
        if (existing) {
            existing.set_value(value->c_str());
        } else {
            end_elem.append_attribute(attr_str.c_str()) = value->c_str();
        }
    }

    save();
}

// ---------------------------------------------------------------------------
// apply_to_ln — write the whole in-memory model onto an <a:ln>
// ---------------------------------------------------------------------------

void LineFormat::apply_to_ln(pugi::xml_node ln) const {
    // -- Attributes ---------------------------------------------------------
    if (width_ > 0.0) {
        auto w = std::to_string(static_cast<int>(std::round(width_ * kEmuPerPoint)));
        set_or_remove_attribute(ln, "w", w.c_str());
    } else {
        ln.remove_attribute("w");
    }
    set_or_remove_attribute(ln, "cap", cap_style_to_ooxml(cap_style_));
    set_or_remove_attribute(ln, "cmpd", line_style_to_ooxml(style_));
    set_or_remove_attribute(ln, "algn", alignment_to_ooxml(alignment_));

    // -- Children, in CT_LineProperties sequence order ----------------------
    // A fill type this class does not model is left in place rather than
    // replaced with nothing, so opening a deck with a gradient outline and
    // setting an unrelated property does not discard the gradient.
    if (fill_format_.fill_type() != FillType::NOT_DEFINED) {
        remove_children(ln, {"a:noFill", "a:solidFill", "a:gradFill", "a:pattFill"});
        if (fill_format_.fill_type() == FillType::SOLID) {
            write_color_element(insert_ln_child(ln, "a:solidFill"),
                                fill_format_.solid_fill_color().color());
        } else if (fill_format_.fill_type() == FillType::NO_FILL) {
            insert_ln_child(ln, "a:noFill");
        }
    }

    // a:prstDash and a:custDash are a choice; a named style wins over a
    // pattern when both were set.
    remove_children(ln, {"a:prstDash", "a:custDash"});
    if (const char* dash = dash_style_to_ooxml(dash_style_)) {
        insert_ln_child(ln, "a:prstDash").append_attribute("val") = dash;
    } else if (!custom_dash_pattern_.empty()) {
        auto cust = insert_ln_child(ln, "a:custDash");
        // The pattern alternates dash length and space length, both as
        // multiples of the line width; ST_PositivePercentage is per
        // hundred-thousand, so 1.0x becomes 100000. A trailing dash with no
        // space gets a zero-length space, since a:ds requires both.
        for (std::size_t i = 0; i < custom_dash_pattern_.size(); i += 2) {
            auto ds = cust.append_child("a:ds");
            ds.append_attribute("d") = static_cast<long long>(
                std::llround(custom_dash_pattern_[i] * 100000.0f));
            float space = (i + 1 < custom_dash_pattern_.size())
                              ? custom_dash_pattern_[i + 1]
                              : 0.0f;
            ds.append_attribute("sp") =
                static_cast<long long>(std::llround(space * 100000.0f));
        }
    }

    remove_children(ln, {"a:round", "a:bevel", "a:miter"});
    if (const char* join = join_style_to_element(join_style_)) {
        auto node = insert_ln_child(ln, join);
        if (join_style_ == LineJoinStyle::MITER && miter_limit_ > 0.0) {
            node.append_attribute("lim") =
                static_cast<long long>(std::llround(miter_limit_ * 1000.0));
        }
    }

    struct End {
        const char* tag;
        LineArrowheadStyle style;
        LineArrowheadWidth width;
        LineArrowheadLength length;
    };
    for (const End& end :
         {End{"a:headEnd", begin_arrow_style_, begin_arrow_width_, begin_arrow_length_},
          End{"a:tailEnd", end_arrow_style_, end_arrow_width_, end_arrow_length_}}) {
        remove_children(ln, {end.tag});
        const char* type = arrowhead_style_to_ooxml(end.style);
        const char* w = arrowhead_width_to_ooxml(end.width);
        const char* len = arrowhead_length_to_ooxml(end.length);
        if (!type && !w && !len) continue;
        auto node = insert_ln_child(ln, end.tag);
        if (type) node.append_attribute("type") = type;
        if (w) node.append_attribute("w") = w;
        if (len) node.append_attribute("len") = len;
    }
}

// ---------------------------------------------------------------------------
// serialize_to_xml — write in-memory line format to an XML spPr node
// ---------------------------------------------------------------------------

void LineFormat::serialize_to_xml(pugi::xml_node sp_pr) const {
    // Only serialize if there's something meaningful to write.
    if (is_format_not_defined() &&
        fill_format_.fill_type() == FillType::NOT_DEFINED) {
        return;
    }
    apply_to_ln(sp_pr.append_child("a:ln"));
}

// ---------------------------------------------------------------------------
// Property setters
//
// The model is the source of truth for every property; a setter updates it and
// then rewrites the backing <a:ln> in one pass. Doing it property by property
// would need one surgical edit per attribute and per child, and the child
// elements have to stay in schema order anyway.
// ---------------------------------------------------------------------------

void LineFormat::persist() {
    if (!parent_element_) return;
    apply_to_ln(ensure_ln());
    save();
}

void LineFormat::set_width(double value) noexcept { width_ = value; persist(); }

void LineFormat::set_dash_style(LineDashStyle value) noexcept {
    dash_style_ = value;
    persist();
}

void LineFormat::set_custom_dash_pattern(std::vector<float> value) {
    custom_dash_pattern_ = std::move(value);
    persist();
}

void LineFormat::set_cap_style(LineCapStyle value) noexcept {
    cap_style_ = value;
    persist();
}

void LineFormat::set_style(LineStyle value) noexcept {
    style_ = value;
    persist();
}

void LineFormat::set_alignment(LineAlignment value) noexcept {
    alignment_ = value;
    persist();
}

void LineFormat::set_join_style(LineJoinStyle value) noexcept {
    join_style_ = value;
    persist();
}

void LineFormat::set_miter_limit(double value) noexcept {
    miter_limit_ = value;
    persist();
}

void LineFormat::set_begin_arrowhead_style(LineArrowheadStyle value) noexcept {
    begin_arrow_style_ = value;
    persist();
}

void LineFormat::set_begin_arrowhead_width(LineArrowheadWidth value) noexcept {
    begin_arrow_width_ = value;
    persist();
}

void LineFormat::set_begin_arrowhead_length(LineArrowheadLength value) noexcept {
    begin_arrow_length_ = value;
    persist();
}

void LineFormat::set_end_arrowhead_style(LineArrowheadStyle value) noexcept {
    end_arrow_style_ = value;
    persist();
}

void LineFormat::set_end_arrowhead_width(LineArrowheadWidth value) noexcept {
    end_arrow_width_ = value;
    persist();
}

void LineFormat::set_end_arrowhead_length(LineArrowheadLength value) noexcept {
    end_arrow_length_ = value;
    persist();
}

} // namespace Aspose::Slides::Foss
