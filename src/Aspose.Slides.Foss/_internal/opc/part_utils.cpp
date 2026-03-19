// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/opc/part_utils.h>

#include <algorithm>
#include <stdexcept>
#include <string>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss::Internal::opc {

namespace {

/// Split a path into directory segments.
std::vector<std::string> split_path(std::string_view path) {
    std::vector<std::string> segments;
    while (!path.empty()) {
        auto sep = path.find('/');
        auto segment = path.substr(0, sep);
        path = (sep == std::string_view::npos)
            ? std::string_view{}
            : path.substr(sep + 1);
        if (!segment.empty()) {
            segments.emplace_back(segment);
        }
    }
    return segments;
}

/// Get the directory portion of a part path.
std::string get_directory(std::string_view part) {
    auto pos = part.rfind('/');
    if (pos != std::string_view::npos) {
        return std::string(part.substr(0, pos));
    }
    return {};
}

/// Normalize a path by collapsing ".." and "." segments.
std::string normalize_path(const std::vector<std::string>& segments) {
    std::vector<std::string_view> resolved;
    for (const auto& seg : segments) {
        if (seg == "..") {
            if (!resolved.empty()) {
                resolved.pop_back();
            }
        } else if (seg != ".") {
            resolved.push_back(seg);
        }
    }
    std::string result;
    for (size_t i = 0; i < resolved.size(); ++i) {
        if (i > 0) result += '/';
        result += resolved[i];
    }
    return result;
}

} // anonymous namespace

// ---------------------------------------------------------------------------
// resolve_target
// ---------------------------------------------------------------------------

std::string resolve_target(std::string_view base_part, std::string_view target) {
    // Absolute target — strip leading '/'
    if (!target.empty() && target.front() == '/') {
        target.remove_prefix(1);
        return std::string(target);
    }

    // Relative target — resolve against the base part's directory
    auto base_dir = get_directory(base_part);
    std::string combined = base_dir.empty()
        ? std::string(target)
        : base_dir + "/" + std::string(target);

    return normalize_path(split_path(combined));
}

// ---------------------------------------------------------------------------
// compute_relative_target
// ---------------------------------------------------------------------------

std::string compute_relative_target(std::string_view source_part,
                                     std::string_view target_part) {
    auto source_segments = split_path(get_directory(source_part));
    auto target_segments = split_path(target_part);

    // Find common prefix length
    size_t common = 0;
    size_t max_common = std::min(source_segments.size(),
                                  target_segments.empty() ? size_t{0} : target_segments.size() - 1);
    while (common < max_common && source_segments[common] == target_segments[common]) {
        ++common;
    }

    // Build relative path: ".." for each remaining source dir, then remaining target
    std::string result;
    for (size_t i = common; i < source_segments.size(); ++i) {
        if (!result.empty()) result += '/';
        result += "..";
    }
    for (size_t i = common; i < target_segments.size(); ++i) {
        if (!result.empty()) result += '/';
        result += target_segments[i];
    }
    return result;
}

// ---------------------------------------------------------------------------
// clone_related_part
// ---------------------------------------------------------------------------

std::string clone_related_part(OpcPackage& source_package,
                                std::string_view source_target,
                                OpcPackage& dest_package,
                                [[maybe_unused]] std::string_view dest_part_name,
                                [[maybe_unused]] std::string_view rel_type) {
    auto content = source_package.get_part(source_target);
    if (!content) {
        throw std::runtime_error(
            "Related part not found: " + std::string(source_target));
    }

    // Clone to the same absolute path in the destination
    std::string dest_target(source_target);
    dest_package.set_part(dest_target, std::move(*content));
    return dest_target;
}

// ---------------------------------------------------------------------------
// update_rid_references
// ---------------------------------------------------------------------------

void update_rid_references(pugi::xml_node root,
                           const std::unordered_map<std::string, std::string>& rid_mapping) {
    if (rid_mapping.empty()) return;

    // The r:id attribute in OOXML uses the relationships namespace.
    // In pugixml with non-namespace-aware parsing, it appears as "r:id".
    // We check both the prefixed form and the Clark-notation form.
    static const std::string clark_r_id = pptx::Attributes::kRId;
    static const std::string clark_r_embed = pptx::Attributes::kREmbed;

    // Recursively update all nodes
    struct Walker : pugi::xml_tree_walker {
        const std::unordered_map<std::string, std::string>& mapping;
        const std::string& clark_id;
        const std::string& clark_embed;

        Walker(const std::unordered_map<std::string, std::string>& m,
               const std::string& cid, const std::string& cembed)
            : mapping(m), clark_id(cid), clark_embed(cembed) {}

        bool for_each(pugi::xml_node& node) override {
            for (auto attr : node.attributes()) {
                std::string attr_name = attr.name();
                // Check if this is a relationship ID attribute
                if (attr_name == "r:id" || attr_name == clark_id ||
                    attr_name == "r:embed" || attr_name == clark_embed) {
                    auto it = mapping.find(attr.as_string());
                    if (it != mapping.end()) {
                        attr.set_value(it->second.c_str());
                    }
                }
            }
            return true; // continue traversal
        }
    };

    Walker walker(rid_mapping, clark_r_id, clark_r_embed);
    root.traverse(walker);
}

} // namespace Aspose::Slides::Foss::Internal::opc
