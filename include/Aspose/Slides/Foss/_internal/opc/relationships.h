// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file relationships.h
/// @brief OPC relationship types, data structures, and namespace constants.

#include <optional>
#include <string>
#include <string_view>

namespace Aspose::Slides::Foss::Internal::opc {

/// OPC relationships XML namespace URI.
inline constexpr std::string_view kRelsNamespace =
    "http://schemas.openxmlformats.org/package/2006/relationships";

/// A single OPC relationship entry.
struct Relationship {
    std::string id;                          ///< Relationship ID (e.g., "rId1").
    std::string type;                        ///< Relationship type URI.
    std::string target;                      ///< Target path (relative or absolute).
    std::optional<std::string> target_mode;  ///< "External" for external targets; nullopt for internal.

    bool operator==(const Relationship&) const = default;
};

/// Well-known OPC relationship type URIs used in Office/PPTX files.
namespace rel_types {

inline constexpr std::string_view kOfficeDocument =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument";
inline constexpr std::string_view kSlide =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/slide";
inline constexpr std::string_view kSlideLayout =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/slideLayout";
inline constexpr std::string_view kSlideMaster =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/slideMaster";
inline constexpr std::string_view kNotesSlide =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/notesSlide";
inline constexpr std::string_view kNotesMaster =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/notesMaster";
inline constexpr std::string_view kHandoutMaster =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/handoutMaster";
inline constexpr std::string_view kTheme =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme";
inline constexpr std::string_view kCoreProperties =
    "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties";
inline constexpr std::string_view kExtendedProperties =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties";
inline constexpr std::string_view kThumbnail =
    "http://schemas.openxmlformats.org/package/2006/relationships/metadata/thumbnail";
inline constexpr std::string_view kImage =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image";
inline constexpr std::string_view kHyperlink =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink";
inline constexpr std::string_view kChart =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/chart";
inline constexpr std::string_view kOleObject =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/oleObject";
inline constexpr std::string_view kPackage =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/package";
inline constexpr std::string_view kAudio =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/audio";
inline constexpr std::string_view kVideo =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/video";
inline constexpr std::string_view kComments =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/comments";
inline constexpr std::string_view kCommentAuthors =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/commentAuthors";
inline constexpr std::string_view kCustomProperties =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/custom-properties";

} // namespace rel_types

} // namespace Aspose::Slides::Foss::Internal::opc
