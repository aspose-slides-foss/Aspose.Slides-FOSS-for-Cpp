// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file app_properties_part.h
/// @brief Parse and serialize docProps/app.xml (extended properties).
///
/// Handles: Application, AppVersion, Company, Manager, PresentationFormat,
/// Template, TotalTime, Slides, HiddenSlides, Notes, Paragraphs, Words,
/// MMClips, ScaleCrop, LinksUpToDate, SharedDoc, HyperlinksChanged,
/// HyperlinkBase, HeadingPairs, TitlesOfParts.

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::pptx {

/// Part name inside the OPC package.
inline constexpr std::string_view kAppPropertiesPartName = "docProps/app.xml";

/// Internal representation of a heading pair (name + count).
struct HeadingPairData {
    std::string name;
    int count = 0;

    bool operator==(const HeadingPairData&) const = default;
};

/// Parse/serialize docProps/app.xml.
///
/// Reads extended properties from the OPC package on construction,
/// exposes them as public fields, and can serialize them back via save().
class AppPropertiesPart final {
public:
    /// Construct from an OPC package, parsing docProps/app.xml if present.
    explicit AppPropertiesPart(opc::OpcPackage& package);

    /// Mark the part as dirty so save() will regenerate the XML.
    void mark_dirty();

    /// Serialize properties back to the package.
    /// Only writes if the part is dirty or was not originally present.
    void save();

    /// Reset all properties to empty/null state and mark dirty.
    void clear();

    /// @name String properties
    /// @{
    std::optional<std::string> application;
    std::optional<std::string> app_version;
    std::optional<std::string> company;
    std::optional<std::string> manager;
    std::optional<std::string> presentation_format;
    std::optional<std::string> template_name;
    std::optional<std::string> hyperlink_base;
    /// @}

    /// @name Integer properties
    /// @{
    std::optional<int> total_time;
    std::optional<int> slides;
    std::optional<int> hidden_slides;
    std::optional<int> notes;
    std::optional<int> paragraphs;
    std::optional<int> words;
    std::optional<int> mm_clips;
    /// @}

    /// @name Boolean properties
    /// @{
    std::optional<bool> scale_crop;
    std::optional<bool> links_up_to_date;
    std::optional<bool> shared_doc;
    std::optional<bool> hyperlinks_changed;
    /// @}

    /// @name Vector properties
    /// @{
    std::vector<HeadingPairData> heading_pairs;
    std::vector<std::string> titles_of_parts;
    /// @}

private:
    void parse();

    [[nodiscard]] std::optional<std::string> get_text(
        std::string_view local_name) const;
    [[nodiscard]] std::optional<int> get_int(std::string_view local_name) const;
    [[nodiscard]] std::optional<bool> get_bool(
        std::string_view local_name) const;

    void parse_heading_pairs();
    void parse_titles_of_parts();

    static void set_text(pugi::xml_node root, std::string_view local_name,
                         const std::optional<std::string>& value);
    static void set_int(pugi::xml_node root, std::string_view local_name,
                        std::optional<int> value);
    static void set_bool(pugi::xml_node root, std::string_view local_name,
                         std::optional<bool> value);

    void write_heading_pairs(pugi::xml_node root) const;
    void write_titles_of_parts(pugi::xml_node root) const;

    opc::OpcPackage& package_;
    pugi::xml_node root_;
    pugi::xml_document doc_;
    bool dirty_ = false;
    bool has_original_ = false;
};

} // namespace Aspose::Slides::Foss::Internal::pptx
