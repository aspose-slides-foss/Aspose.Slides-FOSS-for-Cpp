// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/font_data.h>
#include <Aspose/Slides/Foss/i_font_data.h>

#include <gtest/gtest.h>
#include <memory>
#include <sstream>

using namespace Aspose::Slides::Foss;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

class FontDataTest : public ::testing::Test {
protected:
    FontData fd{"Arial"};
};

// ---------------------------------------------------------------------------
// Construction and font_name accessor
// ---------------------------------------------------------------------------

TEST_F(FontDataTest, ConstructorStoresFontName) {
    EXPECT_EQ(fd.font_name(), "Arial");
}

TEST_F(FontDataTest, ConstructWithDifferentName) {
    FontData courier("Courier New");
    EXPECT_EQ(courier.font_name(), "Courier New");
}

// ---------------------------------------------------------------------------
// get_font_name(theme) — ignores theme, returns stored name
// ---------------------------------------------------------------------------

TEST_F(FontDataTest, GetFontNameIgnoresTheme) {
    EXPECT_EQ(fd.get_font_name(nullptr), "Arial");
}

TEST_F(FontDataTest, GetFontNameMatchesFontName) {
    EXPECT_EQ(fd.get_font_name(nullptr), fd.font_name());
}

// ---------------------------------------------------------------------------
// set_font_name round-trip
// ---------------------------------------------------------------------------

TEST_F(FontDataTest, SetFontNameRoundTrip) {
    fd.set_font_name("Times New Roman");
    EXPECT_EQ(fd.font_name(), "Times New Roman");
    EXPECT_EQ(fd.get_font_name(nullptr), "Times New Roman");
}

// ---------------------------------------------------------------------------
// Equality operator
// ---------------------------------------------------------------------------

TEST_F(FontDataTest, EqualWhenSameName) {
    FontData other("Arial");
    EXPECT_EQ(fd, other);
}

TEST_F(FontDataTest, NotEqualWhenDifferentName) {
    FontData other("Courier New");
    EXPECT_NE(fd, other);
}

// ---------------------------------------------------------------------------
// Stream insertion operator
// ---------------------------------------------------------------------------

TEST_F(FontDataTest, StreamOutput) {
    std::ostringstream os;
    os << fd;
    EXPECT_EQ(os.str(), "FontData(\"Arial\")");
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

TEST(FontDataStandaloneTest, LatinFontNamePersists) {
    FontData courier("Courier New");
    EXPECT_EQ(courier.font_name(), "Courier New");
}

// ---------------------------------------------------------------------------
// IFontData interface — FontData satisfies the abstract contract
// ---------------------------------------------------------------------------

TEST(IFontDataInterfaceTest, FontDataSatisfiesIFontData) {
    auto fd = std::make_unique<FontData>("Verdana");
    IFontData* iface = fd.get();

    EXPECT_EQ(iface->font_name(), "Verdana");
    EXPECT_EQ(iface->get_font_name(nullptr), "Verdana");
}

TEST(IFontDataInterfaceTest, SetFontNameThroughInterface) {
    auto fd = std::make_unique<FontData>("Arial");
    IFontData* iface = fd.get();

    iface->set_font_name("Courier New");
    EXPECT_EQ(iface->font_name(), "Courier New");
    EXPECT_EQ(iface->get_font_name(nullptr), "Courier New");
}
