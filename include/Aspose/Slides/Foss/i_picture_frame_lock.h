// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

/// Determines which operations are disabled on the parent PictureFrame.
class IPictureFrameLock {
public:
    virtual ~IPictureFrameLock() = default;

    /// Determines whether adding this shape to a group is forbidden. Read/write.
    [[nodiscard]] virtual bool grouping_locked() const = 0;
    virtual void set_grouping_locked(bool value) = 0;

    /// Determines whether selecting this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool select_locked() const = 0;
    virtual void set_select_locked(bool value) = 0;

    /// Determines whether changing the rotation angle of this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool rotation_locked() const = 0;
    virtual void set_rotation_locked(bool value) = 0;

    /// Determines whether a shape must preserve aspect ratio on resizing. Read/write.
    [[nodiscard]] virtual bool aspect_ratio_locked() const = 0;
    virtual void set_aspect_ratio_locked(bool value) = 0;

    /// Determines whether moving this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool position_locked() const = 0;
    virtual void set_position_locked(bool value) = 0;

    /// Determines whether resizing this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool size_locked() const = 0;
    virtual void set_size_locked(bool value) = 0;

    /// Determines whether direct changing of the contour of this shape is forbidden. Read/write.
    [[nodiscard]] virtual bool edit_points_locked() const = 0;
    virtual void set_edit_points_locked(bool value) = 0;

    /// Determines whether changing adjust values is forbidden. Read/write.
    [[nodiscard]] virtual bool adjust_handles_locked() const = 0;
    virtual void set_adjust_handles_locked(bool value) = 0;

    /// Determines whether changing arrowheads is forbidden. Read/write.
    [[nodiscard]] virtual bool arrowheads_locked() const = 0;
    virtual void set_arrowheads_locked(bool value) = 0;

    /// Determines whether changing the shape type is forbidden. Read/write.
    [[nodiscard]] virtual bool shape_type_locked() const = 0;
    virtual void set_shape_type_locked(bool value) = 0;

    /// Determines whether image cropping is forbidden. Read/write.
    [[nodiscard]] virtual bool crop_locked() const = 0;
    virtual void set_crop_locked(bool value) = 0;

protected:
    IPictureFrameLock() = default;
};

} // namespace Aspose::Slides::Foss
