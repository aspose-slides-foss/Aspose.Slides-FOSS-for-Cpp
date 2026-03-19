// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file exporter_registry.h
/// @brief Central registry for presentation format exporters.

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "exporter_base.h"

namespace Aspose::Slides::Foss::Internal::export_ {

/// Factory function type that creates an ExporterBase instance.
using ExporterFactory = std::function<std::unique_ptr<ExporterBase>()>;

/// Central registry for format exporters.
///
/// Maintains a mapping from SaveFormat value strings to their corresponding
/// exporter factories. New exporters can be registered dynamically, making
/// it easy to add new export formats.
///
/// @code
///     // Register an exporter
///     ExporterRegistry::register_exporter<PptxExporter>();
///
///     // Get an exporter for a format
///     auto exporter = ExporterRegistry::get_exporter("Pptx");
///     if (exporter) {
///         exporter->export_presentation(package, "output.pptx");
///     }
/// @endcode
class ExporterRegistry final {
public:
    ExporterRegistry() = delete;

    /// Register an exporter class for its supported formats.
    ///
    /// Calls T::get_supported_formats() to discover which format strings
    /// the exporter handles, then maps each to a factory that creates T.
    ///
    /// @tparam T Exporter class derived from ExporterBase.
    ///           Must have a static get_supported_formats() method.
    template <typename T>
        requires std::is_base_of_v<ExporterBase, T>
    static void register_exporter() {
        for (const auto& format : T::get_supported_formats()) {
            exporters_[format] = []() -> std::unique_ptr<ExporterBase> {
                return std::make_unique<T>();
            };
        }
    }

    /// Unregister an exporter for a specific format.
    ///
    /// @param format_value The SaveFormat value string to unregister.
    /// @return True if unregistered, false if not found.
    static bool unregister_exporter(std::string_view format_value);

    /// Get an exporter instance for a specific format.
    ///
    /// @param format_value The SaveFormat value string (e.g., "Pptx", "Pdf").
    /// @return Exporter instance, or nullptr if no exporter is registered.
    [[nodiscard]] static std::unique_ptr<ExporterBase>
    get_exporter(std::string_view format_value);

    /// Get the exporter factory for a specific format.
    ///
    /// @param format_value The SaveFormat value string.
    /// @return Factory function, or std::nullopt if not registered.
    [[nodiscard]] static std::optional<ExporterFactory>
    get_exporter_class(std::string_view format_value);

    /// Check if a format has a registered exporter.
    ///
    /// @param format_value The SaveFormat value string.
    /// @return True if an exporter is registered for this format.
    [[nodiscard]] static bool is_format_supported(std::string_view format_value);

    /// Get all formats that have registered exporters.
    ///
    /// @return List of SaveFormat value strings.
    [[nodiscard]] static std::vector<std::string> get_supported_formats();

    /// Clear all registered exporters. Mainly for testing.
    static void clear();

private:
    static std::unordered_map<std::string, ExporterFactory> exporters_;
};

} // namespace Aspose::Slides::Foss::Internal::export_
