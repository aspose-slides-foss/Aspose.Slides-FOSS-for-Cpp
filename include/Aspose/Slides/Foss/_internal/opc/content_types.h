// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file content_types.h
/// @brief OPC content type constants for PPTX parts.

#include <string_view>

namespace Aspose::Slides::Foss::Internal::opc {

/// Well-known content types used in PPTX packages.
namespace content_types {

inline constexpr std::string_view kSlide =
    "application/vnd.openxmlformats-officedocument.presentationml.slide+xml";
inline constexpr std::string_view kSlideLayout =
    "application/vnd.openxmlformats-officedocument.presentationml.slideLayout+xml";
inline constexpr std::string_view kSlideMaster =
    "application/vnd.openxmlformats-officedocument.presentationml.slideMaster+xml";
inline constexpr std::string_view kPresentation =
    "application/vnd.openxmlformats-officedocument.presentationml.presentation.main+xml";
inline constexpr std::string_view kComments =
    "application/vnd.openxmlformats-officedocument.presentationml.comments+xml";
inline constexpr std::string_view kCommentAuthors =
    "application/vnd.openxmlformats-officedocument.presentationml.commentAuthors+xml";
inline constexpr std::string_view kNotesSlide =
    "application/vnd.openxmlformats-officedocument.presentationml.notesSlide+xml";
inline constexpr std::string_view kCoreProperties =
    "application/vnd.openxmlformats-package.core-properties+xml";
inline constexpr std::string_view kExtendedProperties =
    "application/vnd.openxmlformats-officedocument.extended-properties+xml";
inline constexpr std::string_view kCustomProperties =
    "application/vnd.openxmlformats-officedocument.custom-properties+xml";

} // namespace content_types

} // namespace Aspose::Slides::Foss::Internal::opc
