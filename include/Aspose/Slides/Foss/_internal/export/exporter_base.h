// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file exporter_base.h
/// @brief Abstract base class for presentation format exporters.

#include <any>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace Aspose::Slides::Foss::Internal::opc {
class OpcPackage;
} // namespace Aspose::Slides::Foss::Internal::opc

namespace Aspose::Slides::Foss::Internal::export_ {

/// Abstract base class for presentation format exporters.
///
/// Each exporter handles conversion from the internal presentation
/// representation to a specific output format (PPTX, PDF, HTML, etc.).
///
/// Subclasses should override:
/// - export_to_path(): Export to a file path
/// - export_to_stream(): Export to a binary stream
/// - get_supported_formats(): Return list of SaveFormat values supported
class ExporterBase {
public:
    virtual ~ExporterBase() = 0;

    /// Export the presentation to a file path.
    ///
    /// @param package The OPC package containing the presentation data.
    /// @param path The output file path.
    /// @param options Optional export options specific to the format.
    /// @throws std::ios_base::failure If the file cannot be written.
    /// @throws std::invalid_argument If the options are invalid.
    virtual void export_to_path(
        opc::OpcPackage& package,
        std::string_view path,
        const std::any& options = {});

    /// Export the presentation to a binary stream.
    ///
    /// @param package The OPC package containing the presentation data.
    /// @param stream The output stream with write capability.
    /// @param options Optional export options specific to the format.
    /// @throws std::ios_base::failure If the stream cannot be written to.
    /// @throws std::invalid_argument If the options are invalid.
    virtual void export_to_stream(
        opc::OpcPackage& package,
        std::ostream& stream,
        const std::any& options = {});

    /// Get the list of SaveFormat values this exporter supports.
    ///
    /// @return List of SaveFormat enum value strings (e.g., {"Pptx", "Pptm"}).
    [[nodiscard]] static std::vector<std::string> get_supported_formats();

    /// Export to either a file path or stream.
    ///
    /// Dispatches to export_to_path() when called with a string path,
    /// or export_to_stream() when called with a stream.
    ///
    /// @param package The OPC package containing the presentation data.
    /// @param path The output file path.
    /// @param options Optional export options specific to the format.
    void export_presentation(
        opc::OpcPackage& package,
        std::string_view path,
        const std::any& options = {});

    /// @overload
    /// @param package The OPC package containing the presentation data.
    /// @param stream The output stream.
    /// @param options Optional export options specific to the format.
    void export_presentation(
        opc::OpcPackage& package,
        std::ostream& stream,
        const std::any& options = {});
};

} // namespace Aspose::Slides::Foss::Internal::export_
