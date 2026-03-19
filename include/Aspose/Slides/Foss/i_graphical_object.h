// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IGraphicalObjectLock;

/// Represents an abstract graphical object.
///
/// GraphicalObject class combines Shape (IShape implementation) with this
/// interface via multiple inheritance, avoiding a diamond on downstream
/// types such as Table that do not inherit Shape.
class IGraphicalObject {
public:
    virtual ~IGraphicalObject() = default;

    /// Returns shape's locks. Read-only.
    /// @return Pointer to the graphical object lock, or nullptr if not available.
    [[nodiscard]] virtual IGraphicalObjectLock* graphical_object_lock() const = 0;

protected:
    IGraphicalObject() = default;
};

} // namespace Aspose::Slides::Foss
