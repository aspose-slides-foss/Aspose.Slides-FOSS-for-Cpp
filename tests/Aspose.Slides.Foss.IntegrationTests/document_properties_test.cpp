// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file document_properties_test.cpp
/// Integration tests for DocumentProperties: core + custom properties.

#include <any>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/document_properties.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class DocumentPropertiesIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("doc_props_integration_test_" +
                    std::to_string(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()));
        std::filesystem::create_directories(tmp_dir_);
    }

    void TearDown() override {
        std::filesystem::remove_all(tmp_dir_);
    }

    /// Saves a presentation to a temp file and reopens from that file.
    Presentation save_and_reopen(Presentation& pres) {
        auto path = (tmp_dir_ / "roundtrip.pptx").string();
        pres.save(path, static_cast<int>(SaveFormat::PPTX));
        return Presentation(path);
    }

    std::filesystem::path tmp_dir_;
};

// -------------------------------------------------------------------------
// Core properties persist after save/reload.
// -------------------------------------------------------------------------
TEST_F(DocumentPropertiesIntegrationTest, CorePropertiesPersist) {
    Presentation pres;
    auto& props = pres.document_properties();
    props.set_title("My Presentation");
    props.set_subject("Demo Subject");
    props.set_author("John Doe");
    props.set_keywords("demo, test");
    props.set_category("Examples");

    auto pres2 = save_and_reopen(pres);
    auto& p2 = pres2.document_properties();
    EXPECT_EQ(p2.title(), "My Presentation");
    EXPECT_EQ(p2.subject(), "Demo Subject");
    EXPECT_EQ(p2.author(), "John Doe");
    EXPECT_EQ(p2.keywords(), "demo, test");
    EXPECT_EQ(p2.category(), "Examples");
}

// -------------------------------------------------------------------------
// Custom string properties persist.
// -------------------------------------------------------------------------
TEST_F(DocumentPropertiesIntegrationTest, CustomStringPropertyPersists) {
    Presentation pres;
    pres.document_properties().set_custom_property_value(
        "MyProp", std::any(std::string("hello")));

    auto pres2 = save_and_reopen(pres);
    std::any out;
    bool found = pres2.document_properties().get_custom_property_value("MyProp", out);
    ASSERT_TRUE(found);
    ASSERT_TRUE(out.has_value());
    EXPECT_EQ(std::any_cast<std::string>(out), "hello");
}

// -------------------------------------------------------------------------
// Custom integer properties persist.
// -------------------------------------------------------------------------
TEST_F(DocumentPropertiesIntegrationTest, CustomIntPropertyPersists) {
    Presentation pres;
    pres.document_properties().set_custom_property_value(
        "Count", std::any(static_cast<int32_t>(42)));

    auto pres2 = save_and_reopen(pres);
    std::any out;
    bool found = pres2.document_properties().get_custom_property_value("Count", out);
    ASSERT_TRUE(found);
    ASSERT_TRUE(out.has_value());
    EXPECT_EQ(std::any_cast<int32_t>(out), 42);
}

// -------------------------------------------------------------------------
// Removing a custom property decreases count.
// -------------------------------------------------------------------------
TEST(DocumentPropertiesIntegrationTestNoFixture, RemoveCustomProperty) {
    Presentation pres;
    auto& props = pres.document_properties();
    props.set_custom_property_value("A", std::any(std::string("val")));
    props.set_custom_property_value("B", std::any(std::string("val")));
    EXPECT_EQ(props.count_of_custom_properties(), 2);

    props.remove_custom_property("A");
    EXPECT_EQ(props.count_of_custom_properties(), 1);
    EXPECT_FALSE(props.contains_custom_property("A"));
    EXPECT_TRUE(props.contains_custom_property("B"));
}

} // namespace
