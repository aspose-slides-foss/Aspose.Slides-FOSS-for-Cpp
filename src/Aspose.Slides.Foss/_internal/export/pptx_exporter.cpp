// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file pptx_exporter.cpp
/// @brief Implementation of the PptxExporter and PptxExporterFactory classes.

#include "Aspose/Slides/Foss/_internal/export/pptx_exporter.h"

#include <filesystem>

#include "Aspose/Slides/Foss/_internal/export/exporter_registry.h"
#include "Aspose/Slides/Foss/_internal/opc/opc_package.h"

namespace Aspose::Slides::Foss::Internal::export_ {

const std::unordered_map<std::string, std::string> PptxExporter::kContentTypes = {
    {"Pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation.main+xml"},
    {"Pptm", "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml"},
    {"Ppsx", "application/vnd.openxmlformats-officedocument.presentationml.slideshow.main+xml"},
    {"Ppsm", "application/vnd.ms-powerpoint.slideshow.macroEnabled.main+xml"},
    {"Potx", "application/vnd.openxmlformats-officedocument.presentationml.template.main+xml"},
    {"Potm", "application/vnd.ms-powerpoint.template.macroEnabled.main+xml"},
};

PptxExporter::PptxExporter(std::string_view target_format)
    : target_format_(target_format) {}

void PptxExporter::export_to_path(
    opc::OpcPackage& package,
    std::string_view path,
    const std::any& /*options*/) {
    update_content_type_if_needed(package);
    auto& mem_pkg = dynamic_cast<opc::InMemoryOpcPackage&>(package);
    mem_pkg.save(std::filesystem::path(path));
}

void PptxExporter::export_to_stream(
    opc::OpcPackage& package,
    std::ostream& stream,
    const std::any& /*options*/) {
    update_content_type_if_needed(package);
    auto& mem_pkg = dynamic_cast<opc::InMemoryOpcPackage&>(package);
    mem_pkg.save(stream);
}

void PptxExporter::update_content_type_if_needed(
    opc::OpcPackage& /*package*/) {
    // Content type is preserved from the original package.
}

std::vector<std::string> PptxExporter::get_supported_formats() {
    std::vector<std::string> formats;
    formats.reserve(kContentTypes.size());
    for (const auto& [key, _] : kContentTypes) {
        formats.push_back(key);
    }
    return formats;
}

std::unique_ptr<PptxExporter>
PptxExporterFactory::create_for_format(std::string_view format_value) {
    return std::make_unique<PptxExporter>(format_value);
}

namespace {
/// Auto-register PptxExporter for all supported formats at static init.
const bool kRegistered = [] {
    ExporterRegistry::register_exporter<PptxExporter>();
    return true;
}();
} // namespace

} // namespace Aspose::Slides::Foss::Internal::export_
