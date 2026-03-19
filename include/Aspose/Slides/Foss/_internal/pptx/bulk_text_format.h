// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file bulk_text_format.h
/// @brief Helpers for applying bulk text formatting to collections of table cells.
///
/// Implements the logic behind IBulkTextFormattable.set_text_format for
/// Table, Row, and Column classes.  Three overloads cover:
///   - PortionFormat  -> applied to every run (<a:rPr>) in every cell
///   - ParagraphFormat -> applied to every paragraph (<a:pPr>) in every cell
///   - TextFrameFormat -> applied to every text body (<a:bodyPr>) in every cell

#include <functional>
#include <span>
#include <variant>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss::Internal::pptx {

// ── Low-level XML helpers ───────────────────────────────────────────────

/// Copy all attributes from @p src to @p dst, overwriting existing ones.
void copy_xml_attrs(pugi::xml_node src, pugi::xml_node dst);

/// Replace the first child in @p parent whose tag matches @p src_child,
/// or append a deep copy if none exists.
void replace_or_add_child(pugi::xml_node parent, pugi::xml_node src_child);

/// Copy attributes and children from a source rPr node to a target rPr-like node.
void apply_rpr_to_element(pugi::xml_node src_rpr, pugi::xml_node target);

// ── Per-format appliers ─────────────────────────────────────────────────

/// Apply a PortionFormat's <a:rPr> element to every run and endParaRPr
/// in every cell.
///
/// @param tc_nodes  span of <a:tc> XML nodes (one per cell).
/// @param src_rpr   the source <a:rPr> node from a PortionFormat.
void apply_portion_format(std::span<pugi::xml_node> tc_nodes,
                          pugi::xml_node src_rpr);

/// Apply a ParagraphFormat's <a:pPr> element to every paragraph in every cell.
///
/// @param tc_nodes  span of <a:tc> XML nodes.
/// @param src_ppr   the source <a:pPr> node from a ParagraphFormat.
void apply_paragraph_format(std::span<pugi::xml_node> tc_nodes,
                            pugi::xml_node src_ppr);

/// Apply a TextFrameFormat's <a:bodyPr> element to every text body in every
/// cell, and mirror the @c vert attribute onto <a:tcPr>.
///
/// @param tc_nodes      span of <a:tc> XML nodes.
/// @param src_txbody    the source <a:txBody> node from a TextFrameFormat.
void apply_text_frame_format(std::span<pugi::xml_node> tc_nodes,
                             pugi::xml_node src_txbody);

// ── Variant-based dispatch ──────────────────────────────────────────────

/// Tagged wrapper so the dispatcher knows which applier to invoke.
struct PortionFormatSource {
    pugi::xml_node rpr;  ///< The source <a:rPr> node.
};

/// Tagged wrapper for paragraph format source.
struct ParagraphFormatSource {
    pugi::xml_node ppr;  ///< The source <a:pPr> node.
};

/// Tagged wrapper for text-frame format source.
struct TextFrameFormatSource {
    pugi::xml_node txbody;  ///< The source <a:txBody> node.
};

/// A discriminated union of the three format source types.
using TextFormatSource = std::variant<PortionFormatSource,
                                      ParagraphFormatSource,
                                      TextFrameFormatSource>;

/// Dispatch to the correct applier based on @p source, then invoke
/// @p save_callback (if non-null) to persist the changes.
///
/// @param tc_nodes       span of <a:tc> XML nodes (one per cell).
/// @param source         one of PortionFormatSource, ParagraphFormatSource,
///                       or TextFrameFormatSource.
/// @param save_callback  called after formatting is applied (e.g. slide_part.save()).
void apply_text_format(std::span<pugi::xml_node> tc_nodes,
                       const TextFormatSource& source,
                       std::function<void()> save_callback = nullptr);

} // namespace Aspose::Slides::Foss::Internal::pptx
