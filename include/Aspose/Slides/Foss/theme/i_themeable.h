// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_slide_component.h>

namespace Aspose::Slides::Foss::Theme {

/// Represents objects that can be themed.
class IThemeable : public virtual ISlideComponent {
public:
    ~IThemeable() override = default;

    /// Returns the presentation. Read-only.
    [[nodiscard]] virtual IPresentation* presentation() = 0;
    [[nodiscard]] virtual const IPresentation* presentation() const = 0;
};

} // namespace Aspose::Slides::Foss::Theme
