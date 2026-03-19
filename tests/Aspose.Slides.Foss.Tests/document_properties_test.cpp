// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <any>
#include <chrono>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/document_properties.h>
#include <Aspose/Slides/Foss/heading_pair.h>
#include <Aspose/Slides/Foss/presentation.h>

using namespace Aspose::Slides::Foss;
using namespace std::chrono_literals;

// -- Core string properties --

TEST(DocumentPropertiesTest, DefaultStringPropertiesAreEmpty) {
    DocumentProperties props;
    EXPECT_EQ(props.title(), "");
    EXPECT_EQ(props.subject(), "");
    EXPECT_EQ(props.author(), "");
    EXPECT_EQ(props.keywords(), "");
    EXPECT_EQ(props.comments(), "");
    EXPECT_EQ(props.category(), "");
    EXPECT_EQ(props.content_status(), "");
    EXPECT_EQ(props.content_type(), "");
    EXPECT_EQ(props.last_saved_by(), "");
}

TEST(DocumentPropertiesTest, SetAndGetTitle) {
    DocumentProperties props;
    props.set_title("My Presentation");
    EXPECT_EQ(props.title(), "My Presentation");
}

TEST(DocumentPropertiesTest, SetAndGetSubject) {
    DocumentProperties props;
    props.set_subject("Quarterly Review");
    EXPECT_EQ(props.subject(), "Quarterly Review");
}

TEST(DocumentPropertiesTest, SetAndGetAuthor) {
    DocumentProperties props;
    props.set_author("Alice");
    EXPECT_EQ(props.author(), "Alice");
}

TEST(DocumentPropertiesTest, SetAndGetKeywords) {
    DocumentProperties props;
    props.set_keywords("slides, review, Q1");
    EXPECT_EQ(props.keywords(), "slides, review, Q1");
}

TEST(DocumentPropertiesTest, SetAndGetComments) {
    DocumentProperties props;
    props.set_comments("Draft version");
    EXPECT_EQ(props.comments(), "Draft version");
}

TEST(DocumentPropertiesTest, SetAndGetCategory) {
    DocumentProperties props;
    props.set_category("Reports");
    EXPECT_EQ(props.category(), "Reports");
}

TEST(DocumentPropertiesTest, SetAndGetContentStatus) {
    DocumentProperties props;
    props.set_content_status("Final");
    EXPECT_EQ(props.content_status(), "Final");
}

TEST(DocumentPropertiesTest, SetAndGetContentType) {
    DocumentProperties props;
    props.set_content_type("application/vnd.ms-powerpoint");
    EXPECT_EQ(props.content_type(), "application/vnd.ms-powerpoint");
}

TEST(DocumentPropertiesTest, SetAndGetLastSavedBy) {
    DocumentProperties props;
    props.set_last_saved_by("Bob");
    EXPECT_EQ(props.last_saved_by(), "Bob");
}

// -- Revision number --

TEST(DocumentPropertiesTest, DefaultRevisionNumberIsZero) {
    DocumentProperties props;
    EXPECT_EQ(props.revision_number(), 0);
}

TEST(DocumentPropertiesTest, SetAndGetRevisionNumber) {
    DocumentProperties props;
    props.set_revision_number(42);
    EXPECT_EQ(props.revision_number(), 42);
}

// -- Date/time properties --

TEST(DocumentPropertiesTest, DefaultDateTimesAreNullopt) {
    DocumentProperties props;
    EXPECT_FALSE(props.created_time().has_value());
    EXPECT_FALSE(props.last_saved_time().has_value());
    EXPECT_FALSE(props.last_printed().has_value());
}

TEST(DocumentPropertiesTest, SetAndGetCreatedTime) {
    DocumentProperties props;
    auto now = std::chrono::system_clock::now();
    props.set_created_time(now);
    ASSERT_TRUE(props.created_time().has_value());
    EXPECT_EQ(props.created_time().value(), now);
}

TEST(DocumentPropertiesTest, SetAndGetLastSavedTime) {
    DocumentProperties props;
    auto now = std::chrono::system_clock::now();
    props.set_last_saved_time(now);
    ASSERT_TRUE(props.last_saved_time().has_value());
    EXPECT_EQ(props.last_saved_time().value(), now);
}

