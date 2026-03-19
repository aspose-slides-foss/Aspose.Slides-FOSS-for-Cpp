// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/effect_format.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/simple_color_format.h>
#include <Aspose/Slides/Foss/effects/blur.h>
#include <Aspose/Slides/Foss/effects/fill_overlay.h>
#include <Aspose/Slides/Foss/effects/glow.h>
#include <Aspose/Slides/Foss/effects/inner_shadow.h>
#include <Aspose/Slides/Foss/effects/outer_shadow.h>
#include <Aspose/Slides/Foss/effects/preset_shadow.h>
#include <Aspose/Slides/Foss/effects/reflection.h>
#include <Aspose/Slides/Foss/effects/soft_edge.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// Tag constants (prefixed names for pugixml)
// ---------------------------------------------------------------------------

static constexpr std::string_view kEffectLst = "a:effectLst";
static constexpr std::string_view kScene3d   = "a:scene3d";
static constexpr std::string_view kSp3d      = "a:sp3d";
static constexpr std::string_view kExtLst    = "a:extLst";

static constexpr std::string_view kBlur        = "a:blur";
static constexpr std::string_view kFillOverlay = "a:fillOverlay";
static constexpr std::string_view kGlow        = "a:glow";
static constexpr std::string_view kInnerShdw   = "a:innerShdw";
static constexpr std::string_view kOuterShdw   = "a:outerShdw";
static constexpr std::string_view kPrstShdw    = "a:prstShdw";
static constexpr std::string_view kReflection  = "a:reflection";
static constexpr std::string_view kSoftEdge    = "a:softEdge";

/// OOXML-mandated ordering of children within <a:effectLst>.
static constexpr std::array kEffectLstOrder = {
    std::string_view{"a:blur"},
    std::string_view{"a:fillOverlay"},
    std::string_view{"a:glow"},
    std::string_view{"a:innerShdw"},
    std::string_view{"a:outerShdw"},
    std::string_view{"a:prstShdw"},
    std::string_view{"a:reflection"},
    std::string_view{"a:softEdge"},
};

/// Return the rank of a tag in the effect list ordering, or -1 if unknown.
static int effect_rank(std::string_view tag) {
    auto it = std::ranges::find(kEffectLstOrder, tag);
    if (it == kEffectLstOrder.end()) return -1;
    return static_cast<int>(it - kEffectLstOrder.begin());
}

// ---------------------------------------------------------------------------
// EffectFormat – XML-backed internal methods
// ---------------------------------------------------------------------------

void EffectFormat::init_internal(pugi::xml_node parent_element,
                                 std::function<void()> save_callback,
                                 IBaseSlide* parent_slide) {
    parent_element_ = parent_element;
    save_callback_ = std::move(save_callback);
    parent_slide_ = parent_slide;

    // Load existing effects from <a:effectLst> children.
    auto effect_lst = get_effect_lst();
    if (!effect_lst) return;

    if (auto node = effect_lst.child(std::string(kBlur).c_str()); node) {
        blur_ = std::make_unique<Effects::Blur>();
        blur_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kFillOverlay).c_str()); node) {
        fill_overlay_ = std::make_unique<Effects::FillOverlay>();
        fill_overlay_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kGlow).c_str()); node) {
        glow_ = std::make_unique<Effects::Glow>();
        glow_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kInnerShdw).c_str()); node) {
        inner_shadow_ = std::make_unique<Effects::InnerShadow>();
        inner_shadow_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kOuterShdw).c_str()); node) {
        outer_shadow_ = std::make_unique<Effects::OuterShadow>();
        outer_shadow_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kPrstShdw).c_str()); node) {
        preset_shadow_ = std::make_unique<Effects::PresetShadow>();
        preset_shadow_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kReflection).c_str()); node) {
        reflection_ = std::make_unique<Effects::Reflection>();
        reflection_->init_internal(node, save_callback_, parent_slide_);
    }
    if (auto node = effect_lst.child(std::string(kSoftEdge).c_str()); node) {
        soft_edge_ = std::make_unique<Effects::SoftEdge>();
        soft_edge_->init_internal(node, save_callback_, parent_slide_);
    }
}

pugi::xml_node EffectFormat::get_effect_lst() const {
    return parent_element_.child(std::string(kEffectLst).c_str());
}

