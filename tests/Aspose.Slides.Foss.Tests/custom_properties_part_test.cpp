// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/custom_properties_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Sample custom.xml with various typed properties.
static const std::string kSampleCustomXml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/custom-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="2" name="Author">
    <vt:lpwstr>Alice</vt:lpwstr>
  </property>
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="3" name="Version">
    <vt:i4>42</vt:i4>
  </property>
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="4" name="Score">
    <vt:r8>3.14</vt:r8>
  </property>
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="5" name="Published">
    <vt:bool>true</vt:bool>
  </property>
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="6" name="Date">
    <vt:filetime>2024-06-15T12:00:00Z</vt:filetime>
  </property>
</Properties>)";

class CustomPropertiesPartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_custom_xml(const std::string& xml) {
        package_.set_part("docProps/custom.xml", xml);
    }
};

// ---------------------------------------------------------------------------
// Parsing tests
// ---------------------------------------------------------------------------

TEST_F(CustomPropertiesPartTest, ParseAllTypes) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    EXPECT_EQ(part.count(), 5);
    EXPECT_TRUE(part.contains("Author"));
    EXPECT_TRUE(part.contains("Version"));
    EXPECT_TRUE(part.contains("Score"));
    EXPECT_TRUE(part.contains("Published"));
    EXPECT_TRUE(part.contains("Date"));
}

TEST_F(CustomPropertiesPartTest, ParseStringValue) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Author");
    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(std::holds_alternative<std::string>(*val));
    EXPECT_EQ(std::get<std::string>(*val), "Alice");
}

TEST_F(CustomPropertiesPartTest, ParseIntValue) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Version");
    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(std::holds_alternative<int32_t>(*val));
    EXPECT_EQ(std::get<int32_t>(*val), 42);
}

TEST_F(CustomPropertiesPartTest, ParseDoubleValue) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Score");
    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(std::holds_alternative<double>(*val));
    EXPECT_DOUBLE_EQ(std::get<double>(*val), 3.14);
}

TEST_F(CustomPropertiesPartTest, ParseBoolValue) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Published");
    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(std::holds_alternative<bool>(*val));
    EXPECT_TRUE(std::get<bool>(*val));
}

TEST_F(CustomPropertiesPartTest, ParseFiletimeValue) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Date");
    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(std::holds_alternative<pptx::CustomTimePoint>(*val));
}

TEST_F(CustomPropertiesPartTest, MissingPartReturnsEmpty) {
    pptx::CustomPropertiesPart part(package_);
    EXPECT_EQ(part.count(), 0);
    EXPECT_FALSE(part.contains("anything"));
}

TEST_F(CustomPropertiesPartTest, GetValueMissing) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);
    EXPECT_FALSE(part.get_value("NonExistent").has_value());
}

// ---------------------------------------------------------------------------
// get_name tests
// ---------------------------------------------------------------------------

TEST_F(CustomPropertiesPartTest, GetNameByIndex) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    EXPECT_EQ(part.get_name(0), "Author");
    EXPECT_EQ(part.get_name(1), "Version");
    EXPECT_EQ(part.get_name(4), "Date");
}

TEST_F(CustomPropertiesPartTest, GetNameOutOfRange) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    EXPECT_THROW(part.get_name(-1), std::out_of_range);
    EXPECT_THROW(part.get_name(5), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Mutation tests
// ---------------------------------------------------------------------------

TEST_F(CustomPropertiesPartTest, SetNewValue) {
    pptx::CustomPropertiesPart part(package_);
    part.set_value("Key", pptx::CustomPropertyValue{std::string("Value")});

    EXPECT_EQ(part.count(), 1);
    EXPECT_TRUE(part.contains("Key"));
    auto val = part.get_value("Key");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(std::get<std::string>(*val), "Value");
}

TEST_F(CustomPropertiesPartTest, SetOverwritesExisting) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    part.set_value("Author", pptx::CustomPropertyValue{std::string("Bob")});
    EXPECT_EQ(part.count(), 5);  // No new entry
    auto val = part.get_value("Author");
    EXPECT_EQ(std::get<std::string>(*val), "Bob");
}

TEST_F(CustomPropertiesPartTest, RemoveExisting) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    EXPECT_TRUE(part.remove("Author"));
    EXPECT_EQ(part.count(), 4);
    EXPECT_FALSE(part.contains("Author"));
}

TEST_F(CustomPropertiesPartTest, RemoveNonExistent) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    EXPECT_FALSE(part.remove("NonExistent"));
    EXPECT_EQ(part.count(), 5);
}

TEST_F(CustomPropertiesPartTest, ClearAll) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);

    part.clear();
    EXPECT_EQ(part.count(), 0);
}

