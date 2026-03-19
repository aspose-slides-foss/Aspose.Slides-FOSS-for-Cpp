// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/base_shape_lock.h>
#include <Aspose/Slides/Foss/i_picture_frame_lock.h>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Determines which operations are disabled on the parent PictureFrame.
///
/// Supports two modes:
/// - **In-memory** (default): lock values stored as plain booleans.
/// - **XML-backed**: after init_internal(), values are read from / written to
///   the backing `a:picLocks` XML element.
class PictureFrameLock final : public BaseShapeLock, public IPictureFrameLock {
public:
    PictureFrameLock() = default;

    /// Initialize from an `a:picLocks` XML element.
    /// @param pic_locks_element The XML node (may be null/empty).
    /// @param slide_part       The owning SlidePart. May be nullptr.
    void init_internal(pugi::xml_node pic_locks_element,
                       Internal::pptx::SlidePart* slide_part);

    /// Gets whether grouping is locked.
    [[nodiscard]] bool grouping_locked() const override;
    /// Sets whether grouping is locked.
    void set_grouping_locked(bool value) override;

    /// Gets whether selection is locked.
    [[nodiscard]] bool select_locked() const override;
    /// Sets whether selection is locked.
    void set_select_locked(bool value) override;

    /// Gets whether rotation is locked.
    [[nodiscard]] bool rotation_locked() const override;
    /// Sets whether rotation is locked.
    void set_rotation_locked(bool value) override;

    /// Gets whether aspect ratio is locked.
    [[nodiscard]] bool aspect_ratio_locked() const override;
    /// Sets whether aspect ratio is locked.
    void set_aspect_ratio_locked(bool value) override;

    /// Gets whether position is locked.
    [[nodiscard]] bool position_locked() const override;
    /// Sets whether position is locked.
    void set_position_locked(bool value) override;

    /// Gets whether size is locked.
    [[nodiscard]] bool size_locked() const override;
    /// Sets whether size is locked.
    void set_size_locked(bool value) override;

    /// Gets whether edit points is locked.
    [[nodiscard]] bool edit_points_locked() const override;
    /// Sets whether edit points is locked.
    void set_edit_points_locked(bool value) override;

    /// Gets whether adjust handles is locked.
    [[nodiscard]] bool adjust_handles_locked() const override;
    /// Sets whether adjust handles is locked.
    void set_adjust_handles_locked(bool value) override;

    /// Gets whether arrowheads is locked.
    [[nodiscard]] bool arrowheads_locked() const override;
    /// Sets whether arrowheads is locked.
    void set_arrowheads_locked(bool value) override;

    /// Gets whether shape type is locked.
    [[nodiscard]] bool shape_type_locked() const override;
    /// Sets whether shape type is locked.
    void set_shape_type_locked(bool value) override;

    /// Gets whether crop is locked.
    [[nodiscard]] bool crop_locked() const override;
    /// Sets whether crop is locked.
    void set_crop_locked(bool value) override;

    /// Returns true if all locks are disabled.
    [[nodiscard]] bool no_locks() const;

private:
    /// Read a lock attribute from the picLocks element.
    [[nodiscard]] bool get_lock(const char* attr_name, bool fallback) const;

    /// Write a lock attribute to the picLocks element, or update the fallback.
    void set_lock(const char* attr_name, bool value, bool& fallback);

    pugi::xml_node pic_locks_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    bool xml_backed_ = false;

    // In-memory fallback values (used when no XML element is attached).
    bool grouping_locked_ = false;
    bool select_locked_ = false;
    bool rotation_locked_ = false;
    bool aspect_ratio_locked_ = false;
    bool position_locked_ = false;
    bool size_locked_ = false;
    bool edit_points_locked_ = false;
    bool adjust_handles_locked_ = false;
    bool arrowheads_locked_ = false;
    bool shape_type_locked_ = false;
    bool crop_locked_ = false;
};

} // namespace Aspose::Slides::Foss
