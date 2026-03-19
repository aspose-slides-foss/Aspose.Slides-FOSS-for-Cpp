// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/base_shape_lock.h>
#include <Aspose/Slides/Foss/i_graphical_object_lock.h>

namespace Aspose::Slides::Foss {

/// Concrete locking properties for a graphical object.
///
/// Determines which operations are disabled on the parent GraphicalObject.
/// Inherits from BaseShapeLock (shape lock hierarchy) and implements
/// IGraphicalObjectLock (graphical-object-specific lock interface).
class GraphicalObjectLock final : public BaseShapeLock, public IGraphicalObjectLock {
public:
    GraphicalObjectLock() = default;

    /// Gets whether grouping is locked.
    [[nodiscard]] bool grouping_locked() const override { return grouping_locked_; }
    /// Sets whether grouping is locked.
    void set_grouping_locked(bool value) override { grouping_locked_ = value; }

    /// Gets whether selection is locked.
    [[nodiscard]] bool select_locked() const override { return select_locked_; }
    /// Sets whether selection is locked.
    void set_select_locked(bool value) override { select_locked_ = value; }

    /// Gets whether position is locked.
    [[nodiscard]] bool position_locked() const override { return position_locked_; }
    /// Sets whether position is locked.
    void set_position_locked(bool value) override { position_locked_ = value; }

    /// Gets whether size is locked.
    [[nodiscard]] bool size_locked() const override { return size_locked_; }
    /// Sets whether size is locked.
    void set_size_locked(bool value) override { size_locked_ = value; }

    /// Returns true if all locks are disabled.
    [[nodiscard]] bool no_locks() const {
        return !grouping_locked_ && !select_locked_ &&
               !position_locked_ && !size_locked_;
    }

private:
    bool grouping_locked_ = false;
    bool select_locked_ = false;
    bool position_locked_ = false;
    bool size_locked_ = false;
};

} // namespace Aspose::Slides::Foss
