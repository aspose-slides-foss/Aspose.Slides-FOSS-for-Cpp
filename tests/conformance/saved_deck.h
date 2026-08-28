// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file saved_deck.h
/// @brief Test fixture: build a deck through the public API, save it, and open
///        the saved bytes as a package.
///
/// The fixture deliberately offers no way to reopen the file through
/// `Presentation`. Reading a file back with the same code that wrote it proves
/// only that the writer and the reader agree, which they do even when both are
/// wrong about the format.

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <system_error>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>

#include "conformance/conformance.h"

namespace conformance {

/// Gives each test its own temp directory and a save-then-inspect helper.
class SavedDeckTest : public ::testing::Test {
protected:
    void SetUp() override {
        const auto* info =
            ::testing::UnitTest::GetInstance()->current_test_info();
        dir_ = std::filesystem::temp_directory_path() /
               ("conformance_" + std::string(info->test_suite_name()) + "_" +
                std::string(info->name()) + "_" +
                std::to_string(std::chrono::steady_clock::now()
                                   .time_since_epoch()
                                   .count()));
        std::filesystem::create_directories(dir_);
    }

    void TearDown() override {
        std::error_code ec;
        std::filesystem::remove_all(dir_, ec);
    }

    [[nodiscard]] std::filesystem::path path_for(std::string_view name) const {
        return dir_ / std::filesystem::path(std::string(name));
    }

    /// Saves and returns the path written.
    ///
    /// When the environment variable `ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT`
    /// names a directory, a copy of every saved file is left there. That is
    /// how CI collects a corpus for `tests/conformance/validate.py`, which
    /// runs the checks that cannot run in-process — a schema-aware
    /// third-party reader, and an independent implementation of the package
    /// rules.
    std::filesystem::path save(Aspose::Slides::Foss::Presentation& pres,
                               std::string_view name = "out.pptx",
                               Aspose::Slides::Foss::SaveFormat format =
                                   Aspose::Slides::Foss::SaveFormat::PPTX) {
        return save_to(pres, path_for(name), format);
    }

    /// Saves to an explicit path, and collects it like `save` does.
    std::filesystem::path save_to(Aspose::Slides::Foss::Presentation& pres,
                                  const std::filesystem::path& path,
                                  Aspose::Slides::Foss::SaveFormat format =
                                      Aspose::Slides::Foss::SaveFormat::PPTX) {
        pres.save(path.string(), format);
        keep_a_copy(path);
        return path;
    }

    /// Saves, then reopens the bytes as an OPC package for assertion.
    Package save_and_inspect(Aspose::Slides::Foss::Presentation& pres,
                             std::string_view name = "out.pptx",
                             Aspose::Slides::Foss::SaveFormat format =
                                 Aspose::Slides::Foss::SaveFormat::PPTX) {
        return Package(save(pres, name, format));
    }

    std::filesystem::path dir_;

private:
    /// Copies a saved file into the collection directory, if one is named.
    void keep_a_copy(const std::filesystem::path& path) const {
        const char* out = std::getenv("ASPOSE_SLIDES_FOSS_CONFORMANCE_OUT");
        if (!out || !*out) return;
        std::error_code ec;
        std::filesystem::path target(out);
        std::filesystem::create_directories(target, ec);
        const auto* info =
            ::testing::UnitTest::GetInstance()->current_test_info();
        auto copy_name = std::string(info->test_suite_name()) + "." +
                         std::string(info->name()) + "." +
                         path.filename().string();
        std::filesystem::copy_file(
            path, target / copy_name,
            std::filesystem::copy_options::overwrite_existing, ec);
    }
};

} // namespace conformance
