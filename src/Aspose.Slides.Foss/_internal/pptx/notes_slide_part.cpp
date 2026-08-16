// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/notes_slide_part.h>

#include <algorithm>
#include <stdexcept>

namespace Aspose::Slides::Foss::Internal::pptx {

// ---------------------------------------------------------------------------
// Construction / load
// ---------------------------------------------------------------------------

NotesSlidePart::NotesSlidePart(opc::OpcPackage& package,
                               std::string_view part_name)
    : package_(package),
      part_name_(part_name),
      rels_manager_(package, part_name) {
    load();
}

void NotesSlidePart::load() {
    auto content = package_.get_part(part_name_);
    if (!content) {
        throw std::runtime_error(
            "Notes slide part not found: " + part_name_);
    }
    auto result = doc_.load_buffer(content->data(), content->size());
    if (!result) {
        throw std::runtime_error(
            "Failed to parse notes slide XML: " + part_name_);
    }
    root_ = doc_.first_child();
}

// ---------------------------------------------------------------------------
// Properties
// ---------------------------------------------------------------------------

const std::string& NotesSlidePart::part_name() const {
    return part_name_;
}

std::string NotesSlidePart::name() const {
    auto csld = root_.child("p:cSld");
    if (csld) {
        return csld.attribute("name").as_string("");
    }
    return "";
}

void NotesSlidePart::set_name(std::string_view value) {
    auto csld = root_.child("p:cSld");
    if (csld) {
        if (!csld.attribute("name")) {
            csld.append_attribute("name");
        }
        csld.attribute("name").set_value(std::string(value).c_str());
    }
}

// ---------------------------------------------------------------------------
// Shape tree / placeholder access
// ---------------------------------------------------------------------------

pugi::xml_node NotesSlidePart::get_sp_tree() const {
    auto csld = root_.child("p:cSld");
    if (csld) {
        return csld.child("p:spTree");
    }
    return {};
}

pugi::xml_node NotesSlidePart::find_placeholder(std::string_view type) const {
    auto sp_tree = get_sp_tree();
    if (!sp_tree) return {};

    for (auto sp : sp_tree.children("p:sp")) {
        auto nv_sp_pr = sp.child("p:nvSpPr");
        if (!nv_sp_pr) continue;
        auto nv_pr = nv_sp_pr.child("p:nvPr");
        if (!nv_pr) continue;
        auto ph = nv_pr.child("p:ph");
        if (!ph) continue;
        if (std::string_view(ph.attribute("type").as_string("")) == type) {
            return sp;
        }
    }
    return {};
}

pugi::xml_node NotesSlidePart::get_notes_txbody() const {
    auto body_sp = find_placeholder(ph_type::kBody);
    if (body_sp) {
        return body_sp.child("p:txBody");
    }
    return {};
}

bool NotesSlidePart::has_placeholder(std::string_view type) const {
    return !find_placeholder(type).empty();
}

void NotesSlidePart::remove_placeholder(std::string_view type) {
    auto sp = find_placeholder(type);
    if (sp) {
        auto sp_tree = get_sp_tree();
        if (sp_tree) {
            sp_tree.remove_child(sp);
        }
    }
}

void NotesSlidePart::add_placeholder(std::string_view type) {
    if (has_placeholder(type)) return;

    auto sp_tree = get_sp_tree();
    if (!sp_tree) return;

    // Find the next available shape ID
    int max_id = 1;
    for (auto sp : sp_tree.children("p:sp")) {
        auto nv_sp_pr = sp.child("p:nvSpPr");
        if (!nv_sp_pr) continue;
        auto c_nv_pr = nv_sp_pr.child("p:cNvPr");
        if (!c_nv_pr) continue;
        int sp_id = c_nv_pr.attribute("id").as_int(1);
        max_id = std::max(max_id, sp_id);
    }

    // The node it returns is already attached to sp_tree; nothing here needs
    // a handle to it. The cast says the discard is deliberate.
    static_cast<void>(build_placeholder_shape(sp_tree, type, max_id + 1));
}

bool NotesSlidePart::is_text_placeholder(std::string_view type) {
    return type == ph_type::kDt || type == ph_type::kFtr || type == ph_type::kHdr;
}

pugi::xml_node NotesSlidePart::build_placeholder_shape(
    pugi::xml_node parent, std::string_view type, int shape_id) {

    auto sp = parent.append_child("p:sp");

    auto nv_sp_pr = sp.append_child("p:nvSpPr");
    auto c_nv_pr = nv_sp_pr.append_child("p:cNvPr");
    c_nv_pr.append_attribute("id") = shape_id;
    auto name_str = std::string(type) + " Placeholder " + std::to_string(shape_id);
    c_nv_pr.append_attribute("name") = name_str.c_str();

    auto c_nv_sp_pr = nv_sp_pr.append_child("p:cNvSpPr");
    auto sp_locks = c_nv_sp_pr.append_child("a:spLocks");
    sp_locks.append_attribute("noGrp") = "1";

    auto nv_pr = nv_sp_pr.append_child("p:nvPr");
    auto ph = nv_pr.append_child("p:ph");
    ph.append_attribute("type") = std::string(type).c_str();

    // Empty shape properties
    sp.append_child("p:spPr");

    // Add empty text body for text-bearing placeholders
    if (is_text_placeholder(type)) {
        auto tx_body = sp.append_child("p:txBody");
        tx_body.append_child("a:bodyPr");
        tx_body.append_child("a:lstStyle");
        auto a_p = tx_body.append_child("a:p");
        a_p.append_child("a:endParaRPr");
    }

    return sp;
}

// ---------------------------------------------------------------------------
// Text manipulation
// ---------------------------------------------------------------------------

void NotesSlidePart::set_placeholder_text(std::string_view type,
                                          std::string_view text) {
    if (!has_placeholder(type)) {
        add_placeholder(type);
    }

    auto sp = find_placeholder(type);
    if (!sp) return;

    auto txbody = sp.child("p:txBody");
    if (!txbody) {
        txbody = sp.append_child("p:txBody");
        txbody.append_child("a:bodyPr");
        txbody.append_child("a:lstStyle");
    }

    // Remove existing paragraphs
    while (auto p_elem = txbody.child("a:p")) {
        txbody.remove_child(p_elem);
    }

    // Add new paragraph with the given text
    auto a_p = txbody.append_child("a:p");
    if (!text.empty()) {
        auto a_r = a_p.append_child("a:r");
        auto a_t = a_r.append_child("a:t");
        a_t.text().set(std::string(text).c_str());
    } else {
        a_p.append_child("a:endParaRPr");
    }
}

// ---------------------------------------------------------------------------
// Save
// ---------------------------------------------------------------------------

void NotesSlidePart::save() {
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

// ---------------------------------------------------------------------------
// Target resolution
// ---------------------------------------------------------------------------

std::string NotesSlidePart::resolve_target(std::string_view target) const {
    if (!target.empty() && target.front() == '/') {
        target.remove_prefix(1);
        return std::string(target);
    }

    std::string base_dir;
    auto slash_pos = part_name_.rfind('/');
    if (slash_pos != std::string::npos) {
        base_dir = part_name_.substr(0, slash_pos);
    }

    std::string combined = base_dir.empty()
        ? std::string(target)
        : base_dir + "/" + std::string(target);

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
// Static: compute_relative_target
// ---------------------------------------------------------------------------

std::string NotesSlidePart::compute_relative_target(
    std::string_view from_part, std::string_view to_part) {

    auto split_dir_file = [](std::string_view path)
        -> std::pair<std::string_view, std::string_view> {
        auto pos = path.rfind('/');
        if (pos == std::string_view::npos) return {{}, path};
        return {path.substr(0, pos), path.substr(pos + 1)};
    };

    auto [from_dir, _] = split_dir_file(from_part);
    auto [to_dir, to_file] = split_dir_file(to_part);

    if (from_dir == to_dir) {
        return std::string(to_file);
    }

    // Split directories into segments
    auto split_segments = [](std::string_view dir) -> std::vector<std::string_view> {
        std::vector<std::string_view> parts;
        if (dir.empty()) return parts;
        while (!dir.empty()) {
            auto sep = dir.find('/');
            parts.push_back(dir.substr(0, sep));
            dir = (sep == std::string_view::npos) ? std::string_view{} : dir.substr(sep + 1);
        }
        return parts;
    };

    auto from_parts = split_segments(from_dir);
    auto to_parts = split_segments(to_dir);

    // Find common prefix length
    size_t common_len = 0;
    for (size_t i = 0; i < std::min(from_parts.size(), to_parts.size()); ++i) {
        if (from_parts[i] == to_parts[i]) {
            common_len = i + 1;
        } else {
            break;
        }
    }

    size_t up_count = from_parts.size() - common_len;

    std::string result;
    for (size_t i = 0; i < up_count; ++i) {
        result += "../";
    }

    // Append remaining to_parts after common prefix
    for (size_t i = common_len; i < to_parts.size(); ++i) {
        result += to_parts[i];
        result += '/';
    }

    result += to_file;
    return result;
}

// ---------------------------------------------------------------------------
// Static: find_notes_master
// ---------------------------------------------------------------------------

std::optional<std::string> NotesSlidePart::find_notes_master(
    opc::OpcPackage& package) {

    // OpcPackage doesn't have get_part_names on abstract interface,
    // but we can check the well-known path pattern
    // Try notesSlide masters typically at ppt/notesMasters/notesMaster1.xml
    for (int i = 1; i <= 10; ++i) {
        auto candidate = "ppt/notesMasters/notesMaster" + std::to_string(i) + ".xml";
        if (package.has_part(candidate)) {
            return candidate;
        }
    }
    return std::nullopt;
}

// ---------------------------------------------------------------------------
// Static: build_notes_xml
// ---------------------------------------------------------------------------

std::vector<uint8_t> NotesSlidePart::build_notes_xml() {
    pugi::xml_document doc;

    auto decl = doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto notes = doc.append_child("p:notes");
    notes.append_attribute("xmlns:a") =
        "http://schemas.openxmlformats.org/drawingml/2006/main";
    notes.append_attribute("xmlns:r") =
        "http://schemas.openxmlformats.org/officeDocument/2006/relationships";
    notes.append_attribute("xmlns:p") =
        "http://schemas.openxmlformats.org/presentationml/2006/main";

    // <p:cSld>
    auto c_sld = notes.append_child("p:cSld");
    auto sp_tree = c_sld.append_child("p:spTree");

    // Group shape header (required)
    auto nv_grp_sp_pr = sp_tree.append_child("p:nvGrpSpPr");
    auto c_nv_pr_grp = nv_grp_sp_pr.append_child("p:cNvPr");
    c_nv_pr_grp.append_attribute("id") = 1;
    c_nv_pr_grp.append_attribute("name") = "";
    nv_grp_sp_pr.append_child("p:cNvGrpSpPr");
    nv_grp_sp_pr.append_child("p:nvPr");

    auto grp_sp_pr = sp_tree.append_child("p:grpSpPr");
    auto xfrm = grp_sp_pr.append_child("a:xfrm");
    auto off = xfrm.append_child("a:off");
    off.append_attribute("x") = "0";
    off.append_attribute("y") = "0";
    auto ext = xfrm.append_child("a:ext");
    ext.append_attribute("cx") = "0";
    ext.append_attribute("cy") = "0";
    auto ch_off = xfrm.append_child("a:chOff");
    ch_off.append_attribute("x") = "0";
    ch_off.append_attribute("y") = "0";
    auto ch_ext = xfrm.append_child("a:chExt");
    ch_ext.append_attribute("cx") = "0";
    ch_ext.append_attribute("cy") = "0";

    // Slide image placeholder (type="sldImg")
    auto sp1 = sp_tree.append_child("p:sp");
    auto nv_sp_pr1 = sp1.append_child("p:nvSpPr");
    auto c_nv_pr1 = nv_sp_pr1.append_child("p:cNvPr");
    c_nv_pr1.append_attribute("id") = 2;
    c_nv_pr1.append_attribute("name") = "Slide Image Placeholder 1";
    auto c_nv_sp_pr1 = nv_sp_pr1.append_child("p:cNvSpPr");
    auto sp_locks1 = c_nv_sp_pr1.append_child("a:spLocks");
    sp_locks1.append_attribute("noGrp") = "1";
    auto nv_pr1 = nv_sp_pr1.append_child("p:nvPr");
    auto ph1 = nv_pr1.append_child("p:ph");
    ph1.append_attribute("type") = "sldImg";
    sp1.append_child("p:spPr");

    // Notes body placeholder (type="body", idx="1")
    auto sp2 = sp_tree.append_child("p:sp");
    auto nv_sp_pr2 = sp2.append_child("p:nvSpPr");
    auto c_nv_pr2 = nv_sp_pr2.append_child("p:cNvPr");
    c_nv_pr2.append_attribute("id") = 3;
    c_nv_pr2.append_attribute("name") = "Notes Placeholder 2";
    auto c_nv_sp_pr2 = nv_sp_pr2.append_child("p:cNvSpPr");
    auto sp_locks2 = c_nv_sp_pr2.append_child("a:spLocks");
    sp_locks2.append_attribute("noGrp") = "1";
    auto nv_pr2 = nv_sp_pr2.append_child("p:nvPr");
    auto ph2 = nv_pr2.append_child("p:ph");
    ph2.append_attribute("type") = "body";
    ph2.append_attribute("idx") = "1";
    sp2.append_child("p:spPr");
    auto tx_body = sp2.append_child("p:txBody");
    tx_body.append_child("a:bodyPr");
    tx_body.append_child("a:lstStyle");
    auto a_p = tx_body.append_child("a:p");
    a_p.append_child("a:endParaRPr");

    // Color map override
    auto clr_map_ovr = notes.append_child("p:clrMapOvr");
    clr_map_ovr.append_child("a:masterClrMapping");

    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;

    doc.save(writer, "  ");
    return std::move(writer.result);
}

// ---------------------------------------------------------------------------
// Static: create_empty
// ---------------------------------------------------------------------------

NotesSlidePart NotesSlidePart::create_empty(opc::OpcPackage& package,
                                            std::string_view slide_part_name) {
    // Find the next available notes slide number
    int next_num = 1;
    std::string part_name;
    while (true) {
        auto candidate = "ppt/notesSlides/notesSlide" + std::to_string(next_num) + ".xml";
        if (!package.has_part(candidate)) {
            part_name = std::move(candidate);
            break;
        }
        ++next_num;
    }

    // Build and store the notes slide XML
    auto notes_xml = build_notes_xml();
    package.set_part(part_name, std::move(notes_xml));

    // Create the notes slide's own relationships
    opc::RelationshipsManager rels_manager(package, part_name);

    // Relationship: notes slide -> parent slide
    auto slide_relative = compute_relative_target(part_name, slide_part_name);
    rels_manager.add_relationship(opc::rel_types::kSlide, slide_relative);

    // Relationship: notes slide -> notes master (if present)
    auto notes_master = find_notes_master(package);
    if (notes_master) {
        auto master_relative = compute_relative_target(part_name, *notes_master);
        rels_manager.add_relationship(opc::rel_types::kNotesMaster, master_relative);
    }

    rels_manager.save();

    // Register content type
    opc::ContentTypesManager ct_manager(package);
    ct_manager.add_override(part_name, opc::content_types::kNotesSlide);
    ct_manager.save();

    return NotesSlidePart(package, part_name);
}

// ---------------------------------------------------------------------------
// Static: delete
// ---------------------------------------------------------------------------

void NotesSlidePart::remove(opc::OpcPackage& package,
                            std::string_view part_name) {
    package.delete_part(part_name);

    auto rels_part_name = opc::RelationshipsManager::get_rels_part_name(part_name);
    package.delete_part(rels_part_name);

    opc::ContentTypesManager ct_manager(package);
    ct_manager.remove_override(part_name);
    ct_manager.save();
}

} // namespace Aspose::Slides::Foss::Internal::pptx
