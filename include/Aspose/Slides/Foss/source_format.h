// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents source file format.
enum class SourceFormat {
    PPT,
    PPTX,
    ODP,
};

/// Returns the string representation of a SourceFormat value.
constexpr std::string_view to_string_view(SourceFormat value) {
    switch (value) {
        case SourceFormat::PPT: return "Ppt";
        case SourceFormat::PPTX: return "Pptx";
        case SourceFormat::ODP: return "Odp";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
