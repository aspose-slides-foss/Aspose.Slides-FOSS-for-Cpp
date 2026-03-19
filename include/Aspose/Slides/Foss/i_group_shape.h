// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IShapeCollection;

/// Interface for a group shape that contains a nested shape collection.
class IGroupShape {
public:
    virtual ~IGroupShape() = default;

    /// Returns the shape collection within this group.
    [[nodiscard]] virtual IShapeCollection& shapes() = 0;

protected:
    IGroupShape() = default;
};

} // namespace Aspose::Slides::Foss
