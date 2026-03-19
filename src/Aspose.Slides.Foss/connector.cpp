// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/connector.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/shape_collection.h>

namespace Aspose::Slides::Foss {

// ---------------------------------------------------------------------------
// get_c_nv_cxn_sp_pr
// ---------------------------------------------------------------------------

pugi::xml_node Connector::get_c_nv_cxn_sp_pr() const {
    auto elem = xml_element();
    if (!elem) return {};
    auto nv_cxn_sp_pr = elem.child("p:nvCxnSpPr");
    if (!nv_cxn_sp_pr) return {};
    return nv_cxn_sp_pr.child("p:cNvCxnSpPr");
}

// ---------------------------------------------------------------------------
// ensure_c_nv_cxn_sp_pr
// ---------------------------------------------------------------------------

pugi::xml_node Connector::ensure_c_nv_cxn_sp_pr() {
    auto elem = xml_element();
    if (!elem) {
        throw std::runtime_error("Connector has no XML element");
    }
    auto nv_cxn_sp_pr = elem.child("p:nvCxnSpPr");
    if (!nv_cxn_sp_pr) {
        throw std::runtime_error("Connector has no nvCxnSpPr element");
    }
    auto c_nv_cxn_sp_pr = nv_cxn_sp_pr.child("p:cNvCxnSpPr");
    if (!c_nv_cxn_sp_pr) {
        c_nv_cxn_sp_pr = nv_cxn_sp_pr.append_child("p:cNvCxnSpPr");
    }
    return c_nv_cxn_sp_pr;
}

// ---------------------------------------------------------------------------
// find_shape_by_id
// ---------------------------------------------------------------------------

Shape* Connector::find_shape_by_id(std::uint32_t shape_id) const {
    // const_cast is safe: we only use this for lookup, and the returned pointer's
    auto* parent = const_cast<Connector*>(this)->slide();
    if (!parent) return nullptr;
    auto& shapes = parent->shapes();
    for (std::size_t i = 0; i < shapes.size(); ++i) {
        auto& shape = shapes[i];
        auto c_nv_pr = shape.get_c_nv_pr();
        if (c_nv_pr) {
            auto id_attr = c_nv_pr.attribute("id");
            if (id_attr && id_attr.as_uint() == shape_id) {
                return &shape;
            }
        }
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// get_connection_point
// ---------------------------------------------------------------------------

std::pair<double, double> Connector::get_connection_point(
    const Shape& shape, std::uint32_t site_index) noexcept {
    double sx = shape.x();
    double sy = shape.y();
    double sw = shape.width();
    double sh = shape.height();

    switch (site_index) {
        case 0: return {sx + sw / 2.0, sy};              // top-center
        case 1: return {sx,            sy + sh / 2.0};   // left-center
        case 2: return {sx + sw / 2.0, sy + sh};         // bottom-center
        case 3: return {sx + sw,       sy + sh / 2.0};   // right-center
        default: return {sx + sw / 2.0, sy + sh / 2.0};  // center (fallback)
    }
}

void Connector::reroute() {
    if (!start_shape_ && !end_shape_) return;

    double sx, sy;
    if (start_shape_) {
        auto [px, py] = get_connection_point(*start_shape_, start_site_index_);
        sx = px;
        sy = py;
    } else {
        sx = x();
        sy = y();
    }

    double ex, ey;
    if (end_shape_) {
        auto [px, py] = get_connection_point(*end_shape_, end_site_index_);
        ex = px;
        ey = py;
    } else {
        ex = x() + width();
        ey = y() + height();
    }

    set_x(std::min(sx, ex));
    set_y(std::min(sy, ey));
    set_width(std::abs(ex - sx));
    set_height(std::abs(ey - sy));
}

} // namespace Aspose::Slides::Foss