TEST_F(CustomPropertiesPartTest, ClearEmptyIsNoop) {
    pptx::CustomPropertiesPart part(package_);
    part.clear();  // Should not crash or set dirty.
    EXPECT_EQ(part.count(), 0);
}

// ---------------------------------------------------------------------------
// Save / round-trip tests
// ---------------------------------------------------------------------------

TEST_F(CustomPropertiesPartTest, SaveAndReload) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);
    part.set_value("NewProp", pptx::CustomPropertyValue{int32_t{99}});
    part.save();

    pptx::CustomPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.count(), 6);
    EXPECT_EQ(std::get<std::string>(*reloaded.get_value("Author")), "Alice");
    EXPECT_EQ(std::get<int32_t>(*reloaded.get_value("Version")), 42);
    EXPECT_EQ(std::get<int32_t>(*reloaded.get_value("NewProp")), 99);
}

TEST_F(CustomPropertiesPartTest, SaveNewPart) {
    pptx::CustomPropertiesPart part(package_);
    part.set_value("Greeting", pptx::CustomPropertyValue{std::string("Hello")});
    part.set_value("Count", pptx::CustomPropertyValue{int32_t{7}});
    part.set_value("Ratio", pptx::CustomPropertyValue{2.5});
    part.set_value("Active", pptx::CustomPropertyValue{true});
    part.save();

    pptx::CustomPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.count(), 4);
    EXPECT_EQ(std::get<std::string>(*reloaded.get_value("Greeting")), "Hello");
    EXPECT_EQ(std::get<int32_t>(*reloaded.get_value("Count")), 7);
    EXPECT_DOUBLE_EQ(std::get<double>(*reloaded.get_value("Ratio")), 2.5);
    EXPECT_TRUE(std::get<bool>(*reloaded.get_value("Active")));
}

TEST_F(CustomPropertiesPartTest, SaveDeletesPartWhenEmpty) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);
    part.clear();
    part.save();

    EXPECT_FALSE(package_.has_part("docProps/custom.xml"));
}

TEST_F(CustomPropertiesPartTest, SkipSaveWhenNotDirty) {
    set_custom_xml(kSampleCustomXml);
    pptx::CustomPropertiesPart part(package_);
    // Not dirty, save should be a no-op.
    part.save();

    pptx::CustomPropertiesPart reloaded(package_);
    EXPECT_EQ(reloaded.count(), 5);
}

TEST_F(CustomPropertiesPartTest, SaveEnsuresContentType) {
    pptx::CustomPropertiesPart part(package_);
    part.set_value("Key", pptx::CustomPropertyValue{std::string("Val")});
    part.save();

    opc::ContentTypesManager ct_mgr(package_);
    EXPECT_FALSE(ct_mgr.get_content_type("docProps/custom.xml").empty());
}

TEST_F(CustomPropertiesPartTest, SaveEnsuresRelationship) {
    pptx::CustomPropertiesPart part(package_);
    part.set_value("Key", pptx::CustomPropertyValue{std::string("Val")});
    part.save();

    opc::RelationshipsManager rels_mgr(package_);
    auto rels = rels_mgr.get_relationships_by_type(
        opc::rel_types::kCustomProperties);
    EXPECT_EQ(rels.size(), 1u);
    EXPECT_EQ(rels[0].target, "docProps/custom.xml");
}

// ---------------------------------------------------------------------------
// Edge cases in parsing
// ---------------------------------------------------------------------------

TEST_F(CustomPropertiesPartTest, ParseBoolFalse) {
    set_custom_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/custom-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="2" name="Flag">
    <vt:bool>false</vt:bool>
  </property>
</Properties>)");
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Flag");
    ASSERT_TRUE(val.has_value());
    EXPECT_FALSE(std::get<bool>(*val));
}

TEST_F(CustomPropertiesPartTest, ParseInvalidIntDefaultsToZero) {
    set_custom_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/custom-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="2" name="Bad">
    <vt:i4>not_a_number</vt:i4>
  </property>
</Properties>)");
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Bad");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(std::get<int32_t>(*val), 0);
}

TEST_F(CustomPropertiesPartTest, ParseInvalidDoubleDefaultsToZero) {
    set_custom_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/custom-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="2" name="Bad">
    <vt:r8>not_a_number</vt:r8>
  </property>
</Properties>)");
    pptx::CustomPropertiesPart part(package_);

    auto val = part.get_value("Bad");
    ASSERT_TRUE(val.has_value());
    EXPECT_DOUBLE_EQ(std::get<double>(*val), 0.0);
}

TEST_F(CustomPropertiesPartTest, SkipPropertyWithNoName) {
    set_custom_xml(R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/custom-properties"
            xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" pid="2">
    <vt:lpwstr>orphan</vt:lpwstr>
  </property>
</Properties>)");
    pptx::CustomPropertiesPart part(package_);
    EXPECT_EQ(part.count(), 0);
}
