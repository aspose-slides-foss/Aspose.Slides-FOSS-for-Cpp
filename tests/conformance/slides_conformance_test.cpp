// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file slides_conformance_test.cpp
/// What editing a deck opened from a file leaves in the package.
///
/// The slide collection reports its own state, so `slides().size()` answers
/// from memory and agrees with the caller whether or not anything was written.
/// These tests ask the ZIP instead.

#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/global_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;

namespace {

class SlidesConformance : public conformance::SavedDeckTest {
protected:
    static std::string fixture_path() {
        return (conformance::test_data_dir() /
                "powerpoint_title_and_content.pptx")
            .string();
    }
};

/// `add_empty_slide` on a deck loaded from a file reported success and wrote
/// nothing: the OPC-backed path that creates the part, the relationship and
/// the `<p:sldId>` was reachable only through an internal overload, and the
/// public entry point always took the in-memory one.
TEST_F(SlidesConformance, ASlideAddedToALoadedDeckReachesTheFile) {
    Presentation pres;
    pres.slides()[0].shapes().add_auto_shape(ShapeType::RECTANGLE, 50, 50, 200,
                                             100);
    auto first = save(pres, "one.pptx");

    Presentation loaded(first.string());
    ASSERT_EQ(loaded.slides().size(), 1u);
    loaded.slides().add_empty_slide(&loaded.layout_slides()[0]);
    ASSERT_EQ(loaded.slides().size(), 2u);

    conformance::Package pkg(save_to(loaded, path_for("two.pptx")));
    EXPECT_TRUE(pkg.has_entry("ppt/slides/slide2.xml"))
        << "the slide the caller added is not in the package";
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/presentation.xml",
                                        "//p:sldIdLst/p:sldId"),
              2u)
        << "the deck registers a different number of slides than it carries";
    EXPECT_TRUE(conformance::AllRelationshipReferencesResolve(pkg));
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg));
}

/// The mirror image: removing a slide from a loaded deck left the part, the
/// relationship and the `<p:sldId>` exactly where they were. `slides().size()`
/// dropped, the call reported success, and the saved file still had the slide
/// in it.
TEST_F(SlidesConformance, ASlideRemovedFromALoadedDeckLeavesTheFile) {
    Presentation pres;
    auto* layout = &pres.layout_slides()[0];
    pres.slides().add_empty_slide(layout);
    pres.slides().add_empty_slide(layout);
    auto first = save(pres, "three.pptx");

    Presentation loaded(first.string());
    ASSERT_EQ(loaded.slides().size(), 3u);
    loaded.slides().remove_at(1);

    conformance::Package pkg(save_to(loaded, path_for("two.pptx")));
    EXPECT_EQ(conformance::CountMatches(pkg, "ppt/presentation.xml",
                                        "//p:sldIdLst/p:sldId"),
              2u)
        << "the deck still registers the slide that was removed";
    EXPECT_FALSE(pkg.has_entry("ppt/slides/slide2.xml"))
        << "the removed slide's part is still in the package";
    EXPECT_FALSE(pkg.has_entry("ppt/slides/_rels/slide2.xml.rels"));
    EXPECT_TRUE(conformance::AllRelationshipReferencesResolve(pkg));
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(pkg))
        << "a content-type Override naming a part that is gone is a package a "
           "strict consumer rejects";
}

/// A deck this library did not write must come back out whole. Nothing in the
/// suite held this, and `save()` rewrites `[Content_Types].xml` through the
/// exporter, which is exactly the kind of change that would quietly drop a
/// part it does not understand.
TEST_F(SlidesConformance, LoadingAndSavingAForeignDeckKeepsEveryPart) {
    ASSERT_TRUE(std::filesystem::exists(fixture_path()))
        << "missing fixture; regenerate with tests/conformance/make_fixtures.py";
    conformance::Package before{std::filesystem::path(fixture_path())};

    Presentation loaded(fixture_path());
    conformance::Package after(save_to(loaded, path_for("round-trip.pptx")));

    EXPECT_EQ(after.entry_names(), before.entry_names())
        << "the round trip changed which parts the package contains";
    EXPECT_EQ(after.entry_bytes("ppt/slides/slide1.xml"),
              before.entry_bytes("ppt/slides/slide1.xml"))
        << "an untouched slide part was rewritten";
    EXPECT_TRUE(conformance::PackageIsInternallyConsistent(after));
}

} // namespace
