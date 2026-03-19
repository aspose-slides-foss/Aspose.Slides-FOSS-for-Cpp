// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/app_properties_part.h>

#include <charconv>
#include <stdexcept>
#include <string>

namespace Aspose::Slides::Foss::Internal::pptx {

// Namespace URIs for extended properties and variant types.
static constexpr const char* kNsEp =
    "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties";
static constexpr const char* kNsVt =
    "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes";

// ---------------------------------------------------------------------------
// Construction / parse
// ---------------------------------------------------------------------------

AppPropertiesPart::AppPropertiesPart(opc::OpcPackage& package)
    : package_(package) {
    parse();
}

void AppPropertiesPart::parse() {
    auto data = package_.get_part(kAppPropertiesPartName);
    if (!data) return;

    auto result = doc_.load_buffer(data->data(), data->size());
    if (!result) return;

    root_ = doc_.first_child();
    has_original_ = true;

    application = get_text("Application");
    app_version = get_text("AppVersion");
    company = get_text("Company");
    manager = get_text("Manager");
    presentation_format = get_text("PresentationFormat");
    template_name = get_text("Template");
    hyperlink_base = get_text("HyperlinkBase");

    total_time = get_int("TotalTime");
    slides = get_int("Slides");
    hidden_slides = get_int("HiddenSlides");
    notes = get_int("Notes");
    paragraphs = get_int("Paragraphs");
    words = get_int("Words");
    mm_clips = get_int("MMClips");

    scale_crop = get_bool("ScaleCrop");
    links_up_to_date = get_bool("LinksUpToDate");
    shared_doc = get_bool("SharedDoc");
    hyperlinks_changed = get_bool("HyperlinksChanged");

    parse_heading_pairs();
    parse_titles_of_parts();
}

// ---------------------------------------------------------------------------
// Simple property getters (from parsed XML)
// ---------------------------------------------------------------------------

std::optional<std::string> AppPropertiesPart::get_text(
    std::string_view local_name) const {
    if (!root_) return std::nullopt;
    auto el = root_.child(std::string(local_name).c_str());
    if (el && el.text().get()[0] != '\0') {
        return std::string(el.text().get());
    }
    return std::nullopt;
}

std::optional<int> AppPropertiesPart::get_int(
    std::string_view local_name) const {
    auto text = get_text(local_name);
    if (!text) return std::nullopt;
    int value = 0;
    auto [ptr, ec] =
        std::from_chars(text->data(), text->data() + text->size(), value);
    if (ec == std::errc{}) return value;
    return std::nullopt;
}

std::optional<bool> AppPropertiesPart::get_bool(
    std::string_view local_name) const {
    auto text = get_text(local_name);
    if (!text) return std::nullopt;
    auto& t = *text;
    // Lowercase compare
    if (t == "true" || t == "True" || t == "TRUE" || t == "1") return true;
    return false;
}

// ---------------------------------------------------------------------------
// Vector property parsing
// ---------------------------------------------------------------------------

void AppPropertiesPart::parse_heading_pairs() {
    if (!root_) return;
    auto hp_el = root_.child("HeadingPairs");
    if (!hp_el) return;
    auto vector = hp_el.child("vt:vector");
    if (!vector) return;

    // Pairs alternate: name variant, count variant
    std::vector<pugi::xml_node> variants;
    for (auto v : vector.children("vt:variant")) {
        variants.push_back(v);
    }

    for (size_t i = 0; i + 1 < variants.size(); i += 2) {
        auto name_el = variants[i].child("vt:lpstr");
        auto count_el = variants[i + 1].child("vt:i4");
        if (name_el && count_el) {
            std::string name = name_el.text().get();
            int count = 0;
            auto count_text = count_el.text().get();
            auto [ptr, ec] = std::from_chars(
                count_text, count_text + std::char_traits<char>::length(count_text), count);
            if (ec != std::errc{}) count = 0;
            heading_pairs.push_back({std::move(name), count});
        }
    }
}

void AppPropertiesPart::parse_titles_of_parts() {
    if (!root_) return;
    auto tp_el = root_.child("TitlesOfParts");
    if (!tp_el) return;
    auto vector = tp_el.child("vt:vector");
    if (!vector) return;

    for (auto lpstr : vector.children("vt:lpstr")) {
        titles_of_parts.emplace_back(lpstr.text().get());
    }
}

// ---------------------------------------------------------------------------
// mark_dirty / clear
// ---------------------------------------------------------------------------

void AppPropertiesPart::mark_dirty() {
    dirty_ = true;
}

void AppPropertiesPart::clear() {
    application = std::nullopt;
    app_version = std::nullopt;
    company = std::nullopt;
    manager = std::nullopt;
    presentation_format = std::nullopt;
    template_name = std::nullopt;
    hyperlink_base = std::nullopt;
    total_time = std::nullopt;
    slides = std::nullopt;
    hidden_slides = std::nullopt;
    notes = std::nullopt;
    paragraphs = std::nullopt;
    words = std::nullopt;
    mm_clips = std::nullopt;
    scale_crop = std::nullopt;
    links_up_to_date = std::nullopt;
    shared_doc = std::nullopt;
    hyperlinks_changed = std::nullopt;
    heading_pairs.clear();
    titles_of_parts.clear();
    dirty_ = true;
}

// ---------------------------------------------------------------------------
// save
// ---------------------------------------------------------------------------

void AppPropertiesPart::save() {
    if (!dirty_ && has_original_) return;

    pugi::xml_document out_doc;
    auto decl = out_doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto root = out_doc.append_child("Properties");
    root.append_attribute("xmlns") = kNsEp;
    root.append_attribute("xmlns:vt") = kNsVt;

    set_text(root, "Application", application);
    set_text(root, "AppVersion", app_version);
    set_text(root, "Company", company);
    set_text(root, "Manager", manager);
    set_text(root, "PresentationFormat", presentation_format);
    set_text(root, "Template", template_name);
    set_text(root, "HyperlinkBase", hyperlink_base);

    set_int(root, "TotalTime", total_time);
    set_int(root, "Slides", slides);
    set_int(root, "HiddenSlides", hidden_slides);
    set_int(root, "Notes", notes);
    set_int(root, "Paragraphs", paragraphs);
    set_int(root, "Words", words);
    set_int(root, "MMClips", mm_clips);

    set_bool(root, "ScaleCrop", scale_crop);
    set_bool(root, "LinksUpToDate", links_up_to_date);
    set_bool(root, "SharedDoc", shared_doc);
    set_bool(root, "HyperlinksChanged", hyperlinks_changed);

    if (!heading_pairs.empty()) {
        write_heading_pairs(root);
    }
    if (!titles_of_parts.empty()) {
        write_titles_of_parts(root);
    }

    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    out_doc.save(writer, "  ");
    package_.set_part(kAppPropertiesPartName,
                      std::move(writer.result));
    dirty_ = false;
}

// ---------------------------------------------------------------------------
// Static set helpers
// ---------------------------------------------------------------------------

void AppPropertiesPart::set_text(pugi::xml_node root,
                                  std::string_view local_name,
                                  const std::optional<std::string>& value) {
    if (!value) return;
    auto el = root.append_child(std::string(local_name).c_str());
    el.text().set(value->c_str());
}

void AppPropertiesPart::set_int(pugi::xml_node root,
                                 std::string_view local_name,
                                 std::optional<int> value) {
    if (!value) return;
    auto el = root.append_child(std::string(local_name).c_str());
    el.text().set(std::to_string(*value).c_str());
}

void AppPropertiesPart::set_bool(pugi::xml_node root,
                                  std::string_view local_name,
                                  std::optional<bool> value) {
    if (!value) return;
    auto el = root.append_child(std::string(local_name).c_str());
    el.text().set(*value ? "true" : "false");
}

// ---------------------------------------------------------------------------
// Vector property writers
// ---------------------------------------------------------------------------

void AppPropertiesPart::write_heading_pairs(pugi::xml_node root) const {
    auto hp_el = root.append_child("HeadingPairs");
    auto vector = hp_el.append_child("vt:vector");
    vector.append_attribute("size") =
        static_cast<int>(heading_pairs.size() * 2);
    vector.append_attribute("baseType") = "variant";

    for (const auto& pair : heading_pairs) {
        auto v1 = vector.append_child("vt:variant");
        auto lpstr = v1.append_child("vt:lpstr");
        lpstr.text().set(pair.name.c_str());

        auto v2 = vector.append_child("vt:variant");
        auto i4 = v2.append_child("vt:i4");
        i4.text().set(std::to_string(pair.count).c_str());
    }
}

void AppPropertiesPart::write_titles_of_parts(pugi::xml_node root) const {
    auto tp_el = root.append_child("TitlesOfParts");
    auto vector = tp_el.append_child("vt:vector");
    vector.append_attribute("size") =
        static_cast<int>(titles_of_parts.size());
    vector.append_attribute("baseType") = "lpstr";

    for (const auto& title : titles_of_parts) {
        auto lpstr = vector.append_child("vt:lpstr");
        lpstr.text().set(title.c_str());
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
