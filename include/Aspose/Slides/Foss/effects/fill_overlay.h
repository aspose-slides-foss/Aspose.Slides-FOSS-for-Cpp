// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_fill_overlay.h>
#include <Aspose/Slides/Foss/effects/image_transform_operation.h>
#include <Aspose/Slides/Foss/fill_blend_mode.h>
#include <Aspose/Slides/Foss/fill_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
class IPresentationComponent;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Returns the ST_BlendMode token for a FillBlendMode value ("mult", "over", …).
///
/// These are not the display names returned by `to_string_view(FillBlendMode)`.
const char* fill_blend_mode_to_ooxml(FillBlendMode value);

/// Represents a Fill Overlay effect.
///
/// A fill overlay specifies an additional fill for an object
/// and blends the two fills together using the selected blend mode.
class FillOverlay final : public ImageTransformOperation, public IFillOverlay {
public:
    FillOverlay() = default;
    ~FillOverlay() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:fillOverlay>) with a persistence callback.
    /// @param element  The <a:fillOverlay> XML node.
    /// @param save_callback  Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide  The owning slide (may be nullptr).
    void init_internal(pugi::xml_node element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Persist changes via the save callback provided at init time.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns the fill blend mode. Defaults to OVERLAY.
    [[nodiscard]] FillBlendMode blend() const noexcept override { return blend_; }

    /// Sets the fill blend mode.
    void set_blend(FillBlendMode value) noexcept override;

    /// Returns the fill format associated with this overlay. Read-only.
    [[nodiscard]] IFillFormat& fill_format() noexcept override { return fill_format_; }

    /// Returns the fill format associated with this overlay (const). Read-only.
    [[nodiscard]] const IFillFormat& fill_format() const noexcept override { return fill_format_; }

    // -- Bridging overrides (IFillOverlay ↔ PVIObject) ----------------------

    /// Returns the parent slide, or nullptr if not set.
    [[nodiscard]] IBaseSlide* slide() override { return PVIObject::slide(); }
    [[nodiscard]] const IBaseSlide* slide() const override { return PVIObject::slide(); }

    /// Returns this object as IPresentationComponent, or nullptr.
    ///
    /// Note: PVIObject base returns `this`, but standalone FillOverlay objects
    /// are not meaningful as IPresentationComponent without a shape hierarchy.
    /// Returns nullptr for compatibility with existing call-site expectations.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override {
        return nullptr;
    }

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] IImageTransformOperation& as_i_image_transform_operation() noexcept override {
        return *this;
    }

private:
    FillBlendMode blend_ = FillBlendMode::OVERLAY;
    FillFormat fill_format_;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
