// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file table_conformance_test.cpp
/// The graphic frame a table lives in.
///
/// `CT_NonVisualGraphicFrameProperties` allows exactly one child element,
/// `a:graphicFrameLocks`. `a:graphicFrameLocking` is not a name in the schema
/// — the *type* is `CT_GraphicalObjectFrameLocking`, which is presumably where
/// it came from. PowerPoint silently discards the unknown element and opens
/// the file, which is why nothing catches this without a validator or an
/// assertion on the element name itself.

#include <array>
#include <span>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/cell.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/table.h>
#include <Aspose/Slides/Foss/text_frame.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;

namespace {

constexpr const char* kSlide = "ppt/slides/slide1.xml";

class TableConformance : public conformance::SavedDeckTest {
protected:
    Table& fresh_table(Presentation& pres) {
        pres.slides()[0].shapes().clear();
        static constexpr std::array<double, 2> columns{150.0, 150.0};
        static constexpr std::array<double, 2> rows{40.0, 40.0};
        return pres.slides()[0].shapes().add_table(
            50, 50, std::span<const double>(columns),
            std::span<const double>(rows));
    }
};

TEST_F(TableConformance, ATableLocksItsGraphicFrameWithTheSchemaElement) {
    Presentation pres;
    fresh_table(pres);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//p:nvGraphicFramePr/p:cNvGraphicFramePr/a:graphicFrameLocks",
        {{"noGrp", "1"}}));
}

TEST_F(TableConformance, ATableDoesNotCarryAnElementThatIsNotInTheSchema) {
    Presentation pres;
    fresh_table(pres);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementAbsent(pkg, kSlide, "//a:graphicFrameLocking"))
        << "a:graphicFrameLocking is not a name in DrawingML; PowerPoint "
           "discards it silently and a strict consumer rejects the part";
}

/// The loaded-deck path has its own copy of the same call site, so fixing one
/// and not the other leaves every table written by an edited deck invalid.
TEST_F(TableConformance, ATableAddedToALoadedDeckUsesTheSchemaElementToo) {
    Presentation pres;
    auto first = save(pres, "empty.pptx");

    Presentation loaded(first.string());
    static constexpr std::array<double, 2> columns{150.0, 150.0};
    static constexpr std::array<double, 2> rows{40.0, 40.0};
    loaded.slides()[0].shapes().add_table(50, 50,
                                          std::span<const double>(columns),
                                          std::span<const double>(rows));
    auto second = save_to(loaded, path_for("with_table.pptx"));

    conformance::Package pkg(second);
    EXPECT_TRUE(conformance::ElementAbsent(pkg, kSlide, "//a:graphicFrameLocking"));
    EXPECT_TRUE(conformance::ElementExists(
        pkg, kSlide, "//p:nvGraphicFramePr/p:cNvGraphicFramePr/a:graphicFrameLocks",
        {{"noGrp", "1"}}));
}

/// Cell merging is written correctly and must stay that way.
TEST_F(TableConformance, AHorizontallyMergedCellPairIsWrittenAsGridSpanAndHMerge) {
    Presentation pres;
    auto& table = fresh_table(pres);
    table.merge_cells(table.cell(0, 0), table.cell(0, 1), false);

    auto pkg = save_and_inspect(pres);
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:tc",
                                           {{"gridSpan", "2"}}));
    EXPECT_TRUE(conformance::ElementExists(pkg, kSlide, "//a:tc",
                                           {{"hMerge", "1"}}));
}

} // namespace
