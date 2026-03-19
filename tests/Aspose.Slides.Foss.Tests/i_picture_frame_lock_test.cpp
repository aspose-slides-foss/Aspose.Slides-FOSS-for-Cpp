// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/i_picture_frame_lock.h>
#include <Aspose/Slides/Foss/picture_frame_lock.h>

using namespace Aspose::Slides::Foss;

// ---------- Default values ----------

TEST(IPictureFrameLockTest, AllLocksDefaultToFalse) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;

    EXPECT_FALSE(iface.grouping_locked());
    EXPECT_FALSE(iface.select_locked());
    EXPECT_FALSE(iface.rotation_locked());
    EXPECT_FALSE(iface.aspect_ratio_locked());
    EXPECT_FALSE(iface.position_locked());
    EXPECT_FALSE(iface.size_locked());
    EXPECT_FALSE(iface.edit_points_locked());
    EXPECT_FALSE(iface.adjust_handles_locked());
    EXPECT_FALSE(iface.arrowheads_locked());
    EXPECT_FALSE(iface.shape_type_locked());
    EXPECT_FALSE(iface.crop_locked());
}

// ---------- Get/Set via interface ----------

TEST(IPictureFrameLockTest, GroupingLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_grouping_locked(true);
    EXPECT_TRUE(iface.grouping_locked());
    iface.set_grouping_locked(false);
    EXPECT_FALSE(iface.grouping_locked());
}

TEST(IPictureFrameLockTest, SelectLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_select_locked(true);
    EXPECT_TRUE(iface.select_locked());
}

TEST(IPictureFrameLockTest, RotationLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_rotation_locked(true);
    EXPECT_TRUE(iface.rotation_locked());
}

TEST(IPictureFrameLockTest, AspectRatioLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_aspect_ratio_locked(true);
    EXPECT_TRUE(iface.aspect_ratio_locked());
}

TEST(IPictureFrameLockTest, PositionLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_position_locked(true);
    EXPECT_TRUE(iface.position_locked());
}

TEST(IPictureFrameLockTest, SizeLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_size_locked(true);
    EXPECT_TRUE(iface.size_locked());
}

TEST(IPictureFrameLockTest, EditPointsLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_edit_points_locked(true);
    EXPECT_TRUE(iface.edit_points_locked());
}

TEST(IPictureFrameLockTest, AdjustHandlesLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_adjust_handles_locked(true);
    EXPECT_TRUE(iface.adjust_handles_locked());
}

TEST(IPictureFrameLockTest, ArrowheadsLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_arrowheads_locked(true);
    EXPECT_TRUE(iface.arrowheads_locked());
}

TEST(IPictureFrameLockTest, ShapeTypeLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_shape_type_locked(true);
    EXPECT_TRUE(iface.shape_type_locked());
}

TEST(IPictureFrameLockTest, CropLockedGetSet) {
    PictureFrameLock lock;
    IPictureFrameLock& iface = lock;
    iface.set_crop_locked(true);
    EXPECT_TRUE(iface.crop_locked());
}

// ---------- no_locks helper ----------

TEST(IPictureFrameLockTest, NoLocksReturnsTrueWhenAllFalse) {
    PictureFrameLock lock;
    EXPECT_TRUE(lock.no_locks());
}

TEST(IPictureFrameLockTest, NoLocksReturnsFalseWhenAnySet) {
    PictureFrameLock lock;
    lock.set_edit_points_locked(true);
    EXPECT_FALSE(lock.no_locks());
}
