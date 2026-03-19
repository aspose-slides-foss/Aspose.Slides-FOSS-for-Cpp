// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_slide_component.h>

namespace Aspose::Slides::Foss {

class IBaseSlide;
class IPresentation;

/// Encapsulates basic service infrastructure for objects that can be
/// a subject of property value inheritance.
class PVIObject : public ISlideComponent {
public:
    ~PVIObject() override = default;

    /// Allows to get base IPresentationComponent interface. Read-only.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    /// Returns the base slide. Read-only.
    [[nodiscard]] IBaseSlide* slide() override;
    [[nodiscard]] const IBaseSlide* slide() const override;

    /// Returns the presentation. Read-only.
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    /// Sets the parent slide for this object.
    void set_parent_slide(IBaseSlide* slide);

protected:
    PVIObject() = default;

private:
    IBaseSlide* parent_slide_ = nullptr;
};

} // namespace Aspose::Slides::Foss
