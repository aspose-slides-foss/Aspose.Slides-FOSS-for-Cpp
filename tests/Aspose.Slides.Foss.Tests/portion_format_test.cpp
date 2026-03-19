// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/portion_format.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class PortionFormatTest : public ::testing::Test {
protected:
    PortionFormat fmt;
};

// ---------------------------------------------------------------------------
// Construction: default-constructed PortionFormat inherits BasePortionFormat
// defaults and satisfies both IPortionFormat and IBasePortionFormat interfaces.
// ---------------------------------------------------------------------------

TEST_F(PortionFormatTest, DefaultConstruction) {
    EXPECT_EQ(fmt.font_bold(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_italic(), NullableBool::NOT_DEFINED);
    EXPECT_EQ(fmt.font_underline(), TextUnderlineType::NOT_DEFINED);
    EXPECT_TRUE(std::isnan(fmt.font_height()));
    EXPECT_FALSE(fmt.latin_font().has_value());
    EXPECT_FALSE(fmt.language_id().has_value());
}

// ---------------------------------------------------------------------------
// Writability: PortionFormat exposes writable properties (unlike a
// read-only base). Verify round-trip through setters.
// ---------------------------------------------------------------------------

TEST_F(PortionFormatTest, PropertiesAreWritable) {
    fmt.set_font_bold(NullableBool::TRUE);
    EXPECT_EQ(fmt.font_bold(), NullableBool::TRUE);

    fmt.set_font_height(16.0);
    EXPECT_DOUBLE_EQ(fmt.font_height(), 16.0);

    fmt.set_latin_font(FontData("Consolas"));
    ASSERT_TRUE(fmt.latin_font().has_value());
    EXPECT_EQ(fmt.latin_font()->font_name(), "Consolas");

    fmt.set_language_id("fr-FR");
    ASSERT_TRUE(fmt.language_id().has_value());
    EXPECT_EQ(fmt.language_id().value(), "fr-FR");
}

// ---------------------------------------------------------------------------
// Interface satisfaction: PortionFormat is-a IPortionFormat.
// ---------------------------------------------------------------------------

TEST_F(PortionFormatTest, SatisfiesIPortionFormat) {
    IPortionFormat* iface = &fmt;
    iface->set_font_bold(NullableBool::TRUE);
    EXPECT_EQ(iface->font_bold(), NullableBool::TRUE);
}

TEST_F(PortionFormatTest, SatisfiesIBasePortionFormat) {
    IBasePortionFormat* iface = &fmt;
    iface->set_font_italic(NullableBool::FALSE);
    EXPECT_EQ(iface->font_italic(), NullableBool::FALSE);
}
