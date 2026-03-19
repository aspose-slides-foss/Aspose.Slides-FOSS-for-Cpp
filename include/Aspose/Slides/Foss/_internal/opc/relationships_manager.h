// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file relationships_manager.h
/// @brief Manages OPC .rels files for a given part.

#include <algorithm>
#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>

namespace Aspose::Slides::Foss::Internal::opc {

/// Manages the .rels file associated with a given OPC part.
///
/// Loads existing relationships on construction and provides methods to
/// query, add, and remove relationships. Call save() to persist changes.
class RelationshipsManager final {
public:
    /// Construct a relationships manager for the given part.
    /// @param package The OPC package.
    /// @param source_part The part path whose relationships to manage.
    ///                    Empty string for root relationships (_rels/.rels).
    RelationshipsManager(OpcPackage& package, std::string_view source_part = "")
        : package_(package), source_part_(source_part) {
        rels_part_name_ = get_rels_part_name(source_part_);
        load();
    }

    /// Get a relationship by ID.
    /// @param rel_id The relationship ID (e.g., "rId1").
    /// @return The relationship, or nullopt if not found.
    [[nodiscard]] std::optional<Relationship> get_relationship(
        std::string_view rel_id) const {
        auto it = relationships_.find(std::string(rel_id));
        if (it != relationships_.end()) return it->second;
        return std::nullopt;
    }

    /// Get all relationships filtered by type.
    [[nodiscard]] std::vector<Relationship> get_relationships_by_type(
        std::string_view type) const {
        std::vector<Relationship> result;
        for (const auto& [_, rel] : relationships_) {
            if (rel.type == type) result.push_back(rel);
        }
        return result;
    }

    /// Get all relationships.
    [[nodiscard]] std::vector<Relationship> get_all_relationships() const {
        std::vector<Relationship> result;
        result.reserve(relationships_.size());
        for (const auto& [_, rel] : relationships_) {
            result.push_back(rel);
        }
        return result;
    }

    /// Add a new relationship.
    /// @param rel_type The relationship type URI.
    /// @param target The target part path (relative to source).
    /// @param rel_id Optional specific ID. If empty, auto-generated.
    /// @param target_mode Optional target mode ("External" for external links).
    /// @return The relationship ID.
    std::string add_relationship(
        std::string_view rel_type,
        std::string_view target,
        std::string_view rel_id = "",
        std::optional<std::string_view> target_mode = std::nullopt) {

        std::string id = rel_id.empty() ? generate_rel_id() : std::string(rel_id);

        Relationship rel;
        rel.id = id;
        rel.type = std::string(rel_type);
        rel.target = std::string(target);
        rel.target_mode = target_mode
            ? std::optional<std::string>(std::string(*target_mode))
            : std::nullopt;
        relationships_[id] = std::move(rel);
        return id;
    }

    /// Remove a relationship by ID.
    /// @return true if removed, false if not found.
    bool remove_relationship(std::string_view rel_id) {
        return relationships_.erase(std::string(rel_id)) > 0;
    }

    /// Persist the relationships back to the package as a .rels XML file.
    /// If no relationships remain, the .rels part is deleted.
    void save() {
        if (relationships_.empty()) {
            package_.delete_part(rels_part_name_);
            return;
        }

        pugi::xml_document doc;
        auto decl = doc.append_child(pugi::node_declaration);
        decl.append_attribute("version") = "1.0";
        decl.append_attribute("encoding") = "UTF-8";
        decl.append_attribute("standalone") = "yes";

        auto root = doc.append_child("Relationships");
        root.append_attribute("xmlns") =
            std::string(kRelsNamespace).c_str();

        for (const auto& [_, rel] : relationships_) {
            auto node = root.append_child("Relationship");
            node.append_attribute("Id") = rel.id.c_str();
            node.append_attribute("Type") = rel.type.c_str();
            node.append_attribute("Target") = rel.target.c_str();
            if (rel.target_mode.has_value()) {
                node.append_attribute("TargetMode") = rel.target_mode->c_str();
            }
        }

        struct XmlWriter : pugi::xml_writer {
            std::vector<uint8_t> result;
            void write(const void* data, size_t size) override {
                auto p = static_cast<const uint8_t*>(data);
                result.insert(result.end(), p, p + size);
            }
        } writer;
        doc.save(writer, "  ");
        package_.set_part(rels_part_name_, std::move(writer.result));
    }

    /// Compute the .rels part name for any given part path.
    ///
    /// Examples:
    ///   "" -> "_rels/.rels"
    ///   "ppt/presentation.xml" -> "ppt/_rels/presentation.xml.rels"
    ///   "ppt/slides/slide1.xml" -> "ppt/slides/_rels/slide1.xml.rels"
    [[nodiscard]] static std::string get_rels_part_name(std::string_view source_part) {
        if (source_part.empty()) {
            return "_rels/.rels";
        }
        auto s = std::string(source_part);
        auto pos = s.rfind('/');
        if (pos != std::string::npos) {
            return s.substr(0, pos + 1) + "_rels/" + s.substr(pos + 1) + ".rels";
        }
        return "_rels/" + s + ".rels";
    }

    /// Get the .rels file part name.
    [[nodiscard]] const std::string& part_name() const { return rels_part_name_; }

private:
    void load() {
        auto content = package_.get_part(rels_part_name_);
        if (!content) return;

        pugi::xml_document doc;
        doc.load_buffer(content->data(), content->size());

        for (auto node : doc.child("Relationships").children("Relationship")) {
            Relationship rel;
            rel.id = node.attribute("Id").as_string();
            rel.type = node.attribute("Type").as_string();
            rel.target = node.attribute("Target").as_string();
            auto tm = node.attribute("TargetMode");
            rel.target_mode = tm
                ? std::optional<std::string>(tm.as_string())
                : std::nullopt;
            relationships_[rel.id] = std::move(rel);
        }
    }

    /// Generate a unique relationship ID by trying rId1, rId2, ... until free.
    [[nodiscard]] std::string generate_rel_id() const {
        std::set<std::string> existing;
        for (const auto& [id, _] : relationships_) {
            existing.insert(id);
        }
        uint32_t counter = 1;
        while (true) {
            auto candidate = "rId" + std::to_string(counter);
            if (!existing.contains(candidate)) return candidate;
            ++counter;
        }
    }

    OpcPackage& package_;
    std::string source_part_;
    std::string rels_part_name_;
    std::unordered_map<std::string, Relationship> relationships_;
};

} // namespace Aspose::Slides::Foss::Internal::opc
