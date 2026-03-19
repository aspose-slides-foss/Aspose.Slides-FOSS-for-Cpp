// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file template.h
/// @brief PPTX template loading for new presentations.

#include <filesystem>
#include <string>

namespace Aspose::Slides::Foss::Internal::opc {
class InMemoryOpcPackage;
} // namespace Aspose::Slides::Foss::Internal::opc

namespace Aspose::Slides::Foss::Internal::pptx {

/// Default template filename.
inline constexpr std::string_view kTemplateFilename = "Template.pptx";

/// Set the directory where Template.pptx is located.
///
/// Must be called before any use of get_template_path() or load_template()
/// if the template file is not in the current working directory.
/// @param dir Absolute or relative path to the directory containing Template.pptx.
void set_template_directory(const std::filesystem::path& dir);

/// Get the full path to the Template.pptx file.
///
/// @return Absolute path to Template.pptx.
/// @throws std::filesystem::filesystem_error if the template file does not exist.
[[nodiscard]] std::filesystem::path get_template_path();

/// Load Template.pptx into the given package.
///
/// Opens the template file and copies every part into @p package,
/// overwriting any parts that already exist.
/// @param package The OPC package to populate with template contents.
/// @throws std::filesystem::filesystem_error if Template.pptx does not exist.
/// @throws std::runtime_error if the template cannot be read as a valid ZIP.
void load_template(opc::InMemoryOpcPackage& package);

} // namespace Aspose::Slides::Foss::Internal::pptx
