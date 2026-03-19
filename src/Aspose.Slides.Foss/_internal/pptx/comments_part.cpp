// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/comments_part.h>

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

namespace Aspose::Slides::Foss::Internal::pptx {

// Fully-qualified element names with namespace URI.
static const std::string kCmTag = "p:cm";
static const std::string kCmLstTag = "p:cmLst";
static const std::string kPosTag = "p:pos";
static const std::string kTextTag = "p:text";

// ---------------------------------------------------------------------------
// dt_to_str / str_to_dt
// ---------------------------------------------------------------------------

std::string dt_to_str(std::chrono::system_clock::time_point tp) {
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &tt);
#else
    gmtime_r(&tt, &tm);
#endif
    auto dur = tp.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() % 1000;

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms;
    return oss.str();
}

std::optional<std::chrono::system_clock::time_point> str_to_dt(std::string_view s) {
    if (s.empty()) return std::nullopt;

    std::tm tm{};
    int ms = 0;
    std::string str(s);

    // Try: YYYY-MM-DDTHH:MM:SS.fff
    std::istringstream iss(str);
    iss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    if (!iss.fail()) {
        char dot = 0;
        if (iss.peek() == '.') {
            iss.get(dot);
            iss >> ms;
        }
        tm.tm_isdst = 0;
#ifdef _WIN32
        auto tt = _mkgmtime(&tm);
#else
        auto tt = timegm(&tm);
#endif
        if (tt != -1) {
            auto tp = std::chrono::system_clock::from_time_t(tt);
            tp += std::chrono::milliseconds(ms);
            return tp;
        }
    }

    // Try: YYYY-MM-DD only
    std::tm tm2{};
    std::istringstream iss2(str);
    iss2 >> std::get_time(&tm2, "%Y-%m-%d");
    if (!iss2.fail()) {
        tm2.tm_isdst = 0;
#ifdef _WIN32
        auto tt = _mkgmtime(&tm2);
#else
        auto tt = timegm(&tm2);
#endif
        if (tt != -1) {
            return std::chrono::system_clock::from_time_t(tt);
        }
    }

    return std::nullopt;
}

// ---------------------------------------------------------------------------
// CommentData
// ---------------------------------------------------------------------------

int32_t CommentData::author_id() const {
    return node_.attribute("authorId").as_int(0);
}

int32_t CommentData::idx() const {
    return node_.attribute("idx").as_int(0);
}

std::string CommentData::dt_str() const {
    return node_.attribute("dt").as_string("");
}

void CommentData::set_dt_str(std::string_view value) {
    node_.attribute("dt").set_value(std::string(value).c_str());
}

std::optional<int32_t> CommentData::parent_cm_id() const {
    auto attr = node_.attribute("parentCmId");
    if (attr.empty()) return std::nullopt;
    return attr.as_int();
}

void CommentData::set_parent_cm_id(std::optional<int32_t> value) {
    if (!value.has_value()) {
        node_.remove_attribute("parentCmId");
    } else {
        auto attr = node_.attribute("parentCmId");
        if (attr.empty()) {
            node_.append_attribute("parentCmId") = *value;
        } else {
            attr.set_value(*value);
        }
    }
}

std::string CommentData::text() const {
    auto text_node = node_.child(kTextTag.c_str());
    if (text_node) {
        auto t = text_node.text().as_string("");
        return t;
    }
    return {};
}

void CommentData::set_text(std::string_view value) {
    auto text_node = node_.child(kTextTag.c_str());
    if (!text_node) {
        text_node = node_.append_child(kTextTag.c_str());
    }
    text_node.text().set(std::string(value).c_str());
}

double CommentData::pos_x() const {
    auto pos = node_.child(kPosTag.c_str());
    if (pos) {
        return pos.attribute("x").as_int(0) / kCmToEmu;
    }
    return 0.0;
}

