// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file template.cpp
/// @brief PPTX template loading implementation.

#include "template.h"

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

#include <filesystem>
#include <mutex>
#include <optional>
#include <stdexcept>

namespace Aspose::Slides::Foss::Internal::pptx {

namespace {

/// Guarded mutable state for the template directory.
std::mutex g_template_dir_mutex;
std::optional<std::filesystem::path> g_template_dir;

} // namespace

void set_template_directory(const std::filesystem::path& dir) {
    std::lock_guard lock(g_template_dir_mutex);
    g_template_dir = dir;
}

std::filesystem::path get_template_path() {
    std::filesystem::path dir;
    {
        std::lock_guard lock(g_template_dir_mutex);
        dir = g_template_dir.value_or(std::filesystem::current_path());
    }

    auto path = dir / std::string(kTemplateFilename);

    if (!std::filesystem::exists(path)) {
        throw std::filesystem::filesystem_error(
            "Template.pptx not found. Please ensure the template file exists.",
            path,
            std::make_error_code(std::errc::no_such_file_or_directory));
    }

    return path;
}

void load_template(opc::InMemoryOpcPackage& package) {
    auto template_path = get_template_path();
    auto template_package = opc::InMemoryOpcPackage::open(template_path);

    for (const auto& part_name : template_package.get_part_names()) {
        auto content = template_package.get_part(part_name);
        if (content) {
            package.set_part(part_name, std::move(*content));
        }
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
