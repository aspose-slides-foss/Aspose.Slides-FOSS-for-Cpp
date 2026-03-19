// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file master_slide_part.h
/// @brief Manages ppt/slideMasters/slideMasterN.xml parts (read-only for now).

#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Manages a master slide XML part (ppt/slideMasters/slideMasterN.xml).
///
/// Read-only for now; provides access to master slide properties
/// and the list of associated layout slide parts.
class MasterSlidePart final {
public:
    /// Construct a master slide part.
    /// @param package The OPC package containing the master slide.
    /// @param part_name The part path (e.g., "ppt/slideMasters/slideMaster1.xml").
    /// @throws std::runtime_error if the part is not found in the package.
    MasterSlidePart(opc::OpcPackage& package, std::string_view part_name);

    /// Get the part name of this master slide.
    [[nodiscard]] const std::string& part_name() const;

    /// Get the master slide name from <p:cSld name="...">.
    /// @return The name attribute value, or empty string if not present.
    [[nodiscard]] std::string name() const;

    /// Set the master slide name on <p:cSld name="...">.
    /// @param value The new name to set.
    void set_name(std::string_view value);

    /// Get list of layout slide part names from this master's relationships.
    /// @return Resolved absolute part paths for each slide layout relationship.
    [[nodiscard]] std::vector<std::string> layout_part_names() const;

    /// Save the master slide XML back to the package.
    void save();

private:
    void load();

    /// Resolve a relative target path to an absolute part name.
    [[nodiscard]] std::string resolve_target(std::string_view target) const;

    opc::OpcPackage& package_;
    std::string part_name_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
    opc::RelationshipsManager rels_manager_;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
