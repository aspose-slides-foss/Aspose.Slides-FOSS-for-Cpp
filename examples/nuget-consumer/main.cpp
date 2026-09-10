// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd
//
// A consumer of the NuGet package, not of this source tree and not of an install
// prefix. The project beside this file names the package and nothing else: no
// include directory, no library, no path of any kind. Everything it needs comes
// from the .targets file NuGet imports out of the package.
//
// That is what makes this a test rather than a demonstration. If the .targets is
// at the wrong path inside the package, this fails to compile on the first
// #include -- which is exactly how the mistake would reach a user.

#include <cstdio>
#include <exception>
#include <string>

#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/export/save_format.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/shape_collection.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/slide.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/version.h>

// pugixml is in this library's public interface: including presentation.h above
// already pulled in <pugixml.hpp>. Naming it here makes that explicit, so that a
// package which shipped our headers but not pugixml's fails on this line with an
// obvious cause rather than deep inside a header of ours.
#include <pugixml.hpp>

int main(int argc, char** argv) {
    const std::string out = argc > 1 ? argv[1] : "nuget_consumer.pptx";

    try {
        Aspose::Slides::Foss::Presentation presentation;
        auto& shape = presentation.slides()[0].shapes().add_auto_shape(
            Aspose::Slides::Foss::ShapeType::RECTANGLE, 50, 50, 400, 120);
        shape.add_text_frame("Written by a consumer of the NuGet package");
        presentation.save(out, Aspose::Slides::Foss::SaveFormat::PPTX);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "failed: %s\n", e.what());
        return 1;
    }

    std::printf("Aspose.Slides FOSS for C++ %s wrote %s\n",
                ASPOSE_SLIDES_FOSS_VERSION_STRING, out.c_str());
    return 0;
}
