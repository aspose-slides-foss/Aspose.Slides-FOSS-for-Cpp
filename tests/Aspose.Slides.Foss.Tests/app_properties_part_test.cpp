// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/pptx/app_properties_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Minimal valid docProps/app.xml for testing.
static const std::string kSampleAppXml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <Application>Microsoft Office PowerPoint</Application>
  <AppVersion>16.0000</AppVersion>
  <Company>ACME Corp</Company>
  <Manager>Jane Doe</Manager>
  <PresentationFormat>On-screen Show (4:3)</PresentationFormat>
  <Template>blank</Template>
  <HyperlinkBase>https://example.com</HyperlinkBase>
  <TotalTime>42</TotalTime>
  <Slides>10</Slides>
  <HiddenSlides>2</HiddenSlides>
  <Notes>5</Notes>
  <Paragraphs>100</Paragraphs>
  <Words>500</Words>
  <MMClips>0</MMClips>
  <ScaleCrop>false</ScaleCrop>
  <LinksUpToDate>true</LinksUpToDate>
  <SharedDoc>false</SharedDoc>
  <HyperlinksChanged>false</HyperlinksChanged>
  <HeadingPairs>
    <vt:vector size="4" baseType="variant">
      <vt:variant><vt:lpstr>Theme</vt:lpstr></vt:variant>
      <vt:variant><vt:i4>1</vt:i4></vt:variant>
      <vt:variant><vt:lpstr>Slide Titles</vt:lpstr></vt:variant>
      <vt:variant><vt:i4>10</vt:i4></vt:variant>
    </vt:vector>
  </HeadingPairs>
  <TitlesOfParts>
    <vt:vector size="3" baseType="lpstr">
      <vt:lpstr>Office Theme</vt:lpstr>
      <vt:lpstr>Introduction</vt:lpstr>
      <vt:lpstr>Summary</vt:lpstr>
    </vt:vector>
  </TitlesOfParts>
</Properties>)";

class AppPropertiesPartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_app_xml(const std::string& xml) {
        package_.set_part("docProps/app.xml", xml);
    }
};

// ---------------------------------------------------------------------------
// Parsing tests
// ---------------------------------------------------------------------------

TEST_F(AppPropertiesPartTest, ParseStringProperties) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);

    EXPECT_EQ(part.application, "Microsoft Office PowerPoint");
    EXPECT_EQ(part.app_version, "16.0000");
    EXPECT_EQ(part.company, "ACME Corp");
    EXPECT_EQ(part.manager, "Jane Doe");
    EXPECT_EQ(part.presentation_format, "On-screen Show (4:3)");
    EXPECT_EQ(part.template_name, "blank");
    EXPECT_EQ(part.hyperlink_base, "https://example.com");
}

TEST_F(AppPropertiesPartTest, ParseIntProperties) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);

    EXPECT_EQ(part.total_time, 42);
    EXPECT_EQ(part.slides, 10);
    EXPECT_EQ(part.hidden_slides, 2);
    EXPECT_EQ(part.notes, 5);
    EXPECT_EQ(part.paragraphs, 100);
    EXPECT_EQ(part.words, 500);
    EXPECT_EQ(part.mm_clips, 0);
}

TEST_F(AppPropertiesPartTest, ParseBoolProperties) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);

    EXPECT_EQ(part.scale_crop, false);
    EXPECT_EQ(part.links_up_to_date, true);
    EXPECT_EQ(part.shared_doc, false);
    EXPECT_EQ(part.hyperlinks_changed, false);
}

TEST_F(AppPropertiesPartTest, ParseHeadingPairs) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);

    ASSERT_EQ(part.heading_pairs.size(), 2u);
    EXPECT_EQ(part.heading_pairs[0].name, "Theme");
    EXPECT_EQ(part.heading_pairs[0].count, 1);
    EXPECT_EQ(part.heading_pairs[1].name, "Slide Titles");
    EXPECT_EQ(part.heading_pairs[1].count, 10);
}

TEST_F(AppPropertiesPartTest, ParseTitlesOfParts) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);

    ASSERT_EQ(part.titles_of_parts.size(), 3u);
    EXPECT_EQ(part.titles_of_parts[0], "Office Theme");
    EXPECT_EQ(part.titles_of_parts[1], "Introduction");
    EXPECT_EQ(part.titles_of_parts[2], "Summary");
}

