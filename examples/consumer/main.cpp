// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd
//
// Creates a one-slide presentation with a single shape and saves it, using
// nothing but the installed package.

#include <cstdio>
#include <exception>
#include <string>

// presentation.h forward-declares the types its collections return; the
// definitions come from these. A consumer that reaches through
// slides()[0].shapes() needs slide.h and shape_collection.h as well.
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/version.h>

int main(int argc, char** argv) {
    const std::string out = argc > 1 ? argv[1] : "consumer_example.pptx";

    try {
        Aspose::Slides::Foss::Presentation pres;
        auto& shape = pres.slides()[0].shapes().add_auto_shape(
            Aspose::Slides::Foss::ShapeType::RECTANGLE, 50, 50, 400, 120);
        shape.add_text_frame("Written by a consumer of the installed package");
        pres.save(out, Aspose::Slides::Foss::SaveFormat::PPTX);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "failed: %s\n", e.what());
        return 1;
    }

    std::printf("Aspose.Slides FOSS for C++ %s wrote %s\n",
                ASPOSE_SLIDES_FOSS_VERSION_STRING, out.c_str());
    return 0;
}
