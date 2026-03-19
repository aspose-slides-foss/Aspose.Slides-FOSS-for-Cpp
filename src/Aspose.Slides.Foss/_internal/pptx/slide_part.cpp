// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>

#include <stdexcept>

#include <Aspose/Slides/Foss/_internal/opc/relationships.h>

namespace Aspose::Slides::Foss::Internal::pptx {

// ---------------------------------------------------------------------------
// Construction / load
// ---------------------------------------------------------------------------

SlidePart::SlidePart(opc::OpcPackage& package, std::string_view part_name)
    : package_(package),
      part_name_(part_name),
      rels_manager_(package, part_name) {
    load();
}

void SlidePart::load() {
    auto content = package_.get_part(part_name_);
    if (!content) {
        throw std::runtime_error("Slide part not found: " + part_name_);
    }
    auto result = doc_.load_buffer(content->data(), content->size());
    if (!result) {
        throw std::runtime_error("Failed to parse slide XML: " + part_name_);
    }
    root_ = doc_.first_child();
}

// ---------------------------------------------------------------------------
// Properties
// ---------------------------------------------------------------------------

const std::string& SlidePart::part_name() const {
    return part_name_;
}

opc::OpcPackage& SlidePart::package() {
    return package_;
}

const opc::OpcPackage& SlidePart::package() const {
    return package_;
}

// ---------------------------------------------------------------------------
// Layout part name
// ---------------------------------------------------------------------------

std::string SlidePart::layout_part_name() const {
    auto rels = rels_manager_.get_relationships_by_type(
        opc::rel_types::kSlideLayout);
    if (rels.empty()) {
        return "";
    }
    return resolve_target(rels.front().target);
}

// ---------------------------------------------------------------------------
// Target resolution
// ---------------------------------------------------------------------------

std::string SlidePart::resolve_target(std::string_view target) const {
    // Absolute target — strip leading '/'
    if (!target.empty() && target.front() == '/') {
        target.remove_prefix(1);
        return std::string(target);
    }

    // Relative target — resolve against the part's directory
    std::string base_dir;
    auto slash_pos = part_name_.rfind('/');
    if (slash_pos != std::string::npos) {
        base_dir = part_name_.substr(0, slash_pos);
    }

    std::string combined = base_dir.empty()
        ? std::string(target)
        : base_dir + "/" + std::string(target);

    // Normalize path segments, collapsing ".." and skipping "."
    std::vector<std::string_view> resolved;
    std::string_view remaining(combined);
    while (!remaining.empty()) {
        auto sep = remaining.find('/');
        auto segment = remaining.substr(0, sep);
        remaining = (sep == std::string_view::npos)
            ? std::string_view{}
            : remaining.substr(sep + 1);

        if (segment == "..") {
            if (!resolved.empty()) {
                resolved.pop_back();
            }
        } else if (!segment.empty() && segment != ".") {
            resolved.push_back(segment);
        }
    }

    std::string result;
    for (size_t i = 0; i < resolved.size(); ++i) {
        if (i > 0) result += '/';
        result += resolved[i];
    }
    return result;
}

// ---------------------------------------------------------------------------
// Save
// ---------------------------------------------------------------------------

void SlidePart::save() {
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    doc_.save(writer, "  ");
    package_.set_part(part_name_, std::move(writer.result));
    rels_manager_.save();
}

} // namespace Aspose::Slides::Foss::Internal::pptx
