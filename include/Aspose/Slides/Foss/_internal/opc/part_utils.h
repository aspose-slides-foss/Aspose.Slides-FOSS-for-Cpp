// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file part_utils.h
/// @brief Utility functions for OPC part path resolution and cloning.

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::opc {

/// Resolve a relative target path against a base part's directory.
/// Handles ".." segments and absolute targets (leading '/').
/// @param base_part The referencing part's absolute path (e.g., "ppt/slideMasters/slideMaster1.xml").
/// @param target The target to resolve (absolute or relative).
/// @return Resolved absolute part path.
[[nodiscard]] std::string resolve_target(std::string_view base_part,
                                         std::string_view target);

/// Compute a relative path from a source part to a target part.
/// @param source_part The part containing the reference.
/// @param target_part The target part's absolute path.
/// @return A relative path suitable for use in .rels files.
[[nodiscard]] std::string compute_relative_target(std::string_view source_part,
                                                   std::string_view target_part);

/// Clone a related part (theme, image, etc.) from one package to another.
/// Copies the binary content unchanged. If the target already exists in the
/// destination, the content is overwritten.
/// @param source_package Source OPC package.
/// @param source_target Absolute path of the part to clone.
/// @param dest_package Destination OPC package.
/// @param dest_part_name The part that will reference the cloned part (used for path context).
/// @param rel_type The relationship type (used for context only).
/// @return Absolute path of the cloned part in the destination.
[[nodiscard]] std::string clone_related_part(OpcPackage& source_package,
                                              std::string_view source_target,
                                              OpcPackage& dest_package,
                                              std::string_view dest_part_name,
                                              std::string_view rel_type);

/// Update all r:id attribute references in an XML tree using a mapping.
/// Finds attributes in the relationships namespace ("r:id", "{...}id") and
/// remaps their values according to the provided old-to-new mapping.
/// @param root Root XML node to process recursively.
/// @param rid_mapping Map of old relationship IDs to new ones.
void update_rid_references(pugi::xml_node root,
                           const std::unordered_map<std::string, std::string>& rid_mapping);

} // namespace Aspose::Slides::Foss::Internal::opc
