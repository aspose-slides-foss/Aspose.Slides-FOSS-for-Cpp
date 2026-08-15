// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file save_format_conformance_test.cpp
/// What a caller gets when they ask for a format other than PPTX.
///
/// `save()` takes a SaveFormat and the caller is entitled to assume it means
/// something. Two obligations follow. A format that is not implemented has to
/// say so instead of returning success. A format that shares the PPTX package
/// shape still has its own main-part content type, and PowerPoint refuses a
/// file whose extension and main content type disagree.

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>

#include "conformance/conformance.h"
#include "conformance/saved_deck.h"

using namespace Aspose::Slides::Foss;

namespace {

class SaveFormatConformance : public conformance::SavedDeckTest {
protected:
    /// The ContentType `[Content_Types].xml` gives the main presentation part.
    std::string main_part_content_type(const conformance::Package& pkg) {
        return pkg.content_type_of("ppt/presentation.xml");
    }
};

constexpr const char* kPresentationMain =
    "application/vnd.openxmlformats-officedocument.presentationml.presentation.main+xml";
constexpr const char* kTemplateMain =
    "application/vnd.openxmlformats-officedocument.presentationml.template.main+xml";
constexpr const char* kSlideshowMain =
    "application/vnd.openxmlformats-officedocument.presentationml.slideshow.main+xml";
constexpr const char* kMacroEnabledMain =
    "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml";

// -- The PPTX baseline. Guards §"already correct" behaviour; passes today. ---

TEST_F(SaveFormatConformance, SavingAsPptxWritesThePresentationContentType) {
    Presentation pres;
    auto pkg = save_and_inspect(pres, "deck.pptx", SaveFormat::PPTX);
    EXPECT_EQ(main_part_content_type(pkg), kPresentationMain);
}

// -- The PPTX-family formats, which differ only in the main content type ----

TEST_F(SaveFormatConformance, SavingAsATemplateWritesTheTemplateContentType) {
    Presentation pres;
    auto pkg = save_and_inspect(pres, "deck.potx", SaveFormat::POTX);
    EXPECT_EQ(main_part_content_type(pkg), kTemplateMain)
        << "a .potx whose main part claims to be a presentation is a file "
           "PowerPoint refuses to open";
}

TEST_F(SaveFormatConformance, SavingAsASlideshowWritesTheSlideshowContentType) {
    Presentation pres;
    auto pkg = save_and_inspect(pres, "deck.ppsx", SaveFormat::PPSX);
    EXPECT_EQ(main_part_content_type(pkg), kSlideshowMain);
}

TEST_F(SaveFormatConformance,
       SavingAsAMacroEnabledDeckWritesTheMacroEnabledContentType) {
    Presentation pres;
    auto pkg = save_and_inspect(pres, "deck.pptm", SaveFormat::PPTM);
    EXPECT_EQ(main_part_content_type(pkg), kMacroEnabledMain);
}

// -- The formats that are not implemented -----------------------------------

/// Every format outside the PPTX package family. None of these is implemented;
/// each currently writes a PPTX and names it after the format that was asked
/// for, so a caller converting to PDF gets a PowerPoint file called .pdf and
/// no indication that anything went wrong.
const std::vector<std::pair<SaveFormat, const char*>>& unimplemented_formats() {
    static const std::vector<std::pair<SaveFormat, const char*>> formats = {
        {SaveFormat::PPT, "deck.ppt"},   {SaveFormat::PDF, "deck.pdf"},
        {SaveFormat::XPS, "deck.xps"},   {SaveFormat::TIFF, "deck.tiff"},
        {SaveFormat::ODP, "deck.odp"},   {SaveFormat::HTML, "deck.html"},
        {SaveFormat::SWF, "deck.swf"},   {SaveFormat::OTP, "deck.otp"},
        {SaveFormat::PPS, "deck.pps"},   {SaveFormat::POT, "deck.pot"},
        {SaveFormat::FODP, "deck.fodp"}, {SaveFormat::GIF, "deck.gif"},
        {SaveFormat::HTML5, "deck.html"}, {SaveFormat::MD, "deck.md"},
        {SaveFormat::XML, "deck.xml"},
    };
    return formats;
}

TEST_F(SaveFormatConformance, AskingForAFormatThatIsNotImplementedThrows) {
    std::vector<std::string> silently_accepted;
    for (const auto& [format, name] : unimplemented_formats()) {
        Presentation pres;
        bool threw = false;
        try {
            save(pres, name, format);
        } catch (const std::exception&) {
            threw = true;
        }
        if (!threw)
            silently_accepted.emplace_back(to_string_view(format));
    }
    EXPECT_TRUE(silently_accepted.empty())
        << silently_accepted.size()
        << " unimplemented format(s) returned success instead of throwing: "
        << [&] {
               std::string s;
               for (std::size_t i = 0; i < silently_accepted.size(); ++i) {
                   if (i) s += ", ";
                   s += silently_accepted[i];
               }
               return s;
           }();
}

TEST_F(SaveFormatConformance, APdfRequestDoesNotProduceAPresentationPackage) {
    Presentation pres;
    std::filesystem::path written;
    try {
        written = save(pres, "report.pdf", SaveFormat::PDF);
    } catch (const std::exception&) {
        SUCCEED() << "PDF export is refused, which is the honest answer";
        return;
    }
    conformance::Package pkg(written);
    EXPECT_FALSE(pkg.has_entry("ppt/presentation.xml"))
        << "report.pdf is a PowerPoint package with a .pdf name; PowerPoint "
           "reports that the file extension has changed and refuses it";
}

} // namespace