TEST(DocumentPropertiesTest, SetAndGetLastPrinted) {
    DocumentProperties props;
    auto now = std::chrono::system_clock::now();
    props.set_last_printed(now);
    ASSERT_TRUE(props.last_printed().has_value());
    EXPECT_EQ(props.last_printed().value(), now);
}

TEST(DocumentPropertiesTest, ClearDateTimeBySettingNullopt) {
    DocumentProperties props;
    props.set_created_time(std::chrono::system_clock::now());
    ASSERT_TRUE(props.created_time().has_value());
    props.set_created_time(std::nullopt);
    EXPECT_FALSE(props.created_time().has_value());
}

// -- App properties --

TEST(DocumentPropertiesTest, DefaultAppVersion) {
    DocumentProperties props;
    EXPECT_EQ(props.app_version(), "16.0000");
}

TEST(DocumentPropertiesTest, SetAndGetNameOfApplication) {
    DocumentProperties props;
    props.set_name_of_application("Microsoft Office PowerPoint");
    EXPECT_EQ(props.name_of_application(), "Microsoft Office PowerPoint");
}

TEST(DocumentPropertiesTest, SetAndGetCompany) {
    DocumentProperties props;
    props.set_company("Acme Corp");
    EXPECT_EQ(props.company(), "Acme Corp");
}

TEST(DocumentPropertiesTest, SetAndGetManager) {
    DocumentProperties props;
    props.set_manager("Charlie");
    EXPECT_EQ(props.manager(), "Charlie");
}

TEST(DocumentPropertiesTest, SetAndGetPresentationFormat) {
    DocumentProperties props;
    props.set_presentation_format("On-screen Show (4:3)");
    EXPECT_EQ(props.presentation_format(), "On-screen Show (4:3)");
}

TEST(DocumentPropertiesTest, SetAndGetApplicationTemplate) {
    DocumentProperties props;
    props.set_application_template("template.potx");
    EXPECT_EQ(props.application_template(), "template.potx");
}

TEST(DocumentPropertiesTest, SetAndGetHyperlinkBase) {
    DocumentProperties props;
    props.set_hyperlink_base("https://example.com");
    EXPECT_EQ(props.hyperlink_base(), "https://example.com");
}

// -- Total editing time --

TEST(DocumentPropertiesTest, DefaultTotalEditingTimeIsZero) {
    DocumentProperties props;
    EXPECT_EQ(props.total_editing_time().count(), 0);
}

TEST(DocumentPropertiesTest, SetAndGetTotalEditingTime) {
    DocumentProperties props;
    props.set_total_editing_time(std::chrono::minutes{120});
    EXPECT_EQ(props.total_editing_time(), std::chrono::minutes{120});
}

// -- Boolean app properties --

TEST(DocumentPropertiesTest, DefaultBoolPropertiesAreFalse) {
    DocumentProperties props;
    EXPECT_FALSE(props.shared_doc());
    EXPECT_FALSE(props.scale_crop());
    EXPECT_FALSE(props.links_up_to_date());
    EXPECT_FALSE(props.hyperlinks_changed());
}

TEST(DocumentPropertiesTest, SetAndGetSharedDoc) {
    DocumentProperties props;
    props.set_shared_doc(true);
    EXPECT_TRUE(props.shared_doc());
}

TEST(DocumentPropertiesTest, SetAndGetScaleCrop) {
    DocumentProperties props;
    props.set_scale_crop(true);
    EXPECT_TRUE(props.scale_crop());
}

TEST(DocumentPropertiesTest, SetAndGetLinksUpToDate) {
    DocumentProperties props;
    props.set_links_up_to_date(true);
    EXPECT_TRUE(props.links_up_to_date());
}

TEST(DocumentPropertiesTest, SetAndGetHyperlinksChanged) {
    DocumentProperties props;
    props.set_hyperlinks_changed(true);
    EXPECT_TRUE(props.hyperlinks_changed());
}

// -- Read-only statistics --

TEST(DocumentPropertiesTest, DefaultStatisticsAreZero) {
    DocumentProperties props;
    EXPECT_EQ(props.slides(), 0);
    EXPECT_EQ(props.hidden_slides(), 0);
    EXPECT_EQ(props.notes(), 0);
    EXPECT_EQ(props.paragraphs(), 0);
    EXPECT_EQ(props.words(), 0);
    EXPECT_EQ(props.multimedia_clips(), 0);
}

