// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file conformance.h
/// @brief Assertions made against a produced .pptx package, not against the
///        library that produced it.
///
/// Every helper here opens the saved file as a ZIP archive, parses the XML
/// inside it and asserts on elements and attributes.  Nothing in this header
/// calls the presentation API, on purpose: a test that asks the writer's own
/// reader whether the writer worked cannot fail when both sides share the same
/// misunderstanding, and that is how a whole class of packaging faults stays
/// invisible to a green suite.
///
/// This is test-only code.  It is not part of the installed public interface
/// and nothing under `include/` may depend on it.

#include <cstdint>
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <pugixml.hpp>

namespace conformance {

/// Absolute path of the committed `tests/test_data` directory.
[[nodiscard]] std::filesystem::path test_data_dir();

/// A saved .pptx, opened read-only as an OPC package.
///
/// Entry names are the ZIP member names, which are OPC part names without the
/// leading slash: `ppt/slides/slide1.xml`, `[Content_Types].xml`.
class Package {
public:
    /// Opens a .pptx and reads every member into memory.
    /// @throws std::runtime_error if the file is missing or is not a ZIP.
    explicit Package(const std::filesystem::path& pptx);

    /// Every member name, sorted, directories excluded.
    [[nodiscard]] const std::vector<std::string>& entry_names() const noexcept {
        return names_;
    }

    [[nodiscard]] bool has_entry(std::string_view name) const;

    /// Raw bytes of one member.
    /// @throws std::runtime_error if the member does not exist.
    [[nodiscard]] const std::vector<std::uint8_t>& entry_bytes(
        std::string_view name) const;

    /// One member decoded as text.
    [[nodiscard]] std::string entry_text(std::string_view name) const;

    /// One member parsed as XML.  Parsed once and cached.
    /// @throws std::runtime_error if the member is missing or is not well-formed.
    [[nodiscard]] const pugi::xml_document& xml(std::string_view name) const;

    /// Member names matching an ECMAScript regular expression, sorted.
    [[nodiscard]] std::vector<std::string> entries_matching(
        std::string_view pattern) const;

    /// Name of the `.rels` part that owns `part_name`.
    /// `ppt/slides/slide1.xml` -> `ppt/slides/_rels/slide1.xml.rels`.
    [[nodiscard]] static std::string rels_part_name(std::string_view part_name);

    /// Relationship ids declared in `rels_part`, mapped to their Target.
    /// Returns an empty map when the .rels part does not exist.
    [[nodiscard]] std::map<std::string, std::string> relationship_targets(
        std::string_view rels_part) const;

    /// Content type `[Content_Types].xml` resolves for `part_name`, preferring
    /// an Override over the extension Default.  Empty when nothing resolves.
    [[nodiscard]] std::string content_type_of(std::string_view part_name) const;

private:
    std::filesystem::path path_;
    std::vector<std::string> names_;
    std::map<std::string, std::vector<std::uint8_t>, std::less<>> entries_;
    mutable std::map<std::string, std::unique_ptr<pugi::xml_document>,
                     std::less<>> parsed_;
};

// ---------------------------------------------------------------------------
// Package-wide rules
// ---------------------------------------------------------------------------

/// Every `r:id` / `r:embed` / `r:link` in every XML part resolves to a
/// `Relationship Id` in that part's own `.rels`.
///
/// A reference that does not resolve is a dangling pointer inside the file: the
/// image bytes may well be present and simply unreachable, which is why a test
/// that only checks "is there a picture shape" passes over it.
[[nodiscard]] ::testing::AssertionResult AllRelationshipReferencesResolve(
    const Package& pkg);

/// Every part resolves a content type through an `Override` or a `Default`.
///
/// Per ISO/IEC 29500-2 the content type *is* the part's identity; a slide part
/// that falls through to `Default Extension="xml"` is `application/xml` and not
/// a slide, whatever its name and contents say.
[[nodiscard]] ::testing::AssertionResult EveryPartHasAContentType(
    const Package& pkg);

/// Every `Override` in `[Content_Types].xml` names a part that exists.
[[nodiscard]] ::testing::AssertionResult NoContentTypeOverrideDangles(
    const Package& pkg);

/// Parts whose name follows a known ECMA-376 convention carry the content type
/// that convention requires (slides, layouts, masters, notes, media).
[[nodiscard]] ::testing::AssertionResult PartContentTypesMatchEcma(
    const Package& pkg);

/// The three package rules above, applied together.  A good default for any
/// test that saves a file for some other reason.
[[nodiscard]] ::testing::AssertionResult PackageIsInternallyConsistent(
    const Package& pkg);

// ---------------------------------------------------------------------------
// Element-level assertions
// ---------------------------------------------------------------------------

/// Attribute name/value pairs an element is required to carry.
using Attributes = std::vector<std::pair<std::string, std::string>>;

/// An element selected by XPath exists in `part` and carries every attribute
/// in `attrs` with exactly that value.
///
/// pugixml is not namespace-aware, so XPath name tests use the literal prefixed
/// name as written in the file: `//a:effectLst/a:outerShdw`.
[[nodiscard]] ::testing::AssertionResult ElementExists(
    const Package& pkg, std::string_view part, std::string_view xpath,
    const Attributes& attrs = {});

/// No element matches the XPath in `part`.
[[nodiscard]] ::testing::AssertionResult ElementAbsent(
    const Package& pkg, std::string_view part, std::string_view xpath);

/// The element selected by XPath has exactly these child elements, in this
/// order.  Child order is not cosmetic: OOXML complex types are sequences, and
/// a consumer that meets a child out of order is entitled to discard it.
[[nodiscard]] ::testing::AssertionResult ChildOrderIs(
    const Package& pkg, std::string_view part, std::string_view xpath,
    const std::vector<std::string>& expected_children);

/// Number of elements matching the XPath in `part`.
[[nodiscard]] std::size_t CountMatches(const Package& pkg,
                                       std::string_view part,
                                       std::string_view xpath);

/// Child element names of a node, in document order.
[[nodiscard]] std::vector<std::string> ChildNames(pugi::xml_node node);

} // namespace conformance