pugi::xml_node EffectFormat::ensure_effect_lst() {
    auto el = get_effect_lst();
    if (el) return el;

    // Insert before scene3d / sp3d / extLst to maintain OOXML order.
    for (auto child : parent_element_.children()) {
        std::string_view name{child.name()};
        if (name == kScene3d || name == kSp3d || name == kExtLst) {
            return parent_element_.insert_child_before(
                std::string(kEffectLst).c_str(), child);
        }
    }
    return parent_element_.append_child(std::string(kEffectLst).c_str());
}

pugi::xml_node EffectFormat::get_effect_child(std::string_view tag) const {
    auto effect_lst = get_effect_lst();
    if (!effect_lst) return {};
    return effect_lst.child(std::string(tag).c_str());
}

pugi::xml_node EffectFormat::ensure_effect_child(std::string_view tag) {
    auto effect_lst = ensure_effect_lst();
    std::string tag_str{tag};
    auto existing = effect_lst.child(tag_str.c_str());
    if (existing) return existing;

    int new_rank = effect_rank(tag);
    if (new_rank < 0) {
        // Unknown tag — append at end.
        return effect_lst.append_child(tag_str.c_str());
    }

    // Insert before the first child with a higher rank.
    for (auto child : effect_lst.children()) {
        int child_rank = effect_rank(child.name());
        if (child_rank >= 0 && child_rank > new_rank) {
            return effect_lst.insert_child_before(tag_str.c_str(), child);
        }
    }
    return effect_lst.append_child(tag_str.c_str());
}

void EffectFormat::remove_effect_child(std::string_view tag) {
    auto effect_lst = get_effect_lst();
    if (!effect_lst) return;

    std::string tag_str{tag};
    auto child = effect_lst.child(tag_str.c_str());
    if (child) {
        effect_lst.remove_child(child);
    }
    // If effectLst is now empty, remove it too.
    if (!effect_lst.first_child()) {
        parent_element_.remove_child(effect_lst);
    }
}

void EffectFormat::save() {
    if (save_callback_) {
        save_callback_();
    }
}

// ---------------------------------------------------------------------------
// Helper: create effect object with XML backing
// ---------------------------------------------------------------------------

template <typename T>
std::unique_ptr<T> EffectFormat::create_and_init_effect(std::string_view xml_tag) {
    auto obj = std::make_unique<T>();
    if (parent_element_) {
        auto node = ensure_effect_child(xml_tag);
        obj->init_internal(node, save_callback_, parent_slide_);
        save();
    }
    return obj;
}

// ---------------------------------------------------------------------------
// Enable methods
// ---------------------------------------------------------------------------

void EffectFormat::set_blur_effect(double radius, bool grow) {
    if (!blur_) {
        blur_ = create_and_init_effect<Effects::Blur>(kBlur);
    }
    blur_->set_radius(radius);
    blur_->set_grow(grow);
}

void EffectFormat::enable_fill_overlay_effect() {
    if (!fill_overlay_) {
        fill_overlay_ = create_and_init_effect<Effects::FillOverlay>(kFillOverlay);
    }
}

void EffectFormat::enable_glow_effect() {
    if (!glow_) {
        glow_ = create_and_init_effect<Effects::Glow>(kGlow);
    }
}

void EffectFormat::enable_inner_shadow_effect() {
    if (!inner_shadow_) {
        inner_shadow_ = create_and_init_effect<Effects::InnerShadow>(kInnerShdw);
    }
}

void EffectFormat::enable_outer_shadow_effect() {
    if (!outer_shadow_) {
        outer_shadow_ = create_and_init_effect<Effects::OuterShadow>(kOuterShdw);
    }
}

void EffectFormat::enable_preset_shadow_effect() {
    if (!preset_shadow_) {
        preset_shadow_ = create_and_init_effect<Effects::PresetShadow>(kPrstShdw);
    }
}

void EffectFormat::enable_reflection_effect() {
    if (!reflection_) {
        reflection_ = create_and_init_effect<Effects::Reflection>(kReflection);
    }
}

void EffectFormat::enable_soft_edge_effect() {
    if (!soft_edge_) {
        soft_edge_ = create_and_init_effect<Effects::SoftEdge>(kSoftEdge);
    }
}

// ---------------------------------------------------------------------------
// Disable methods
// ---------------------------------------------------------------------------

