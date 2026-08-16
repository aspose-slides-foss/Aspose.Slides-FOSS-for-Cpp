// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/custom_properties_part.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <ctime>
#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>

namespace Aspose::Slides::Foss::Internal::pptx {

// Namespace URIs for custom properties.
static constexpr const char* kNsCustom =
    "http://schemas.openxmlformats.org/officeDocument/2006/custom-properties";
static constexpr const char* kNsVt =
    "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes";

// Clark-notation prefixed tags for pugixml.
static const std::string kCustomProperty =
    std::string("{") + kNsCustom + "}property";
static const std::string kVtLpwstr =
    std::string("{") + kNsVt + "}lpwstr";
static const std::string kVtI4 =
    std::string("{") + kNsVt + "}i4";
static const std::string kVtR8 =
    std::string("{") + kNsVt + "}r8";
static const std::string kVtBool =
    std::string("{") + kNsVt + "}bool";
static const std::string kVtFiletime =
    std::string("{") + kNsVt + "}filetime";

// Format ID for custom properties.
static constexpr const char* kFmtId =
    "{D5CDD505-2E9C-101B-9397-08002B2CF9AE}";

// ---------------------------------------------------------------------------
// Construction / parse
// ---------------------------------------------------------------------------

CustomPropertiesPart::CustomPropertiesPart(opc::OpcPackage& package)
    : package_(package) {
    parse();
}

void CustomPropertiesPart::parse() {
    auto data = package_.get_part(kCustomPropertiesPartName);
    if (!data) return;

    pugi::xml_document doc;
    auto result = doc.load_buffer(data->data(), data->size());
    if (!result) return;

    auto root = doc.first_child();
    for (auto prop_el : root.children("property")) {
        auto name_attr = prop_el.attribute("name");
        if (!name_attr) continue;

        std::string name = name_attr.as_string();
        auto value = read_value(prop_el);
        if (value) {
            properties_.emplace_back(std::move(name), std::move(*value));
        }
    }
}

std::optional<CustomPropertyValue> CustomPropertiesPart::read_value(
    const pugi::xml_node& prop_el) const {
    for (auto child : prop_el.children()) {
        std::string tag = child.name();
        std::string text = child.text().as_string();

        if (tag == "vt:lpwstr") {
            return CustomPropertyValue{text};
        } else if (tag == "vt:i4") {
            try {
                return CustomPropertyValue{static_cast<int32_t>(std::stoi(text))};
            } catch (...) {
                return CustomPropertyValue{int32_t{0}};
            }
        } else if (tag == "vt:r8") {
            try {
                return CustomPropertyValue{std::stod(text)};
            } catch (...) {
                return CustomPropertyValue{0.0};
            }
        } else if (tag == "vt:bool") {
            std::string lower = text;
            // ::tolower takes an int that must be representable as unsigned
            // char; handing it a negative char -- which any byte above 0x7F is
            // on a signed-char platform -- is undefined. The cast is what makes
            // this safe, and taking the result back through unsigned char is
            // what keeps the conversion in range.
            std::ranges::transform(lower, lower.begin(), [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            });
            return CustomPropertyValue{lower == "true" || lower == "1"};
        } else if (tag == "vt:filetime") {
            auto tp = parse_filetime(text);
            if (tp) {
                return CustomPropertyValue{*tp};
            }
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<CustomTimePoint> CustomPropertiesPart::parse_filetime(
    std::string_view text) {
    if (text.empty()) return std::nullopt;

    std::string buf(text);

    // Strip trailing Z for uniform parsing.
    if (buf.back() == 'Z') {
        buf.pop_back();
    }

    // Strip +00:00 style timezone suffix.
    if (buf.size() >= 6 && buf[buf.size() - 6] == '+') {
        buf.resize(buf.size() - 6);
    }

    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
    if (std::sscanf(buf.c_str(), "%d-%d-%dT%d:%d:%d",
                    &year, &month, &day, &hour, &minute, &second) >= 3) {
        std::tm tm = {};
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

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

int32_t CustomPropertiesPart::count() const {
    return static_cast<int32_t>(properties_.size());
}

bool CustomPropertiesPart::contains(std::string_view name) const {
    return std::ranges::any_of(properties_,
        [&](const auto& p) { return p.first == name; });
}

std::string CustomPropertiesPart::get_name(int32_t index) const {
    if (index < 0 || index >= static_cast<int32_t>(properties_.size())) {
        throw std::out_of_range(
            "Index " + std::to_string(index) + " out of range");
    }
    return properties_[static_cast<size_t>(index)].first;
}

std::optional<CustomPropertyValue> CustomPropertiesPart::get_value(
    std::string_view name) const {
    auto it = std::ranges::find_if(properties_,
        [&](const auto& p) { return p.first == name; });
    if (it != properties_.end()) {
        return it->second;
    }
    return std::nullopt;
}

void CustomPropertiesPart::set_value(std::string_view name,
                                      CustomPropertyValue value) {
    auto it = std::ranges::find_if(properties_,
        [&](const auto& p) { return p.first == name; });
    if (it != properties_.end()) {
        it->second = std::move(value);
    } else {
        properties_.emplace_back(std::string(name), std::move(value));
    }
    dirty_ = true;
}

bool CustomPropertiesPart::remove(std::string_view name) {
    auto it = std::ranges::find_if(properties_,
        [&](const auto& p) { return p.first == name; });
    if (it != properties_.end()) {
        properties_.erase(it);
        dirty_ = true;
        return true;
    }
    return false;
}

void CustomPropertiesPart::clear() {
    if (!properties_.empty()) {
        properties_.clear();
        dirty_ = true;
    }
}

// ---------------------------------------------------------------------------
// Save
// ---------------------------------------------------------------------------

void CustomPropertiesPart::save() {
    if (!dirty_) return;

    if (properties_.empty()) {
        package_.delete_part(kCustomPropertiesPartName);
        dirty_ = false;
        return;
    }

    pugi::xml_document doc;
    auto decl = doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto root = doc.append_child("Properties");
    root.append_attribute("xmlns") = kNsCustom;
    root.append_attribute("xmlns:vt") = kNsVt;

    int pid = 2;
    for (const auto& [name, value] : properties_) {
        auto prop_el = root.append_child("property");
        prop_el.append_attribute("fmtid") = kFmtId;
        prop_el.append_attribute("pid") = std::to_string(pid).c_str();
        prop_el.append_attribute("name") = name.c_str();
        write_value(prop_el, value);
        ++pid;
    }

    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    doc.save(writer, "  ");
    package_.set_part(kCustomPropertiesPartName, std::move(writer.result));

    ensure_content_type();
    ensure_relationship();
    dirty_ = false;
}

void CustomPropertiesPart::write_value(pugi::xml_node prop_el,
                                        const CustomPropertyValue& value) const {
    std::visit([&](const auto& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, bool>) {
            auto el = prop_el.append_child("vt:bool");
            el.text().set(v ? "true" : "false");
        } else if constexpr (std::is_same_v<T, int32_t>) {
            auto el = prop_el.append_child("vt:i4");
            el.text().set(std::to_string(v).c_str());
        } else if constexpr (std::is_same_v<T, double>) {
            auto el = prop_el.append_child("vt:r8");
            // Use snprintf for consistent formatting (no trailing zeros issue).
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%g", v);
            el.text().set(buf);
        } else if constexpr (std::is_same_v<T, CustomTimePoint>) {
            auto el = prop_el.append_child("vt:filetime");
            auto time = std::chrono::system_clock::to_time_t(v);
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
            el.text().set(buf);
        } else if constexpr (std::is_same_v<T, std::string>) {
            auto el = prop_el.append_child("vt:lpwstr");
            el.text().set(v.c_str());
        }
    }, value);
}

void CustomPropertiesPart::ensure_content_type() {
    opc::ContentTypesManager ct_mgr(package_);
    if (ct_mgr.get_content_type(kCustomPropertiesPartName).empty()) {
        ct_mgr.add_override(kCustomPropertiesPartName,
                            opc::content_types::kCustomProperties);
        ct_mgr.save();
    }
}

void CustomPropertiesPart::ensure_relationship() {
    opc::RelationshipsManager rels_mgr(package_);
    auto existing = rels_mgr.get_relationships_by_type(
        opc::rel_types::kCustomProperties);
    if (existing.empty()) {
        rels_mgr.add_relationship(opc::rel_types::kCustomProperties,
                                  std::string(kCustomPropertiesPartName));
        rels_mgr.save();
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