void CommentData::set_pos_x(double value) {
    auto pos = node_.child(kPosTag.c_str());
    if (!pos) {
        pos = node_.append_child(kPosTag.c_str());
    }
    auto x_val = static_cast<int64_t>(std::round(value * kCmToEmu));
    pos.attribute("x").set_value(x_val);
    if (pos.attribute("x").empty()) {
        pos.append_attribute("x") = x_val;
    }
}

double CommentData::pos_y() const {
    auto pos = node_.child(kPosTag.c_str());
    if (pos) {
        return pos.attribute("y").as_int(0) / kCmToEmu;
    }
    return 0.0;
}

void CommentData::set_pos_y(double value) {
    auto pos = node_.child(kPosTag.c_str());
    if (!pos) {
        pos = node_.append_child(kPosTag.c_str());
    }
    auto y_val = static_cast<int64_t>(std::round(value * kCmToEmu));
    auto attr = pos.attribute("y");
    if (attr.empty()) {
        pos.append_attribute("y") = y_val;
    } else {
        attr.set_value(y_val);
    }
}

// ---------------------------------------------------------------------------
// CommentsPart
// ---------------------------------------------------------------------------

CommentsPart::CommentsPart(opc::OpcPackage& package, std::string_view part_name)
    : package_(package), part_name_(part_name) {
    load();
}

void CommentsPart::load() {
    auto content = package_.get_part(part_name_);
    if (!content) {
        throw std::runtime_error("Comments part not found: " + part_name_);
    }
    auto result = doc_.load_buffer(content->data(), content->size());
    if (!result) {
        throw std::runtime_error("Failed to parse comments XML: " + part_name_);
    }
    root_ = doc_.first_child();
}

std::vector<pugi::xml_node> CommentsPart::cm_nodes() const {
    std::vector<pugi::xml_node> nodes;
    for (auto child : root_.children(kCmTag.c_str())) {
        nodes.push_back(child);
    }
    return nodes;
}

std::vector<CommentData> CommentsPart::get_comments() const {
    std::vector<CommentData> result;
    for (auto child : root_.children(kCmTag.c_str())) {
        result.emplace_back(child);
    }
    return result;
}

std::vector<CommentData> CommentsPart::get_comments_by_author(
    int32_t author_id) const {
    std::vector<CommentData> result;
    for (auto child : root_.children(kCmTag.c_str())) {
        if (child.attribute("authorId").as_int(-1) == author_id) {
            result.emplace_back(child);
        }
    }
    return result;
}

std::optional<CommentData> CommentsPart::find_comment_by_idx(
    int32_t author_id, int32_t idx) const {
    for (auto child : root_.children(kCmTag.c_str())) {
        if (child.attribute("authorId").as_int(-1) == author_id &&
            child.attribute("idx").as_int(-1) == idx) {
            return CommentData(child);
        }
    }
    return std::nullopt;
}

std::optional<CommentData> CommentsPart::find_comment_by_idx_all(
    int32_t idx) const {
    for (auto child : root_.children(kCmTag.c_str())) {
        if (child.attribute("idx").as_int(-1) == idx) {
            return CommentData(child);
        }
    }
    return std::nullopt;
}

CommentData CommentsPart::add_comment(int32_t author_id, int32_t idx,
                                       std::string_view text, double pos_x,
                                       double pos_y, std::string_view dt_str,
                                       std::optional<int32_t> parent_idx) {
    auto elem = root_.append_child(kCmTag.c_str());
    elem.append_attribute("authorId") = author_id;
    elem.append_attribute("dt") = std::string(dt_str).c_str();
    elem.append_attribute("idx") = idx;
    if (parent_idx.has_value()) {
        elem.append_attribute("parentCmId") = *parent_idx;
    }

    auto pos = elem.append_child(kPosTag.c_str());
    pos.append_attribute("x") = static_cast<int64_t>(std::round(pos_x * kCmToEmu));
    pos.append_attribute("y") = static_cast<int64_t>(std::round(pos_y * kCmToEmu));

    auto text_node = elem.append_child(kTextTag.c_str());
    text_node.text().set(std::string(text).c_str());

    return CommentData(elem);
}

