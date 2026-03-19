// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/fill_format.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/pattern_style.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// Fill tag constants (prefix notation for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::array kFillTags = {
    std::string_view{"a:noFill"},
    std::string_view{"a:solidFill"},
    std::string_view{"a:gradFill"},
    std::string_view{"a:pattFill"},
    std::string_view{"a:blipFill"},
    std::string_view{"a:grpFill"},
};

/// Tags that must appear after fill elements in OOXML spPr ordering.
static constexpr std::array kPostFillTags = {
    std::string_view{"a:ln"},
    std::string_view{"a:effectLst"},
    std::string_view{"a:effectDag"},
    std::string_view{"a:scene3d"},
    std::string_view{"a:sp3d"},
    std::string_view{"a:extLst"},
};

static constexpr std::string_view kGradFill = "a:gradFill";
static constexpr std::string_view kBlipFill = "a:blipFill";
static constexpr std::string_view kLin      = "a:lin";
static constexpr std::string_view kBlip     = "a:blip";
static constexpr std::string_view kStretch  = "a:stretch";
static constexpr std::string_view kFillRect = "a:fillRect";

/// Check whether a tag is a fill element.
static bool is_fill_tag(std::string_view tag) {
    return std::ranges::find(kFillTags, tag) != kFillTags.end();
}

/// Check whether a tag is a post-fill element.
static bool is_post_fill_tag(std::string_view tag) {
    return std::ranges::find(kPostFillTags, tag) != kPostFillTags.end();
}

// ---------------------------------------------------------------------------
// Color helpers
// ---------------------------------------------------------------------------

