// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file presentation_test.cpp
/// Integration tests for Presentation: create / load / save / properties.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/presentation.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class PresentationIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("presentation_integration_test_" +
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

// -- test_create_empty --
// A brand-new presentation has exactly 1 slide.
TEST_F(PresentationIntegrationTest, CreateEmpty) {
    Presentation pres;
    EXPECT_EQ(pres.slides().size(), 1u);
}

// -- test_save_and_reload --
// Round-trip: create -> save -> reload preserves slide count.
TEST_F(PresentationIntegrationTest, SaveAndReload) {
    Presentation pres;
    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.slides().size(), 1u);
}

// -- test_save_to_stream --
// Saving to a file produces a non-empty output.
// (C++ API has no stream overload, so we save to file and check size.)
TEST_F(PresentationIntegrationTest, SaveToFile) {
    Presentation pres;
    auto path = (tmp_dir_ / "output.pptx").string();
    pres.save(path, static_cast<int>(SaveFormat::PPTX));
    EXPECT_GT(std::filesystem::file_size(path), 0u);
}

// -- test_context_manager --
// Presentation can be used with RAII (C++ equivalent of context manager).
TEST_F(PresentationIntegrationTest, RaiiDestruction) {
    {
        Presentation pres;
        EXPECT_GE(pres.slides().size(), 1u);
    }
    // Object destroyed without explicit dispose — should not crash.
}

// -- test_first_slide_number --
// first_slide_number persists across save/reload.
TEST_F(PresentationIntegrationTest, FirstSlideNumber) {
    Presentation pres;
    pres.set_first_slide_number(5);
    EXPECT_EQ(pres.first_slide_number(), 5);

    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.first_slide_number(), 5);
}

// -- test_load_existing --
// Save a presentation then load it back, verifying it opens correctly.
TEST_F(PresentationIntegrationTest, LoadExisting) {
    auto path = (tmp_dir_ / "existing.pptx").string();
    {
        Presentation pres;
        pres.save(path, static_cast<int>(SaveFormat::PPTX));
    }
    Presentation pres(path);
    EXPECT_GE(pres.slides().size(), 1u);
}

// -- test_dispose_is_idempotent --
// Calling dispose() twice must not raise.
TEST_F(PresentationIntegrationTest, DisposeIsIdempotent) {
    Presentation pres;
    pres.dispose();
    pres.dispose(); // second call should be harmless
}

// -- test_slide_count_after_add --
// Adding a slide increases slide count to 2.
TEST_F(PresentationIntegrationTest, SlideCountAfterAdd) {
    Presentation pres;
    auto* layout = dynamic_cast<ILayoutSlide*>(&pres.layout_slides()[0]);
    ASSERT_NE(layout, nullptr);
    pres.slides().add_empty_slide(layout);
    EXPECT_EQ(pres.slides().size(), 2u);
}

} // namespace
