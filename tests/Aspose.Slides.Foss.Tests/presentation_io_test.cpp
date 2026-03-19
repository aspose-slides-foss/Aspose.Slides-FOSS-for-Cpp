// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <chrono>

#include <gtest/gtest.h>

#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/source_format.h>

using namespace Aspose::Slides::Foss;

// -- SaveFormat enum tests --

TEST(SaveFormatTest, EnumValues) {
    EXPECT_EQ(to_string_view(SaveFormat::PPT), "Ppt");
    EXPECT_EQ(to_string_view(SaveFormat::PDF), "Pdf");
    EXPECT_EQ(to_string_view(SaveFormat::XPS), "Xps");
    EXPECT_EQ(to_string_view(SaveFormat::PPTX), "Pptx");
    EXPECT_EQ(to_string_view(SaveFormat::PPSX), "Ppsx");
    EXPECT_EQ(to_string_view(SaveFormat::TIFF), "Tiff");
    EXPECT_EQ(to_string_view(SaveFormat::ODP), "Odp");
    EXPECT_EQ(to_string_view(SaveFormat::PPTM), "Pptm");
    EXPECT_EQ(to_string_view(SaveFormat::PPSM), "Ppsm");
    EXPECT_EQ(to_string_view(SaveFormat::POTX), "Potx");
    EXPECT_EQ(to_string_view(SaveFormat::POTM), "Potm");
    EXPECT_EQ(to_string_view(SaveFormat::HTML), "Html");
    EXPECT_EQ(to_string_view(SaveFormat::SWF), "Swf");
    EXPECT_EQ(to_string_view(SaveFormat::OTP), "Otp");
    EXPECT_EQ(to_string_view(SaveFormat::PPS), "Pps");
    EXPECT_EQ(to_string_view(SaveFormat::POT), "Pot");
    EXPECT_EQ(to_string_view(SaveFormat::FODP), "Fodp");
    EXPECT_EQ(to_string_view(SaveFormat::GIF), "Gif");
    EXPECT_EQ(to_string_view(SaveFormat::HTML5), "Html5");
    EXPECT_EQ(to_string_view(SaveFormat::MD), "Md");
    EXPECT_EQ(to_string_view(SaveFormat::XML), "Xml");
}

TEST(SaveFormatTest, DistinctValues) {
    // Each enum value should be distinct.
    EXPECT_NE(SaveFormat::PPT, SaveFormat::PPTX);
    EXPECT_NE(SaveFormat::PDF, SaveFormat::XPS);
    EXPECT_NE(SaveFormat::HTML, SaveFormat::HTML5);
}

// -- Presentation property tests --

TEST(PresentationIOTest, DefaultSourceFormat) {
    Presentation pres;
    EXPECT_EQ(pres.source_format(), SourceFormat::PPTX);
}

TEST(PresentationIOTest, DefaultFirstSlideNumber) {
    Presentation pres;
    EXPECT_EQ(pres.first_slide_number(), 1);
}

TEST(PresentationIOTest, SetFirstSlideNumber) {
    Presentation pres;
    pres.set_first_slide_number(5);
    EXPECT_EQ(pres.first_slide_number(), 5);
}

TEST(PresentationIOTest, CurrentDateTime) {
    auto before = std::chrono::system_clock::now();
    Presentation pres;
    auto after = std::chrono::system_clock::now();

    // Default current_date_time should be around construction time.
    EXPECT_GE(pres.current_date_time(), before);
    EXPECT_LE(pres.current_date_time(), after);
}

TEST(PresentationIOTest, SetCurrentDateTime) {
    Presentation pres;
    auto custom_time = std::chrono::system_clock::from_time_t(1000000);
    pres.set_current_date_time(custom_time);
    EXPECT_EQ(pres.current_date_time(), custom_time);
}

TEST(PresentationIOTest, Dispose) {
    Presentation pres;
    // dispose should not throw.
    EXPECT_NO_THROW(pres.dispose());
}

TEST(PresentationIOTest, AsIPresentationComponent) {
    Presentation pres;
    IPresentationComponent* component = pres.as_i_presentation_component();
    // Should return the same presentation via the component interface.
    EXPECT_EQ(component->presentation(), pres.presentation());
}

TEST(PresentationIOTest, PresentationReturnsThis) {
    Presentation pres;
    IPresentation* ipres = pres.presentation();
    EXPECT_EQ(ipres, &pres);
}

TEST(PresentationIOTest, HasOneSlideByDefault) {
    Presentation pres;
    EXPECT_EQ(pres.slides().size(), 1);
}

TEST(PresentationIOTest, EmptyCommentAuthorsAndImages) {
    Presentation pres;
    EXPECT_EQ(pres.comment_authors().size(), 0);
    EXPECT_EQ(pres.images().size(), 0);
}
