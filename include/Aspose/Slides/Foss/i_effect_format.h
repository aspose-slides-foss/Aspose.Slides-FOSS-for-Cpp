// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/effects/blur.h>
#include <Aspose/Slides/Foss/effects/fill_overlay.h>
#include <Aspose/Slides/Foss/effects/glow.h>
#include <Aspose/Slides/Foss/effects/inner_shadow.h>
#include <Aspose/Slides/Foss/effects/outer_shadow.h>
#include <Aspose/Slides/Foss/effects/preset_shadow.h>
#include <Aspose/Slides/Foss/effects/reflection.h>
#include <Aspose/Slides/Foss/effects/soft_edge.h>
#include <Aspose/Slides/Foss/i_effect_param_source.h>

namespace Aspose::Slides::Foss {

/// Interface for shape effect formatting.
class IEffectFormat : public IEffectParamSource {
public:
    virtual ~IEffectFormat() = default;

    /// Returns true if all effects are disabled.
    [[nodiscard]] virtual bool is_no_effects() const = 0;

    /// Returns the blur effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::Blur* blur_effect() = 0;

    /// Returns the fill overlay effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::FillOverlay* fill_overlay_effect() = 0;

    /// Returns the glow effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::Glow* glow_effect() = 0;

    /// Returns the inner shadow effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::InnerShadow* inner_shadow_effect() = 0;

    /// Returns the outer shadow effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::OuterShadow* outer_shadow_effect() = 0;

    /// Returns the preset shadow effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::PresetShadow* preset_shadow_effect() = 0;

    /// Returns the reflection effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::Reflection* reflection_effect() = 0;

    /// Returns the soft edge effect, or nullptr if disabled.
    [[nodiscard]] virtual Effects::SoftEdge* soft_edge_effect() = 0;

    /// Sets the blur effect with given radius and grow flag.
    virtual void set_blur_effect(double radius, bool grow) = 0;

    /// Enables the fill overlay effect.
    virtual void enable_fill_overlay_effect() = 0;

    /// Enables the glow effect.
    virtual void enable_glow_effect() = 0;

    /// Enables the inner shadow effect.
    virtual void enable_inner_shadow_effect() = 0;

    /// Enables the outer shadow effect.
    virtual void enable_outer_shadow_effect() = 0;

    /// Enables the preset shadow effect.
    virtual void enable_preset_shadow_effect() = 0;

    /// Enables the reflection effect.
    virtual void enable_reflection_effect() = 0;

    /// Enables the soft edge effect.
    virtual void enable_soft_edge_effect() = 0;

    /// Disables the blur effect.
    virtual void disable_blur_effect() = 0;

    /// Disables the fill overlay effect.
    virtual void disable_fill_overlay_effect() = 0;

    /// Disables the glow effect.
    virtual void disable_glow_effect() = 0;

    /// Disables the inner shadow effect.
    virtual void disable_inner_shadow_effect() = 0;

    /// Disables the outer shadow effect.
    virtual void disable_outer_shadow_effect() = 0;

    /// Disables the preset shadow effect.
    virtual void disable_preset_shadow_effect() = 0;

    /// Disables the reflection effect.
    virtual void disable_reflection_effect() = 0;

    /// Disables the soft edge effect.
    virtual void disable_soft_edge_effect() = 0;

    /// Returns this object as IEffectParamSource.
    [[nodiscard]] virtual IEffectParamSource& as_i_effect_param_source() noexcept = 0;
};

} // namespace Aspose::Slides::Foss
