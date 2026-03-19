// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file comment_authors_part.h
/// @brief Comment authors part handling for PPTX format.
///
/// Manages the ppt/commentAuthors.xml part which holds all comment author
/// definitions used across a presentation's comments.

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Part path inside the OPC package.
inline constexpr std::string_view kCommentAuthorsPartName =
    "ppt/commentAuthors.xml";

// ---------------------------------------------------------------------------
// AuthorData
// ---------------------------------------------------------------------------

/// Raw data for a comment author parsed from XML.
///
/// Wraps a pugixml node and provides typed accessors for the author
/// attributes. Changes made through the setters are reflected directly
/// in the underlying XML node.
class AuthorData final {
public:
    /// Construct from a `<p:cmAuthor>` XML node.
    explicit AuthorData(pugi::xml_node node) : node_(node) {}

    /// Author numeric ID.
    [[nodiscard]] int32_t id() const;

    /// Author display name.
    [[nodiscard]] std::string name() const;
    void set_name(std::string_view value);

    /// Author initials.
    [[nodiscard]] std::string initials() const;
    void set_initials(std::string_view value);

    /// Last comment index used by this author.
    [[nodiscard]] int32_t last_idx() const;
    void set_last_idx(int32_t value);

    /// Color index for this author (cycles 0–9).
    [[nodiscard]] int32_t clr_idx() const;

    /// Access the underlying XML node.
    [[nodiscard]] pugi::xml_node node() const { return node_; }

private:
    pugi::xml_node node_;
};

// ---------------------------------------------------------------------------
// CommentAuthorsPart
// ---------------------------------------------------------------------------

/// Manages the comment authors XML part (`ppt/commentAuthors.xml`).
///
/// This part holds all author definitions used across the presentation's
/// comments. Provides CRUD operations and a globally-unique comment index
/// allocator.
class CommentAuthorsPart final {
public:
    /// Construct by loading (or creating) the comment authors part.
    explicit CommentAuthorsPart(opc::OpcPackage& package);

    /// Get all authors in this part.
    [[nodiscard]] std::vector<AuthorData> get_authors() const;

    /// Find an author by numeric ID.
    [[nodiscard]] std::optional<AuthorData> find_author_by_id(
        int32_t author_id) const;

    /// Add a new author and return its AuthorData.
    AuthorData add_author(std::string_view name, std::string_view initials);

    /// Remove an author by numeric ID.
    void remove_author(int32_t author_id);

    /// Remove all authors.
    void clear();

    /// Return the next globally-unique comment index.
    ///
    /// OOXML parentCmId references idx values that must be unique across ALL
    /// authors within the presentation (not just per-author). This method
    /// takes the maximum lastIdx across every author, increments it, and
    /// updates the target author's lastIdx.
    int32_t next_comment_idx(int32_t author_id);

    /// Persist the XML back to the package.
    void save();

    /// Ensure that commentAuthors.xml is registered in content types and
    /// the presentation has a relationship to it. Call before first save.
    ///
    /// @param presentation_part_name The part name of the presentation
    ///   (e.g. "ppt/presentation.xml").
    static void ensure_registered(opc::OpcPackage& package,
                                  std::string_view presentation_part_name);

private:
    void load();

    opc::OpcPackage& package_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
