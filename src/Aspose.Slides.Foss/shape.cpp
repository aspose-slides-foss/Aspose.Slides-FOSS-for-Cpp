// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/shape.h>

#include <cmath>
#include <stdexcept>
#include <string_view>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>
#include <Aspose/Slides/Foss/_internal/pptx/layout_slide_part.h>
#include <Aspose/Slides/Foss/_internal/pptx/slide_part.h>
#include <Aspose/Slides/Foss/nullable_bool.h>

namespace Aspose::Slides::Foss {

using Internal::pptx::kEmuPerPoint;
using Internal::pptx::kRotationUnit;

// Names of nvXxxPr container elements (prefix-qualified for pugixml).
static constexpr std::string_view kNvNames[] = {
    "p:nvSpPr",
    "p:nvPicPr",
    "p:nvGraphicFramePr",
    "p:nvGrpSpPr",
    "p:nvCxnSpPr",
};

// ---------------------------------------------------------------------------
// init_internal
// ---------------------------------------------------------------------------

void Shape::init_internal(pugi::xml_node xml_element,
                          Internal::pptx::SlidePart* slide_part,
                          IBaseSlide* parent_slide) {
    xml_element_ = xml_element;
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;

    // Populate frame properties (x, y, width, height, rotation) from XML.
    auto frm = build_frame();
    frame_ = frm;
    sync_from_frame();

    // Initialize effect format, fill format, and line format from spPr element.
    auto sp_pr = get_sp_pr();
    if (sp_pr && slide_part_) {
        effect_format_.init_internal(
            sp_pr,
            [this]() { slide_part_->save(); },
            parent_slide_);
        fill_format_.init_internal(
            sp_pr,
            [this]() { slide_part_->save(); });
        line_format_.init_internal(
            sp_pr,
            [this]() { slide_part_->save(); });
        three_d_format_.init_internal(
            sp_pr,
            [this]() { slide_part_->save(); });
    }
}

// ---------------------------------------------------------------------------
// Geometry property setters — update in-memory state and XML.
// ---------------------------------------------------------------------------

void Shape::set_x(double value) {
    x_ = value;
    frame_ = ShapeFrame(x_, y_, width_, height_, frame_.flip_h(), frame_.flip_v(), rotation_);
    if (xml_element_) {
        apply_frame(frame_);
    }
}

void Shape::set_y(double value) {
    y_ = value;
    frame_ = ShapeFrame(x_, y_, width_, height_, frame_.flip_h(), frame_.flip_v(), rotation_);
    if (xml_element_) {
        apply_frame(frame_);
    }
}

void Shape::set_width(double value) {
    width_ = value;
    frame_ = ShapeFrame(x_, y_, width_, height_, frame_.flip_h(), frame_.flip_v(), rotation_);
    if (xml_element_) {
        apply_frame(frame_);
    }
}

void Shape::set_height(double value) {
    height_ = value;
    frame_ = ShapeFrame(x_, y_, width_, height_, frame_.flip_h(), frame_.flip_v(), rotation_);
    if (xml_element_) {
        apply_frame(frame_);
    }
}

void Shape::set_rotation(double value) {
    rotation_ = value;
    frame_ = ShapeFrame(x_, y_, width_, height_, frame_.flip_h(), frame_.flip_v(), rotation_);
    if (xml_element_) {
        apply_frame(frame_);
    }
}

// ---------------------------------------------------------------------------
// build_frame
// ---------------------------------------------------------------------------

ShapeFrame Shape::build_frame() const {
    auto xfrm = get_xfrm();
    if (!xfrm) {
        return ShapeFrame(0, 0, 0, 0, NullableBool::NOT_DEFINED,
                          NullableBool::NOT_DEFINED, 0);
    }

    auto off = xfrm.child("a:off");
    auto ext = xfrm.child("a:ext");

    double x_val = off ? off.attribute("x").as_int(0) / static_cast<double>(kEmuPerPoint) : 0.0;
    double y_val = off ? off.attribute("y").as_int(0) / static_cast<double>(kEmuPerPoint) : 0.0;
    double w_val = ext ? ext.attribute("cx").as_int(0) / static_cast<double>(kEmuPerPoint) : 0.0;
    double h_val = ext ? ext.attribute("cy").as_int(0) / static_cast<double>(kEmuPerPoint) : 0.0;
    double rot = xfrm.attribute("rot").as_int(0) / static_cast<double>(kRotationUnit);

    auto flip_h_val = std::string_view(xfrm.attribute("flipH").as_string("")) == "1"
        ? NullableBool::TRUE : NullableBool::FALSE;
    auto flip_v_val = std::string_view(xfrm.attribute("flipV").as_string("")) == "1"
        ? NullableBool::TRUE : NullableBool::FALSE;

    return ShapeFrame(x_val, y_val, w_val, h_val, flip_h_val, flip_v_val, rot);
}

// ---------------------------------------------------------------------------
// apply_frame
// ---------------------------------------------------------------------------

void Shape::apply_frame(const IShapeFrame& value) {
    auto xfrm = ensure_xfrm();

    auto off = xfrm.child("a:off");
    if (!off) {
        off = xfrm.append_child("a:off");
        off.append_attribute("x") = "0";
        off.append_attribute("y") = "0";
    }

    auto ext = xfrm.child("a:ext");
    if (!ext) {
        ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx") = "0";
        ext.append_attribute("cy") = "0";
    }

    // Set offset
    off.attribute("x").set_value(
        std::to_string(static_cast<int>(std::round(value.x() * kEmuPerPoint))).c_str());
    off.attribute("y").set_value(
        std::to_string(static_cast<int>(std::round(value.y() * kEmuPerPoint))).c_str());

    // Set extent
    ext.attribute("cx").set_value(
        std::to_string(static_cast<int>(std::round(value.width() * kEmuPerPoint))).c_str());
    ext.attribute("cy").set_value(
        std::to_string(static_cast<int>(std::round(value.height() * kEmuPerPoint))).c_str());

    // Set rotation
    auto rot_str = std::to_string(static_cast<int>(std::round(value.rotation() * kRotationUnit)));
    if (xfrm.attribute("rot")) {
        xfrm.attribute("rot").set_value(rot_str.c_str());
    } else {
        xfrm.append_attribute("rot") = rot_str.c_str();
    }

    // Flip horizontal
    if (value.flip_h() == NullableBool::TRUE) {
        if (!xfrm.attribute("flipH")) {
            xfrm.append_attribute("flipH") = "1";
        } else {
            xfrm.attribute("flipH").set_value("1");
        }
    } else {
        xfrm.remove_attribute("flipH");
    }

    // Flip vertical
    if (value.flip_v() == NullableBool::TRUE) {
        if (!xfrm.attribute("flipV")) {
            xfrm.append_attribute("flipV") = "1";
        } else {
            xfrm.attribute("flipV").set_value("1");
        }
    } else {
        xfrm.remove_attribute("flipV");
    }

    if (slide_part_) {
        slide_part_->save();
    }
}

// ---------------------------------------------------------------------------
// get_sp_pr
// ---------------------------------------------------------------------------

pugi::xml_node Shape::get_sp_pr() const {
    if (!xml_element_) {
        return {};
    }
    auto sp_pr = xml_element_.child("p:spPr");
    if (sp_pr) {
        return sp_pr;
    }
    return xml_element_.child("p:grpSpPr");
}

// ---------------------------------------------------------------------------
// ensure_sp_pr
// ---------------------------------------------------------------------------

pugi::xml_node Shape::ensure_sp_pr() {
    auto sp_pr = get_sp_pr();
    if (sp_pr) {
        return sp_pr;
    }
    if (!xml_element_) {
        throw std::runtime_error("Shape has no XML element");
    }
    return xml_element_.append_child("p:spPr");
}

// ---------------------------------------------------------------------------
// get_c_nv_pr
// ---------------------------------------------------------------------------

pugi::xml_node Shape::get_c_nv_pr() const {
    if (!xml_element_) {
        return {};
    }
    for (auto nv_name : kNvNames) {
        auto nv_elem = xml_element_.child(std::string(nv_name).c_str());
        if (nv_elem) {
            return nv_elem.child("p:cNvPr");
        }
    }
    return {};
}

// ---------------------------------------------------------------------------
// find_xfrm_in_element
// ---------------------------------------------------------------------------

pugi::xml_node Shape::find_xfrm_in_element(pugi::xml_node xml_element) {
    // Try spPr (most common: sp, pic, cxnSp)
    auto sp_pr = xml_element.child("p:spPr");
    if (sp_pr) {
        auto xfrm = sp_pr.child("a:xfrm");
        if (xfrm) return xfrm;
    }
    // Try grpSpPr (group shapes)
    auto grp_sp_pr = xml_element.child("p:grpSpPr");
    if (grp_sp_pr) {
        auto xfrm = grp_sp_pr.child("a:xfrm");
        if (xfrm) return xfrm;
    }
    // Try p:xfrm (graphic frames like tables, charts)
    return xml_element.child("p:xfrm");
}

// ---------------------------------------------------------------------------
// get_placeholder_info
// ---------------------------------------------------------------------------

std::optional<std::pair<std::optional<std::string>, std::string>>
Shape::get_placeholder_info() const {
    if (!xml_element_) {
        return std::nullopt;
    }
    for (auto nv_name : kNvNames) {
        auto nv_elem = xml_element_.child(std::string(nv_name).c_str());
        if (nv_elem) {
            auto nv_pr = nv_elem.child("p:nvPr");
            if (nv_pr) {
                auto ph = nv_pr.child("p:ph");
                if (ph) {
                    auto type_attr = ph.attribute("type");
                    std::optional<std::string> ph_type;
                    if (type_attr) {
                        ph_type = type_attr.as_string();
                    }
                    std::string ph_idx = ph.attribute("idx").as_string("0");
                    return std::make_pair(std::move(ph_type), std::move(ph_idx));
                }
            }
        }
    }
    return std::nullopt;
}

// ---------------------------------------------------------------------------
// find_placeholder_xfrm_in_xml
// ---------------------------------------------------------------------------

pugi::xml_node Shape::find_placeholder_xfrm_in_xml(
    pugi::xml_node root,
    const std::optional<std::string>& ph_type,
    std::string_view ph_idx) {

    // Find the spTree: root/p:cSld/p:spTree
    auto csld = root.child("p:cSld");
    if (!csld) return {};
    auto sp_tree = csld.child("p:spTree");
    if (!sp_tree) return {};

    // Search all child shape elements
    for (auto child : sp_tree.children()) {
        // Find the nvPr/ph element
        pugi::xml_node ph;
        for (auto nv_name : kNvNames) {
            auto nv_elem = child.child(std::string(nv_name).c_str());
            if (nv_elem) {
                auto nv_pr = nv_elem.child("p:nvPr");
                if (nv_pr) {
                    ph = nv_pr.child("p:ph");
                    break;
                }
            }
        }
        if (!ph) continue;

        // Match by type and idx
        auto child_type_attr = ph.attribute("type");
        std::optional<std::string> child_type;
        if (child_type_attr) {
            child_type = child_type_attr.as_string();
        }
        std::string child_idx = ph.attribute("idx").as_string("0");

        if (child_type == ph_type && child_idx == std::string(ph_idx)) {
            auto xfrm = find_xfrm_in_element(child);
            if (xfrm) return xfrm;
        }
    }
    return {};
}

// ---------------------------------------------------------------------------
// get_inherited_xfrm
// ---------------------------------------------------------------------------

pugi::xml_node Shape::get_inherited_xfrm() const {
    auto ph_info = get_placeholder_info();
    if (!ph_info || !slide_part_) {
        return {};
    }
    auto& [ph_type, ph_idx] = *ph_info;
    auto& package = slide_part_->package();

    // Try layout slide
    auto layout_part_name = slide_part_->layout_part_name();
    if (!layout_part_name.empty()) {
        auto layout_content = package.get_part(layout_part_name);
        if (layout_content) {
            pugi::xml_document layout_doc;
            layout_doc.load_buffer(layout_content->data(), layout_content->size());
            auto layout_root = layout_doc.first_child();
            auto xfrm = find_placeholder_xfrm_in_xml(layout_root, ph_type, ph_idx);
            if (xfrm) return xfrm;

            // Try master slide (resolve from layout's relationships)
            Internal::pptx::LayoutSlidePart layout_part(package, layout_part_name);
            auto master_part_name = layout_part.master_part_name();
            if (!master_part_name.empty()) {
                auto master_content = package.get_part(master_part_name);
                if (master_content) {
                    pugi::xml_document master_doc;
                    master_doc.load_buffer(master_content->data(), master_content->size());
                    auto master_root = master_doc.first_child();
                    auto master_xfrm = find_placeholder_xfrm_in_xml(
                        master_root, ph_type, ph_idx);
                    if (master_xfrm) return master_xfrm;
                }
            }
        }
    }
    return {};
}

// ---------------------------------------------------------------------------
// get_xfrm
// ---------------------------------------------------------------------------

pugi::xml_node Shape::get_xfrm() const {
    if (!xml_element_) {
        return {};
    }
    auto xfrm = find_xfrm_in_element(xml_element_);
    if (xfrm) {
        return xfrm;
    }
    // Placeholder inheritance: try layout, then master
    return get_inherited_xfrm();
}

// ---------------------------------------------------------------------------
// ensure_xfrm
// ---------------------------------------------------------------------------

pugi::xml_node Shape::ensure_xfrm() {
    auto xfrm = get_xfrm();
    if (xfrm) {
        return xfrm;
    }
    if (!xml_element_) {
        throw std::runtime_error("Shape has no XML element");
    }
    // Create xfrm under the appropriate parent
    auto sp_pr = xml_element_.child("p:spPr");
    if (!sp_pr) {
        auto grp_sp_pr = xml_element_.child("p:grpSpPr");
        if (grp_sp_pr) {
            sp_pr = grp_sp_pr;
        } else {
            sp_pr = xml_element_.append_child("p:spPr");
        }
    }
    xfrm = sp_pr.append_child("a:xfrm");
    auto off = xfrm.append_child("a:off");
    off.append_attribute("x") = "0";
    off.append_attribute("y") = "0";
    auto ext = xfrm.append_child("a:ext");
    ext.append_attribute("cx") = "0";
    ext.append_attribute("cy") = "0";
    return xfrm;
}

} // namespace Aspose::Slides::Foss
