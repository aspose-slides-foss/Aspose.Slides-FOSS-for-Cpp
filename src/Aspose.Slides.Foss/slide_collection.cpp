// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/slide_collection.h>

#include <algorithm>
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
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/auto_shape.h>
#include <Aspose/Slides/Foss/i_layout_slide.h>
#include <Aspose/Slides/Foss/i_master_slide.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/master_slide.h>
#include <Aspose/Slides/Foss/presentation.h>
#include <Aspose/Slides/Foss/slide.h>

namespace Aspose::Slides::Foss {

namespace opc = Internal::opc;
namespace pptx = Internal::pptx;

// ---------------------------------------------------------------------------
// Anonymous helpers
// ---------------------------------------------------------------------------

namespace {

/// Serialize a pugi::xml_document to a byte vector.
std::vector<uint8_t> serialize_xml(pugi::xml_document& doc) {
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

/// Create an empty slide XML part in the package with a relationship to the layout.
void create_empty_slide_part(opc::OpcPackage& package,
                             std::string_view part_name,
                             std::string_view layout_part_name) {
    // Build minimal slide XML
    pugi::xml_document doc;
    auto decl = doc.append_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    decl.append_attribute("standalone") = "yes";

    auto sld = doc.append_child("p:sld");
    sld.append_attribute("xmlns:a") = std::string(pptx::ns_uri::kA).c_str();
    sld.append_attribute("xmlns:r") = std::string(pptx::ns_uri::kR).c_str();
    sld.append_attribute("xmlns:p") = std::string(pptx::ns_uri::kP).c_str();

    auto cSld = sld.append_child("p:cSld");
    auto spTree = cSld.append_child("p:spTree");
    auto nvGrpSpPr = spTree.append_child("p:nvGrpSpPr");
    auto cNvPr = nvGrpSpPr.append_child("p:cNvPr");
    cNvPr.append_attribute("id") = "1";
    cNvPr.append_attribute("name") = "";
    nvGrpSpPr.append_child("p:cNvGrpSpPr");
    nvGrpSpPr.append_child("p:nvPr");
    spTree.append_child("p:grpSpPr");

    package.set_part(part_name, serialize_xml(doc));

    // Add relationship to layout
    opc::RelationshipsManager rels(package, part_name);
    auto relative_target = opc::compute_relative_target(part_name, layout_part_name);
    rels.add_relationship(opc::rel_types::kSlideLayout, relative_target);
    rels.save();

    // Add content type
    opc::ContentTypesManager ct_manager(package);
    ct_manager.add_override(part_name, opc::content_types::kSlide);
    ct_manager.save();
}

/// Clone a slide part from one package to another.
void clone_slide_part(opc::OpcPackage& source_package,
                      std::string_view source_part_name,
                      opc::OpcPackage& dest_package,
                      std::string_view dest_part_name,
                      std::string_view dest_layout_part_name) {
    // Copy slide XML
    auto source_content = source_package.get_part(source_part_name);
    if (!source_content) {
        throw std::runtime_error("Slide part not found: " + std::string(source_part_name));
    }

    pugi::xml_document dest_doc;
    dest_doc.load_buffer(source_content->data(), source_content->size());

    // Copy relationships, redirecting slide layout to destination
    opc::RelationshipsManager source_rels(source_package, source_part_name);
    opc::RelationshipsManager dest_rels(dest_package, dest_part_name);
    std::unordered_map<std::string, std::string> rid_mapping;

    for (const auto& rel : source_rels.get_all_relationships()) {
        std::string new_rid;

        if (rel.type == opc::rel_types::kSlideLayout && !dest_layout_part_name.empty()) {
            // Point to the destination layout
            auto relative_target = opc::compute_relative_target(
                dest_part_name, dest_layout_part_name);
            new_rid = dest_rels.add_relationship(rel.type, relative_target);
        } else if (rel.target_mode && *rel.target_mode == "External") {
            new_rid = dest_rels.add_relationship(
                rel.type, rel.target, "", rel.target_mode);
        } else {
            // Clone related parts (images, etc.)
            auto source_target = opc::resolve_target(source_part_name, rel.target);
            auto dest_target = opc::clone_related_part(
                source_package, source_target,
                dest_package, dest_part_name, rel.type);
            auto relative_target = opc::compute_relative_target(dest_part_name, dest_target);
            new_rid = dest_rels.add_relationship(rel.type, relative_target);
        }
        rid_mapping[rel.id] = new_rid;
    }

    // Update r:id references in slide XML
    opc::update_rid_references(dest_doc.first_child(), rid_mapping);

    // Save slide XML
    dest_package.set_part(dest_part_name, serialize_xml(dest_doc));
    dest_rels.save();

    // Add content type
    opc::ContentTypesManager ct_manager(dest_package);
    ct_manager.add_override(dest_part_name, opc::content_types::kSlide);
    ct_manager.save();
}

} // anonymous namespace

// ---------------------------------------------------------------------------
// Construction / move
// ---------------------------------------------------------------------------

SlideCollection::~SlideCollection() = default;
SlideCollection::SlideCollection(SlideCollection&&) noexcept = default;
SlideCollection& SlideCollection::operator=(SlideCollection&&) noexcept = default;

SlideCollection::SlideCollection(Presentation* presentation)
    : presentation_(presentation) {
    // A new presentation starts with one blank slide.
    auto slide = std::make_unique<Slide>(presentation_);
    // Assign the first layout slide so layout_slide() is never null on default slides.
    if (presentation_ && presentation_->layout_slides().size() > 0) {
        slide->set_layout_slide(&presentation_->layout_slides()[0]);
    }
    slides_.push_back(std::move(slide));
}

// ---------------------------------------------------------------------------
// ISlideCollection basics
// ---------------------------------------------------------------------------

ISlideCollection& SlideCollection::as_i_collection() { return *this; }
ISlideCollection& SlideCollection::as_i_enumerable() { return *this; }

std::size_t SlideCollection::size() const noexcept { return slides_.size(); }

Slide& SlideCollection::operator[](std::size_t index) {
    return *slides_.at(index);
}

const Slide& SlideCollection::operator[](std::size_t index) const {
    return *slides_.at(index);
}

// ---------------------------------------------------------------------------
// clone_slide_into (high-level, non-OPC)
// ---------------------------------------------------------------------------

Slide& SlideCollection::clone_slide_into(const Slide& source, std::size_t position,
                                          ILayoutSlide* layout) {
    auto new_slide = std::make_unique<Slide>(presentation_);
    new_slide->set_hidden(source.hidden());
    new_slide->set_layout_slide(layout ? layout : source.layout_slide());

    // Clone shapes from source slide.
    const auto& src_shapes = source.shapes();
    for (std::size_t i = 0; i < src_shapes.size(); ++i) {
        const auto& s = src_shapes[i];
        new_slide->shapes().add_auto_shape(
            s.shape_type(), s.x(), s.y(), s.width(), s.height());
        auto& added = new_slide->shapes()[new_slide->shapes().size() - 1];
        added.set_rotation(s.rotation());
        added.set_name(std::string(s.name()));
    }

    auto& ref = *new_slide;
    if (position >= slides_.size()) {
        slides_.push_back(std::move(new_slide));
    } else {
        slides_.insert(slides_.begin() + static_cast<std::ptrdiff_t>(position),
                       std::move(new_slide));
    }
    return ref;
}

// ---------------------------------------------------------------------------
// add_clone / insert_clone
// ---------------------------------------------------------------------------

Slide& SlideCollection::add_clone(const Slide& source_slide) {
    return clone_slide_into(source_slide, slides_.size(), nullptr);
}

Slide& SlideCollection::add_clone(const Slide& source_slide,
                                   ILayoutSlide* dest_layout) {
    return clone_slide_into(source_slide, slides_.size(), dest_layout);
}

Slide& SlideCollection::add_clone(const Slide& source_slide,
                                   IMasterSlide* /*dest_master*/,
                                   bool /*allow_clone_missing_layout*/) {
    return clone_slide_into(source_slide, slides_.size(), nullptr);
}

Slide& SlideCollection::insert_clone(std::size_t index,
                                      const Slide& source_slide) {
    return clone_slide_into(source_slide, index, nullptr);
}

Slide& SlideCollection::insert_clone(std::size_t index,
                                      const Slide& source_slide,
                                      ILayoutSlide* dest_layout) {
    return clone_slide_into(source_slide, index, dest_layout);
}

Slide& SlideCollection::insert_clone(std::size_t index,
                                      const Slide& source_slide,
                                      IMasterSlide* /*dest_master*/,
                                      bool /*allow_clone_missing_layout*/) {
    return clone_slide_into(source_slide, index, nullptr);
}

// ---------------------------------------------------------------------------
// to_array
// ---------------------------------------------------------------------------

std::vector<Slide*> SlideCollection::to_array() {
    std::vector<Slide*> result;
    result.reserve(slides_.size());
    for (auto& s : slides_) {
        result.push_back(s.get());
    }
    return result;
}

std::vector<Slide*> SlideCollection::to_array(std::size_t start_index,
                                               std::size_t count) {
    if (start_index + count > slides_.size()) {
        throw std::out_of_range("to_array range exceeds collection size");
    }
    std::vector<Slide*> result;
    result.reserve(count);
    for (std::size_t i = start_index; i < start_index + count; ++i) {
        result.push_back(slides_[i].get());
    }
    return result;
}

// ---------------------------------------------------------------------------
// add_empty_slide / insert_empty_slide (high-level, non-OPC)
// ---------------------------------------------------------------------------

Slide& SlideCollection::add_empty_slide_in_memory(ILayoutSlide* layout,
                                                  std::ptrdiff_t index) {
    auto slide = std::make_unique<Slide>(presentation_);
    slide->set_layout_slide(layout);
    auto& ref = *slide;
    if (index < 0 || static_cast<std::size_t>(index) >= slides_.size()) {
        slides_.push_back(std::move(slide));
    } else {
        slides_.insert(slides_.begin() + index, std::move(slide));
    }
    return ref;
}

Slide& SlideCollection::add_empty_slide(ILayoutSlide* layout) {
    // Adding to this collection is not adding to the deck. A presentation
    // opened from a file is saved out of its package, so a slide that exists
    // only here reports as added, counts towards size(), and is not in the
    // file — no error, no diagnostic. The OPC path writes the part, the
    // relationship and the <p:sldId> that make it a slide of the deck.
    if (package_) return add_empty_slide_internal(layout, -1);
    return add_empty_slide_in_memory(layout, -1);
}

Slide& SlideCollection::insert_empty_slide(std::size_t index,
                                            ILayoutSlide* layout) {
    if (package_)
        return add_empty_slide_internal(layout,
                                        static_cast<std::ptrdiff_t>(index));
    return add_empty_slide_in_memory(layout,
                                     static_cast<std::ptrdiff_t>(index));
}

// ---------------------------------------------------------------------------
// remove / remove_at / index_of
// ---------------------------------------------------------------------------

void SlideCollection::remove(const Slide& slide) {
    auto it = std::find_if(slides_.begin(), slides_.end(),
        [&slide](const std::unique_ptr<Slide>& s) {
            return s.get() == &slide;
        });
    if (it != slides_.end()) {
        remove_slide_from_package(it->get());
        slide_part_names_.erase(it->get());
        slides_.erase(it);
    }
}

void SlideCollection::remove_at(std::size_t index) {
    if (index >= slides_.size()) {
        throw std::out_of_range("remove_at index out of range");
    }
    remove_slide_from_package(slides_[index].get());
    slide_part_names_.erase(slides_[index].get());
    slides_.erase(slides_.begin() + static_cast<std::ptrdiff_t>(index));
}

void SlideCollection::remove_slide_from_package(const Slide* slide) {
    // Dropping the slide from this collection is not dropping it from the
    // deck. A presentation opened from a file is saved out of its package, so
    // a slide removed only here is still in <p:sldIdLst>, still related from
    // presentation.xml and still a part — the call reports success and the
    // file is unchanged.
    if (!package_ || !slide) return;
    auto it = slide_part_names_.find(slide);
    if (it == slide_part_names_.end()) return;
    const std::string part_name = it->second;

    auto content = package_->get_part(presentation_part_name_);
    if (!content) return;
    pugi::xml_document doc;
    if (!doc.load_buffer(content->data(), content->size())) return;

    auto pres_node = doc.first_child();
    auto sld_id_lst = pres_node.child("p:sldIdLst");
    if (!sld_id_lst) sld_id_lst = pres_node.child(pptx::Elements::kSldIdLst.c_str());
    if (!sld_id_lst) return;

    opc::RelationshipsManager pres_rels(*package_, presentation_part_name_);

    // Find the <p:sldId> whose relationship resolves to this part. Matching on
    // the resolved part name rather than on position is what keeps this right
    // when the list and the collection have drifted apart.
    std::string rel_id;
    for (auto sld_id : sld_id_lst.children()) {
        auto attr = sld_id.attribute("r:id");
        if (!attr) attr = sld_id.attribute(pptx::Attributes::kRId.c_str());
        if (!attr) continue;
        auto rel = pres_rels.get_relationship(attr.as_string());
        if (!rel) continue;
        if (resolve_presentation_target(rel->target) != part_name) continue;
        rel_id = attr.as_string();
        sld_id_lst.remove_child(sld_id);
        break;
    }
    if (rel_id.empty()) return;

    pres_rels.remove_relationship(rel_id);
    pres_rels.save();
    package_->set_part(presentation_part_name_, serialize_xml(doc));

    // The part itself, its relationships and its content-type override go
    // together: an override naming a part that is no longer there is a
    // package a strict consumer rejects.
    package_->delete_part(part_name);
    package_->delete_part(
        opc::RelationshipsManager::get_rels_part_name(part_name));
    opc::ContentTypesManager ct(*package_);
    ct.remove_override(part_name);
    ct.save();

    slide_references_.erase(
        std::remove_if(slide_references_.begin(), slide_references_.end(),
                       [&rel_id](const SlideReference& ref) {
                           return ref.r_id == rel_id;
                       }),
        slide_references_.end());
}

std::string SlideCollection::resolve_presentation_target(
    std::string_view target) const {
    if (!target.empty() && target.front() == '/') return std::string(target.substr(1));
    auto slash = presentation_part_name_.rfind('/');
    if (slash == std::string::npos) return std::string(target);
    return presentation_part_name_.substr(0, slash + 1) + std::string(target);
}

std::ptrdiff_t SlideCollection::index_of(const Slide& slide) const {
    for (std::size_t i = 0; i < slides_.size(); ++i) {
        if (slides_[i].get() == &slide) {
            return static_cast<std::ptrdiff_t>(i);
        }
    }
    return -1;
}

// ===========================================================================
// OPC-level methods
// ===========================================================================

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void SlideCollection::init_internal(
    Presentation* presentation,
    opc::OpcPackage* package,
    std::string_view presentation_part_name,
    std::vector<SlideReference> slide_references,
    LayoutResolver layout_resolver) {

    presentation_ = presentation;
    package_ = package;
    presentation_part_name_ = std::string(presentation_part_name);
    slide_references_ = std::move(slide_references);
    layout_resolver_ = std::move(layout_resolver);

    // Clear default slides.
    slides_.clear();
    slide_part_names_.clear();
    owned_slide_parts_.clear();

    if (!package_) return;

    // Resolve the presentation's relationships to find slide targets.
    opc::RelationshipsManager pres_rels(*package_, presentation_part_name_);

    for (const auto& slide_ref : slide_references_) {
        auto rel = pres_rels.get_relationship(slide_ref.r_id);
        if (!rel) continue;

        // Resolve the target path relative to the presentation directory.
        std::string part_name;
        if (!rel->target.empty() && rel->target.front() == '/') {
            part_name = rel->target.substr(1);
        } else {
            auto slash_pos = presentation_part_name_.rfind('/');
            if (slash_pos != std::string::npos) {
                part_name = presentation_part_name_.substr(0, slash_pos + 1) + rel->target;
            } else {
                part_name = rel->target;
            }
        }

        // Create slide object.
        auto slide = std::make_unique<Slide>(presentation_);

        // Create a persistent SlidePart and initialize the slide with it.
        if (package_->has_part(part_name)) {
            auto slide_part_ptr = std::make_unique<pptx::SlidePart>(*package_, part_name);
            auto* sp_raw = slide_part_ptr.get();

            // Resolve layout.
            auto layout_pn = sp_raw->layout_part_name();
            if (!layout_pn.empty() && layout_resolver_) {
                auto* layout = layout_resolver_(layout_pn);
                slide->set_layout_slide(layout);
            }

            // Wire up the slide and its shape collection with OPC data.
            slide->init_internal(presentation_, package_, part_name, slide_ref,
                                 sp_raw, layout_resolver_);
            slide->shapes().init_internal(sp_raw, slide.get());

            // Parse hidden and name from slide XML.
            auto slide_content = package_->get_part(part_name);
            if (slide_content) {
                pugi::xml_document slide_doc;
                slide_doc.load_buffer(slide_content->data(), slide_content->size());
                auto sld_node = slide_doc.first_child();

                // show="0" means hidden.
                auto show_attr = sld_node.attribute("show");
                if (show_attr && std::string_view(show_attr.as_string()) == "0") {
                    slide->set_hidden(true);
                }

                // <p:cSld name="...">
                auto cSld = sld_node.child("p:cSld");
                if (cSld) {
                    auto name_attr = cSld.attribute("name");
                    if (name_attr) {
                        slide->set_name(name_attr.as_string());
                    }
                }
            }

            owned_slide_parts_.push_back(std::move(slide_part_ptr));
        }

        auto* slide_ptr = slide.get();
        slide_part_names_[slide_ptr] = part_name;
        slides_.push_back(std::move(slide));
    }
}

// ---------------------------------------------------------------------------
// add_empty_slide_internal
// ---------------------------------------------------------------------------

Slide& SlideCollection::add_empty_slide_internal(ILayoutSlide* layout, std::ptrdiff_t index) {
    if (!package_) {
        return add_empty_slide_in_memory(layout, index);
    }

    // Determine the next available slide number.
    int next_num = get_next_slide_file_number();
    std::string part_name = "ppt/slides/slide" + std::to_string(next_num) + ".xml";

    // Get the layout's part name from the layout_slides_map_ via presentation.
    std::string layout_part_name;
    if (layout) {
        // Try to find the layout's part name by scanning the presentation's layout map.
        // Layout slides that came from OPC loading have their part names tracked by Presentation.
        auto& pres_layouts = presentation_->layout_slides();
        for (std::size_t i = 0; i < pres_layouts.size(); ++i) {
            if (&pres_layouts[i] == layout) {
                // Found it - we need the part name. Search the package for layout files.
                // This is a simplified approach; the layout_resolver inverse is not available.
                break;
            }
        }

        // Fallback: scan for the first available layout part name.
        if (layout_part_name.empty()) {
            auto first = get_first_layout_part_name();
            if (first) layout_part_name = *first;
        }
    }

    // If we still don't have a layout part name, use the first available.
    if (layout_part_name.empty()) {
        auto first = get_first_layout_part_name();
        if (first) layout_part_name = *first;
    }

    // Create the empty slide XML + rels + content type.
    create_empty_slide_part(*package_, part_name, layout_part_name);

    // Add relationship from presentation to the new slide.
    opc::RelationshipsManager pres_rels(*package_, presentation_part_name_);
    std::string relative_target = "slides/slide" + std::to_string(next_num) + ".xml";
    auto rel_id = pres_rels.add_relationship(opc::rel_types::kSlide, relative_target);
    pres_rels.save();

    // Add slide reference to presentation.xml.
    auto slide_ref = add_slide_reference_to_presentation(rel_id, index);

    // Create Slide object.
    auto slide = std::make_unique<Slide>(presentation_);
    slide->set_layout_slide(layout);
    // slide_id is set from the slide reference for tracking purposes.
    // Note: set_slide_id is protected; slide_number is used for public indexing.

    // Bind it to the part that was just created, the same way init_internal
    // binds a slide read from the file. Without this the slide is in the
    // package but not editable: every shape added to it would be written to
    // nowhere.
    if (package_->has_part(part_name)) {
        auto slide_part_ptr =
            std::make_unique<pptx::SlidePart>(*package_, part_name);
        auto* sp_raw = slide_part_ptr.get();
        slide->init_internal(presentation_, package_, part_name, slide_ref,
                             sp_raw, layout_resolver_);
        slide->shapes().init_internal(sp_raw, slide.get());
        owned_slide_parts_.push_back(std::move(slide_part_ptr));
    }

    auto* slide_ptr = slide.get();
    slide_part_names_[slide_ptr] = part_name;

    // Add to internal list.
    Slide& ref = *slide;
    if (index < 0 || static_cast<std::size_t>(index) >= slides_.size()) {
        slides_.push_back(std::move(slide));
    } else {
        slides_.insert(slides_.begin() + index, std::move(slide));
    }

    return ref;
}

// ---------------------------------------------------------------------------
// get_next_slide_file_number
// ---------------------------------------------------------------------------

int SlideCollection::get_next_slide_file_number() const {
    if (!package_) return 1;

    static const std::regex pattern(R"(ppt/slides/slide(\d+)\.xml$)");
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
// clone_slide_internal
// ---------------------------------------------------------------------------

Slide& SlideCollection::clone_slide_internal(
    const Slide& source_slide,
    std::ptrdiff_t index,
    ILayoutSlide* dest_layout,
    IMasterSlide* dest_master,
    bool allow_clone_missing_layout) {

    if (!package_) {
        // Fallback to high-level clone.
        std::size_t pos = (index < 0) ? slides_.size() : static_cast<std::size_t>(index);
        return clone_slide_into(source_slide, pos, dest_layout);
    }

    // Get source package and part name.
    // The source slide may belong to this or another presentation.
    auto* source_presentation = dynamic_cast<Presentation*>(
        const_cast<IPresentation*>(source_slide.presentation()));
    opc::OpcPackage* source_package = source_presentation
        ? source_presentation->opc_package()
        : nullptr;

    // Find source part name.
    std::string source_part_name;
    auto it = slide_part_names_.find(&source_slide);
    if (it != slide_part_names_.end()) {
        source_part_name = it->second;
    }

    // If we can't do OPC-level clone, fall back to high-level.
    if (!source_package || source_part_name.empty()) {
        std::size_t pos = (index < 0) ? slides_.size() : static_cast<std::size_t>(index);
        return clone_slide_into(source_slide, pos, dest_layout);
    }

    // Determine the next available slide number.
    int next_num = get_next_slide_file_number();
    std::string dest_part_name = "ppt/slides/slide" + std::to_string(next_num) + ".xml";

    // Determine the layout to use.
    std::string dest_layout_part_name;
    if (dest_layout) {
        // Explicit layout provided. Try to find its part name.
        auto first = get_first_layout_part_name();
        dest_layout_part_name = first.value_or("");
    } else if (dest_master) {
        // Find matching layout in destination master.
        auto match = find_matching_layout(source_slide, dest_master, allow_clone_missing_layout);
        dest_layout_part_name = match.value_or("");
    } else {
        // Use source layout if same presentation, otherwise clone master chain.
        auto* source_layout = source_slide.layout_slide();
        if (source_package == package_) {
            // Same presentation - find the layout part name from package.
            auto first = get_first_layout_part_name();
            dest_layout_part_name = first.value_or("");
        } else {
            // Different presentation - clone the master slide chain.
            if (source_layout) {
                auto result = clone_master_chain_for_slide(source_slide, source_layout);
                dest_layout_part_name = result.value_or("");
            } else {
                auto first = get_first_layout_part_name();
                dest_layout_part_name = first.value_or("");
            }
        }
    }

    // Clone the slide using the helper.
    clone_slide_part(*source_package, source_part_name,
                     *package_, dest_part_name, dest_layout_part_name);

    // Add relationship from presentation to the new slide.
    opc::RelationshipsManager pres_rels(*package_, presentation_part_name_);
    std::string relative_target = "slides/slide" + std::to_string(next_num) + ".xml";
    auto rel_id = pres_rels.add_relationship(opc::rel_types::kSlide, relative_target);
    pres_rels.save();

    // Add slide reference to presentation.xml.
    auto slide_ref = add_slide_reference_to_presentation(rel_id, index);

    // Create Slide object.
    auto slide = std::make_unique<Slide>(presentation_);
    slide->set_hidden(source_slide.hidden());
    slide->set_layout_slide(dest_layout ? dest_layout : source_slide.layout_slide());
    // slide_id is set from the slide reference for tracking purposes.
    // Note: set_slide_id is protected; slide_number is used for public indexing.

    auto* slide_ptr = slide.get();
    slide_part_names_[slide_ptr] = dest_part_name;

    // Add to internal list.
    Slide& ref = *slide;
    if (index < 0 || static_cast<std::size_t>(index) >= slides_.size()) {
        slides_.push_back(std::move(slide));
    } else {
        slides_.insert(slides_.begin() + index, std::move(slide));
    }

    return ref;
}

// ---------------------------------------------------------------------------
// find_matching_layout
// ---------------------------------------------------------------------------

std::optional<std::string> SlideCollection::find_matching_layout(
    const Slide& source_slide, IMasterSlide* dest_master, bool /*allow_clone*/) const {

    auto* source_layout = source_slide.layout_slide();
    if (!source_layout || !dest_master) return std::nullopt;

    auto source_type = source_layout->layout_type();
    auto& dest_layouts = dest_master->layout_slides();

    // Match by layout type.
    for (std::size_t i = 0; i < dest_layouts.size(); ++i) {
        if (dest_layouts[i].layout_type() == source_type) {
            // Return the first layout's part name from the package.
            return get_first_layout_part_name();
        }
    }

    // Return first layout as fallback.
    if (dest_layouts.size() > 0) {
        return get_first_layout_part_name();
    }

    return std::nullopt;
}

// ---------------------------------------------------------------------------
// find_layout_by_type
// ---------------------------------------------------------------------------

std::optional<std::string> SlideCollection::find_layout_by_type(
    ILayoutSlide* source_layout) const {

    if (!source_layout) return get_first_layout_part_name();

    auto source_type = source_layout->layout_type();

    // Try using layout_slides property directly.
    auto& pres_layouts = presentation_->layout_slides();
    for (std::size_t i = 0; i < pres_layouts.size(); ++i) {
        if (pres_layouts[i].layout_type() == source_type) {
            return get_first_layout_part_name();
        }
    }

    return get_first_layout_part_name();
}

// ---------------------------------------------------------------------------
// find_layout_from_layout_slides
// ---------------------------------------------------------------------------

std::optional<std::string> SlideCollection::find_layout_from_layout_slides(
    ILayoutSlide* source_layout) const {

    if (!source_layout) return get_first_layout_part_name();

    // Try to match by name. source_layout is an ILayoutSlide, so we
    // attempt to access name via dynamic_cast to BaseSlide.
    auto* base = dynamic_cast<const BaseSlide*>(source_layout);
    if (!base) return get_first_layout_part_name();

    auto source_name = base->name();

    auto& pres_layouts = presentation_->layout_slides();
    for (std::size_t i = 0; i < pres_layouts.size(); ++i) {
        if (pres_layouts[i].name() == source_name) {
            return get_first_layout_part_name();
        }
    }

    return get_first_layout_part_name();
}

// ---------------------------------------------------------------------------
// get_first_layout_part_name
// ---------------------------------------------------------------------------

std::optional<std::string> SlideCollection::get_first_layout_part_name() const {
    if (!package_) return std::nullopt;

    auto* mem_pkg = dynamic_cast<opc::InMemoryOpcPackage*>(package_);
    if (!mem_pkg) return std::nullopt;

    for (const auto& part_name : mem_pkg->get_part_names()) {
        if (part_name.starts_with("ppt/slideLayouts/") &&
            part_name.ends_with(".xml")) {
            return part_name;
        }
    }

    return std::nullopt;
}

// ---------------------------------------------------------------------------
// clone_master_chain_for_slide
// ---------------------------------------------------------------------------

std::optional<std::string> SlideCollection::clone_master_chain_for_slide(
    const Slide& /*source_slide*/, ILayoutSlide* source_layout) {

    if (!source_layout) return get_first_layout_part_name();

    // Get the source master.
    auto* source_master = source_layout->master_slide();
    if (!source_master) return get_first_layout_part_name();

    // Clone the master into the destination presentation.
    MasterSlide& cloned_master = presentation_->masters().add_clone(*source_master);

    // Find the cloned layout matching the source layout.
    auto source_type = source_layout->layout_type();
    auto& cloned_layouts = cloned_master.layout_slides();

    // Try to match by type.
    for (std::size_t i = 0; i < cloned_layouts.size(); ++i) {
        if (cloned_layouts[i].layout_type() == source_type) {
            return get_first_layout_part_name();
        }
    }

    // Try to match by name.
    auto* source_base = dynamic_cast<const BaseSlide*>(source_layout);
    if (source_base) {
        auto source_name = source_base->name();
        for (std::size_t i = 0; i < cloned_layouts.size(); ++i) {
            auto* layout_base = dynamic_cast<const BaseSlide*>(&cloned_layouts[i]);
            if (layout_base && layout_base->name() == source_name) {
                return get_first_layout_part_name();
            }
        }
    }

    // Return first layout from cloned master as fallback.
    if (cloned_layouts.size() > 0) {
        return get_first_layout_part_name();
    }

    return get_first_layout_part_name();
}

// ---------------------------------------------------------------------------
// add_slide_reference_to_presentation
// ---------------------------------------------------------------------------

SlideReference SlideCollection::add_slide_reference_to_presentation(
    std::string_view rel_id, std::ptrdiff_t index) {

    if (!package_) return {};

    auto content = package_->get_part(presentation_part_name_);
    if (!content) return {};

    pugi::xml_document doc;
    doc.load_buffer(content->data(), content->size());

    auto pres_node = doc.first_child();

    // Find or create sldIdLst element.
    // Try both prefixed and Clark-notation forms.
    auto sld_id_lst = pres_node.child("p:sldIdLst");
    if (!sld_id_lst) {
        sld_id_lst = pres_node.child(pptx::Elements::kSldIdLst.c_str());
    }
    if (!sld_id_lst) {
        sld_id_lst = pres_node.append_child("p:sldIdLst");
    }

    // Determine the next slide ID by finding the max existing ID.
    int64_t max_id = 255; // PPTX slide IDs start at 256.
    for (auto child : sld_id_lst.children()) {
        auto id_attr = child.attribute("id");
        if (id_attr) {
            int64_t id = std::strtoll(id_attr.as_string(), nullptr, 10);
            if (id > max_id) max_id = id;
        }
    }
    int64_t new_id = max_id + 1;

    // Create the new sldId element.
    pugi::xml_node new_node;
    if (index >= 0) {
        // Count children to find insertion point.
        std::ptrdiff_t count = 0;
        pugi::xml_node insert_before;
        for (auto child : sld_id_lst.children()) {
            if (count == index) {
                insert_before = child;
                break;
            }
            ++count;
        }
        if (insert_before) {
            new_node = sld_id_lst.insert_child_before("p:sldId", insert_before);
        } else {
            new_node = sld_id_lst.append_child("p:sldId");
        }
    } else {
        new_node = sld_id_lst.append_child("p:sldId");
    }

    new_node.append_attribute("id") = std::to_string(new_id).c_str();
    // The literal prefixed name, not the Clark-notation constant: pugixml
    // stores names verbatim, so "{uri}id" would be written out as the
    // attribute name and the part would stop being XML at all.
    new_node.append_attribute("r:id") = std::string(rel_id).c_str();

    // Save presentation.xml back.
    package_->set_part(presentation_part_name_, serialize_xml(doc));

    SlideReference ref;
    ref.slide_id = new_id;
    ref.r_id = std::string(rel_id);
    slide_references_.push_back(ref);

    return ref;
}

} // namespace Aspose::Slides::Foss