CommentData CommentsPart::insert_comment(int32_t index, int32_t author_id,
                                          int32_t idx, std::string_view text,
                                          double pos_x, double pos_y,
                                          std::string_view dt_str,
                                          std::optional<int32_t> parent_idx) {
    auto all_cm = cm_nodes();

    // Build the element by first adding, then moving if needed
    auto elem = root_.append_child(kCmTag.c_str());
    elem.append_attribute("authorId") = author_id;
    elem.append_attribute("dt") = std::string(dt_str).c_str();
    elem.append_attribute("idx") = idx;
    if (parent_idx.has_value()) {
        elem.append_attribute("parentCmId") = *parent_idx;
    }

    auto pos = elem.append_child(kPosTag.c_str());
    pos.append_attribute("x") = static_cast<int64_t>(std::round(pos_x * kCmToEmu));
    pos.append_attribute("y") = static_cast<int64_t>(std::round(pos_y * kCmToEmu));

    auto text_node = elem.append_child(kTextTag.c_str());
    text_node.text().set(std::string(text).c_str());

    // Move to correct position if needed
    if (index < static_cast<int32_t>(all_cm.size())) {
        root_.insert_move_before(elem, all_cm[index]);
    }

    return CommentData(elem);
}

void CommentsPart::remove_comment(int32_t author_id, int32_t idx) {
    for (auto child : root_.children(kCmTag.c_str())) {
        if (child.attribute("authorId").as_int(-1) == author_id &&
            child.attribute("idx").as_int(-1) == idx) {
            root_.remove_child(child);
            return;
        }
    }
}

void CommentsPart::remove_comment_elem(pugi::xml_node elem) {
    root_.remove_child(elem);
}

void CommentsPart::remove_comments_at(int32_t index) {
    auto all_cm = cm_nodes();
    if (index >= 0 && index < static_cast<int32_t>(all_cm.size())) {
        root_.remove_child(all_cm[index]);
    }
}

void CommentsPart::clear() {
    while (auto child = root_.child(kCmTag.c_str())) {
        root_.remove_child(child);
    }
}

int32_t CommentsPart::count() const {
    int32_t n = 0;
    for ([[maybe_unused]] auto child : root_.children(kCmTag.c_str())) {
        ++n;
    }
    return n;
}

bool CommentsPart::is_empty() const {
    return count() == 0;
}

void CommentsPart::save() {
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    doc_.save(writer, "  ");
    package_.set_part(part_name_, std::move(writer.result));
}

// ---------------------------------------------------------------------------
// Static methods
// ---------------------------------------------------------------------------

CommentsPart CommentsPart::create_for_slide(
    opc::OpcPackage& package, std::string_view slide_part_name,
    opc::RelationshipsManager* slide_rels_manager) {

    // Find a unique part name
    int num = 1;
    std::string part_name;
    while (true) {
        part_name = "ppt/comments/slide" + std::to_string(num) + ".xml";
        if (!package.has_part(part_name)) break;
        ++num;
    }

    // Build minimal XML: <p:cmLst xmlns:p="..."/>
    pugi::xml_document doc;
    auto decl = doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto root = doc.append_child(kCmLstTag.c_str());
    root.append_attribute("xmlns:p") = std::string(ns_uri::kP).c_str();

    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    doc.save(writer, "  ");
    package.set_part(part_name, std::move(writer.result));

    // Content type
    opc::ContentTypesManager ct(package);
    ct.add_override(part_name, opc::content_types::kComments);
    ct.save();

    // Relationship: slide -> comments
    auto rel_target = compute_relative_target(
        std::string(slide_part_name), part_name);

    if (slide_rels_manager) {
        slide_rels_manager->add_relationship(
            opc::rel_types::kComments, rel_target);
        slide_rels_manager->save();
    } else {
        opc::RelationshipsManager slide_rels(package, slide_part_name);
        slide_rels.add_relationship(opc::rel_types::kComments, rel_target);
        slide_rels.save();
    }

    return CommentsPart(package, part_name);
}

