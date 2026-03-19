// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_layout_slide_collection.h>

namespace Aspose::Slides::Foss {

/// Represents a collection of all layout slides in presentation.
/// Extends ILayoutSlideCollection interface with methods for adding/cloning
/// layout slides in context of uniting the individual collections of master's
/// layout slides.
class IGlobalLayoutSlideCollection : public virtual ILayoutSlideCollection {
public:
    ~IGlobalLayoutSlideCollection() override = default;

    /// Returns this collection viewed as an ILayoutSlideCollection.
    /// @return Reference to the ILayoutSlideCollection interface.
    [[nodiscard]] virtual ILayoutSlideCollection& as_i_layout_slide_collection() noexcept = 0;

    /// Returns this collection viewed as an ILayoutSlideCollection (const).
    /// @return Const reference to the ILayoutSlideCollection interface.
    [[nodiscard]] virtual const ILayoutSlideCollection& as_i_layout_slide_collection() const noexcept = 0;

protected:
    IGlobalLayoutSlideCollection() = default;
};

} // namespace Aspose::Slides::Foss
