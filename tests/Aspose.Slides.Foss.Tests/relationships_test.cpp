// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file relationships_test.cpp
/// @brief Tests for OPC relationships management.

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace opc = Aspose::Slides::Foss::Internal::opc;

// ---------------------------------------------------------------------------
// Relationship struct tests
// ---------------------------------------------------------------------------

TEST(RelationshipTest, DefaultTargetModeIsNullopt) {
    opc::Relationship rel;
    rel.id = "rId1";
    rel.type = "http://example.com/type";
    rel.target = "target.xml";
    EXPECT_FALSE(rel.target_mode.has_value());
}

TEST(RelationshipTest, Equality) {
    opc::Relationship a{"rId1", "type", "target", std::nullopt};
    opc::Relationship b{"rId1", "type", "target", std::nullopt};
    EXPECT_EQ(a, b);

    opc::Relationship c{"rId2", "type", "target", std::nullopt};
    EXPECT_NE(a, c);
}

// ---------------------------------------------------------------------------
// Constants tests
// ---------------------------------------------------------------------------

TEST(RelationshipsConstantsTest, RelsNamespace) {
    EXPECT_EQ(opc::kRelsNamespace,
              "http://schemas.openxmlformats.org/package/2006/relationships");
}

TEST(RelationshipsConstantsTest, RelTypesExist) {
    EXPECT_FALSE(opc::rel_types::kOfficeDocument.empty());
    EXPECT_FALSE(opc::rel_types::kSlide.empty());
    EXPECT_FALSE(opc::rel_types::kSlideLayout.empty());
    EXPECT_FALSE(opc::rel_types::kSlideMaster.empty());
    EXPECT_FALSE(opc::rel_types::kNotesSlide.empty());
    EXPECT_FALSE(opc::rel_types::kNotesMaster.empty());
    EXPECT_FALSE(opc::rel_types::kHandoutMaster.empty());
    EXPECT_FALSE(opc::rel_types::kTheme.empty());
    EXPECT_FALSE(opc::rel_types::kCoreProperties.empty());
    EXPECT_FALSE(opc::rel_types::kExtendedProperties.empty());
    EXPECT_FALSE(opc::rel_types::kThumbnail.empty());
    EXPECT_FALSE(opc::rel_types::kImage.empty());
    EXPECT_FALSE(opc::rel_types::kHyperlink.empty());
    EXPECT_FALSE(opc::rel_types::kChart.empty());
    EXPECT_FALSE(opc::rel_types::kOleObject.empty());
    EXPECT_FALSE(opc::rel_types::kPackage.empty());
    EXPECT_FALSE(opc::rel_types::kAudio.empty());
    EXPECT_FALSE(opc::rel_types::kVideo.empty());
    EXPECT_FALSE(opc::rel_types::kComments.empty());
    EXPECT_FALSE(opc::rel_types::kCommentAuthors.empty());
}

// ---------------------------------------------------------------------------
// RelationshipsManager::get_rels_part_name tests
// ---------------------------------------------------------------------------

TEST(RelsPartNameTest, GetRelsPartNameRoot) {
    EXPECT_EQ(opc::RelationshipsManager::get_rels_part_name(""), "_rels/.rels");
}

TEST(RelsPartNameTest, GetRelsPartNameTopLevel) {
    EXPECT_EQ(opc::RelationshipsManager::get_rels_part_name("file.xml"),
              "_rels/file.xml.rels");
}

TEST(RelsPartNameTest, GetRelsPartNameNested) {
    EXPECT_EQ(
        opc::RelationshipsManager::get_rels_part_name("ppt/presentation.xml"),
        "ppt/_rels/presentation.xml.rels");
}

TEST(RelsPartNameTest, GetRelsPartNameDeepNested) {
    EXPECT_EQ(
        opc::RelationshipsManager::get_rels_part_name("ppt/slides/slide1.xml"),
        "ppt/slides/_rels/slide1.xml.rels");
}

// ---------------------------------------------------------------------------
// RelationshipsManager CRUD tests
// ---------------------------------------------------------------------------

