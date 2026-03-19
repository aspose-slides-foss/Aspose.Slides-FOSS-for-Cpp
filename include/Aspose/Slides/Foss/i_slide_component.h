// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_presentation_component.h>

namespace Aspose::Slides::Foss {

class IBaseSlide;

/// Base interface for components that belong to a slide.
class ISlideComponent : public virtual IPresentationComponent {
public:
    ~ISlideComponent() override = default;

    /// Returns the base slide. Read-only.
    [[nodiscard]] virtual IBaseSlide* slide() = 0;
    [[nodiscard]] virtual const IBaseSlide* slide() const = 0;

    /// Allows to get base IPresentationComponent interface. Read-only.
    [[nodiscard]] virtual IPresentationComponent* as_i_presentation_component() = 0;
    [[nodiscard]] virtual const IPresentationComponent* as_i_presentation_component() const = 0;
};

} // namespace Aspose::Slides::Foss
