// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file harness_self_test.cpp
/// Calibration for the conformance harness.
///
/// Every assertion in `conformance.h` is proved twice here: once against a
/// package that satisfies the rule, and once against a package with exactly
/// one deliberate fault injected. An assertion that has never been shown to
/// fail is not evidence of anything, and a harness whose detectors were never
/// calibrated is how a whole sweep gets reported as "no problems found".
///
/// The packages are built here as raw ZIP members, without touching the
/// presentation API, so a change in the library cannot make these tests pass
/// or fail.

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <miniz.h>

#include "conformance/conformance.h"

namespace {

using conformance::Package;

constexpr const char* kPml =
    "application/vnd.openxmlformats-officedocument.presentationml.";

struct Member {
    std::string name;
    std::string text;
};

/// Write a .pptx from literal part text. No library involved on either side.
void write_zip(const std::filesystem::path& path,
               const std::vector<Member>& members) {
    mz_zip_archive zip{};
    ASSERT_TRUE(mz_zip_writer_init_file(&zip, path.string().c_str(), 0));
    for (const auto& m : members) {
        ASSERT_TRUE(mz_zip_writer_add_mem(&zip, m.name.c_str(), m.text.data(),
                                          m.text.size(), MZ_DEFAULT_COMPRESSION));
    }
    ASSERT_TRUE(mz_zip_writer_finalize_archive(&zip));
    mz_zip_writer_end(&zip);
}

std::string content_types(const std::string& extra_overrides,
                          bool with_png_default = true) {
    std::string out =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">)"
        R"(<Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>)"
        R"(<Default Extension="xml" ContentType="application/xml"/>)";
    if (with_png_default)
        out += R"(<Default Extension="png" ContentType="image/png"/>)";
    out += R"(<Override PartName="/ppt/slides/slide1.xml" ContentType=")";
    out += kPml;
    out += R"(slide+xml"/>)";
    out += extra_overrides;
    out += "</Types>";
    return out;
}

std::string slide_with_blip(const std::string& embed_id) {
    return
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<p:sld xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main")"
        R"( xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main")"
        R"( xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships">)"
        R"(<p:cSld><p:spTree><p:pic><p:blipFill><a:blip r:embed=")" + embed_id +
        R"("/></p:blipFill></p:pic></p:spTree></p:cSld></p:sld>)";
}

std::string slide_rels(const std::string& image_rel_id) {
    std::string out =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">)";
    if (!image_rel_id.empty()) {
        out += R"(<Relationship Id=")" + image_rel_id +
               R"(" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image")"
               R"( Target="../media/image1.png"/>)";
    }
    out += "</Relationships>";
    return out;
}

/// A package that satisfies every rule the harness checks.
std::vector<Member> good_package() {
    return {
        {"[Content_Types].xml", content_types("")},
        {"ppt/slides/slide1.xml", slide_with_blip("rId1")},
        {"ppt/slides/_rels/slide1.xml.rels", slide_rels("rId1")},
        {"ppt/media/image1.png", "not really a png, but named like one"},
    };
}

class HarnessSelfTest : public ::testing::Test {
protected:
    void SetUp() override {
        dir_ = std::filesystem::temp_directory_path() /
               ("conformance_harness_self_test_" +
                std::to_string(::testing::UnitTest::GetInstance()
                                   ->current_test_info()
                                   ->line()));
        std::filesystem::create_directories(dir_);
    }
    void TearDown() override { std::filesystem::remove_all(dir_); }

    Package build(const std::vector<Member>& members) {
        auto path = dir_ / "case.pptx";
        write_zip(path, members);
        return Package(path);
    }

    std::filesystem::path dir_;
};

// -- Package: reading ------------------------------------------------------

TEST_F(HarnessSelfTest, ListsEveryMemberAndReturnsItsBytes) {
    auto pkg = build(good_package());
    EXPECT_EQ(pkg.entry_names().size(), 4u);
    EXPECT_TRUE(pkg.has_entry("ppt/slides/slide1.xml"));
    EXPECT_FALSE(pkg.has_entry("ppt/slides/slide2.xml"));
    EXPECT_EQ(pkg.entry_text("ppt/media/image1.png"),
              "not really a png, but named like one");
    EXPECT_EQ(pkg.entries_matching(R"(^ppt/slides/slide\d+\.xml$)").size(), 1u);
}

TEST_F(HarnessSelfTest, DerivesTheRelsPartNameOfAPart) {
    EXPECT_EQ(Package::rels_part_name("ppt/slides/slide1.xml"),
              "ppt/slides/_rels/slide1.xml.rels");
    EXPECT_EQ(Package::rels_part_name("ppt/presentation.xml"),
              "ppt/_rels/presentation.xml.rels");
}

// -- Rule 1: relationship references ---------------------------------------

TEST_F(HarnessSelfTest, AcceptsAPackageWhoseEveryReferenceResolves) {
    auto pkg = build(good_package());
    EXPECT_TRUE(conformance::AllRelationshipReferencesResolve(pkg));
}

TEST_F(HarnessSelfTest, RejectsABlipPointingAtAMissingRelationship) {
    auto members = good_package();
    members[1].text = slide_with_blip("rId2"); // only rId1 is declared
    auto pkg = build(members);
    EXPECT_FALSE(conformance::AllRelationshipReferencesResolve(pkg));
}