TEST_F(AppPropertiesPartTest, MissingPartReturnsNullopt) {
    // No app.xml set in package
    pptx::AppPropertiesPart part(package_);

    EXPECT_FALSE(part.application.has_value());
    EXPECT_FALSE(part.slides.has_value());
    EXPECT_FALSE(part.scale_crop.has_value());
    EXPECT_TRUE(part.heading_pairs.empty());
    EXPECT_TRUE(part.titles_of_parts.empty());
}

// ---------------------------------------------------------------------------
// Round-trip tests
// ---------------------------------------------------------------------------

TEST_F(AppPropertiesPartTest, SaveAndReload) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);
    part.mark_dirty();
    part.save();

    // Reload from package
    pptx::AppPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.application, "Microsoft Office PowerPoint");
    EXPECT_EQ(reloaded.slides, 10);
    EXPECT_EQ(reloaded.links_up_to_date, true);
    ASSERT_EQ(reloaded.heading_pairs.size(), 2u);
    EXPECT_EQ(reloaded.heading_pairs[0].name, "Theme");
    ASSERT_EQ(reloaded.titles_of_parts.size(), 3u);
    EXPECT_EQ(reloaded.titles_of_parts[2], "Summary");
}

TEST_F(AppPropertiesPartTest, SaveNewPart) {
    // No original part — constructing and saving creates one.
    pptx::AppPropertiesPart part(package_);
    part.application = "Test App";
    part.slides = 3;
    part.scale_crop = true;
    part.heading_pairs.push_back({"Slides", 3});
    part.titles_of_parts = {"A", "B", "C"};
    part.save();

    pptx::AppPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.application, "Test App");
    EXPECT_EQ(reloaded.slides, 3);
    EXPECT_EQ(reloaded.scale_crop, true);
    ASSERT_EQ(reloaded.heading_pairs.size(), 1u);
    EXPECT_EQ(reloaded.heading_pairs[0].name, "Slides");
    EXPECT_EQ(reloaded.heading_pairs[0].count, 3);
    ASSERT_EQ(reloaded.titles_of_parts.size(), 3u);
}

TEST_F(AppPropertiesPartTest, SkipSaveWhenNotDirtyAndOriginalExists) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);
    // Modify in-memory but don't mark dirty
    part.application = "Changed";
    part.save();

    // Reload — should still be original since save was skipped
    pptx::AppPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.application, "Microsoft Office PowerPoint");
}

// ---------------------------------------------------------------------------
// clear() test
// ---------------------------------------------------------------------------

TEST_F(AppPropertiesPartTest, ClearResetsAll) {
    set_app_xml(kSampleAppXml);
    pptx::AppPropertiesPart part(package_);
    part.clear();

    EXPECT_FALSE(part.application.has_value());
    EXPECT_FALSE(part.slides.has_value());
    EXPECT_FALSE(part.scale_crop.has_value());
    EXPECT_TRUE(part.heading_pairs.empty());
    EXPECT_TRUE(part.titles_of_parts.empty());
}

// ---------------------------------------------------------------------------
// Edge cases
// ---------------------------------------------------------------------------

TEST_F(AppPropertiesPartTest, ParseInvalidIntReturnsNullopt) {
    set_app_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties">
  <Slides>not_a_number</Slides>
</Properties>)");
    pptx::AppPropertiesPart part(package_);
    EXPECT_FALSE(part.slides.has_value());
}

TEST_F(AppPropertiesPartTest, ParseBoolVariants) {
    set_app_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties">
  <ScaleCrop>1</ScaleCrop>
  <SharedDoc>false</SharedDoc>
</Properties>)");
    pptx::AppPropertiesPart part(package_);
    EXPECT_EQ(part.scale_crop, true);
    EXPECT_EQ(part.shared_doc, false);
}

TEST_F(AppPropertiesPartTest, EmptyVectorsNotWritten) {
    pptx::AppPropertiesPart part(package_);
    part.application = "Test";
    part.save();

    pptx::AppPropertiesPart reloaded(package_);
    EXPECT_TRUE(reloaded.heading_pairs.empty());
    EXPECT_TRUE(reloaded.titles_of_parts.empty());
}

TEST_F(AppPropertiesPartTest, HeadingPairDataEquality) {
    pptx::HeadingPairData a{"Slides", 5};
    pptx::HeadingPairData b{"Slides", 5};
    pptx::HeadingPairData c{"Notes", 5};
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}
