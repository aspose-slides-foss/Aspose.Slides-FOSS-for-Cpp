// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <Aspose/Slides/Foss/i_effect_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

class IBaseSlide;

/// Represents effect properties of a shape (shadow, glow, blur, etc.).
class EffectFormat final : public IEffectFormat {
public:
    EffectFormat() = default;
    ~EffectFormat() override = default;

    /// Initialize XML-backed effect format.
    /// @param parent_element The XML element that may contain <a:effectLst>
    ///        (e.g., <p:spPr>).
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide The owning slide (may be nullptr).
    void init_internal(pugi::xml_node parent_element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Get the <a:effectLst> element if it exists.
    [[nodiscard]] pugi::xml_node get_effect_lst() const;

    /// Get or create the <a:effectLst> element at the correct position in spPr.
    pugi::xml_node ensure_effect_lst();

    /// Get a specific effect child from effectLst by tag name.
    [[nodiscard]] pugi::xml_node get_effect_child(std::string_view tag) const;

    /// Get or create a specific effect child in effectLst at the correct position.
    pugi::xml_node ensure_effect_child(std::string_view tag);

    /// Remove a specific effect child from effectLst.
    void remove_effect_child(std::string_view tag);

    /// Save changes via the save callback.
    void save();

    /// Serialize all in-memory effects into an XML <a:effectLst> under the given spPr node.
    void serialize_to_xml(pugi::xml_node sp_pr) const;

    /// Returns true if all effects are disabled.
    [[nodiscard]] bool is_no_effects() const override {
        return !blur_ && !fill_overlay_ && !glow_ && !inner_shadow_ &&
               !outer_shadow_ && !preset_shadow_ && !reflection_ && !soft_edge_;
    }

    /// Returns the blur effect, or nullptr if disabled.
    [[nodiscard]] Effects::Blur* blur_effect() override { return blur_.get(); }

    /// Returns the fill overlay effect, or nullptr if disabled.
    [[nodiscard]] Effects::FillOverlay* fill_overlay_effect() override { return fill_overlay_.get(); }

    /// Returns the glow effect, or nullptr if disabled.
    [[nodiscard]] Effects::Glow* glow_effect() override { return glow_.get(); }

    /// Returns the inner shadow effect, or nullptr if disabled.
    [[nodiscard]] Effects::InnerShadow* inner_shadow_effect() override { return inner_shadow_.get(); }

    /// Returns the outer shadow effect, or nullptr if disabled.
    [[nodiscard]] Effects::OuterShadow* outer_shadow_effect() override { return outer_shadow_.get(); }

    /// Returns the preset shadow effect, or nullptr if disabled.
    [[nodiscard]] Effects::PresetShadow* preset_shadow_effect() override { return preset_shadow_.get(); }

    /// Returns the reflection effect, or nullptr if disabled.
    [[nodiscard]] Effects::Reflection* reflection_effect() override { return reflection_.get(); }

    /// Returns the soft edge effect, or nullptr if disabled.
    [[nodiscard]] Effects::SoftEdge* soft_edge_effect() override { return soft_edge_.get(); }

    /// Sets the blur effect with given radius and grow flag.
    void set_blur_effect(double radius, bool grow) override;

    /// Enables the fill overlay effect.
    void enable_fill_overlay_effect() override;

    /// Enables the glow effect.
    void enable_glow_effect() override;

    /// Enables the inner shadow effect.
    void enable_inner_shadow_effect() override;

    /// Enables the outer shadow effect.
    void enable_outer_shadow_effect() override;

    /// Enables the preset shadow effect.
    void enable_preset_shadow_effect() override;

    /// Enables the reflection effect.
    void enable_reflection_effect() override;

    /// Enables the soft edge effect.
    void enable_soft_edge_effect() override;

    /// Disables the blur effect.
    void disable_blur_effect() override;

    /// Disables the fill overlay effect.
    void disable_fill_overlay_effect() override;

    /// Disables the glow effect.
    void disable_glow_effect() override;

    /// Disables the inner shadow effect.
    void disable_inner_shadow_effect() override;

    /// Disables the outer shadow effect.
    void disable_outer_shadow_effect() override;

    /// Disables the preset shadow effect.
    void disable_preset_shadow_effect() override;

    /// Disables the reflection effect.
    void disable_reflection_effect() override;

    /// Disables the soft edge effect.
    void disable_soft_edge_effect() override;

    /// Returns this object as IEffectParamSource.
    [[nodiscard]] IEffectParamSource& as_i_effect_param_source() noexcept override { return *this; }

private:
    /// Helper: create an effect object, ensure its XML element, and call init_internal.
    template <typename T>
    std::unique_ptr<T> create_and_init_effect(std::string_view xml_tag);

    std::unique_ptr<Effects::Blur> blur_;
    std::unique_ptr<Effects::FillOverlay> fill_overlay_;
    std::unique_ptr<Effects::Glow> glow_;
    std::unique_ptr<Effects::InnerShadow> inner_shadow_;
    std::unique_ptr<Effects::OuterShadow> outer_shadow_;
    std::unique_ptr<Effects::PresetShadow> preset_shadow_;
    std::unique_ptr<Effects::Reflection> reflection_;
    std::unique_ptr<Effects::SoftEdge> soft_edge_;

    pugi::xml_node parent_element_;
    std::function<void()> save_callback_;
    IBaseSlide* parent_slide_ = nullptr;
};

} // namespace Aspose::Slides::Foss