class RelationshipsManagerTest : public ::testing::Test {
protected:
    opc::InMemoryOpcPackage package_ = opc::InMemoryOpcPackage::create_new();
};

TEST_F(RelationshipsManagerTest, EmptyManagerHasNoRelationships) {
    opc::RelationshipsManager mgr(package_);
    EXPECT_TRUE(mgr.get_all_relationships().empty());
}

TEST_F(RelationshipsManagerTest, AddRelationshipAutoId) {
    opc::RelationshipsManager mgr(package_);
    auto id = mgr.add_relationship(
        std::string(opc::rel_types::kSlide), "slides/slide1.xml");
    EXPECT_EQ(id, "rId1");

    auto rel = mgr.get_relationship("rId1");
    ASSERT_TRUE(rel.has_value());
    EXPECT_EQ(rel->type, opc::rel_types::kSlide);
    EXPECT_EQ(rel->target, "slides/slide1.xml");
    EXPECT_FALSE(rel->target_mode.has_value());
}

TEST_F(RelationshipsManagerTest, AddRelationshipExplicitId) {
    opc::RelationshipsManager mgr(package_);
    auto id = mgr.add_relationship(
        std::string(opc::rel_types::kSlide), "slides/slide1.xml", "rId42");
    EXPECT_EQ(id, "rId42");

    auto rel = mgr.get_relationship("rId42");
    ASSERT_TRUE(rel.has_value());
    EXPECT_EQ(rel->id, "rId42");
}

TEST_F(RelationshipsManagerTest, AddRelationshipWithTargetMode) {
    opc::RelationshipsManager mgr(package_);
    mgr.add_relationship(
        std::string(opc::rel_types::kHyperlink),
        "https://example.com", "", "External");
    auto rels = mgr.get_all_relationships();
    ASSERT_EQ(rels.size(), 1u);
    ASSERT_TRUE(rels[0].target_mode.has_value());
    EXPECT_EQ(*rels[0].target_mode, "External");
}

TEST_F(RelationshipsManagerTest, GetRelationshipNotFound) {
    opc::RelationshipsManager mgr(package_);
    EXPECT_FALSE(mgr.get_relationship("rId999").has_value());
}

TEST_F(RelationshipsManagerTest, GetRelationshipsByType) {
    opc::RelationshipsManager mgr(package_);
    mgr.add_relationship(std::string(opc::rel_types::kSlide), "slides/slide1.xml");
    mgr.add_relationship(std::string(opc::rel_types::kImage), "media/image1.png");
    mgr.add_relationship(std::string(opc::rel_types::kSlide), "slides/slide2.xml");

    auto slides = mgr.get_relationships_by_type(opc::rel_types::kSlide);
    EXPECT_EQ(slides.size(), 2u);

    auto images = mgr.get_relationships_by_type(opc::rel_types::kImage);
    EXPECT_EQ(images.size(), 1u);
}

TEST_F(RelationshipsManagerTest, RemoveRelationship) {
    opc::RelationshipsManager mgr(package_);
    mgr.add_relationship(std::string(opc::rel_types::kSlide), "slides/slide1.xml");
    EXPECT_TRUE(mgr.remove_relationship("rId1"));
    EXPECT_TRUE(mgr.get_all_relationships().empty());
}

TEST_F(RelationshipsManagerTest, RemoveNonExistentReturnsFalse) {
    opc::RelationshipsManager mgr(package_);
    EXPECT_FALSE(mgr.remove_relationship("rId999"));
}

TEST_F(RelationshipsManagerTest, GenerateRelIdFillsGaps) {
    opc::RelationshipsManager mgr(package_);
    mgr.add_relationship(std::string(opc::rel_types::kSlide), "a.xml", "rId1");
    mgr.add_relationship(std::string(opc::rel_types::kSlide), "b.xml", "rId3");
    // rId2 is free, so auto-generation should pick it
    auto id = mgr.add_relationship(std::string(opc::rel_types::kSlide), "c.xml");
    EXPECT_EQ(id, "rId2");
}

