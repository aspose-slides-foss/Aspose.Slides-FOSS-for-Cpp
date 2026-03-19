// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file content_types_manager.h
/// @brief Manages the [Content_Types].xml part in an OPC package.

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>

namespace Aspose::Slides::Foss::Internal::opc {

/// Manages the [Content_Types].xml part, which maps part names to MIME types.
class ContentTypesManager final {
public:
    static constexpr std::string_view kPartName = "[Content_Types].xml";

    explicit ContentTypesManager(OpcPackage& package) : package_(package) {
        load();
    }

    /// Add or update a default content type for the given file extension.
    void add_default(std::string_view extension, std::string_view content_type) {
        defaults_[std::string(extension)] = std::string(content_type);
    }

    /// Add or update an override for the given part name.
    void add_override(std::string_view part_name, std::string_view content_type) {
        auto key = ensure_leading_slash(part_name);
        overrides_[key] = std::string(content_type);
    }

    /// Remove an override for the given part name.
    void remove_override(std::string_view part_name) {
        overrides_.erase(ensure_leading_slash(part_name));
    }

    /// Get the content type for a part, or empty string if not found.
    [[nodiscard]] std::string get_content_type(std::string_view part_name) const {
        auto it = overrides_.find(ensure_leading_slash(part_name));
        if (it != overrides_.end()) return it->second;
        return {};
    }

    /// Persist the content types back to the package.
    void save() {
        pugi::xml_document doc;
        auto decl = doc.append_child(pugi::node_declaration);
        decl.append_attribute("version") = "1.0";
        decl.append_attribute("encoding") = "UTF-8";
        decl.append_attribute("standalone") = "yes";

        auto root = doc.append_child("Types");
        root.append_attribute("xmlns") =
            "http://schemas.openxmlformats.org/package/2006/content-types";

        for (const auto& [ext, ct] : defaults_) {
            auto node = root.append_child("Default");
            node.append_attribute("Extension") = ext.c_str();
            node.append_attribute("ContentType") = ct.c_str();
        }

        for (const auto& [pn, ct] : overrides_) {
            auto node = root.append_child("Override");
            node.append_attribute("PartName") = pn.c_str();
            node.append_attribute("ContentType") = ct.c_str();
        }

        struct XmlWriter : pugi::xml_writer {
            std::vector<uint8_t> result;
            void write(const void* data, size_t size) override {
                auto p = static_cast<const uint8_t*>(data);
                result.insert(result.end(), p, p + size);
            }
        } writer;
        doc.save(writer, "  ");
        package_.set_part(kPartName, std::move(writer.result));
    }

private:
    void load() {
        auto content = package_.get_part(kPartName);
        if (!content) return;

        pugi::xml_document doc;
        doc.load_buffer(content->data(), content->size());

        auto root = doc.child("Types");
        for (auto node : root.children("Default")) {
            defaults_[node.attribute("Extension").as_string()] =
                node.attribute("ContentType").as_string();
        }
        for (auto node : root.children("Override")) {
            overrides_[node.attribute("PartName").as_string()] =
                node.attribute("ContentType").as_string();
        }
    }

    [[nodiscard]] static std::string ensure_leading_slash(std::string_view s) {
        if (!s.empty() && s[0] == '/') return std::string(s);
        return "/" + std::string(s);
    }

    OpcPackage& package_;
    std::unordered_map<std::string, std::string> defaults_;
    std::unordered_map<std::string, std::string> overrides_;
};

} // namespace Aspose::Slides::Foss::Internal::opc
