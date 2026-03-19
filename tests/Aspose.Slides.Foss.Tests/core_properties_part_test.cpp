// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/pptx/core_properties_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Minimal valid docProps/core.xml for testing.
static const std::string kSampleCoreXml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<cp:coreProperties xmlns:cp="http://schemas.openxmlformats.org/package/2006/metadata/core-properties"
                   xmlns:dc="http://purl.org/dc/elements/1.1/"
                   xmlns:dcterms="http://purl.org/dc/terms/"
                   xmlns:dcmitype="http://purl.org/dc/dcmitype/"
                   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <dc:title>Test Presentation</dc:title>
  <dc:subject>Unit Testing</dc:subject>
  <dc:creator>John Doe</dc:creator>
  <cp:keywords>test, slides, cpp</cp:keywords>
  <dc:description>A test description</dc:description>
  <cp:category>Testing</cp:category>
  <cp:contentStatus>Draft</cp:contentStatus>
  <cp:contentType>application/pptx</cp:contentType>
  <cp:lastModifiedBy>Jane Doe</cp:lastModifiedBy>
  <cp:revision>5</cp:revision>
  <dcterms:created xsi:type="dcterms:W3CDTF">2024-01-15T10:30:00Z</dcterms:created>
  <dcterms:modified xsi:type="dcterms:W3CDTF">2024-06-20T14:00:00Z</dcterms:modified>
  <cp:lastPrinted>2024-03-01T09:15:00Z</cp:lastPrinted>
</cp:coreProperties>)";

class CorePropertiesPartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_core_xml(const std::string& xml) {
        package_.set_part("docProps/core.xml", xml);
    }
};

// ---------------------------------------------------------------------------
// Parsing tests
// ---------------------------------------------------------------------------

TEST_F(CorePropertiesPartTest, ParseStringProperties) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);

    EXPECT_EQ(part.title, "Test Presentation");
    EXPECT_EQ(part.subject, "Unit Testing");
    EXPECT_EQ(part.creator, "John Doe");
    EXPECT_EQ(part.keywords, "test, slides, cpp");
    EXPECT_EQ(part.description, "A test description");
    EXPECT_EQ(part.category, "Testing");
    EXPECT_EQ(part.content_status, "Draft");
    EXPECT_EQ(part.content_type, "application/pptx");
    EXPECT_EQ(part.last_modified_by, "Jane Doe");
    EXPECT_EQ(part.revision, "5");
}

TEST_F(CorePropertiesPartTest, ParseDateProperties) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);

    ASSERT_TRUE(part.created.has_value());
    ASSERT_TRUE(part.modified.has_value());
    ASSERT_TRUE(part.last_printed.has_value());

    // Verify round-trip through format
    EXPECT_EQ(pptx::format_w3cdtf(part.created), "2024-01-15T10:30:00Z");
    EXPECT_EQ(pptx::format_w3cdtf(part.modified), "2024-06-20T14:00:00Z");
    EXPECT_EQ(pptx::format_w3cdtf(part.last_printed), "2024-03-01T09:15:00Z");
}

TEST_F(CorePropertiesPartTest, MissingPartReturnsNullopt) {
    pptx::CorePropertiesPart part(package_);

    EXPECT_FALSE(part.title.has_value());
    EXPECT_FALSE(part.creator.has_value());
    EXPECT_FALSE(part.created.has_value());
    EXPECT_FALSE(part.modified.has_value());
    EXPECT_FALSE(part.last_printed.has_value());
}

// ---------------------------------------------------------------------------
// W3CDTF parsing edge cases
// ---------------------------------------------------------------------------

TEST_F(CorePropertiesPartTest, ParseW3cdtfEmpty) {
    EXPECT_FALSE(pptx::parse_w3cdtf("").has_value());
    EXPECT_FALSE(pptx::parse_w3cdtf("   ").has_value());
}

TEST_F(CorePropertiesPartTest, ParseW3cdtfWithZ) {
    auto tp = pptx::parse_w3cdtf("2024-01-15T10:30:00Z");
    ASSERT_TRUE(tp.has_value());
    EXPECT_EQ(pptx::format_w3cdtf(tp), "2024-01-15T10:30:00Z");
}

