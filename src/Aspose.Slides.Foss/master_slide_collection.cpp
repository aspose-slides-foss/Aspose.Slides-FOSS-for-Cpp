// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/master_slide_collection.h>

#include <cstdlib>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/_internal/opc/content_types.h>
#include <Aspose/Slides/Foss/_internal/opc/content_types_manager.h>
#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/opc/part_utils.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships.h>
#include <Aspose/Slides/Foss/_internal/opc/relationships_manager.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/global_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/presentation.h>

namespace Aspose::Slides::Foss {

namespace opc = Internal::opc;
namespace pptx = Internal::pptx;

// ---------------------------------------------------------------------------
// Construction / move
// ---------------------------------------------------------------------------

MasterSlideCollection::MasterSlideCollection(Presentation* presentation)
    : presentation_(presentation) {
    // A new presentation starts with one default master slide.
    masters_.push_back(std::make_unique<MasterSlide>());
}

MasterSlideCollection::~MasterSlideCollection() = default;
MasterSlideCollection::MasterSlideCollection(MasterSlideCollection&&) noexcept = default;
MasterSlideCollection& MasterSlideCollection::operator=(MasterSlideCollection&&) noexcept = default;

// ---------------------------------------------------------------------------
// IMasterSlideCollection
// ---------------------------------------------------------------------------

IMasterSlideCollection& MasterSlideCollection::as_i_collection() { return *this; }
IMasterSlideCollection& MasterSlideCollection::as_i_enumerable() { return *this; }

std::size_t MasterSlideCollection::size() const noexcept { return masters_.size(); }

MasterSlide& MasterSlideCollection::operator[](std::size_t index) {
    return *masters_.at(index);
}

const MasterSlide& MasterSlideCollection::operator[](std::size_t index) const {
    return *masters_.at(index);
}

MasterSlide& MasterSlideCollection::add_clone(const IMasterSlide& source_master) {
    auto new_master = std::make_unique<MasterSlide>();

    // Clone shapes from the source master slide.
    const auto& src_shapes = source_master.shapes();
    for (std::size_t i = 0; i < src_shapes.size(); ++i) {
        const auto& s = src_shapes[i];
        new_master->shapes().add_auto_shape(
            s.shape_type(), s.x(), s.y(), s.width(), s.height());
        auto& added = new_master->shapes()[new_master->shapes().size() - 1];
        added.set_rotation(s.rotation());
        added.set_name(std::string(s.name()));
    }

    // Clone layout slides from the source master.
    const auto& src_layouts = source_master.layout_slides();
    for (std::size_t i = 0; i < src_layouts.size(); ++i) {
        const auto& src_layout = src_layouts[i];
        auto cloned_layout = std::make_unique<LayoutSlide>();
        cloned_layout->set_layout_type(src_layout.layout_type());
        cloned_layout->set_master_slide(new_master.get());

        // Clone shapes from the source layout.
        const auto& layout_shapes = src_layout.shapes();
        for (std::size_t j = 0; j < layout_shapes.size(); ++j) {
            const auto& ls = layout_shapes[j];
            cloned_layout->shapes().add_auto_shape(
                ls.shape_type(), ls.x(), ls.y(), ls.width(), ls.height());
            auto& la = cloned_layout->shapes()[cloned_layout->shapes().size() - 1];
            la.set_rotation(ls.rotation());
            la.set_name(std::string(ls.name()));
        }

        // Transfer ownership to the global collection if available,
        // otherwise the layout is owned locally via the master's collection pointer.
        if (presentation_) {
            auto& layout_ref = presentation_->layout_slides().add(std::move(cloned_layout));
            new_master->layout_slides().add(&layout_ref);
        } else {
            new_master->layout_slides().add(cloned_layout.release());
        }
    }

    auto& ref = *new_master;
    masters_.push_back(std::move(new_master));
    return ref;
}

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void MasterSlideCollection::init_internal(
    Presentation* presentation,
    opc::OpcPackage* package,
    std::string_view presentation_part_name,
    std::vector<MasterReference> master_references,
    std::vector<std::unique_ptr<MasterSlide>> master_slides) {

    presentation_ = presentation;
    package_ = package;
    presentation_part_name_ = std::string(presentation_part_name);
    master_references_ = std::move(master_references);
    masters_ = std::move(master_slides);
}

// ---------------------------------------------------------------------------
// get_next_master_file_number / get_next_layout_file_number
// ---------------------------------------------------------------------------

int MasterSlideCollection::get_next_master_file_number() const {
    if (!package_) return 1;

    static const std::regex pattern(R"(ppt/slideMasters/slideMaster(\d+)\.xml$)");
    std::set<int> existing_nums;

    auto* mem_pkg = dynamic_cast<opc::InMemoryOpcPackage*>(package_);
    if (!mem_pkg) return 1;

    for (const auto& part_name : mem_pkg->get_part_names()) {
        std::smatch match;
        if (std::regex_match(part_name, match, pattern)) {
            existing_nums.insert(std::stoi(match[1].str()));
        }
    }

    int num = 1;
    while (existing_nums.contains(num)) {
        ++num;
    }
    return num;
}

int MasterSlideCollection::get_next_layout_file_number() const {
    if (!package_) return 1;

    static const std::regex pattern(R"(ppt/slideLayouts/slideLayout(\d+)\.xml$)");
    std::set<int> existing_nums;

    auto* mem_pkg = dynamic_cast<opc::InMemoryOpcPackage*>(package_);
    if (!mem_pkg) return 1;

    for (const auto& part_name : mem_pkg->get_part_names()) {
        std::smatch match;
        if (std::regex_match(part_name, match, pattern)) {
            existing_nums.insert(std::stoi(match[1].str()));
        }
    }

    int num = 1;
    while (existing_nums.contains(num)) {
        ++num;
    }
    return num;
}

// ---------------------------------------------------------------------------
// clone_master_part
// ---------------------------------------------------------------------------

std::unordered_map<std::string, std::string> MasterSlideCollection::clone_master_part(
    opc::OpcPackage& source_package,
    std::string_view source_part_name,
    opc::OpcPackage& dest_package,
    std::string_view dest_part_name) {

    // Copy master XML
    auto source_content = source_package.get_part(source_part_name);
    if (!source_content) {
        throw std::runtime_error(
            "Master slide not found: " + std::string(source_part_name));
    }

    pugi::xml_document dest_doc;
    dest_doc.load_buffer(source_content->data(), source_content->size());

    // Copy relationships (theme, images, etc.) — skip layouts (handled separately)
    opc::RelationshipsManager source_rels(source_package, source_part_name);
    opc::RelationshipsManager dest_rels(dest_package, dest_part_name);
    std::unordered_map<std::string, std::string> rid_mapping;

    for (const auto& rel : source_rels.get_all_relationships()) {
        if (rel.type == opc::rel_types::kSlideLayout) {
            continue; // layouts handled separately
        }

        std::string new_rid;
        if (rel.target_mode && *rel.target_mode == "External") {
            new_rid = dest_rels.add_relationship(
                rel.type, rel.target, "", rel.target_mode);
        } else {
            // Clone related parts (theme, images, etc.)
            auto source_target = opc::resolve_target(source_part_name, rel.target);
            auto dest_target = opc::clone_related_part(
                source_package, source_target,
                dest_package, dest_part_name, rel.type);
            auto relative_target = opc::compute_relative_target(dest_part_name, dest_target);
            new_rid = dest_rels.add_relationship(rel.type, relative_target);
        }
        rid_mapping[rel.id] = new_rid;
    }

    // Update r:id references in master XML (only for non-layout refs)
    opc::update_rid_references(dest_doc.first_child(), rid_mapping);

    // Save master XML (will be updated again later with layout refs)
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    dest_doc.save(writer, "  ");
    dest_package.set_part(dest_part_name, std::move(writer.result));
    dest_rels.save();

    // Add content type
    opc::ContentTypesManager ct_manager(dest_package);
    ct_manager.add_override(dest_part_name, opc::content_types::kSlideMaster);
    ct_manager.save();

    return rid_mapping;
}

// ---------------------------------------------------------------------------
// clone_layout_part
// ---------------------------------------------------------------------------

void MasterSlideCollection::clone_layout_part(
    opc::OpcPackage& source_package,
    std::string_view source_part_name,
    opc::OpcPackage& dest_package,
    std::string_view dest_part_name,
    std::string_view dest_master_part_name) {

    // Copy layout XML
    auto source_content = source_package.get_part(source_part_name);
    if (!source_content) {
        throw std::runtime_error(
            "Layout slide not found: " + std::string(source_part_name));
    }

    pugi::xml_document dest_doc;
    dest_doc.load_buffer(source_content->data(), source_content->size());

    // Copy relationships
    opc::RelationshipsManager source_rels(source_package, source_part_name);
    opc::RelationshipsManager dest_rels(dest_package, dest_part_name);
    std::unordered_map<std::string, std::string> rid_mapping;

    for (const auto& rel : source_rels.get_all_relationships()) {
        std::string new_rid;

        if (rel.type == opc::rel_types::kSlideMaster) {
            // Point to the cloned master
            auto relative_target = opc::compute_relative_target(
                dest_part_name, dest_master_part_name);
            new_rid = dest_rels.add_relationship(rel.type, relative_target);
        } else if (rel.target_mode && *rel.target_mode == "External") {
            new_rid = dest_rels.add_relationship(
                rel.type, rel.target, "", rel.target_mode);
        } else {
            auto source_target = opc::resolve_target(source_part_name, rel.target);
            auto dest_target = opc::clone_related_part(
                source_package, source_target,
                dest_package, dest_part_name, rel.type);
            auto relative_target = opc::compute_relative_target(dest_part_name, dest_target);
            new_rid = dest_rels.add_relationship(rel.type, relative_target);
        }
        rid_mapping[rel.id] = new_rid;
    }

    // Update r:id references
    opc::update_rid_references(dest_doc.first_child(), rid_mapping);

    // Save layout XML
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    dest_doc.save(writer, "  ");
    dest_package.set_part(dest_part_name, std::move(writer.result));
    dest_rels.save();

    // Add content type
    opc::ContentTypesManager ct_manager(dest_package);
    ct_manager.add_override(dest_part_name, opc::content_types::kSlideLayout);
    ct_manager.save();
}

// ---------------------------------------------------------------------------
// get_max_master_layout_id_in_presentation
// ---------------------------------------------------------------------------

int64_t MasterSlideCollection::get_max_master_layout_id_in_presentation() const {
    // PPTX convention start value
    int64_t max_id = 2147483647;

    // Check master IDs from stored references
    for (const auto& ref : master_references_) {
        if (ref.master_id > max_id) {
            max_id = ref.master_id;
        }
    }

    // Check layout IDs from all master slide XML files in the package
    if (!package_) return max_id;

    auto* mem_pkg = dynamic_cast<opc::InMemoryOpcPackage*>(package_);
    if (!mem_pkg) return max_id;

    // Clark-notation tag for p:sldLayoutId
    const std::string sld_layout_id_tag =
        std::string("{") + std::string(pptx::ns_uri::kP) + "}sldLayoutId";

    for (const auto& part_name : mem_pkg->get_part_names()) {
        if (part_name.starts_with("ppt/slideMasters/") &&
            part_name.ends_with(".xml")) {

            auto content = package_->get_part(part_name);
            if (!content) continue;

            pugi::xml_document doc;
            doc.load_buffer(content->data(), content->size());

            // Walk all descendant sldLayoutId elements
            // pugixml with default (non-namespace-aware) parsing uses the raw tag name
            // Try both prefixed and Clark-notation forms
            struct IdWalker : pugi::xml_tree_walker {
                int64_t& max_val;
                const std::string& clark_tag;
                explicit IdWalker(int64_t& m, const std::string& ct)
                    : max_val(m), clark_tag(ct) {}

                bool for_each(pugi::xml_node& node) override {
                    std::string name = node.name();
                    if (name == "p:sldLayoutId" || name == clark_tag) {
                        auto id_attr = node.attribute("id");
                        if (id_attr) {
                            int64_t layout_id = std::strtoll(id_attr.as_string(), nullptr, 10);
                            if (layout_id > max_val) {
                                max_val = layout_id;
                            }
                        }
                    }
                    return true;
                }
            };

            IdWalker walker(max_id, sld_layout_id_tag);
            doc.traverse(walker);
        }
    }

    return max_id;
}

// ---------------------------------------------------------------------------
// update_master_layout_relationships
// ---------------------------------------------------------------------------

void MasterSlideCollection::update_master_layout_relationships(
    [[maybe_unused]] opc::OpcPackage& source_package,
    [[maybe_unused]] std::string_view source_master_part_name,
    std::string_view dest_master_part_name,
    const std::unordered_map<std::string, std::string>& layout_mapping,
    const std::unordered_map<std::string, std::string>& source_layout_rids) {

    if (!package_) return;

    opc::RelationshipsManager master_rels(*package_, dest_master_part_name);

    // Track source r:id -> new r:id mapping for layout relationships
    std::unordered_map<std::string, std::string> layout_rid_mapping;

    for (const auto& [old_layout_path, new_layout_path] : layout_mapping) {
        auto relative_target = opc::compute_relative_target(
            dest_master_part_name, new_layout_path);
        auto new_rid = master_rels.add_relationship(
            opc::rel_types::kSlideLayout, relative_target);

        // Map old rid to new rid
        auto it = source_layout_rids.find(old_layout_path);
        if (it != source_layout_rids.end()) {
            layout_rid_mapping[it->second] = new_rid;
        }
    }

    master_rels.save();

    // Update the master XML's sldLayoutIdLst references
    auto master_content = package_->get_part(dest_master_part_name);
    if (!master_content) return;

    pugi::xml_document master_doc;
    master_doc.load_buffer(master_content->data(), master_content->size());
    auto master_root = master_doc.first_child();

    // Update r:id references in sldLayoutIdLst
    opc::update_rid_references(master_root, layout_rid_mapping);

    // Renumber layout IDs to avoid conflicts with existing masters
    const std::string sld_layout_id_tag =
        std::string("{") + std::string(pptx::ns_uri::kP) + "}sldLayoutId";

    int64_t next_layout_id = get_max_master_layout_id_in_presentation() + 1;

    struct IdRenumber : pugi::xml_tree_walker {
        int64_t& next_id;
        const std::string& clark_tag;
        IdRenumber(int64_t& nid, const std::string& ct)
            : next_id(nid), clark_tag(ct) {}

        bool for_each(pugi::xml_node& node) override {
            std::string name = node.name();
            if (name == "p:sldLayoutId" || name == clark_tag) {
                node.attribute("id").set_value(std::to_string(next_id).c_str());
                ++next_id;
            }
            return true;
        }
    };

    IdRenumber renumber(next_layout_id, sld_layout_id_tag);
    master_doc.traverse(renumber);

    // Save updated master XML
    struct XmlWriter : pugi::xml_writer {
        std::vector<uint8_t> result;
        void write(const void* data, size_t size) override {
            auto p = static_cast<const uint8_t*>(data);
            result.insert(result.end(), p, p + size);
        }
    } writer;
    master_doc.save(writer, "  ");
    package_->set_part(dest_master_part_name, std::move(writer.result));
}

} // namespace Aspose::Slides::Foss