// -- Heading pairs and titles of parts --

TEST(DocumentPropertiesTest, DefaultHeadingPairsEmpty) {
    DocumentProperties props;
    EXPECT_TRUE(props.heading_pairs().empty());
}

TEST(DocumentPropertiesTest, DefaultTitlesOfPartsEmpty) {
    DocumentProperties props;
    EXPECT_TRUE(props.titles_of_parts().empty());
}

// -- Custom properties --

TEST(DocumentPropertiesTest, DefaultCustomPropertyCountIsZero) {
    DocumentProperties props;
    EXPECT_EQ(props.count_of_custom_properties(), 0);
}

TEST(DocumentPropertiesTest, SetAndGetCustomStringProperty) {
    DocumentProperties props;
    props.set_custom_property_value("MyProp", std::any(std::string("hello")));

    EXPECT_EQ(props.count_of_custom_properties(), 1);
    EXPECT_TRUE(props.contains_custom_property("MyProp"));

    std::any val;
    ASSERT_TRUE(props.get_custom_property_value("MyProp", val));
    EXPECT_EQ(std::any_cast<std::string>(val), "hello");
}

TEST(DocumentPropertiesTest, SetAndGetCustomIntProperty) {
    DocumentProperties props;
    props.set_custom_property_value("Count", std::any(42));

    std::any val;
    ASSERT_TRUE(props.get_custom_property_value("Count", val));
    EXPECT_EQ(std::any_cast<int>(val), 42);
}

TEST(DocumentPropertiesTest, SetAndGetCustomBoolProperty) {
    DocumentProperties props;
    props.set_custom_property_value("Flag", std::any(true));

    std::any val;
    ASSERT_TRUE(props.get_custom_property_value("Flag", val));
    EXPECT_TRUE(std::any_cast<bool>(val));
}

TEST(DocumentPropertiesTest, OverwriteCustomProperty) {
    DocumentProperties props;
    props.set_custom_property_value("Key", std::any(std::string("old")));
    props.set_custom_property_value("Key", std::any(std::string("new")));

    EXPECT_EQ(props.count_of_custom_properties(), 1);
    std::any val;
    ASSERT_TRUE(props.get_custom_property_value("Key", val));
    EXPECT_EQ(std::any_cast<std::string>(val), "new");
}

TEST(DocumentPropertiesTest, GetCustomPropertyValueNonExistent) {
    DocumentProperties props;
    std::any val;
    EXPECT_FALSE(props.get_custom_property_value("NoSuchProp", val));
}

TEST(DocumentPropertiesTest, GetCustomPropertyName) {
    DocumentProperties props;
    props.set_custom_property_value("Alpha", std::any(1));
    props.set_custom_property_value("Beta", std::any(2));
    props.set_custom_property_value("Gamma", std::any(3));

    EXPECT_EQ(props.get_custom_property_name(0), "Alpha");
    EXPECT_EQ(props.get_custom_property_name(1), "Beta");
    EXPECT_EQ(props.get_custom_property_name(2), "Gamma");
}

TEST(DocumentPropertiesTest, GetCustomPropertyNameOutOfRange) {
    DocumentProperties props;
    EXPECT_THROW((void)props.get_custom_property_name(0), std::out_of_range);
    EXPECT_THROW((void)props.get_custom_property_name(-1), std::out_of_range);
}

TEST(DocumentPropertiesTest, RemoveCustomProperty) {
    DocumentProperties props;
    props.set_custom_property_value("ToRemove", std::any(std::string("val")));
    EXPECT_TRUE(props.contains_custom_property("ToRemove"));

    EXPECT_TRUE(props.remove_custom_property("ToRemove"));
    EXPECT_FALSE(props.contains_custom_property("ToRemove"));
    EXPECT_EQ(props.count_of_custom_properties(), 0);
}

TEST(DocumentPropertiesTest, RemoveNonExistentCustomProperty) {
    DocumentProperties props;
    EXPECT_FALSE(props.remove_custom_property("NoSuchProp"));
}

