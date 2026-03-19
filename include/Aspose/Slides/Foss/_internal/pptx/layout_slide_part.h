// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file layout_slide_part.h
/// @brief Manages ppt/slideLayouts/slideLayoutN.xml parts (read-only for now).

#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Manages a layout slide XML part (ppt/slideLayouts/slideLayoutN.xml).
///
/// Read-only for now; provides access to layout slide properties
/// and the associated master slide part.
class LayoutSlidePart final {
public:
    /// Construct a layout slide part.
    /// @param package The OPC package containing the layout slide.
    /// @param part_name The part path (e.g., "ppt/slideLayouts/slideLayout1.xml").
    /// @throws std::runtime_error if the part is not found in the package.
    LayoutSlidePart(opc::OpcPackage& package, std::string_view part_name);

    /// Get the part name of this layout slide.
    [[nodiscard]] const std::string& part_name() const;

    /// Get the layout slide name from <p:cSld name="...">.
    /// @return The name attribute value, or empty string if not present.
    [[nodiscard]] std::string name() const;

    /// Get the layout type from <p:sldLayout type="...">.
    /// @return The type attribute value, or empty string if not present.
    [[nodiscard]] std::string type() const;

    /// Get the master slide part name from this layout's relationships.
    /// @return Resolved absolute part path for the slide master, or empty if not found.
    [[nodiscard]] std::string master_part_name() const;

    /// Save the layout slide XML back to the package.
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
