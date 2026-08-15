// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file exporter_registry.cpp
/// @brief Implementation of the ExporterRegistry class.

#include "Aspose/Slides/Foss/_internal/export/exporter_registry.h"

namespace Aspose::Slides::Foss::Internal::export_ {

std::unordered_map<std::string, ExporterFactory>& ExporterRegistry::exporters() {
    static std::unordered_map<std::string, ExporterFactory> map;
    return map;
}

bool ExporterRegistry::unregister_exporter(std::string_view format_value) {
    auto it = exporters().find(std::string(format_value));
    if (it != exporters().end()) {
        exporters().erase(it);
        return true;
    }
    return false;
}

std::unique_ptr<ExporterBase>
ExporterRegistry::get_exporter(std::string_view format_value) {
    auto it = exporters().find(std::string(format_value));
    if (it != exporters().end()) {
        return it->second();
    }
    return nullptr;
}

std::optional<ExporterFactory>
ExporterRegistry::get_exporter_class(std::string_view format_value) {
    auto it = exporters().find(std::string(format_value));
    if (it != exporters().end()) {
        return it->second;
    }
    return std::nullopt;
}

bool ExporterRegistry::is_format_supported(std::string_view format_value) {
    return exporters().contains(std::string(format_value));
}

std::vector<std::string> ExporterRegistry::get_supported_formats() {
    std::vector<std::string> formats;
    formats.reserve(exporters().size());
    for (const auto& [key, _] : exporters()) {
        formats.push_back(key);
    }
    return formats;
}

void ExporterRegistry::clear() {
    exporters().clear();
}

} // namespace Aspose::Slides::Foss::Internal::export_
