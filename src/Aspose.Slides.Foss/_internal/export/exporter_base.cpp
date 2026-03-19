// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include "Aspose/Slides/Foss/_internal/export/exporter_base.h"

namespace Aspose::Slides::Foss::Internal::export_ {

ExporterBase::~ExporterBase() = default;

void ExporterBase::export_to_path(
    opc::OpcPackage& /*package*/,
    std::string_view /*path*/,
    const std::any& /*options*/) {
    // Default no-op; subclasses override to implement format-specific export.
}

void ExporterBase::export_to_stream(
    opc::OpcPackage& /*package*/,
    std::ostream& /*stream*/,
    const std::any& /*options*/) {
    // Default no-op; subclasses override to implement format-specific export.
}

std::vector<std::string> ExporterBase::get_supported_formats() {
    return {};
}

void ExporterBase::export_presentation(
    opc::OpcPackage& package,
    std::string_view path,
    const std::any& options) {
    export_to_path(package, path, options);
}

void ExporterBase::export_presentation(
    opc::OpcPackage& package,
    std::ostream& stream,
    const std::any& options) {
    export_to_stream(package, stream, options);
}

} // namespace Aspose::Slides::Foss::Internal::export_
