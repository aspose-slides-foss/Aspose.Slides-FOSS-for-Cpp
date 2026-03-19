// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_group_shape.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>

namespace Aspose::Slides::Foss {

/// Represents a group shape that contains a nested collection of shapes.
class GroupShape final : public Shape, public IGroupShape {
public:
    GroupShape() = default;

    /// Returns the shape collection within this group.
    [[nodiscard]] IShapeCollection& shapes() override { return shapes_; }

    /// Returns the shape collection within this group (const overload).
    [[nodiscard]] const ShapeCollection& shapes() const { return shapes_; }

private:
    ShapeCollection shapes_;
};

} // namespace Aspose::Slides::Foss
