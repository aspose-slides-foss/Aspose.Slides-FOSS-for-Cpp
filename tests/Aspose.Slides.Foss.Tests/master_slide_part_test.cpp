// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/master_slide_part.h>

namespace pptx = Aspose::Slides::Foss::Internal::pptx;
namespace opc = Aspose::Slides::Foss::Internal::opc;

// Minimal valid slideMaster XML for testing.
static const std::string kSampleMasterXml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:sldMaster xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main"
             xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
             xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cSld name="TestMaster">
    <p:spTree>
      <p:nvGrpSpPr/>
    </p:spTree>
  </p:cSld>
</p:sldMaster>)";

static const std::string kMasterXmlNoName = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:sldMaster xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
  <p:cSld>
    <p:spTree/>
  </p:cSld>
</p:sldMaster>)";

static const std::string kMasterXmlNoCsld = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<p:sldMaster xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main">
</p:sldMaster>)";

// Relationships XML for a master slide with two layouts.
static const std::string kMasterRels = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/slideLayout" Target="../slideLayouts/slideLayout1.xml"/>
  <Relationship Id="rId2" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/slideLayout" Target="../slideLayouts/slideLayout2.xml"/>
  <Relationship Id="rId3" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme" Target="../theme/theme1.xml"/>
</Relationships>)";

class MasterSlidePartTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();

    void set_master_xml(const std::string& part_name, const std::string& xml) {
        package_.set_part(part_name, xml);
    }

    void set_master_rels(const std::string& part_name,
                         const std::string& rels_xml) {
        auto rels_part = opc::RelationshipsManager::get_rels_part_name(part_name);
        package_.set_part(rels_part, rels_xml);
    }
};

// ---------------------------------------------------------------------------
// Construction tests
// ---------------------------------------------------------------------------

TEST_F(MasterSlidePartTest, ConstructFromValidPart) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    EXPECT_EQ(part.part_name(), "ppt/slideMasters/slideMaster1.xml");
}

TEST_F(MasterSlidePartTest, ThrowsWhenPartNotFound) {
    EXPECT_THROW(
        pptx::MasterSlidePart(package_, "ppt/slideMasters/missing.xml"),
        std::runtime_error);
}

// ---------------------------------------------------------------------------
// Name property tests
// ---------------------------------------------------------------------------

TEST_F(MasterSlidePartTest, GetName) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    EXPECT_EQ(part.name(), "TestMaster");
}

TEST_F(MasterSlidePartTest, GetNameWhenNoNameAttribute) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kMasterXmlNoName);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    EXPECT_EQ(part.name(), "");
}

TEST_F(MasterSlidePartTest, GetNameWhenNoCsld) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kMasterXmlNoCsld);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    EXPECT_EQ(part.name(), "");
}

TEST_F(MasterSlidePartTest, SetName) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    part.set_name("NewName");
    EXPECT_EQ(part.name(), "NewName");
}

// ---------------------------------------------------------------------------
// Layout part names tests
// ---------------------------------------------------------------------------

TEST_F(MasterSlidePartTest, LayoutPartNames) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    set_master_rels("ppt/slideMasters/slideMaster1.xml", kMasterRels);

    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    auto layouts = part.layout_part_names();

    EXPECT_EQ(layouts.size(), 2u);
    // Relative paths "../slideLayouts/slideLayoutN.xml" resolve to
    // "ppt/slideLayouts/slideLayoutN.xml"
    EXPECT_TRUE(std::find(layouts.begin(), layouts.end(),
                          "ppt/slideLayouts/slideLayout1.xml") != layouts.end());
    EXPECT_TRUE(std::find(layouts.begin(), layouts.end(),
                          "ppt/slideLayouts/slideLayout2.xml") != layouts.end());
}

TEST_F(MasterSlidePartTest, LayoutPartNamesEmpty) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    auto layouts = part.layout_part_names();
    EXPECT_TRUE(layouts.empty());
}

// ---------------------------------------------------------------------------
// Target resolution tests
// ---------------------------------------------------------------------------

TEST_F(MasterSlidePartTest, ResolveAbsoluteTarget) {
    // Use rels with an absolute target
    std::string rels_xml = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/slideLayout" Target="/ppt/slideLayouts/slideLayout1.xml"/>
</Relationships>)";

    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    set_master_rels("ppt/slideMasters/slideMaster1.xml", rels_xml);

    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    auto layouts = part.layout_part_names();

    ASSERT_EQ(layouts.size(), 1u);
    EXPECT_EQ(layouts[0], "ppt/slideLayouts/slideLayout1.xml");
}

// ---------------------------------------------------------------------------
// Save / round-trip tests
// ---------------------------------------------------------------------------

TEST_F(MasterSlidePartTest, SaveAndReload) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    part.set_name("UpdatedName");
    part.save();

    pptx::MasterSlidePart reloaded(package_, "ppt/slideMasters/slideMaster1.xml");
    EXPECT_EQ(reloaded.name(), "UpdatedName");
}

TEST_F(MasterSlidePartTest, SavePreservesRelationships) {
    set_master_xml("ppt/slideMasters/slideMaster1.xml", kSampleMasterXml);
    set_master_rels("ppt/slideMasters/slideMaster1.xml", kMasterRels);

    pptx::MasterSlidePart part(package_, "ppt/slideMasters/slideMaster1.xml");
    part.save();

    pptx::MasterSlidePart reloaded(package_, "ppt/slideMasters/slideMaster1.xml");
    auto layouts = reloaded.layout_part_names();
    EXPECT_EQ(layouts.size(), 2u);
}
