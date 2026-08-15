// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file conformance.cpp
/// @brief Implementation of the package-level conformance assertions.

#include "conformance/conformance.h"

#include <miniz.h>

#include <algorithm>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace conformance {

namespace {

constexpr std::string_view kContentTypesPart = "[Content_Types].xml";
constexpr std::string_view kRelationshipsNs =
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships";

/// Attribute local names in the relationships namespace that hold a
/// relationship id.  `r:id` and `r:embed` cover almost everything; `r:link`,
/// `r:pict`, `r:dm`, `r:lo`, `r:qs` and `r:cs` complete the set that appears in
/// PresentationML and DrawingML.
const std::vector<std::string>& rel_attribute_local_names() {
    static const std::vector<std::string> names = {
        "id", "embed", "link", "pict", "dm", "lo", "qs", "cs"};
    return names;
}

std::string_view local_name(std::string_view qname) {
    auto colon = qname.find(':');
    return colon == std::string_view::npos ? qname : qname.substr(colon + 1);
}

std::string_view prefix_of(std::string_view qname) {
    auto colon = qname.find(':');
    return colon == std::string_view::npos ? std::string_view{}
                                           : qname.substr(0, colon);
}

/// Collect every namespace prefix bound to the relationships namespace anywhere
/// in the document.  Almost always just "r", but a file is free to bind another
/// prefix and a harness that hard-codes "r" would then silently check nothing.
void collect_rel_prefixes(pugi::xml_node node, std::vector<std::string>& out) {
    for (auto attr : node.attributes()) {
        std::string_view name(attr.name());
        if (name.rfind("xmlns:", 0) == 0 &&
            std::string_view(attr.value()) == kRelationshipsNs) {
            std::string prefix(name.substr(6));
            if (std::find(out.begin(), out.end(), prefix) == out.end())
                out.push_back(std::move(prefix));
        }
    }
    for (auto child : node.children()) collect_rel_prefixes(child, out);
}

void walk_rel_references(
    pugi::xml_node node, const std::vector<std::string>& prefixes,
    std::vector<std::pair<std::string, std::string>>& out) {
    for (auto attr : node.attributes()) {
        std::string_view qname(attr.name());
        auto prefix = prefix_of(qname);
        if (prefix.empty()) continue;
        if (std::find(prefixes.begin(), prefixes.end(), prefix) ==
            prefixes.end())
            continue;
        auto local = local_name(qname);
        const auto& wanted = rel_attribute_local_names();
        if (std::find(wanted.begin(), wanted.end(), local) == wanted.end())
            continue;
        std::string value(attr.value());
        // An empty r:embed is the documented way to say "no image"; it is not
        // a dangling reference.
        if (value.empty()) continue;
        out.emplace_back(std::string(qname), std::move(value));
    }
    for (auto child : node.children())
        walk_rel_references(child, prefixes, out);
}

bool looks_like_xml_part(std::string_view name) {
    if (name.size() < 4) return false;
    return name.substr(name.size() - 4) == ".xml" ||
           (name.size() >= 5 && name.substr(name.size() - 5) == ".rels");
}

std::string extension_of(std::string_view part_name) {
    auto dot = part_name.rfind('.');
    if (dot == std::string_view::npos) return {};
    std::string ext(part_name.substr(dot + 1));
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return ext;
}

/// ECMA-376 content types for the part names whose shape is fixed by the
/// standard.  Anything not listed here is not checked for a *specific* type,
/// only for having one at all.
const std::vector<std::pair<std::regex, std::string>>& ecma_content_types() {
    static const std::string kPml =
        "application/vnd.openxmlformats-officedocument.presentationml.";
    static const std::vector<std::pair<std::regex, std::string>> table = {
        {std::regex(R"(^ppt/slides/slide\d+\.xml$)"), kPml + "slide+xml"},
        {std::regex(R"(^ppt/slideLayouts/slideLayout\d+\.xml$)"),
         kPml + "slideLayout+xml"},
        {std::regex(R"(^ppt/slideMasters/slideMaster\d+\.xml$)"),
         kPml + "slideMaster+xml"},
        {std::regex(R"(^ppt/notesSlides/notesSlide\d+\.xml$)"),
         kPml + "notesSlide+xml"},
        {std::regex(R"(^ppt/notesMasters/notesMaster\d+\.xml$)"),
         kPml + "notesMaster+xml"},
        {std::regex(R"(^ppt/comments/.*\.xml$)"), kPml + "comments+xml"},
        {std::regex(R"(^ppt/media/.*\.png$)"), "image/png"},
        {std::regex(R"(^ppt/media/.*\.jpe?g$)"), "image/jpeg"},
        {std::regex(R"(^ppt/media/.*\.gif$)"), "image/gif"},
        {std::regex(R"(^ppt/media/.*\.bmp$)"), "image/bmp"},
        {std::regex(R"(^ppt/theme/theme\d+\.xml$)"),
         "application/vnd.openxmlformats-officedocument.theme+xml"},
    };
    return table;
}

std::string join(const std::vector<std::string>& items,
                 std::string_view separator) {
    std::string out;
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (i) out += separator;
        out += items[i];
    }
    return out;
}

} // namespace