void EffectFormat::disable_blur_effect() {
    if (parent_element_) remove_effect_child(kBlur);
    blur_.reset();
    save();
}

void EffectFormat::disable_fill_overlay_effect() {
    if (parent_element_) remove_effect_child(kFillOverlay);
    fill_overlay_.reset();
    save();
}

void EffectFormat::disable_glow_effect() {
    if (parent_element_) remove_effect_child(kGlow);
    glow_.reset();
    save();
}

void EffectFormat::disable_inner_shadow_effect() {
    if (parent_element_) remove_effect_child(kInnerShdw);
    inner_shadow_.reset();
    save();
}

void EffectFormat::disable_outer_shadow_effect() {
    if (parent_element_) remove_effect_child(kOuterShdw);
    outer_shadow_.reset();
    save();
}

void EffectFormat::disable_preset_shadow_effect() {
    if (parent_element_) remove_effect_child(kPrstShdw);
    preset_shadow_.reset();
    save();
}

void EffectFormat::disable_reflection_effect() {
    if (parent_element_) remove_effect_child(kReflection);
    reflection_.reset();
    save();
}

void EffectFormat::disable_soft_edge_effect() {
    if (parent_element_) remove_effect_child(kSoftEdge);
    soft_edge_.reset();
    save();
}

// ---------------------------------------------------------------------------
// serialize_to_xml — write in-memory effects to an XML spPr node
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

/// Write a color child element (a:srgbClr with optional a:alpha) under parent.
void write_color_element(pugi::xml_node parent, const SimpleColorFormat& cf) {
    auto clr = cf.color();
    auto srgb = parent.append_child("a:srgbClr");
    srgb.append_attribute("val") = color_to_hex(clr).c_str();
    if (clr.a() < 255) {
        auto alpha_node = srgb.append_child("a:alpha");
        // Alpha in OOXML is stored as percentage * 1000 (100% = 100000).
        auto alpha_pct = static_cast<int>(std::round(
            static_cast<double>(clr.a()) / 255.0 * 100000.0));
        alpha_node.append_attribute("val") = std::to_string(alpha_pct).c_str();
    }
}

} // anonymous namespace

void EffectFormat::serialize_to_xml(pugi::xml_node sp_pr) const {
    if (is_no_effects()) return;

    auto effect_lst = sp_pr.append_child("a:effectLst");

    // Effects must appear in OOXML-mandated order:
    // blur, fillOverlay, glow, innerShdw, outerShdw, prstShdw, reflection, softEdge

    if (blur_) {
        auto node = effect_lst.append_child("a:blur");
        auto emu = static_cast<long long>(std::round(
            blur_->radius() * Internal::pptx::kEmuPerPoint));
        node.append_attribute("rad") = emu;
        node.append_attribute("grow") = blur_->grow() ? "1" : "0";
    }

    // fillOverlay: skip for now (not tested)

    if (glow_) {
        auto node = effect_lst.append_child("a:glow");
        auto emu = static_cast<long long>(std::round(
            glow_->radius() * Internal::pptx::kEmuPerPoint));
        node.append_attribute("rad") = emu;
        write_color_element(node, glow_->color());
    }

    // innerShdw: skip for now (not tested)

    if (outer_shadow_) {
        auto node = effect_lst.append_child("a:outerShdw");
        auto blur_emu = static_cast<long long>(std::round(
            outer_shadow_->blur_radius() * Internal::pptx::kEmuPerPoint));
        node.append_attribute("blurRad") = blur_emu;
        auto dir_val = static_cast<long long>(std::round(
            outer_shadow_->direction() * Internal::pptx::kRotationUnit));
        node.append_attribute("dir") = dir_val;
        auto dist_emu = static_cast<long long>(std::round(
            outer_shadow_->distance() * Internal::pptx::kEmuPerPoint));
        node.append_attribute("dist") = dist_emu;
        write_color_element(node, outer_shadow_->shadow_color());
    }

    // prstShdw: skip for now (not tested)
    // reflection: skip for now (not tested)

    if (soft_edge_) {
        auto node = effect_lst.append_child("a:softEdge");
        auto emu = static_cast<long long>(std::round(
            soft_edge_->radius() * Internal::pptx::kEmuPerPoint));
        node.append_attribute("rad") = emu;
    }
}

} // namespace Aspose::Slides::Foss
