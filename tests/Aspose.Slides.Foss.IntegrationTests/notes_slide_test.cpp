// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file notes_slide_test.cpp
/// Integration tests for NotesSlide, NotesSlideManager, header/footer, NotesSize.

#include <chrono>
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/i_notes_slide.h>
#include <Aspose/Slides/Foss/i_notes_slide_manager.h>
#include <Aspose/Slides/Foss/i_notes_slide_header_footer_manager.h>
#include <Aspose/Slides/Foss/notes_size.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/text_frame.h>

using namespace Aspose::Slides::Foss;

namespace {

/// Fixture that provides a temp directory and round-trip save/reopen helper.
class NotesSlideIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        tmp_dir_ = std::filesystem::temp_directory_path() /
                   ("notes_slide_integration_test_" +
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
// -------------------------------------------------------------------------
TEST_F(NotesSlideIntegrationTest, AddNotes) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);
    notes->notes_text_frame().set_text("Speaker notes");

    auto pres2 = save_and_reopen(pres);
    auto* ns2 = pres2.slides()[0].notes_slide_manager().notes_slide();
    ASSERT_NE(ns2, nullptr);
    EXPECT_EQ(ns2->notes_text_frame().text(), "Speaker notes");
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(NotesSlideIntegrationTest, RemoveNotes) {
    Presentation pres;
    auto& mgr = pres.slides()[0].notes_slide_manager();
    mgr.add_notes_slide();
    ASSERT_NE(mgr.notes_slide(), nullptr);

    mgr.remove_notes_slide();
    EXPECT_EQ(mgr.notes_slide(), nullptr);

    auto pres2 = save_and_reopen(pres);
    EXPECT_EQ(pres2.slides()[0].notes_slide_manager().notes_slide(), nullptr);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(NotesSlideIntegrationTest, NotesHeaderFooter) {
    Presentation pres;
    auto* notes = pres.slides()[0].notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);
    notes->notes_text_frame().set_text("Notes");
    auto& hfm = notes->header_footer_manager();
    hfm.set_footer_visibility(true);
    hfm.set_footer_text("Confidential");
    hfm.set_slide_number_visibility(true);

    EXPECT_TRUE(hfm.is_footer_visible());
    EXPECT_TRUE(hfm.is_slide_number_visible());

    auto pres2 = save_and_reopen(pres);
    auto* ns2 = pres2.slides()[0].notes_slide_manager().notes_slide();
    ASSERT_NE(ns2, nullptr);
    auto& hfm2 = ns2->header_footer_manager();
    EXPECT_TRUE(hfm2.is_footer_visible());
    EXPECT_TRUE(hfm2.is_slide_number_visible());
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(NotesSlideIntegrationTest, NotesParentSlide) {
    Presentation pres;
    auto& slide = pres.slides()[0];
    auto* notes = slide.notes_slide_manager().add_notes_slide();
    ASSERT_NE(notes, nullptr);
    EXPECT_EQ(notes->parent_slide(), &slide);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
TEST_F(NotesSlideIntegrationTest, NotesSize) {
    Presentation pres;
    auto& ns = pres.notes_size();
    EXPECT_GT(ns.size().width, 0.0f);
    EXPECT_GT(ns.size().height, 0.0f);
}

} // namespace
