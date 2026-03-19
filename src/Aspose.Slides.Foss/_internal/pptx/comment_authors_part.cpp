// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/comment_authors_part.h>

#include <algorithm>
#include <string>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss::Internal::pptx {

// Qualified element tag for pugixml (prefix:local form).
static const std::string kCmAuthorTag = "p:cmAuthor";
static const std::string kCmAuthorLstTag = "p:cmAuthorLst";

// ---------------------------------------------------------------------------
// AuthorData
// ---------------------------------------------------------------------------

int32_t AuthorData::id() const {
    return node_.attribute("id").as_int(0);
}

std::string AuthorData::name() const {
    return node_.attribute("name").as_string("");
}

void AuthorData::set_name(std::string_view value) {
    node_.attribute("name").set_value(std::string(value).c_str());
}

std::string AuthorData::initials() const {
    return node_.attribute("initials").as_string("");
}

void AuthorData::set_initials(std::string_view value) {
    node_.attribute("initials").set_value(std::string(value).c_str());
}

int32_t AuthorData::last_idx() const {
    return node_.attribute("lastIdx").as_int(0);
}

void AuthorData::set_last_idx(int32_t value) {
    node_.attribute("lastIdx").set_value(value);
}

int32_t AuthorData::clr_idx() const {
    return node_.attribute("clrIdx").as_int(0);
}

// ---------------------------------------------------------------------------
// CommentAuthorsPart
// ---------------------------------------------------------------------------

CommentAuthorsPart::CommentAuthorsPart(opc::OpcPackage& package)
    : package_(package) {
    load();
}

void CommentAuthorsPart::load() {
    auto content = package_.get_part(kCommentAuthorsPartName);
    if (content) {
        auto result = doc_.load_buffer(content->data(), content->size());
        if (result) {
            root_ = doc_.first_child();
            return;
        }
    }

    // No existing part (or parse failure) — create empty root element.
    auto decl = doc_.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    root_ = doc_.append_child(kCmAuthorLstTag.c_str());
    root_.append_attribute("xmlns:p") = std::string(ns_uri::kP).c_str();
}

std::vector<AuthorData> CommentAuthorsPart::get_authors() const {
    std::vector<AuthorData> result;
    for (auto child : root_.children(kCmAuthorTag.c_str())) {
        result.emplace_back(child);
    }
    return result;
}

std::optional<AuthorData> CommentAuthorsPart::find_author_by_id(
    int32_t author_id) const {
    for (auto child : root_.children(kCmAuthorTag.c_str())) {
        if (child.attribute("id").as_int(-1) == author_id) {
            return AuthorData(child);
        }
    }
    return std::nullopt;
}

AuthorData CommentAuthorsPart::add_author(std::string_view name,
                                          std::string_view initials) {
    // Compute next id by counting existing authors.
    int32_t count = 0;
    for ([[maybe_unused]] auto child : root_.children(kCmAuthorTag.c_str())) {
        ++count;
    }
    int32_t next_id = count;
    int32_t clr_idx = next_id % 10; // Colors cycle 0–9.

    auto elem = root_.append_child(kCmAuthorTag.c_str());
    elem.append_attribute("id") = next_id;
    elem.append_attribute("name") = std::string(name).c_str();
    elem.append_attribute("initials") = std::string(initials).c_str();
    elem.append_attribute("lastIdx") = 0;
    elem.append_attribute("clrIdx") = clr_idx;

    return AuthorData(elem);
}

void CommentAuthorsPart::remove_author(int32_t author_id) {
    for (auto child : root_.children(kCmAuthorTag.c_str())) {
        if (child.attribute("id").as_int(-1) == author_id) {
            root_.remove_child(child);
            return;
        }
    }
}

void CommentAuthorsPart::clear() {
    while (auto child = root_.child(kCmAuthorTag.c_str())) {
        root_.remove_child(child);
    }
}

int32_t CommentAuthorsPart::next_comment_idx(int32_t author_id) {
    // Find the global maximum lastIdx across all authors.
    int32_t global_max = 0;
    for (auto child : root_.children(kCmAuthorTag.c_str())) {
        global_max = std::max(global_max, child.attribute("lastIdx").as_int(0));
    }
    int32_t new_idx = global_max + 1;

    // Update the target author's lastIdx.
    auto author = find_author_by_id(author_id);
    if (author.has_value()) {
        author->set_last_idx(new_idx);
    }
    return new_idx;
}

void CommentAuthorsPart::save() {
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    doc_.save(writer, "  ");
    package_.set_part(kCommentAuthorsPartName, std::move(writer.result));
}

void CommentAuthorsPart::ensure_registered(
    opc::OpcPackage& package, std::string_view presentation_part_name) {
    // Add content type override if needed.
    opc::ContentTypesManager ct(package);
    auto existing_ct = ct.get_content_type(kCommentAuthorsPartName);
    if (existing_ct != opc::content_types::kCommentAuthors) {
        ct.add_override(kCommentAuthorsPartName,
                        opc::content_types::kCommentAuthors);
        ct.save();
    }

    // Add relationship from presentation to commentAuthors if needed.
    opc::RelationshipsManager rels(package, presentation_part_name);
    auto existing = rels.get_relationships_by_type(
        opc::rel_types::kCommentAuthors);
    if (existing.empty()) {
        rels.add_relationship(opc::rel_types::kCommentAuthors,
                              "commentAuthors.xml");
        rels.save();
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
