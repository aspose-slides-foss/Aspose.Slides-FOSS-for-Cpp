// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file document_properties_conformance_test.cpp
/// What `docProps` says about the deck it ships with.
///
/// `docProps/app.xml` is where PowerPoint, Explorer's details pane, search
/// indexers and document-management systems read the deck's shape from. It is
/// generated once and never refreshed, so a deck that has slides and text
/// reports having neither.

#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/document_properties.h>
#include <Aspose/Slides/Foss/global_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/notes_slide.h>
#include <Aspose/Slides/Foss/notes_slide_manager.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_frame.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;

namespace {

constexpr const char* kAppProps = "docProps/app.xml";

class DocumentPropertiesConformance : public conformance::SavedDeckTest {
protected:
    /// Text of a direct child of the app-properties root, or "" if absent.
    std::string app_property(const conformance::Package& pkg,
                             const char* name) {
        if (!pkg.has_entry(kAppProps)) return {};
        auto node = pkg.xml(kAppProps).document_element().child(name);
        return node ? node.text().get() : "";
    }
};

/// A three-slide deck has to say it has three slides.
TEST_F(DocumentPropertiesConformance, AppPropertiesReportTheActualSlideCount) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    pres.slides().add_empty_slide(layout);
    ASSERT_EQ(pres.slides().size(), 3u);

    auto pkg = save_and_inspect(pres);
    ASSERT_TRUE(pkg.has_entry(kAppProps)) << "no docProps/app.xml was written";
    EXPECT_EQ(app_property(pkg, "Slides"), "3");
}

/// And a deck with text has to say it has paragraphs.
TEST_F(DocumentPropertiesConformance, AppPropertiesReportTheActualParagraphCount) {
    Presentation pres;
    auto& shape = pres.slides()[0].shapes().add_auto_shape(
        ShapeType::RECTANGLE, 50, 50, 300, 80);
    shape.text_frame()->set_text("One paragraph of text");

    auto pkg = save_and_inspect(pres);
    ASSERT_TRUE(pkg.has_entry(kAppProps));
    EXPECT_NE(app_property(pkg, "Paragraphs"), "0")
        << "the deck reports zero paragraphs on a slide that has text";
}

/// A hidden slide counts as hidden. HiddenSlides is what a document-management
/// system reads to know the deck is not all presentable.
TEST_F(DocumentPropertiesConformance, AppPropertiesReportTheHiddenSlideCount) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    pres.slides()[1].set_hidden(true);

    auto pkg = save_and_inspect(pres);
    ASSERT_TRUE(pkg.has_entry(kAppProps));
    EXPECT_EQ(app_property(pkg, "Slides"), "2");
    EXPECT_EQ(app_property(pkg, "HiddenSlides"), "1");
}

/// And a deck with a notes slide says it has one.
TEST_F(DocumentPropertiesConformance, AppPropertiesReportTheNotesCount) {
    Presentation pres;
    ASSERT_NE(pres.slides()[0].notes_slide_manager().add_notes_slide(),
              nullptr);

    auto pkg = save_and_inspect(pres);
    ASSERT_TRUE(pkg.has_entry(kAppProps));
    EXPECT_EQ(app_property(pkg, "Notes"), "1");
}

/// The title and author the caller set are written correctly today; this pins
/// the half of docProps that already works.
TEST_F(DocumentPropertiesConformance, TheTitleAndAuthorThatWereSetAreWritten) {
    Presentation pres;
    pres.document_properties().set_title("Quarterly review");
    pres.document_properties().set_author("A. Author");

    auto pkg = save_and_inspect(pres);
    ASSERT_TRUE(pkg.has_entry("docProps/core.xml"));
    auto core = pkg.entry_text("docProps/core.xml");
    EXPECT_NE(core.find("Quarterly review"), std::string::npos);
    EXPECT_NE(core.find("A. Author"), std::string::npos);
}

} // namespace