TEST(DocumentPropertiesTest, ClearCustomProperties) {
    DocumentProperties props;
    props.set_custom_property_value("A", std::any(1));
    props.set_custom_property_value("B", std::any(2));
    ASSERT_EQ(props.count_of_custom_properties(), 2);

    props.clear_custom_properties();
    EXPECT_EQ(props.count_of_custom_properties(), 0);
    EXPECT_FALSE(props.contains_custom_property("A"));
    EXPECT_FALSE(props.contains_custom_property("B"));
}

TEST(DocumentPropertiesTest, ContainsCustomProperty) {
    DocumentProperties props;
    EXPECT_FALSE(props.contains_custom_property("X"));
    props.set_custom_property_value("X", std::any(true));
    EXPECT_TRUE(props.contains_custom_property("X"));
}

// -- Clear built-in properties --

TEST(DocumentPropertiesTest, ClearBuiltInProperties) {
    DocumentProperties props;
    props.set_title("Title");
    props.set_subject("Subject");
    props.set_author("Author");
    props.set_keywords("kw");
    props.set_comments("comment");
    props.set_category("cat");
    props.set_content_status("status");
    props.set_content_type("type");
    props.set_last_saved_by("user");
    props.set_revision_number(10);
    props.set_created_time(std::chrono::system_clock::now());
    props.set_last_saved_time(std::chrono::system_clock::now());
    props.set_last_printed(std::chrono::system_clock::now());
    props.set_name_of_application("App");
    props.set_company("Co");
    props.set_manager("Mgr");
    props.set_presentation_format("fmt");
    props.set_application_template("tmpl");
    props.set_hyperlink_base("http://x");
    props.set_total_editing_time(std::chrono::minutes{60});
    props.set_shared_doc(true);
    props.set_scale_crop(true);
    props.set_links_up_to_date(true);
    props.set_hyperlinks_changed(true);

    // Custom properties should NOT be cleared
    props.set_custom_property_value("Custom", std::any(42));

    props.clear_built_in_properties();

    // All built-in should be reset
    EXPECT_EQ(props.title(), "");
    EXPECT_EQ(props.subject(), "");
    EXPECT_EQ(props.author(), "");
    EXPECT_EQ(props.keywords(), "");
    EXPECT_EQ(props.comments(), "");
    EXPECT_EQ(props.category(), "");
    EXPECT_EQ(props.content_status(), "");
    EXPECT_EQ(props.content_type(), "");
    EXPECT_EQ(props.last_saved_by(), "");
    EXPECT_EQ(props.revision_number(), 0);
    EXPECT_FALSE(props.created_time().has_value());
    EXPECT_FALSE(props.last_saved_time().has_value());
    EXPECT_FALSE(props.last_printed().has_value());
    EXPECT_EQ(props.name_of_application(), "");
    EXPECT_EQ(props.company(), "");
    EXPECT_EQ(props.manager(), "");
    EXPECT_EQ(props.presentation_format(), "");
    EXPECT_EQ(props.application_template(), "");
    EXPECT_EQ(props.hyperlink_base(), "");
    EXPECT_EQ(props.total_editing_time().count(), 0);
    EXPECT_FALSE(props.shared_doc());
    EXPECT_FALSE(props.scale_crop());
    EXPECT_FALSE(props.links_up_to_date());
    EXPECT_FALSE(props.hyperlinks_changed());

    // Custom properties should remain
    EXPECT_EQ(props.count_of_custom_properties(), 1);
    EXPECT_TRUE(props.contains_custom_property("Custom"));
}

// -- Access through Presentation --

TEST(DocumentPropertiesTest, AccessThroughPresentation) {
    Presentation pres;
    pres.document_properties().set_title("Test Title");
    pres.document_properties().set_author("Test Author");

    EXPECT_EQ(pres.document_properties().title(), "Test Title");
    EXPECT_EQ(pres.document_properties().author(), "Test Author");
}

// -- HeadingPair struct --

TEST(HeadingPairTest, DefaultConstruction) {
    HeadingPair hp;
    EXPECT_EQ(hp.name(), "");
    EXPECT_EQ(hp.count(), 0);
}

TEST(HeadingPairTest, ValueConstruction) {
    HeadingPair hp("Slides", 5);
    EXPECT_EQ(hp.name(), "Slides");
    EXPECT_EQ(hp.count(), 5);
}

TEST(HeadingPairTest, Equality) {
    HeadingPair a("Slides", 5);
    HeadingPair b("Slides", 5);
    HeadingPair c("Notes", 3);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}
