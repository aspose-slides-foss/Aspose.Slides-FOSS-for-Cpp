// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string_view>

namespace Aspose::Slides::Foss {

/// Represents the line dash style.
enum class LineDashStyle {
    NOT_DEFINED,
    SOLID,
    DOT,
    DASH,
    LARGE_DASH,
    DASH_DOT,
    LARGE_DASH_DOT,
    LARGE_DASH_DOT_DOT,
    SYSTEM_DASH,
    SYSTEM_DOT,
    SYSTEM_DASH_DOT,
    SYSTEM_DASH_DOT_DOT,
    CUSTOM,
};

/// Returns the string representation of a LineDashStyle value.
constexpr std::string_view to_string_view(LineDashStyle value) {
    switch (value) {
        case LineDashStyle::NOT_DEFINED: return "NotDefined";
        case LineDashStyle::SOLID: return "Solid";
        case LineDashStyle::DOT: return "Dot";
        case LineDashStyle::DASH: return "Dash";
        case LineDashStyle::LARGE_DASH: return "LargeDash";
        case LineDashStyle::DASH_DOT: return "DashDot";
        case LineDashStyle::LARGE_DASH_DOT: return "LargeDashDot";
        case LineDashStyle::LARGE_DASH_DOT_DOT: return "LargeDashDotDot";
        case LineDashStyle::SYSTEM_DASH: return "SystemDash";
        case LineDashStyle::SYSTEM_DOT: return "SystemDot";
        case LineDashStyle::SYSTEM_DASH_DOT: return "SystemDashDot";
        case LineDashStyle::SYSTEM_DASH_DOT_DOT: return "SystemDashDotDot";
        case LineDashStyle::CUSTOM: return "Custom";
    }
    return "Unknown";
}

} // namespace Aspose::Slides::Foss
