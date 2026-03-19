// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

/// Determines which operations are disabled on the parent IGraphicalObject.
class IGraphicalObjectLock {
public:
    virtual ~IGraphicalObjectLock() = default;

    /// Determines whether adding this shape to a group is forbidden. Read/write.
    [[nodiscard]] virtual bool grouping_locked() const = 0;
    virtual void set_grouping_locked(bool value) = 0;

    /// Determines whether selecting this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool select_locked() const = 0;
    virtual void set_select_locked(bool value) = 0;

    /// Determines whether moving this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool position_locked() const = 0;
    virtual void set_position_locked(bool value) = 0;

    /// Determines whether resizing this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool size_locked() const = 0;
    virtual void set_size_locked(bool value) = 0;

protected:
    IGraphicalObjectLock() = default;
};

} // namespace Aspose::Slides::Foss
