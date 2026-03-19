// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file shape_type_mapping.h
/// @brief Bidirectional mapping between OOXML preset geometry names (ST_ShapeType)
///        and ShapeType enum member names.

#include <optional>
#include <string>
#include <string_view>

namespace Aspose::Slides::Foss::Internal::pptx::shape_type_mapping {

/// Convert an OOXML prstGeom prst attribute value to a ShapeType enum member name.
/// @param prst The OOXML preset geometry name (e.g., "rect", "lineInv").
/// @return The corresponding ShapeType enum member name (e.g., "RECTANGLE", "LINE_INVERSE"),
///         or std::nullopt if the prst value is not recognized.
std::optional<std::string_view> ooxml_prst_to_shape_type_name(std::string_view prst);

/// Convert a ShapeType enum member name to an OOXML prstGeom prst attribute value.
/// @param name The ShapeType enum member name (e.g., "RECTANGLE", "LINE_INVERSE").
/// @return The corresponding OOXML prst value (e.g., "rect", "lineInv"),
///         or std::nullopt if the name is not recognized.
std::optional<std::string_view> shape_type_name_to_ooxml_prst(std::string_view name);

} // namespace Aspose::Slides::Foss::Internal::pptx::shape_type_mapping
