// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class MasterLayoutSlideCollection;
class ShapeCollection;

/// Interface for a master slide in a presentation.
class IMasterSlide {
public:
    virtual ~IMasterSlide() = default;

    /// Returns the collection of shapes.
    [[nodiscard]] virtual ShapeCollection& shapes() = 0;
    [[nodiscard]] virtual const ShapeCollection& shapes() const = 0;

    /// Returns the collection of child layout slides for this master slide. Read-only.
    [[nodiscard]] virtual MasterLayoutSlideCollection& layout_slides() = 0;
    [[nodiscard]] virtual const MasterLayoutSlideCollection& layout_slides() const = 0;

protected:
    IMasterSlide() = default;
};

} // namespace Aspose::Slides::Foss