// ---------------------------------------------------------------------------
// test_data_dir
// ---------------------------------------------------------------------------

std::filesystem::path test_data_dir() {
    // __FILE__ is tests/conformance/conformance.cpp in the source tree, so the
    // fixtures sit one directory up.  Resolving from the source path rather
    // than the working directory keeps the tests runnable from anywhere.
    return std::filesystem::path(__FILE__).parent_path().parent_path() /
           "test_data";
}

// ---------------------------------------------------------------------------
// Package
// ---------------------------------------------------------------------------

Package::Package(const std::filesystem::path& pptx) : path_(pptx) {
    if (!std::filesystem::exists(pptx))
        throw std::runtime_error("Package: no such file: " + pptx.string());

    mz_zip_archive zip{};
    if (!mz_zip_reader_init_file(&zip, pptx.string().c_str(), 0))
        throw std::runtime_error("Package: not a ZIP archive: " +
                                 pptx.string());

    auto count = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < count; ++i) {
        if (mz_zip_reader_is_file_a_directory(&zip, i)) continue;
        mz_zip_archive_file_stat stat;
        if (!mz_zip_reader_file_stat(&zip, i, &stat)) {
            mz_zip_reader_end(&zip);
            throw std::runtime_error("Package: unreadable ZIP entry");
        }
        std::string name(stat.m_filename);
        std::vector<std::uint8_t> data(
            static_cast<std::size_t>(stat.m_uncomp_size));
        if (!data.empty() &&
            !mz_zip_reader_extract_to_mem(&zip, i, data.data(), data.size(),
                                          0)) {
            mz_zip_reader_end(&zip);
            throw std::runtime_error("Package: cannot extract " + name);
        }
        names_.push_back(name);
        entries_.emplace(std::move(name), std::move(data));
    }
    mz_zip_reader_end(&zip);
    std::sort(names_.begin(), names_.end());
}

bool Package::has_entry(std::string_view name) const {
    return entries_.find(name) != entries_.end();
}

const std::vector<std::uint8_t>& Package::entry_bytes(
    std::string_view name) const {
    auto it = entries_.find(name);
    if (it == entries_.end())
        throw std::runtime_error("Package: no such part: " + std::string(name) +
                                 " in " + path_.string());
    return it->second;
}

std::string Package::entry_text(std::string_view name) const {
    const auto& bytes = entry_bytes(name);
    return std::string(reinterpret_cast<const char*>(bytes.data()),
                       bytes.size());
}

const pugi::xml_document& Package::xml(std::string_view name) const {
    auto cached = parsed_.find(name);
    if (cached != parsed_.end()) return *cached->second;

    const auto& bytes = entry_bytes(name);
    auto doc = std::make_unique<pugi::xml_document>();
    auto result = doc->load_buffer(bytes.data(), bytes.size());
    if (!result)
        throw std::runtime_error("Package: " + std::string(name) +
                                 " is not well-formed XML: " +
                                 result.description());
    auto [it, _] = parsed_.emplace(std::string(name), std::move(doc));
    return *it->second;
}

std::vector<std::string> Package::entries_matching(
    std::string_view pattern) const {
    std::regex re{std::string(pattern)};
    std::vector<std::string> out;
    for (const auto& name : names_)
        if (std::regex_search(name, re)) out.push_back(name);
    return out;
}

std::string Package::rels_part_name(std::string_view part_name) {
    auto slash = part_name.rfind('/');
    if (slash == std::string_view::npos)
        return "_rels/" + std::string(part_name) + ".rels";
    return std::string(part_name.substr(0, slash)) + "/_rels/" +
           std::string(part_name.substr(slash + 1)) + ".rels";
}

