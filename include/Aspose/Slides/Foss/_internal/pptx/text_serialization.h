// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file text_serialization.h
/// @brief Writing a text body's formatting model into DrawingML elements.
///
/// These are the serialiser's own plumbing, shared between the paragraph, the
/// bullet and the text frame because all three write into the same two
/// elements. They are not part of the installed public interface.

#include <string_view>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class IBulletFormat;
class IParagraphFormat;
class ITextFrameFormat;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Internal::pptx {

/// Insert a child element into a `<a:pPr>` node at the correct OOXML schema
/// position.
///
/// CT_TextParagraphProperties is a sequence, so a child appended at the end is
/// a child a consumer is entitled to discard.
///
/// @param ppr The `<a:pPr>` element node.
/// @param tag The qualified child element tag (e.g., "a:lnSpc").
/// @return The newly inserted child node.
pugi::xml_node ppr_insert_child(pugi::xml_node ppr, std::string_view tag);

/// Write a bullet's formatting into a `<a:pPr>` element.
///
/// Every element the bullet model owns — the colour, the size, the font and
/// the bullet type itself — is removed first and rewritten, so calling this on
/// a `<a:pPr>` that already carries a bullet replaces it rather than producing
/// two. Nothing else on the element is touched.
void write_bullet(pugi::xml_node ppr, const IBulletFormat& bullet);

/// Write a paragraph's formatting into an empty `<a:pPr>` element.
///
/// Only what the caller actually set is written. A property left undefined is
/// omitted rather than defaulted, so the placeholder / layout / master chain
/// resolves it the way OOXML intends — inventing a value here would take away
/// the caller's only way of saying "inherit".
///
/// Children are emitted in CT_TextParagraphProperties sequence order.
void serialize_ppr(pugi::xml_node ppr, const IParagraphFormat& format);

/// Returns true when @p format has anything at all to write into an `<a:pPr>`.
[[nodiscard]] bool ppr_has_content(const IParagraphFormat& format);

/// Write a text frame's formatting onto an `<a:bodyPr>` element.
///
/// Only what the caller set is written; an undefined property is left off so
/// the layout and master resolve it. The one exception is `@anchor`, which
/// keeps its long-standing `ctr` default when nothing was set — an auto shape
/// has no placeholder chain to inherit from, and PowerPoint centres shape text
/// vertically by default too.
///
/// Any child element this function owns (the autofit choice) is replaced, so
/// calling it twice on the same node is safe.
void serialize_body_pr(pugi::xml_node body_pr, const ITextFrameFormat& format);

} // namespace Aspose::Slides::Foss::Internal::pptx
