// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file pptx_exporter.h
/// @brief PPTX format exporter for Office Open XML presentation formats.

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "exporter_base.h"

namespace Aspose::Slides::Foss::Internal::export_ {

/// Exporter for PPTX and related Office Open XML formats.
///
/// Supports:
/// - PPTX: Standard PowerPoint presentation
/// - PPTM: Macro-enabled presentation
/// - PPSX: PowerPoint show (opens in slideshow mode)
/// - PPSM: Macro-enabled show
/// - POTX: PowerPoint template
/// - POTM: Macro-enabled template
///
/// These formats are all OPC packages with different content types
/// for the main presentation part.
class PptxExporter final : public ExporterBase {
public:
    /// Initialize the PPTX exporter.
    ///
    /// @param target_format The specific format to export to (default: "Pptx").
    explicit PptxExporter(std::string_view target_format = "Pptx");

    ~PptxExporter() override = default;

    /// Export the presentation to a PPTX file.
    ///
    /// @param package The OPC package containing the presentation.
    /// @param path The output file path.
    /// @param options Optional ISaveOptions (currently unused for PPTX).
    void export_to_path(
        opc::OpcPackage& package,
        std::string_view path,
        const std::any& options = {}) override;

    /// Export the presentation to a stream.
    ///
    /// @param package The OPC package containing the presentation.
    /// @param stream The output stream.
    /// @param options Optional ISaveOptions (currently unused for PPTX).
    void export_to_stream(
        opc::OpcPackage& package,
        std::ostream& stream,
        const std::any& options = {}) override;

    /// Register this exporter with ExporterRegistry, once per process.
    ///
    /// The registration used to be a namespace-scope initialiser, which a
    /// static library is free to drop along with the object file when nothing
    /// else refers to it. Calling this before the registry is consulted is
    /// what guarantees the map is populated, in a link as well as at runtime.
    static void ensure_registered();

    /// Get all OPC-based presentation formats.
    ///
    /// @return List of format strings: {"Pptx", "Pptm", "Ppsx", "Ppsm", "Potx", "Potm"}.
    [[nodiscard]] static std::vector<std::string> get_supported_formats();

    /// Check whether this exporter handles the given format.
    ///
    /// @param format_value A SaveFormat value string, e.g. "Potx" or "Pdf".
    /// @return True for the six OPC presentation formats, false otherwise.
    [[nodiscard]] static bool is_format_supported(std::string_view format_value);

    /// The main presentation part content type a format requires.
    ///
    /// The six OPC presentation formats share one package layout and differ
    /// only in this one string. PowerPoint refuses a file whose extension and
    /// main content type disagree, so it is not optional.
    ///
    /// @param format_value A SaveFormat value string.
    /// @return The content type, or an empty string for an unsupported format.
    [[nodiscard]] static std::string_view main_content_type_for(
        std::string_view format_value);

    /// Update the content type of the main presentation part.
    ///
    /// Resolves the main part through the package's root relationships and
    /// writes the content type the target format requires, replacing whatever
    /// the source package declared.
    void update_content_type_if_needed(opc::OpcPackage& package);

private:

    /// Mapping from SaveFormat values to main presentation content types.
    static const std::unordered_map<std::string, std::string> kContentTypes;

    std::string target_format_;
};

} // namespace Aspose::Slides::Foss::Internal::export_
