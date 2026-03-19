// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Constants which define the format of a saved presentation.
enum class SaveFormat {
    PPT,   ///< Save presentation in PPT format.
    PDF,   ///< Save presentation in PDF format.
    XPS,   ///< Save presentation in XPS format.
    PPTX,  ///< Save presentation in PPTX format.
    PPSX,  ///< Save presentation in PPSX (slideshow) format.
    TIFF,  ///< Save presentation as multi-page TIFF image.
    ODP,   ///< Save presentation in ODP format.
    PPTM,  ///< Save presentation in PPTM (macro-enabled) format.
    PPSM,  ///< Save presentation in PPSM (macro-enabled slideshow) format.
    POTX,  ///< Save presentation in POTX (template) format.
    POTM,  ///< Save presentation in POTM (macro-enabled template) format.
    HTML,  ///< Save presentation in HTML format.
    SWF,   ///< Save presentation in SWF format.
    OTP,   ///< Save presentation in OTP (template) format.
    PPS,   ///< Save presentation in PPS format.
    POT,   ///< Save presentation in POT format.
    FODP,  ///< Save presentation in FODP format.
    GIF,   ///< Save presentation in GIF format.
    HTML5, ///< Save presentation in HTML5 format.
    MD,    ///< Save presentation in Markdown format.
    XML,   ///< Save presentation in PowerPoint XML format.
};

/// Returns the string representation of a SaveFormat value.
constexpr std::string_view to_string_view(SaveFormat value) {
    switch (value) {
        case SaveFormat::PPT:  return "Ppt";
        case SaveFormat::PDF:  return "Pdf";
        case SaveFormat::XPS:  return "Xps";
        case SaveFormat::PPTX: return "Pptx";
        case SaveFormat::PPSX: return "Ppsx";
        case SaveFormat::TIFF: return "Tiff";
        case SaveFormat::ODP:  return "Odp";
        case SaveFormat::PPTM: return "Pptm";
        case SaveFormat::PPSM: return "Ppsm";
        case SaveFormat::POTX: return "Potx";
        case SaveFormat::POTM: return "Potm";
        case SaveFormat::HTML: return "Html";
        case SaveFormat::SWF:  return "Swf";
        case SaveFormat::OTP:  return "Otp";
        case SaveFormat::PPS:  return "Pps";
        case SaveFormat::POT:  return "Pot";
        case SaveFormat::FODP: return "Fodp";
        case SaveFormat::GIF:  return "Gif";
        case SaveFormat::HTML5: return "Html5";
        case SaveFormat::MD:   return "Md";
        case SaveFormat::XML:  return "Xml";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
