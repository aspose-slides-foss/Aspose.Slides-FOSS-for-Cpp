// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file slide_part.h
/// @brief Manages ppt/slides/slideN.xml parts.

#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Manages a slide XML part (ppt/slides/slideN.xml).
///
/// Provides access to slide XML, layout part resolution, and save support.
class SlidePart final {
public:
    /// Construct a slide part.
    /// @param package The OPC package containing the slide.
    /// @param part_name The part path (e.g., "ppt/slides/slide1.xml").
    /// @throws std::runtime_error if the part is not found in the package.
    SlidePart(opc::OpcPackage& package, std::string_view part_name);

    /// Get the part name of this slide.
    [[nodiscard]] const std::string& part_name() const;

    /// Get a reference to the OPC package.
    [[nodiscard]] opc::OpcPackage& package();
    [[nodiscard]] const opc::OpcPackage& package() const;

    /// Get the layout slide part name from this slide's relationships.
    /// @return Resolved absolute part path for the slide layout, or empty if not found.
    [[nodiscard]] std::string layout_part_name() const;

    /// Save the slide XML back to the package.
    void save();

    /// Get the XML root element of the slide.
    [[nodiscard]] pugi::xml_node root() const { return root_; }

    /// Get the relationships manager for this slide part.
    [[nodiscard]] opc::RelationshipsManager& rels_manager() { return rels_manager_; }
    [[nodiscard]] const opc::RelationshipsManager& rels_manager() const { return rels_manager_; }

    /// Resolve a relative target path to an absolute part name.
    [[nodiscard]] std::string resolve_target(std::string_view target) const;

private:
    void load();

    opc::OpcPackage& package_;
    std::string part_name_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
    opc::RelationshipsManager rels_manager_;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
