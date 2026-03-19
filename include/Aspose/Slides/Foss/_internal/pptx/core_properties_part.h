// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file core_properties_part.h
/// @brief Parse and serialize docProps/core.xml (Dublin Core metadata).
///
/// Handles: title, subject, creator (author), keywords, description (comments),
/// category, contentStatus, contentType, lastModifiedBy, revision,
/// created, modified, lastPrinted.

#include <chrono>
#include <optional>
#include <string>
#include <string_view>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Part name inside the OPC package.
inline constexpr std::string_view kCorePropertiesPartName =
    "docProps/core.xml";

/// A point in time (UTC) used for Dublin Core date properties.
using TimePoint = std::chrono::system_clock::time_point;

/// Parse a W3CDTF datetime string to a time point.
/// @param text ISO-8601 / W3CDTF string (e.g. "2024-01-15T10:30:00Z").
/// @return Parsed time point, or nullopt on failure.
[[nodiscard]] std::optional<TimePoint> parse_w3cdtf(std::string_view text);

/// Format a time point as a W3CDTF string.
/// @param tp Time point to format.
/// @return Formatted string like "2024-01-15T10:30:00Z", or nullopt if input is nullopt.
[[nodiscard]] std::optional<std::string> format_w3cdtf(
    std::optional<TimePoint> tp);

/// Parse/serialize docProps/core.xml (Dublin Core metadata).
///
/// Reads core properties from the OPC package on construction,
/// exposes them as public fields, and can serialize them back via save().
class CorePropertiesPart final {
public:
    /// Construct from an OPC package, parsing docProps/core.xml if present.
    explicit CorePropertiesPart(opc::OpcPackage& package);

    /// Mark the part as dirty so save() will regenerate the XML.
    void mark_dirty();

    /// Serialize properties back to the package.
    /// Only writes if the part is dirty or was not originally present.
    void save();

    /// Reset all properties to empty/null state and mark dirty.
    void clear();

    /// @name String properties
    /// @{
    std::optional<std::string> title;
    std::optional<std::string> subject;
    std::optional<std::string> creator;
    std::optional<std::string> keywords;
    std::optional<std::string> description;
    std::optional<std::string> category;
    std::optional<std::string> content_status;
    std::optional<std::string> content_type;
    std::optional<std::string> last_modified_by;
    std::optional<std::string> revision;
    /// @}

    /// @name Date properties
    /// @{
    std::optional<TimePoint> created;
    std::optional<TimePoint> modified;
    std::optional<TimePoint> last_printed;
    /// @}

private:
    void parse();

    [[nodiscard]] std::optional<std::string> get_text(
        const char* prefix, const char* local_name) const;

    static void set_dc(pugi::xml_node root, const char* local_name,
                       const std::optional<std::string>& value);
    static void set_cp(pugi::xml_node root, const char* local_name,
                       const std::optional<std::string>& value);
    static void set_dcterms_date(pugi::xml_node root, const char* local_name,
                                 std::optional<TimePoint> tp);

    opc::OpcPackage& package_;
    pugi::xml_node root_;
    pugi::xml_document doc_;
    bool dirty_ = false;
    bool has_original_ = false;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
