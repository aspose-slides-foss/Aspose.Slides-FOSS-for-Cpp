// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/graphical_object_lock.h>

using namespace Aspose::Slides::Foss;

TEST(GraphicalObjectLockTest, DefaultConstruction) {
    GraphicalObjectLock lock;
    EXPECT_FALSE(lock.grouping_locked());
    EXPECT_FALSE(lock.select_locked());
    EXPECT_FALSE(lock.position_locked());
    EXPECT_FALSE(lock.size_locked());
    EXPECT_TRUE(lock.no_locks());
}

TEST(GraphicalObjectLockTest, SetAndGetLocks) {
    GraphicalObjectLock lock;

    lock.set_grouping_locked(true);
    EXPECT_TRUE(lock.grouping_locked());
    EXPECT_FALSE(lock.no_locks());

    lock.set_select_locked(true);
    EXPECT_TRUE(lock.select_locked());

    lock.set_position_locked(true);
    EXPECT_TRUE(lock.position_locked());

    lock.set_size_locked(true);
    EXPECT_TRUE(lock.size_locked());
}

TEST(GraphicalObjectLockTest, NoLocksOnlyWhenAllFalse) {
    GraphicalObjectLock lock;
    EXPECT_TRUE(lock.no_locks());

    lock.set_size_locked(true);
    EXPECT_FALSE(lock.no_locks());

    lock.set_size_locked(false);
    EXPECT_TRUE(lock.no_locks());
}

TEST(GraphicalObjectLockTest, InheritsBaseShapeLock) {
    GraphicalObjectLock lock;
    BaseShapeLock* base = &lock;
    EXPECT_NE(base, nullptr);
}

TEST(GraphicalObjectLockTest, ImplementsIGraphicalObjectLock) {
    GraphicalObjectLock lock;
    IGraphicalObjectLock* iface = &lock;
    iface->set_grouping_locked(true);
    EXPECT_TRUE(iface->grouping_locked());
}
