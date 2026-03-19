// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/core_properties_part.h>

#include <algorithm>
#include <cstring>
#include <ctime>
#include <sstream>
#include <string>

namespace Aspose::Slides::Foss::Internal::pptx {

// Namespace URIs for core properties.
static constexpr const char* kNsCp =
    "http://schemas.openxmlformats.org/package/2006/metadata/core-properties";
static constexpr const char* kNsDc =
    "http://purl.org/dc/elements/1.1/";
static constexpr const char* kNsDcTerms =
    "http://purl.org/dc/terms/";
static constexpr const char* kNsDcmitype =
    "http://purl.org/dc/dcmitype/";
static constexpr const char* kNsXsi =
    "http://www.w3.org/2001/XMLSchema-instance";

// ---------------------------------------------------------------------------
// W3CDTF helpers
// ---------------------------------------------------------------------------

std::optional<TimePoint> parse_w3cdtf(std::string_view text) {
    // Trim whitespace
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t' ||
                             text.front() == '\n' || text.front() == '\r'))
        text.remove_prefix(1);
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t' ||
                             text.back() == '\n' || text.back() == '\r'))
        text.remove_suffix(1);

    if (text.empty()) return std::nullopt;

    // Copy to mutable buffer for parsing
    std::string buf(text);

    // Replace trailing Z with +00:00 for uniform parsing
    if (buf.back() == 'Z') {
        buf.pop_back();
    }

    // Parse: YYYY-MM-DDTHH:MM:SS  (ignore timezone offset beyond Z)
    std::tm tm = {};
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;

    // Try full datetime
    if (std::sscanf(buf.c_str(), "%d-%d-%dT%d:%d:%d",
                    &year, &month, &day, &hour, &minute, &second) >= 3) {
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = 0;

#ifdef _WIN32
        auto time = _mkgmtime(&tm);
#else
        auto time = timegm(&tm);
#endif
        if (time == -1) return std::nullopt;
        return std::chrono::system_clock::from_time_t(time);
    }

    return std::nullopt;
}

std::optional<std::string> format_w3cdtf(std::optional<TimePoint> tp) {
    if (!tp) return std::nullopt;

    auto time = std::chrono::system_clock::to_time_t(*tp);
    std::tm tm = {};
#ifdef _WIN32
    gmtime_s(&tm, &time);
#else
    gmtime_r(&time, &tm);
#endif

    char buf[32];
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02dT%02d:%02d:%02dZ",
                  tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                  tm.tm_hour, tm.tm_min, tm.tm_sec);
    return std::string(buf);
}

// ---------------------------------------------------------------------------
// Construction / parse
// ---------------------------------------------------------------------------

CorePropertiesPart::CorePropertiesPart(opc::OpcPackage& package)
    : package_(package) {
    parse();
}

void CorePropertiesPart::parse() {
    auto data = package_.get_part(kCorePropertiesPartName);
    if (!data) return;

    auto result = doc_.load_buffer(data->data(), data->size());
    if (!result) return;

    root_ = doc_.first_child();
    has_original_ = true;

    // String properties
    title = get_text("dc", "title");
    subject = get_text("dc", "subject");
    creator = get_text("dc", "creator");
    keywords = get_text("cp", "keywords");
    description = get_text("dc", "description");
    category = get_text("cp", "category");
    content_status = get_text("cp", "contentStatus");
    content_type = get_text("cp", "contentType");
    last_modified_by = get_text("cp", "lastModifiedBy");
    revision = get_text("cp", "revision");

    // Date properties
    auto created_text = get_text("dcterms", "created");
    created = created_text ? parse_w3cdtf(*created_text) : std::nullopt;

    auto modified_text = get_text("dcterms", "modified");
    modified = modified_text ? parse_w3cdtf(*modified_text) : std::nullopt;

    auto printed_text = get_text("cp", "lastPrinted");
    last_printed = printed_text ? parse_w3cdtf(*printed_text) : std::nullopt;
}

