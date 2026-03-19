// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>

using namespace Aspose::Slides::Foss;

TEST(INotesSizeTest, NotesSizeHasPositiveWidthAndHeight) {
    Presentation pres;
    const auto& ns = pres.notes_size();
    auto sz = ns.size();
    EXPECT_GT(sz.width, 0.0f);
    EXPECT_GT(sz.height, 0.0f);
}

TEST(INotesSizeTest, DefaultDimensions) {
    Presentation pres;
    const auto& ns = pres.notes_size();
    EXPECT_DOUBLE_EQ(ns.width(), 720.0);
    EXPECT_DOUBLE_EQ(ns.height(), 540.0);
}

TEST(INotesSizeTest, SetSizeRoundTrip) {
    Presentation pres;
    auto& ns = pres.notes_size();
    ns.set_size(Drawing::SizeF{800.0f, 600.0f});
    auto sz = ns.size();
    EXPECT_FLOAT_EQ(sz.width, 800.0f);
    EXPECT_FLOAT_EQ(sz.height, 600.0f);
}

TEST(INotesSizeTest, SetWidthAndHeight) {
    Presentation pres;
    auto& ns = pres.notes_size();
    ns.set_width(1024.0);
    ns.set_height(768.0);
    EXPECT_DOUBLE_EQ(ns.width(), 1024.0);
    EXPECT_DOUBLE_EQ(ns.height(), 768.0);
    auto sz = ns.size();
    EXPECT_FLOAT_EQ(sz.width, 1024.0f);
    EXPECT_FLOAT_EQ(sz.height, 768.0f);
}