namespace {

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

/// Write a color child element (a:srgbClr with optional a:alpha) under parent.
void write_color_element(pugi::xml_node parent, const SimpleColorFormat& cf) {
    auto clr = cf.color();
    auto srgb = parent.append_child("a:srgbClr");
    srgb.append_attribute("val") = color_to_hex(clr).c_str();
    if (clr.a() < 255) {
        auto alpha_node = srgb.append_child("a:alpha");
        auto alpha_pct = static_cast<int>(std::round(
            static_cast<double>(clr.a()) / 255.0 * 100000.0));
        alpha_node.append_attribute("val") = std::to_string(alpha_pct).c_str();
    }
}

/// Read a color from the first srgbClr child of the given element.
Drawing::Color read_color_element(pugi::xml_node parent) {
    auto srgb = parent.child("a:srgbClr");
    if (srgb) {
        return hex_to_color(srgb.attribute("val").as_string(""));
    }
    return {};
}

// ---------------------------------------------------------------------------
// Pattern style OOXML name mappings
// ---------------------------------------------------------------------------

const char* pattern_style_to_ooxml(PatternStyle style) {
    switch (style) {
        case PatternStyle::PERCENT05: return "pct5";
        case PatternStyle::PERCENT10: return "pct10";
        case PatternStyle::PERCENT20: return "pct20";
        case PatternStyle::PERCENT25: return "pct25";
        case PatternStyle::PERCENT30: return "pct30";
        case PatternStyle::PERCENT40: return "pct40";
        case PatternStyle::PERCENT50: return "pct50";
        case PatternStyle::PERCENT60: return "pct60";
        case PatternStyle::PERCENT70: return "pct70";
        case PatternStyle::PERCENT75: return "pct75";
        case PatternStyle::PERCENT80: return "pct80";
        case PatternStyle::PERCENT90: return "pct90";
        case PatternStyle::DARK_HORIZONTAL: return "dkHorz";
        case PatternStyle::DARK_VERTICAL: return "dkVert";
        case PatternStyle::DARK_DOWNWARD_DIAGONAL: return "dkDnDiag";
        case PatternStyle::DARK_UPWARD_DIAGONAL: return "dkUpDiag";
        case PatternStyle::SMALL_CHECKER_BOARD: return "smCheck";
        case PatternStyle::TRELLIS: return "trellis";
        case PatternStyle::LIGHT_HORIZONTAL: return "ltHorz";
        case PatternStyle::LIGHT_VERTICAL: return "ltVert";
        case PatternStyle::LIGHT_DOWNWARD_DIAGONAL: return "ltDnDiag";
        case PatternStyle::LIGHT_UPWARD_DIAGONAL: return "ltUpDiag";
        case PatternStyle::SMALL_GRID: return "smGrid";
        case PatternStyle::DOTTED_DIAMOND: return "dottedDmnd";
        case PatternStyle::WIDE_DOWNWARD_DIAGONAL: return "wdDnDiag";
        case PatternStyle::WIDE_UPWARD_DIAGONAL: return "wdUpDiag";
        case PatternStyle::DASHED_DOWNWARD_DIAGONAL: return "dashDnDiag";
        case PatternStyle::DASHED_UPWARD_DIAGONAL: return "dashUpDiag";
        case PatternStyle::NARROW_VERTICAL: return "narVert";
        case PatternStyle::NARROW_HORIZONTAL: return "narHorz";
        case PatternStyle::DASHED_VERTICAL: return "dashVert";
        case PatternStyle::DASHED_HORIZONTAL: return "dashHorz";
        case PatternStyle::LARGE_CONFETTI: return "lgConfetti";
        case PatternStyle::LARGE_GRID: return "lgGrid";
        case PatternStyle::HORIZONTAL_BRICK: return "horzBrick";
        case PatternStyle::LARGE_CHECKER_BOARD: return "lgCheck";
        case PatternStyle::SMALL_CONFETTI: return "smConfetti";
        case PatternStyle::ZIGZAG: return "zigZag";
        case PatternStyle::SOLID_DIAMOND: return "solidDmnd";
        case PatternStyle::DIAGONAL_BRICK: return "diagBrick";
        case PatternStyle::OUTLINED_DIAMOND: return "openDmnd";
        case PatternStyle::PLAID: return "plaid";
        case PatternStyle::SPHERE: return "sphere";
        case PatternStyle::WEAVE: return "weave";
        case PatternStyle::DOTTED_GRID: return "dottedGrid";
        case PatternStyle::DIVOT: return "divot";
        case PatternStyle::SHINGLE: return "shingle";
        case PatternStyle::WAVE: return "wave";
        case PatternStyle::HORIZONTAL: return "horz";
        case PatternStyle::VERTICAL: return "vert";
        case PatternStyle::CROSS: return "cross";
        case PatternStyle::DOWNWARD_DIAGONAL: return "dnDiag";
        case PatternStyle::UPWARD_DIAGONAL: return "upDiag";
        case PatternStyle::DIAGONAL_CROSS: return "diagCross";
        default: return nullptr;
    }
}

PatternStyle ooxml_to_pattern_style(std::string_view prst) {
    static const std::unordered_map<std::string_view, PatternStyle> map = {
        {"pct5", PatternStyle::PERCENT05},
        {"pct10", PatternStyle::PERCENT10},
        {"pct20", PatternStyle::PERCENT20},
        {"pct25", PatternStyle::PERCENT25},
        {"pct30", PatternStyle::PERCENT30},
        {"pct40", PatternStyle::PERCENT40},
        {"pct50", PatternStyle::PERCENT50},
        {"pct60", PatternStyle::PERCENT60},
        {"pct70", PatternStyle::PERCENT70},
        {"pct75", PatternStyle::PERCENT75},
        {"pct80", PatternStyle::PERCENT80},
        {"pct90", PatternStyle::PERCENT90},
        {"dkHorz", PatternStyle::DARK_HORIZONTAL},
        {"dkVert", PatternStyle::DARK_VERTICAL},
        {"dkDnDiag", PatternStyle::DARK_DOWNWARD_DIAGONAL},
        {"dkUpDiag", PatternStyle::DARK_UPWARD_DIAGONAL},
        {"smCheck", PatternStyle::SMALL_CHECKER_BOARD},
        {"trellis", PatternStyle::TRELLIS},
        {"ltHorz", PatternStyle::LIGHT_HORIZONTAL},
        {"ltVert", PatternStyle::LIGHT_VERTICAL},
        {"ltDnDiag", PatternStyle::LIGHT_DOWNWARD_DIAGONAL},
        {"ltUpDiag", PatternStyle::LIGHT_UPWARD_DIAGONAL},
        {"smGrid", PatternStyle::SMALL_GRID},
        {"dottedDmnd", PatternStyle::DOTTED_DIAMOND},
        {"wdDnDiag", PatternStyle::WIDE_DOWNWARD_DIAGONAL},
        {"wdUpDiag", PatternStyle::WIDE_UPWARD_DIAGONAL},
        {"dashDnDiag", PatternStyle::DASHED_DOWNWARD_DIAGONAL},
        {"dashUpDiag", PatternStyle::DASHED_UPWARD_DIAGONAL},
        {"narVert", PatternStyle::NARROW_VERTICAL},
        {"narHorz", PatternStyle::NARROW_HORIZONTAL},
        {"dashVert", PatternStyle::DASHED_VERTICAL},
        {"dashHorz", PatternStyle::DASHED_HORIZONTAL},
        {"lgConfetti", PatternStyle::LARGE_CONFETTI},
        {"lgGrid", PatternStyle::LARGE_GRID},
        {"horzBrick", PatternStyle::HORIZONTAL_BRICK},
        {"lgCheck", PatternStyle::LARGE_CHECKER_BOARD},
        {"smConfetti", PatternStyle::SMALL_CONFETTI},
        {"zigZag", PatternStyle::ZIGZAG},
        {"solidDmnd", PatternStyle::SOLID_DIAMOND},
        {"diagBrick", PatternStyle::DIAGONAL_BRICK},
        {"openDmnd", PatternStyle::OUTLINED_DIAMOND},
        {"plaid", PatternStyle::PLAID},
        {"sphere", PatternStyle::SPHERE},
        {"weave", PatternStyle::WEAVE},
        {"dottedGrid", PatternStyle::DOTTED_GRID},
        {"divot", PatternStyle::DIVOT},
        {"shingle", PatternStyle::SHINGLE},
        {"wave", PatternStyle::WAVE},
        {"horz", PatternStyle::HORIZONTAL},
        {"vert", PatternStyle::VERTICAL},
        {"cross", PatternStyle::CROSS},
        {"dnDiag", PatternStyle::DOWNWARD_DIAGONAL},
        {"upDiag", PatternStyle::UPWARD_DIAGONAL},
        {"diagCross", PatternStyle::DIAGONAL_CROSS},
    };
    auto it = map.find(prst);
    return it != map.end() ? it->second : PatternStyle::NOT_DEFINED;
}

} // anonymous namespace