std::optional<std::string> CorePropertiesPart::get_text(
    const char* prefix, const char* local_name) const {
    if (!root_) return std::nullopt;

    // Build prefixed name "prefix:localName"
    std::string qualified = std::string(prefix) + ":" + local_name;
    auto el = root_.child(qualified.c_str());
    if (el && el.text().get()[0] != '\0') {
        return std::string(el.text().get());
    }
    return std::nullopt;
}

// ---------------------------------------------------------------------------
// mark_dirty / clear
// ---------------------------------------------------------------------------

void CorePropertiesPart::mark_dirty() {
    dirty_ = true;
}

void CorePropertiesPart::clear() {
    title = std::nullopt;
    subject = std::nullopt;
    creator = std::nullopt;
    keywords = std::nullopt;
    description = std::nullopt;
    category = std::nullopt;
    content_status = std::nullopt;
    content_type = std::nullopt;
    last_modified_by = std::nullopt;
    revision = std::nullopt;
    created = std::nullopt;
    modified = std::nullopt;
    last_printed = std::nullopt;
    dirty_ = true;
}

// ---------------------------------------------------------------------------
// save
// ---------------------------------------------------------------------------

void CorePropertiesPart::save() {
    if (!dirty_ && has_original_) return;

    pugi::xml_document out_doc;
    auto decl = out_doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto root = out_doc.append_child("cp:coreProperties");
    root.append_attribute("xmlns:cp") = kNsCp;
    root.append_attribute("xmlns:dc") = kNsDc;
    root.append_attribute("xmlns:dcterms") = kNsDcTerms;
    root.append_attribute("xmlns:dcmitype") = kNsDcmitype;
    root.append_attribute("xmlns:xsi") = kNsXsi;

    set_dc(root, "title", title);
    set_dc(root, "subject", subject);
    set_dc(root, "creator", creator);
    set_cp(root, "keywords", keywords);
    set_dc(root, "description", description);
    set_cp(root, "category", category);
    set_cp(root, "contentStatus", content_status);
    set_cp(root, "contentType", content_type);
    set_cp(root, "lastModifiedBy", last_modified_by);
    set_cp(root, "revision", revision);

    set_dcterms_date(root, "created", created);
    set_dcterms_date(root, "modified", modified);
    if (last_printed) {
        auto formatted = format_w3cdtf(last_printed);
        if (formatted) {
            set_cp(root, "lastPrinted", formatted);
        }
    }

    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    out_doc.save(writer, "  ");
    package_.set_part(kCorePropertiesPartName, std::move(writer.result));
    dirty_ = false;
}

// ---------------------------------------------------------------------------
// Static set helpers
// ---------------------------------------------------------------------------

void CorePropertiesPart::set_dc(pugi::xml_node root, const char* local_name,
                                 const std::optional<std::string>& value) {
    if (!value) return;
    std::string qualified = std::string("dc:") + local_name;
    auto el = root.append_child(qualified.c_str());
    el.text().set(value->c_str());
}

void CorePropertiesPart::set_cp(pugi::xml_node root, const char* local_name,
                                 const std::optional<std::string>& value) {
    if (!value) return;
    std::string qualified = std::string("cp:") + local_name;
    auto el = root.append_child(qualified.c_str());
    el.text().set(value->c_str());
}

void CorePropertiesPart::set_dcterms_date(pugi::xml_node root,
                                           const char* local_name,
                                           std::optional<TimePoint> tp) {
    if (!tp) return;
    auto formatted = format_w3cdtf(tp);
    if (!formatted) return;

    std::string qualified = std::string("dcterms:") + local_name;
    auto el = root.append_child(qualified.c_str());
    el.append_attribute("xsi:type") = "dcterms:W3CDTF";
    el.text().set(formatted->c_str());
}

} // namespace Aspose::Slides::Foss::Internal::pptx
