// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <Aspose/Slides/Foss/effects/i_soft_edge.h>
#include <Aspose/Slides/Foss/effects/image_transform_operation.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Effects {

/// Represents a soft edge effect applied to a shape.
/// The edges of the shape are blurred, while the fill is not affected.
class SoftEdge final : public ImageTransformOperation, public ISoftEdge {
public:
    SoftEdge() = default;
    ~SoftEdge() override = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize from an XML element (e.g., <a:softEdge>) with a persistence callback.
    /// @param element  The <a:softEdge> XML node.
    /// @param save_callback  Callback to persist changes (e.g., SlidePart::save).
    /// @param parent_slide  The owning slide (may be nullptr).
    void init_internal(pugi::xml_node element,
                       std::function<void()> save_callback,
                       IBaseSlide* parent_slide = nullptr);

    /// Persist changes via the save callback provided at init time.
    void save();

    // -- Public property API ----------------------------------------------

    /// Returns this object as IImageTransformOperation.
    [[nodiscard]] IImageTransformOperation& as_i_image_transform_operation() noexcept override { return *this; }

    /// Returns the soft edge radius in points.
    [[nodiscard]] double radius() const noexcept override;
    /// Sets the soft edge radius in points.
    void set_radius(double value) noexcept override;

private:
    double radius_ = 0.0;

    pugi::xml_node element_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss::Effects