std::map<std::string, std::string> Package::relationship_targets(
    std::string_view rels_part) const {
    std::map<std::string, std::string> out;
    if (!has_entry(rels_part)) return out;
    const auto& doc = xml(rels_part);
    for (auto rel : doc.child("Relationships").children("Relationship"))
        out.emplace(rel.attribute("Id").value(), rel.attribute("Target").value());
    return out;
}

std::string Package::content_type_of(std::string_view part_name) const {
    if (!has_entry(kContentTypesPart)) return {};
    const auto& doc = xml(kContentTypesPart);
    auto types = doc.child("Types");

    std::string with_slash = "/" + std::string(part_name);
    for (auto ov : types.children("Override")) {
        if (with_slash == ov.attribute("PartName").value())
            return ov.attribute("ContentType").value();
    }

    auto ext = extension_of(part_name);
    for (auto def : types.children("Default")) {
        std::string declared = def.attribute("Extension").value();
        std::transform(declared.begin(), declared.end(), declared.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (declared == ext) return def.attribute("ContentType").value();
    }
    return {};
}

// ---------------------------------------------------------------------------
// Package-wide rules
// ---------------------------------------------------------------------------

::testing::AssertionResult AllRelationshipReferencesResolve(
    const Package& pkg) {
    std::vector<std::string> problems;

    for (const auto& part : pkg.entry_names()) {
        if (!looks_like_xml_part(part)) continue;
        if (part.size() >= 5 && part.substr(part.size() - 5) == ".rels") continue;
        if (part == kContentTypesPart) continue;

        const pugi::xml_document* doc = nullptr;
        try {
            doc = &pkg.xml(part);
        } catch (const std::exception&) {
            continue; // not XML after all; not this rule's business
        }

        std::vector<std::string> prefixes;
        collect_rel_prefixes(*doc, prefixes);
        if (prefixes.empty()) prefixes.push_back("r");

        std::vector<std::pair<std::string, std::string>> refs;
        walk_rel_references(*doc, prefixes, refs);
        if (refs.empty()) continue;

        auto rels_part = Package::rels_part_name(part);
        auto declared = pkg.relationship_targets(rels_part);

        for (const auto& [attr, id] : refs) {
            if (declared.find(id) == declared.end()) {
                problems.push_back(part + ": " + attr + "=\"" + id +
                                   "\" does not resolve in " + rels_part +
                                   (pkg.has_entry(rels_part)
                                        ? " (declared: " +
                                              [&] {
                                                  std::vector<std::string> ids;
                                                  for (const auto& kv : declared)
                                                      ids.push_back(kv.first);
                                                  return ids.empty()
                                                             ? std::string("none")
                                                             : join(ids, ", ");
                                              }() +
                                              ")"
                                        : " (that .rels part does not exist)"));
            }
        }
    }

    if (problems.empty()) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << problems.size() << " unresolved relationship reference(s):\n  "
           << join(problems, "\n  ");
}

::testing::AssertionResult EveryPartHasAContentType(const Package& pkg) {
    std::vector<std::string> problems;
    for (const auto& part : pkg.entry_names()) {
        if (part == kContentTypesPart) continue;
        if (pkg.content_type_of(part).empty())
            problems.push_back(part + ": no Override and no Default for \"." +
                               extension_of(part) + "\"");
    }
    if (problems.empty()) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << problems.size() << " part(s) with no content type:\n  "
           << join(problems, "\n  ");
}

::testing::AssertionResult NoContentTypeOverrideDangles(const Package& pkg) {
    if (!pkg.has_entry(kContentTypesPart))
        return ::testing::AssertionFailure() << "no [Content_Types].xml";

    std::vector<std::string> problems;
    for (auto ov : pkg.xml(kContentTypesPart).child("Types").children("Override")) {
        std::string declared = ov.attribute("PartName").value();
        std::string entry =
            declared.starts_with("/") ? declared.substr(1) : declared;
        if (!pkg.has_entry(entry))
            problems.push_back(declared + ": no such part in the package");
    }
    if (problems.empty()) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << problems.size() << " dangling content-type Override(s):\n  "
           << join(problems, "\n  ");
}

::testing::AssertionResult PartContentTypesMatchEcma(const Package& pkg) {
    std::vector<std::string> problems;
    for (const auto& part : pkg.entry_names()) {
        for (const auto& [pattern, expected] : ecma_content_types()) {
            if (!std::regex_match(part, pattern)) continue;
            auto actual = pkg.content_type_of(part);
            if (actual != expected)
                problems.push_back(part + ": content type is \"" +
                                   (actual.empty() ? std::string("<none>")
                                                   : actual) +
                                   "\", ECMA-376 requires \"" + expected + "\"");
            break;
        }
    }
    if (problems.empty()) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << problems.size() << " part(s) with the wrong content type:\n  "
           << join(problems, "\n  ");
}

::testing::AssertionResult PackageIsInternallyConsistent(const Package& pkg) {
    if (auto r = AllRelationshipReferencesResolve(pkg); !r) return r;
    if (auto r = EveryPartHasAContentType(pkg); !r) return r;
    if (auto r = NoContentTypeOverrideDangles(pkg); !r) return r;
    if (auto r = PartContentTypesMatchEcma(pkg); !r) return r;
    return ::testing::AssertionSuccess();
}

// ---------------------------------------------------------------------------
// Element-level assertions
// ---------------------------------------------------------------------------

std::vector<std::string> ChildNames(pugi::xml_node node) {
    std::vector<std::string> out;
    for (auto child : node.children())
        if (child.type() == pugi::node_element) out.emplace_back(child.name());
    return out;
}

namespace {

/// Serialise a node so failure messages show the XML that was actually written
/// rather than only naming the element that was expected.
std::string node_to_string(pugi::xml_node node) {
    std::ostringstream out;
    node.print(out, "", pugi::format_raw);
    return out.str();
}

std::string part_excerpt(const Package& pkg, std::string_view part) {
    try {
        return node_to_string(pkg.xml(part).document_element());
    } catch (const std::exception& e) {
        return std::string("<unreadable: ") + e.what() + ">";
    }
}

} // namespace

::testing::AssertionResult ElementExists(const Package& pkg,
                                         std::string_view part,
                                         std::string_view xpath,
                                         const Attributes& attrs) {
    if (!pkg.has_entry(part))
        return ::testing::AssertionFailure()
               << "part \"" << part << "\" is not in the package";

    auto matched = pkg.xml(part).select_nodes(std::string(xpath).c_str());
    if (matched.empty())
        return ::testing::AssertionFailure()
               << "no element matches \"" << xpath << "\" in " << part
               << "\n  written: " << part_excerpt(pkg, part);

    std::vector<std::string> near_misses;
    for (const auto& hit : matched) {
        auto node = hit.node();
        std::vector<std::string> wrong;
        for (const auto& [name, expected] : attrs) {
            auto attr = node.attribute(name.c_str());
            if (!attr)
                wrong.push_back(name + " missing");
            else if (std::string(attr.value()) != expected)
                wrong.push_back(name + "=\"" + attr.value() +
                                "\", expected \"" + expected + "\"");
        }
        if (wrong.empty()) return ::testing::AssertionSuccess();
        near_misses.push_back(node_to_string(node) + "  [" +
                              join(wrong, "; ") + "]");
    }

    return ::testing::AssertionFailure()
           << matched.size() << " element(s) match \"" << xpath << "\" in "
           << part << " but none carries the required attributes:\n  "
           << join(near_misses, "\n  ");
}

::testing::AssertionResult ElementAbsent(const Package& pkg,
                                         std::string_view part,
                                         std::string_view xpath) {
    if (!pkg.has_entry(part)) return ::testing::AssertionSuccess();
    auto matched = pkg.xml(part).select_nodes(std::string(xpath).c_str());
    if (matched.empty()) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << matched.size() << " element(s) match \"" << xpath << "\" in "
           << part << ", expected none:\n  "
           << node_to_string(matched[0].node());
}

::testing::AssertionResult ChildOrderIs(
    const Package& pkg, std::string_view part, std::string_view xpath,
    const std::vector<std::string>& expected_children) {
    if (!pkg.has_entry(part))
        return ::testing::AssertionFailure()
               << "part \"" << part << "\" is not in the package";

    auto node = pkg.xml(part).select_node(std::string(xpath).c_str()).node();
    if (!node)
        return ::testing::AssertionFailure()
               << "no element matches \"" << xpath << "\" in " << part
               << "\n  written: " << part_excerpt(pkg, part);

    auto actual = ChildNames(node);
    if (actual == expected_children) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
           << "children of \"" << xpath << "\" in " << part << " are ["
           << join(actual, ", ") << "], expected ["
           << join(expected_children, ", ") << "]\n  written: "
           << node_to_string(node);
}

std::size_t CountMatches(const Package& pkg, std::string_view part,
                         std::string_view xpath) {
    if (!pkg.has_entry(part)) return 0;
    return pkg.xml(part).select_nodes(std::string(xpath).c_str()).size();
}

} // namespace conformance
