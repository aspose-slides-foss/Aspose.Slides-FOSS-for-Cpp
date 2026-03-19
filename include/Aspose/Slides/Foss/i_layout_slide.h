// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/slide_layout_type.h>

namespace Aspose::Slides::Foss {

class IMasterSlide;
class ShapeCollection;

/// Interface for a layout slide.
class ILayoutSlide {
public:
    virtual ~ILayoutSlide() = default;

    /// Returns the layout type.
    [[nodiscard]] virtual SlideLayoutType layout_type() const = 0;

    /// Returns the parent master slide for this layout. Read/write.
    [[nodiscard]] virtual IMasterSlide* master_slide() const = 0;

    /// Sets the parent master slide for this layout.
    virtual void set_master_slide(IMasterSlide* value) = 0;

    /// Returns the collection of shapes.
    [[nodiscard]] virtual ShapeCollection& shapes() = 0;
    [[nodiscard]] virtual const ShapeCollection& shapes() const = 0;

protected:
    ILayoutSlide() = default;
};

} // namespace Aspose::Slides::Foss