// ---------------------------------------------------------------------------
// FillFormat – XML-backed internal methods
// ---------------------------------------------------------------------------

void FillFormat::init_internal(pugi::xml_node parent_element,
                               std::function<void()> save_callback) {
    parent_element_ = parent_element;
    save_callback_ = std::move(save_callback);

    // Parse existing fill type from XML children.
    auto fill_el = find_fill_element();
    if (!fill_el) return;

    std::string_view name = fill_el.name();
    if (name == "a:noFill") {
        fill_type_ = FillType::NO_FILL;
    } else if (name == "a:solidFill") {
        fill_type_ = FillType::SOLID;
        solid_fill_color_.set_color(read_color_element(fill_el));
    } else if (name == "a:gradFill") {
        fill_type_ = FillType::GRADIENT;
        // Parse gradient shape from a:lin or a:path presence.
        auto lin = fill_el.child("a:lin");
        if (lin) {
            gradient_format_.set_gradient_shape(GradientShape::LINEAR);
            // Angle: OOXML stores in 60000ths of a degree.
            auto ang = lin.attribute("ang").as_llong(0);
            gradient_format_.set_linear_gradient_angle(
                static_cast<float>(ang) / 60000.0f);
        }
        // Parse gradient stops from a:gsLst.
        auto gs_lst = fill_el.child("a:gsLst");
        if (gs_lst) {
            for (auto gs : gs_lst.children("a:gs")) {
                auto pos_attr = gs.attribute("pos");
                float pos = pos_attr
                    ? static_cast<float>(pos_attr.as_int(0)) / 100000.0f
                    : 0.0f;
                auto color = read_color_element(gs);
                gradient_format_.gradient_stops().add(pos, color);
            }
        }
    } else if (name == "a:pattFill") {
        fill_type_ = FillType::PATTERN;
        auto prst = fill_el.attribute("prst");
        if (prst) {
            pattern_format_.set_pattern_style(
                ooxml_to_pattern_style(prst.as_string()));
        }
        auto fg = fill_el.child("a:fgClr");
        if (fg) {
            pattern_format_.fore_color().set_color(read_color_element(fg));
        }
        auto bg = fill_el.child("a:bgClr");
        if (bg) {
            pattern_format_.back_color().set_color(read_color_element(bg));
        }
    } else if (name == "a:blipFill") {
        fill_type_ = FillType::PICTURE;
    } else if (name == "a:grpFill") {
        fill_type_ = FillType::GROUP;
    }
}

pugi::xml_node FillFormat::find_fill_element() const {
    for (auto child : parent_element_.children()) {
        if (is_fill_tag(child.name())) {
            return child;
        }
    }
    return {};
}

