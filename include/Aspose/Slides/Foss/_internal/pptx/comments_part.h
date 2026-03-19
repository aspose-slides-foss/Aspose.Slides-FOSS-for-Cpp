// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file comments_part.h
/// @brief Comments part handling for PPTX format.
///
/// Manages individual ppt/comments/slideN.xml parts (one per slide that has

#include <chrono>
#include <cmath>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// EMU conversion factor: 1 cm = 360 000 EMU.
/// Comment positions in PPTX are stored in EMU; the public API uses cm.
inline constexpr double kCmToEmu = 360000.0;

// ---------------------------------------------------------------------------
// Free-standing datetime helpers
// ---------------------------------------------------------------------------

/// Convert a system_clock time_point to an OOXML datetime string
/// (e.g. "2024-03-15T10:30:00.000").
[[nodiscard]] std::string dt_to_str(
    std::chrono::system_clock::time_point tp);

/// Parse an OOXML datetime string to a system_clock time_point.
/// Returns std::nullopt on failure or empty input.
[[nodiscard]] std::optional<std::chrono::system_clock::time_point> str_to_dt(
    std::string_view s);

// ---------------------------------------------------------------------------
// CommentData
// ---------------------------------------------------------------------------

/// Raw data for a single comment parsed from XML.
///
/// Wraps a pugixml node and provides typed accessors for the comment
/// attributes and child elements. Changes made through the setters are
/// reflected directly in the underlying XML node.
class CommentData final {
public:
    /// Construct from a `<p:cm>` XML node.
    explicit CommentData(pugi::xml_node node) : node_(node) {}

    /// Author ID attribute.
    [[nodiscard]] int32_t author_id() const;

    /// Comment index attribute.
    [[nodiscard]] int32_t idx() const;

    /// Datetime string (OOXML format) from the `dt` attribute.
    [[nodiscard]] std::string dt_str() const;
    void set_dt_str(std::string_view value);

    /// Parent comment ID, or std::nullopt if this is a top-level comment.
    [[nodiscard]] std::optional<int32_t> parent_cm_id() const;
    void set_parent_cm_id(std::optional<int32_t> value);

    /// Comment text content (from the `<p:text>` child element).
    [[nodiscard]] std::string text() const;
    void set_text(std::string_view value);

    /// Position X in centimeters (converted from EMU).
    [[nodiscard]] double pos_x() const;
    void set_pos_x(double value);

    /// Position Y in centimeters (converted from EMU).
    [[nodiscard]] double pos_y() const;
    void set_pos_y(double value);

    /// Access the underlying XML node (for remove operations).
    [[nodiscard]] pugi::xml_node node() const { return node_; }

private:
    pugi::xml_node node_;
};

// ---------------------------------------------------------------------------
// CommentsPart
// ---------------------------------------------------------------------------

/// Manages a slide comments XML part (`ppt/comments/slideN.xml`).
///
/// One file exists per slide that has comments. Provides CRUD operations
/// for individual comment elements and static factory/lifecycle methods.
class CommentsPart final {
public:
    /// Construct by loading an existing comments part from the package.
    /// @throws std::runtime_error if the part does not exist.
    CommentsPart(opc::OpcPackage& package, std::string_view part_name);

    /// The part path inside the package.
    [[nodiscard]] const std::string& part_name() const { return part_name_; }

    /// Get all comments in this part.
    [[nodiscard]] std::vector<CommentData> get_comments() const;

    /// Get comments filtered by author ID.
    [[nodiscard]] std::vector<CommentData> get_comments_by_author(
        int32_t author_id) const;

    /// Find a comment by author ID and index.
    [[nodiscard]] std::optional<CommentData> find_comment_by_idx(
        int32_t author_id, int32_t idx) const;

    /// Find a comment by index across all authors (for parentCmId lookup).
    [[nodiscard]] std::optional<CommentData> find_comment_by_idx_all(
        int32_t idx) const;

    /// Append a new comment element and return its CommentData.
    CommentData add_comment(int32_t author_id, int32_t idx,
                            std::string_view text, double pos_x, double pos_y,
                            std::string_view dt_str,
                            std::optional<int32_t> parent_idx = std::nullopt);

    /// Insert a comment at the given position among existing comments.
    CommentData insert_comment(int32_t index, int32_t author_id, int32_t idx,
                               std::string_view text, double pos_x,
                               double pos_y, std::string_view dt_str,
                               std::optional<int32_t> parent_idx = std::nullopt);

    /// Remove a specific comment by author ID and index.
    void remove_comment(int32_t author_id, int32_t idx);

    /// Remove a comment by its XML node.
    void remove_comment_elem(pugi::xml_node elem);

    /// Remove the comment at the given positional index.
    void remove_comments_at(int32_t index);

    /// Remove all comments from this part.
    void clear();

    /// Number of comments in this part.
    [[nodiscard]] int32_t count() const;

    /// Whether this part has no comments.
    [[nodiscard]] bool is_empty() const;

    /// Persist the XML back to the package.
    void save();

    // -- Static factory / lifecycle methods --

    /// Create a new empty comments part for a slide and register all
    /// relationships and content types.
    ///
    /// @param slide_rels_manager If provided, uses an existing
    ///   RelationshipsManager so the relationship survives subsequent saves.
    [[nodiscard]] static CommentsPart create_for_slide(
        opc::OpcPackage& package, std::string_view slide_part_name,
        opc::RelationshipsManager* slide_rels_manager = nullptr);

    /// Load the comments part for a slide, if one exists.
    [[nodiscard]] static std::optional<CommentsPart> load_for_slide(
        opc::OpcPackage& package, std::string_view slide_part_name);

    /// Delete the comments part associated with a slide.
    static void delete_for_slide(opc::OpcPackage& package,
                                 std::string_view slide_part_name);

    /// Resolve a relative target path to an absolute part name.
    [[nodiscard]] static std::string resolve_target(std::string_view from_part,
                                                    std::string_view target);

    /// Compute a relative path from one part to another.
    [[nodiscard]] static std::string compute_relative_target(
        std::string_view from_part, std::string_view to_part);

private:
    void load();

    /// Collect all `<p:cm>` child nodes of the root.
    [[nodiscard]] std::vector<pugi::xml_node> cm_nodes() const;

    opc::OpcPackage& package_;
    std::string part_name_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