TEST_F(CorePropertiesPartTest, ParseW3cdtfDateOnly) {
    auto tp = pptx::parse_w3cdtf("2024-01-15");
    ASSERT_TRUE(tp.has_value());
    EXPECT_EQ(pptx::format_w3cdtf(tp), "2024-01-15T00:00:00Z");
}

TEST_F(CorePropertiesPartTest, ParseW3cdtfInvalidReturnsNullopt) {
    EXPECT_FALSE(pptx::parse_w3cdtf("not-a-date").has_value());
}

TEST_F(CorePropertiesPartTest, FormatW3cdtfNullopt) {
    EXPECT_FALSE(pptx::format_w3cdtf(std::nullopt).has_value());
}

// ---------------------------------------------------------------------------
// Round-trip tests
// ---------------------------------------------------------------------------

TEST_F(CorePropertiesPartTest, SaveAndReload) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);
    part.mark_dirty();
    part.save();

    pptx::CorePropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.title, "Test Presentation");
    EXPECT_EQ(reloaded.creator, "John Doe");
    EXPECT_EQ(reloaded.keywords, "test, slides, cpp");
    EXPECT_EQ(reloaded.revision, "5");
    EXPECT_EQ(pptx::format_w3cdtf(reloaded.created), "2024-01-15T10:30:00Z");
    EXPECT_EQ(pptx::format_w3cdtf(reloaded.modified), "2024-06-20T14:00:00Z");
    EXPECT_EQ(pptx::format_w3cdtf(reloaded.last_printed), "2024-03-01T09:15:00Z");
}

TEST_F(CorePropertiesPartTest, SaveNewPart) {
    pptx::CorePropertiesPart part(package_);
    part.title = "New Title";
    part.creator = "Author";
    part.created = pptx::parse_w3cdtf("2025-01-01T00:00:00Z");
    part.save();

    pptx::CorePropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.title, "New Title");
    EXPECT_EQ(reloaded.creator, "Author");
    EXPECT_EQ(pptx::format_w3cdtf(reloaded.created), "2025-01-01T00:00:00Z");
}

TEST_F(CorePropertiesPartTest, SkipSaveWhenNotDirtyAndOriginalExists) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);
    part.title = "Changed";
    part.save();

    pptx::CorePropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.title, "Test Presentation");
}

// ---------------------------------------------------------------------------
// clear() test
// ---------------------------------------------------------------------------

TEST_F(CorePropertiesPartTest, ClearResetsAll) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);
    part.clear();

    EXPECT_FALSE(part.title.has_value());
    EXPECT_FALSE(part.subject.has_value());
    EXPECT_FALSE(part.creator.has_value());
    EXPECT_FALSE(part.keywords.has_value());
    EXPECT_FALSE(part.description.has_value());
    EXPECT_FALSE(part.category.has_value());
    EXPECT_FALSE(part.content_status.has_value());
    EXPECT_FALSE(part.content_type.has_value());
    EXPECT_FALSE(part.last_modified_by.has_value());
    EXPECT_FALSE(part.revision.has_value());
    EXPECT_FALSE(part.created.has_value());
    EXPECT_FALSE(part.modified.has_value());
    EXPECT_FALSE(part.last_printed.has_value());
}

TEST_F(CorePropertiesPartTest, ClearAndSaveProducesEmptyProperties) {
    set_core_xml(kSampleCoreXml);
    pptx::CorePropertiesPart part(package_);
    part.clear();
    part.save();

    pptx::CorePropertiesPart reloaded(package_);
    EXPECT_FALSE(reloaded.title.has_value());
    EXPECT_FALSE(reloaded.created.has_value());
}

// ---------------------------------------------------------------------------
// Partial XML
// ---------------------------------------------------------------------------

TEST_F(CorePropertiesPartTest, ParsePartialXml) {
    set_core_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<cp:coreProperties xmlns:cp="http://schemas.openxmlformats.org/package/2006/metadata/core-properties"
                   xmlns:dc="http://purl.org/dc/elements/1.1/">
  <dc:title>Only Title</dc:title>
</cp:coreProperties>)");
    pptx::CorePropertiesPart part(package_);

    EXPECT_EQ(part.title, "Only Title");
    EXPECT_FALSE(part.creator.has_value());
    EXPECT_FALSE(part.created.has_value());
}