void FillFormat::remove_fill_elements() {
    // Collect first, then remove — avoid mutating while iterating.
    std::vector<pugi::xml_node> to_remove;
    for (auto child : parent_element_.children()) {
        if (is_fill_tag(child.name())) {
            to_remove.push_back(child);
        }
    }
    for (auto& node : to_remove) {
        parent_element_.remove_child(node);
    }
}

pugi::xml_node FillFormat::insert_fill_element(std::string_view tag) {
    std::string tag_str{tag};

    // Find insertion point: before the first post-fill element.
    for (auto child : parent_element_.children()) {
        if (is_post_fill_tag(child.name())) {
            return parent_element_.insert_child_before(tag_str.c_str(), child);
        }
    }
    return parent_element_.append_child(tag_str.c_str());
}

pugi::xml_node FillFormat::get_or_create_fill(std::string_view tag) {
    auto el = find_fill_element();
    if (el && tag == el.name()) {
        return el;
    }

    remove_fill_elements();
    el = insert_fill_element(tag);

    // Add default linear direction for gradient fills.
    if (tag == kGradFill) {
        auto lin = el.append_child(std::string(kLin).c_str());
        lin.append_attribute("ang") = "0";
        lin.append_attribute("scaled") = "1";
    }
    // Add default blip and stretch for picture fills.
    else if (tag == kBlipFill) {
        el.append_child(std::string(kBlip).c_str());
        auto stretch = el.append_child(std::string(kStretch).c_str());
        stretch.append_child(std::string(kFillRect).c_str());
    }

    return el;
}

void FillFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// ---------------------------------------------------------------------------
// serialize_to_xml — write in-memory fill format to an XML spPr node
// ---------------------------------------------------------------------------

void FillFormat::serialize_to_xml(pugi::xml_node sp_pr) const {
    switch (fill_type_) {
        case FillType::NO_FILL:
            sp_pr.append_child("a:noFill");
            break;

        case FillType::SOLID: {
            auto sf = sp_pr.append_child("a:solidFill");
            write_color_element(sf, solid_fill_color_);
            break;
        }

        case FillType::GRADIENT: {
            auto gf = sp_pr.append_child("a:gradFill");
            // Gradient stops.
            auto gs_lst = gf.append_child("a:gsLst");
            for (std::size_t i = 0; i < gradient_format_.gradient_stops().size(); ++i) {
                auto& stop = const_cast<GradientStopCollection&>(
                    gradient_format_.gradient_stops())[i];
                auto gs = gs_lst.append_child("a:gs");
                // Position: float 0-1 -> int 0-100000.
                auto pos = static_cast<int>(std::round(stop.position() * 100000.0f));
                gs.append_attribute("pos") = std::to_string(pos).c_str();
                write_color_element(gs, stop.color());
            }
            // Linear direction.
            if (gradient_format_.gradient_shape() == GradientShape::LINEAR ||
                gradient_format_.gradient_shape() == GradientShape::NOT_DEFINED) {
                auto lin = gf.append_child("a:lin");
                auto ang = static_cast<long long>(std::round(
                    gradient_format_.linear_gradient_angle() * 60000.0f));
                lin.append_attribute("ang") = ang;
                lin.append_attribute("scaled") = "1";
            }
            break;
        }

        case FillType::PATTERN: {
            auto pf = sp_pr.append_child("a:pattFill");
            auto* prst = pattern_style_to_ooxml(pattern_format_.pattern_style());
            if (prst) {
                pf.append_attribute("prst") = prst;
            }
            // Foreground color.
            auto fg = pf.append_child("a:fgClr");
            write_color_element(fg, pattern_format_.fore_color());
            // Background color.
            auto bg = pf.append_child("a:bgClr");
            write_color_element(bg, pattern_format_.back_color());
            break;
        }

        case FillType::PICTURE: {
            // a:blipFill with a:blip (r:embed set externally) and a:stretch.
            auto bf = sp_pr.append_child("a:blipFill");
            bf.append_child("a:blip");
            if (picture_fill_.picture_fill_mode() == PictureFillMode::STRETCH) {
                auto stretch = bf.append_child("a:stretch");
                stretch.append_child("a:fillRect");
            } else {
                bf.append_child("a:tile");
            }
            break;
        }

        default:
            // NOT_DEFINED / GROUP — nothing to serialize.
            break;
    }
}

} // namespace Aspose::Slides::Foss