TEST_F(HarnessSelfTest, RejectsAReferenceWhenTheRelsPartIsMissingEntirely) {
    auto members = good_package();
    members.erase(members.begin() + 2);
    auto pkg = build(members);
    EXPECT_FALSE(conformance::AllRelationshipReferencesResolve(pkg));
}

// -- Rule 2: content types -------------------------------------------------

TEST_F(HarnessSelfTest, AcceptsAPackageWhereEveryPartResolvesAContentType) {
    auto pkg = build(good_package());
    EXPECT_TRUE(conformance::EveryPartHasAContentType(pkg));
    EXPECT_TRUE(conformance::PartContentTypesMatchEcma(pkg));
}

TEST_F(HarnessSelfTest, RejectsAMediaPartWithNoContentType) {
    auto members = good_package();
    members[0].text = content_types("", /*with_png_default=*/false);
    auto pkg = build(members);
    EXPECT_FALSE(conformance::EveryPartHasAContentType(pkg));
}

TEST_F(HarnessSelfTest, RejectsASlidePartThatFallsThroughToTheXmlDefault) {
    auto members = good_package();
    // Drop the slide Override: the part is then application/xml, which per
    // ISO/IEC 29500-2 means it is not a slide at all.
    members[0].text =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">)"
        R"(<Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>)"
        R"(<Default Extension="xml" ContentType="application/xml"/>)"
        R"(<Default Extension="png" ContentType="image/png"/>)"
        R"(</Types>)";
    auto pkg = build(members);
    EXPECT_TRUE(conformance::EveryPartHasAContentType(pkg))
        << "the xml Default does resolve something, which is the trap";
    EXPECT_FALSE(conformance::PartContentTypesMatchEcma(pkg));
}

TEST_F(HarnessSelfTest, RejectsAnOverrideNamingAPartThatIsNotThere) {
    auto members = good_package();
    members[0].text = content_types(
        std::string(R"(<Override PartName="/ppt/slides/slide9.xml" ContentType=")") +
        kPml + R"(slide+xml"/>)");
    auto pkg = build(members);
    EXPECT_FALSE(conformance::NoContentTypeOverrideDangles(pkg));
    EXPECT_TRUE(conformance::NoContentTypeOverrideDangles(build(good_package())));
}

// -- Element-level assertions ----------------------------------------------

TEST_F(HarnessSelfTest, FindsAnXPathAddressedElementAndChecksItsAttributes) {
    auto pkg = build(good_package());
    EXPECT_TRUE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                           "//a:blip", {{"r:embed", "rId1"}}));
    EXPECT_FALSE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                            "//a:blip", {{"r:embed", "rId7"}}));
    EXPECT_FALSE(conformance::ElementExists(pkg, "ppt/slides/slide1.xml",
                                            "//a:srgbClr"));
    EXPECT_TRUE(conformance::ElementAbsent(pkg, "ppt/slides/slide1.xml",
                                           "//a:srgbClr"));
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/slides/slide1.xml", "//a:blip"),
              1u);
}

TEST_F(HarnessSelfTest, ChecksChildOrderAndNotOnlyChildPresence) {
    auto members = good_package();
    members[1].text =
        R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)"
        R"(<p:sld xmlns:p="http://schemas.openxmlformats.org/presentationml/2006/main")"
        R"( xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main")"
        R"( xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships">)"
        R"(<a:r><a:t>text</a:t><a:rPr b="1"/></a:r></p:sld>)";
    members[2].text = slide_rels("");
    auto pkg = build(members);

    EXPECT_TRUE(conformance::ChildOrderIs(pkg, "ppt/slides/slide1.xml", "//a:r",
                                          {"a:t", "a:rPr"}))
        << "the harness reports the order that is actually written";
    EXPECT_FALSE(conformance::ChildOrderIs(pkg, "ppt/slides/slide1.xml", "//a:r",
                                           {"a:rPr", "a:t"}))
        << "a:rPr after a:t is the reversal a run-order check has to catch";
}

TEST_F(HarnessSelfTest, ReportsAMissingPartRatherThanPassingVacuously) {
    auto pkg = build(good_package());
    EXPECT_FALSE(conformance::ElementExists(pkg, "ppt/slides/slide2.xml", "//a:blip"));
    EXPECT_FALSE(conformance::ChildOrderIs(pkg, "ppt/slides/slide2.xml", "//a:r", {}));
}

// -- Fixtures --------------------------------------------------------------

TEST_F(HarnessSelfTest, TheCommittedForeignDeckIsAConsistentPackage) {
    auto fixture = conformance::test_data_dir() / "powerpoint_title_and_content.pptx";
    ASSERT_TRUE(std::filesystem::exists(fixture))
        << "missing fixture " << fixture
        << " - regenerate with tests/conformance/make_fixtures.py";
    Package pkg(fixture);
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/presentation.xml", "//p:sldId"), 1u);
    // Both placeholders carry a bare <p:spPr/>: no geometry of their own.
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/slides/slide1.xml", "//p:sp"), 2u);
    EXPECT_TRUE(conformance::ElementAbsent(pkg, "ppt/slides/slide1.xml",
                                           "//p:spPr/a:xfrm"));
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/slideLayouts/slideLayout1.xml",
                                        "//p:spPr/a:xfrm"),
              2u);
}

} // namespace