std::optional<CommentsPart> CommentsPart::load_for_slide(
    opc::OpcPackage& package, std::string_view slide_part_name) {

    opc::RelationshipsManager slide_rels(package, slide_part_name);
    auto comment_rels = slide_rels.get_relationships_by_type(
        opc::rel_types::kComments);
    if (comment_rels.empty()) return std::nullopt;

    auto& rel = comment_rels[0];
    auto part_name = resolve_target(slide_part_name, rel.target);
    if (!package.has_part(part_name)) return std::nullopt;

    return CommentsPart(package, part_name);
}

void CommentsPart::delete_for_slide(opc::OpcPackage& package,
                                     std::string_view slide_part_name) {
    opc::RelationshipsManager slide_rels(package, slide_part_name);
    auto comment_rels = slide_rels.get_relationships_by_type(
        opc::rel_types::kComments);

    for (const auto& rel : comment_rels) {
        auto part_name = resolve_target(slide_part_name, rel.target);
        package.delete_part(part_name);

        opc::ContentTypesManager ct(package);
        ct.remove_override(part_name);
        ct.save();

        slide_rels.remove_relationship(rel.id);
    }

    if (!comment_rels.empty()) {
        slide_rels.save();
    }
}

std::string CommentsPart::resolve_target(std::string_view from_part,
                                          std::string_view target) {
    std::string t(target);
    if (!t.empty() && t[0] == '/') {
        // Absolute path — strip leading slash
        return t.substr(1);
    }
    // Relative path
    std::string from(from_part);
    std::string base_dir;
    auto slash = from.rfind('/');
    if (slash != std::string::npos) {
        base_dir = from.substr(0, slash);
    }

    std::string combined = base_dir + "/" + t;
    std::vector<std::string> parts;
    std::istringstream stream(combined);
    std::string segment;
    while (std::getline(stream, segment, '/')) {
        if (segment == "..") {
            if (!parts.empty()) parts.pop_back();
        } else if (!segment.empty() && segment != ".") {
            parts.push_back(segment);
        }
    }

    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += '/';
        result += parts[i];
    }
    return result;
}

std::string CommentsPart::compute_relative_target(std::string_view from_part,
                                                    std::string_view to_part) {
    // Extract directory and filename components
    std::string from(from_part);
    std::string to(to_part);

    std::string from_dir, to_dir, to_file;
    auto from_slash = from.rfind('/');
    if (from_slash != std::string::npos) {
        from_dir = from.substr(0, from_slash);
    }
    auto to_slash = to.rfind('/');
    if (to_slash != std::string::npos) {
        to_dir = to.substr(0, to_slash);
        to_file = to.substr(to_slash + 1);
    } else {
        to_file = to;
    }

    if (from_dir == to_dir) return to_file;

    // Split into components
    auto split = [](const std::string& s) -> std::vector<std::string> {
        if (s.empty()) return {};
        std::vector<std::string> parts;
        std::istringstream stream(s);
        std::string seg;
        while (std::getline(stream, seg, '/')) {
            if (!seg.empty()) parts.push_back(seg);
        }
        return parts;
    };

    auto from_parts = split(from_dir);
    auto to_parts = split(to_dir);

    // Find common prefix length
    size_t common_len = 0;
    for (size_t i = 0; i < std::min(from_parts.size(), to_parts.size()); ++i) {
        if (from_parts[i] == to_parts[i]) {
            common_len = i + 1;
        } else {
            break;
        }
    }

    // Build relative path
    size_t up_count = from_parts.size() - common_len;
    std::string result;
    for (size_t i = 0; i < up_count; ++i) {
        result += "../";
    }

    for (size_t i = common_len; i < to_parts.size(); ++i) {
        result += to_parts[i] + "/";
    }

    result += to_file;
    return result;
}

} // namespace Aspose::Slides::Foss::Internal::pptx
