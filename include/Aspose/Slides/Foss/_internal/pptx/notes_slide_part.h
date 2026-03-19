// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file notes_slide_part.h
/// @brief Manages ppt/notesSlides/notesSlideN.xml parts.

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Notes slide placeholder type constants.
namespace ph_type {
inline constexpr std::string_view kBody = "body";
inline constexpr std::string_view kDt = "dt";
inline constexpr std::string_view kFtr = "ftr";
inline constexpr std::string_view kHdr = "hdr";
inline constexpr std::string_view kSldNum = "sldNum";
inline constexpr std::string_view kSldImg = "sldImg";
} // namespace ph_type

/// Manages a notes slide XML part (ppt/notesSlides/notesSlideN.xml).
///
/// Provides access to notes text and placeholder management.
class NotesSlidePart final {
public:
    /// Construct a notes slide part from an existing part in the package.
    /// @param package The OPC package containing the notes slide.
    /// @param part_name The part path (e.g., "ppt/notesSlides/notesSlide1.xml").
    /// @throws std::runtime_error if the part is not found or cannot be parsed.
    NotesSlidePart(opc::OpcPackage& package, std::string_view part_name);

    /// Get the part name of this notes slide.
    [[nodiscard]] const std::string& part_name() const;

    /// Get the slide name from <p:cSld name="...">.
    /// @return The name attribute value, or empty string if not present.
    [[nodiscard]] std::string name() const;

    /// Set the slide name on <p:cSld name="...">.
    void set_name(std::string_view value);

    /// Get the txBody element of the notes body placeholder.
    /// @return The <p:txBody> node, or an empty (null) node if not found.
    [[nodiscard]] pugi::xml_node get_notes_txbody() const;

    /// Check if a placeholder of the given type exists.
    /// @param type The placeholder type string (e.g., "body", "ftr", "hdr").
    [[nodiscard]] bool has_placeholder(std::string_view type) const;

    /// Remove the placeholder shape of the given type.
    void remove_placeholder(std::string_view type);

    /// Add a minimal placeholder shape of the given type (if not already present).
    void add_placeholder(std::string_view type);

    /// Set text content for a placeholder shape. Adds the placeholder if absent.
    /// @param type The placeholder type string.
    /// @param text The text to set.
    void set_placeholder_text(std::string_view type, std::string_view text);

    /// Save the notes slide XML back to the package.
    void save();

    /// Create a new empty notes slide in the package for a given slide.
    /// @param package The OPC package.
    /// @param slide_part_name The part name of the owning slide.
    /// @return The newly created NotesSlidePart.
    static NotesSlidePart create_empty(opc::OpcPackage& package,
                                       std::string_view slide_part_name);

    /// Delete a notes slide and its associated files from the package.
    /// @param package The OPC package.
    /// @param part_name The notes slide part name to delete.
    static void remove(opc::OpcPackage& package, std::string_view part_name);

    /// Compute a relative path from one part to another.
    [[nodiscard]] static std::string compute_relative_target(
        std::string_view from_part, std::string_view to_part);

    /// Find the notes master part name in the package.
    /// @return The part name, or nullopt if not found.
    [[nodiscard]] static std::optional<std::string> find_notes_master(
        opc::OpcPackage& package);

    /// Build a minimal notes slide XML document.
    /// @return UTF-8 encoded XML bytes.
    [[nodiscard]] static std::vector<uint8_t> build_notes_xml();

private:
    void load();

    /// Get the spTree element from the notes slide.
    [[nodiscard]] pugi::xml_node get_sp_tree() const;

    /// Find the first placeholder shape with the given type.
    [[nodiscard]] pugi::xml_node find_placeholder(std::string_view type) const;

    /// Build a minimal placeholder shape element.
    [[nodiscard]] static pugi::xml_node build_placeholder_shape(
        pugi::xml_node parent, std::string_view type, int shape_id);

    /// Resolve a relative target path to an absolute part name.
    [[nodiscard]] std::string resolve_target(std::string_view target) const;

    /// Check if a placeholder type is text-bearing (dt, ftr, hdr).
    [[nodiscard]] static bool is_text_placeholder(std::string_view type);

    opc::OpcPackage& package_;
    std::string part_name_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
    opc::RelationshipsManager rels_manager_;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
