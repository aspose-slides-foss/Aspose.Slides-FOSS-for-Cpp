// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file table_style_mapping.h
/// @brief Bidirectional mapping between OOXML table style GUIDs and
///        TableStylePreset enum member names.

#include <optional>
#include <string_view>

namespace Aspose::Slides::Foss::Internal::pptx::table_style_mapping {

/// Look up a TableStylePreset enum member name from an OOXML table style GUID.
/// @param guid The GUID string including braces, e.g.
///        "{2D5ABB26-0587-4C30-8999-92F81FD0307C}".
/// @return The preset name (e.g. "NO_STYLE_NO_GRID"), or std::nullopt if
///         the GUID is not recognized.
std::optional<std::string_view> guid_to_preset(std::string_view guid);

/// Look up an OOXML table style GUID from a TableStylePreset enum member name.
/// @param preset The preset name, e.g. "NO_STYLE_NO_GRID".
/// @return The GUID string including braces, or std::nullopt if the name is
///         not recognized.
std::optional<std::string_view> preset_to_guid(std::string_view preset);

} // namespace Aspose::Slides::Foss::Internal::pptx::table_style_mapping
