// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file foreign_deck_conformance_test.cpp
/// Reading a deck this library did not write.
///
/// Every other .pptx path named in this test tree points at a file the library
/// created seconds earlier, so the load path has only ever been fed its own
/// output. `tests/test_data/powerpoint_title_and_content.pptx` is a committed
/// deck written by hand (see tests/conformance/make_fixtures.py) whose
/// placeholders carry a bare `<p:spPr/>` and inherit their geometry from the
/// layout — the ordinary shape of a deck produced by PowerPoint, and the input
/// that is never exercised otherwise.

#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>

#include "conformance/conformance.h"

using namespace Aspose::Slides::Foss;

namespace {

std::string fixture_path() {
    auto path =
        conformance::test_data_dir() / "powerpoint_title_and_content.pptx";
    return path.string();
}

TEST(ForeignDeck, LoadsADeckWrittenByAnotherToolAndSeesItsSlide) {
    ASSERT_TRUE(std::filesystem::exists(fixture_path()))
        << "missing fixture; regenerate with tests/conformance/make_fixtures.py";
    Presentation pres(fixture_path());
    EXPECT_EQ(pres.slides().size(), 1u);
}

/// Enumerating the shapes of a foreign deck must not take the caller's process
/// down with it.
///
/// The check runs in a child process, because the failure mode under test is
/// an access violation: run inline it would abort the whole test binary and
/// every later test would report nothing at all. The child does the work and
/// exits 0; a child that dies instead fails this test and leaves the suite
/// running. The suite name carries the `DeathTest` suffix because that is what
/// tells GoogleTest to schedule these first, before any test has had a chance
/// to start a thread.
TEST(ForeignDeckDeathTest, EnumeratingShapesOfAForeignDeckDoesNotKillTheProcess) {
    ASSERT_TRUE(std::filesystem::exists(fixture_path()))
        << "missing fixture; regenerate with tests/conformance/make_fixtures.py";

    EXPECT_EXIT(
        {
            Presentation pres(fixture_path());
            auto& shapes = pres.slides()[0].shapes();
            std::size_t n = shapes.size();
            double sum = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                auto& shape = shapes[i];
                sum += shape.x() + shape.y() + shape.width() + shape.height();
            }
            std::fprintf(stderr, "enumerated %zu shape(s), extent sum %f\n", n,
                         sum);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "enumerated")
        << "The child did not reach its own exit(0). Placeholder geometry is "
           "resolved by parsing the layout part into a document that is "
           "destroyed before the resolved node is read, so the read is through "
           "a dangling pointer. That is undefined behaviour, not a wrong "
           "answer: an optimised build usually finds the old bytes still "
           "intact and returns plausible numbers, a debug build reads the "
           "allocator's poison pattern and dies. Build with "
           "-DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON for a located diagnosis.";
}

/// A placeholder with no `a:xfrm` of its own takes its position and size from
/// the layout. The layout in the fixture puts the title at 838200 x 365125 EMU
/// (66 x 28.75 pt), which is what a reader that resolves inheritance reports.
TEST(ForeignDeckDeathTest, APlaceholderInheritsItsGeometryFromTheLayout) {
    ASSERT_TRUE(std::filesystem::exists(fixture_path()))
        << "missing fixture; regenerate with tests/conformance/make_fixtures.py";

    EXPECT_EXIT(
        {
            Presentation pres(fixture_path());
            auto& shape = pres.slides()[0].shapes()[0];
            std::fprintf(stderr, "title x=%.2f y=%.2f w=%.2f h=%.2f\n",
                         shape.x(), shape.y(), shape.width(), shape.height());
            bool ok = std::abs(shape.x() - 66.0) < 0.01 &&
                      std::abs(shape.y() - 28.75) < 0.01;
            std::exit(ok ? 0 : 1);
        },
        ::testing::ExitedWithCode(0), "title x=")
        << "Either the inherited geometry is wrong, or the child died reading "
           "it; see the note on the previous test.";
}

} // namespace