TEST_F(RelationshipsManagerTest, PartName) {
    opc::RelationshipsManager root_mgr(package_);
    EXPECT_EQ(root_mgr.part_name(), "_rels/.rels");

    opc::RelationshipsManager part_mgr(package_, "ppt/presentation.xml");
    EXPECT_EQ(part_mgr.part_name(), "ppt/_rels/presentation.xml.rels");
}

// ---------------------------------------------------------------------------
// Save and reload round-trip tests
// ---------------------------------------------------------------------------

TEST_F(RelationshipsManagerTest, SaveAndReload) {
    {
        opc::RelationshipsManager mgr(package_);
        mgr.add_relationship(
            std::string(opc::rel_types::kOfficeDocument),
            "ppt/presentation.xml");
        mgr.save();
    }

    // Reload from the same package
    opc::RelationshipsManager mgr2(package_);
    auto rels = mgr2.get_all_relationships();
    ASSERT_EQ(rels.size(), 1u);
    EXPECT_EQ(rels[0].id, "rId1");
    EXPECT_EQ(rels[0].type, opc::rel_types::kOfficeDocument);
    EXPECT_EQ(rels[0].target, "ppt/presentation.xml");
}

TEST_F(RelationshipsManagerTest, SaveExternalTargetMode) {
    {
        opc::RelationshipsManager mgr(package_);
        mgr.add_relationship(
            std::string(opc::rel_types::kHyperlink),
            "https://example.com", "", "External");
        mgr.save();
    }

    opc::RelationshipsManager mgr2(package_);
    auto rel = mgr2.get_relationship("rId1");
    ASSERT_TRUE(rel.has_value());
    ASSERT_TRUE(rel->target_mode.has_value());
    EXPECT_EQ(*rel->target_mode, "External");
}

TEST_F(RelationshipsManagerTest, SaveEmptyDeletesPart) {
    // First save a relationship
    {
        opc::RelationshipsManager mgr(package_);
        mgr.add_relationship(std::string(opc::rel_types::kSlide), "s.xml");
        mgr.save();
    }
    EXPECT_TRUE(package_.has_part("_rels/.rels"));

    // Remove all and save -> part should be deleted
    {
        opc::RelationshipsManager mgr(package_);
        mgr.remove_relationship("rId1");
        mgr.save();
    }
    EXPECT_FALSE(package_.has_part("_rels/.rels"));
}

TEST_F(RelationshipsManagerTest, LoadExistingRels) {
    // Manually put a .rels XML into the package
    std::string xml =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">)"
        R"(  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/slide" Target="slides/slide1.xml"/>)"
        R"(  <Relationship Id="rId2" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="https://example.com" TargetMode="External"/>)"
        R"(</Relationships>)";
    package_.set_part("_rels/.rels", std::string_view(xml));

    opc::RelationshipsManager mgr(package_);
    EXPECT_EQ(mgr.get_all_relationships().size(), 2u);

    auto r1 = mgr.get_relationship("rId1");
    ASSERT_TRUE(r1.has_value());
    EXPECT_EQ(r1->target, "slides/slide1.xml");
    EXPECT_FALSE(r1->target_mode.has_value());

    auto r2 = mgr.get_relationship("rId2");
    ASSERT_TRUE(r2.has_value());
    EXPECT_EQ(r2->target, "https://example.com");
    ASSERT_TRUE(r2->target_mode.has_value());
    EXPECT_EQ(*r2->target_mode, "External");
}

TEST_F(RelationshipsManagerTest, MultiplePartsIndependent) {
    opc::RelationshipsManager root_mgr(package_);
    root_mgr.add_relationship(
        std::string(opc::rel_types::kOfficeDocument), "ppt/presentation.xml");
    root_mgr.save();

    opc::RelationshipsManager pres_mgr(package_, "ppt/presentation.xml");
    pres_mgr.add_relationship(std::string(opc::rel_types::kSlide), "slides/slide1.xml");
    pres_mgr.save();

    // Each has exactly one relationship
    opc::RelationshipsManager root_reload(package_);
    EXPECT_EQ(root_reload.get_all_relationships().size(), 1u);

    opc::RelationshipsManager pres_reload(package_, "ppt/presentation.xml");
    EXPECT_EQ(pres_reload.get_all_relationships().size(), 1u);
}
