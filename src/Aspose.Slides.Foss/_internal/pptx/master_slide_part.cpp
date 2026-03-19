// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/master_slide_part.h>

#include <stdexcept>

#include <Aspose/Slides/Foss/_internal/opc/relationships.h>

namespace Aspose::Slides::Foss::Internal::pptx {

// ---------------------------------------------------------------------------
// Construction / load
// ---------------------------------------------------------------------------

MasterSlidePart::MasterSlidePart(opc::OpcPackage& package,
                                 std::string_view part_name)
    : package_(package),
      part_name_(part_name),
      rels_manager_(package, part_name) {
    load();
}

void MasterSlidePart::load() {
    auto content = package_.get_part(part_name_);
    if (!content) {
        throw std::runtime_error(
            "Master slide part not found: " + part_name_);
    }
    auto result = doc_.load_buffer(content->data(), content->size());
    if (!result) {
        throw std::runtime_error(
            "Failed to parse master slide XML: " + part_name_);
    }
    root_ = doc_.first_child();
}

// ---------------------------------------------------------------------------
// Properties
// ---------------------------------------------------------------------------

const std::string& MasterSlidePart::part_name() const {
    return part_name_;
}

std::string MasterSlidePart::name() const {
    // Find p:cSld element (direct child or descendant)
    auto csld = root_.child("p:cSld");
    if (csld) {
        return csld.attribute("name").as_string("");
    }
    return "";
}

void MasterSlidePart::set_name(std::string_view value) {
    auto csld = root_.child("p:cSld");
    if (csld) {
        csld.attribute("name").set_value(std::string(value).c_str());
    }
}

// ---------------------------------------------------------------------------
// Layout part names
// ---------------------------------------------------------------------------

std::vector<std::string> MasterSlidePart::layout_part_names() const {
    auto rels = rels_manager_.get_relationships_by_type(
        opc::rel_types::kSlideLayout);
    std::vector<std::string> result;
    result.reserve(rels.size());
    for (const auto& rel : rels) {
        result.push_back(resolve_target(rel.target));
    }
    return result;
}

// ---------------------------------------------------------------------------
// Target resolution
// ---------------------------------------------------------------------------

std::string MasterSlidePart::resolve_target(std::string_view target) const {
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

void MasterSlidePart::save() {
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
