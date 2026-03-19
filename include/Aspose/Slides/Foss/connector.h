// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <tuple>

#include <Aspose/Slides/Foss/geometry_shape.h>
#include <Aspose/Slides/Foss/i_connector.h>

namespace Aspose::Slides::Foss {

/// Represents a connector shape that links two shapes.
class Connector final : public GeometryShape, public IConnector {
public:
    Connector() = default;
    Connector(ShapeType type, double x, double y, double w, double h)
        : GeometryShape(type, x, y, w, h) {}

    /// Returns nullptr — connector locks are not yet implemented.
    [[nodiscard]] std::nullptr_t connector_lock() const noexcept { return nullptr; }

    /// Returns this connector as an IGeometryShape pointer.
    [[nodiscard]] GeometryShape* as_i_geometry_shape() noexcept { return this; }

    /// Returns the shape connected to the start of this connector.
    [[nodiscard]] Shape* start_shape_connected_to() const noexcept override {
        return start_shape_;
    }
    /// Sets the shape connected to the start and reroutes.
    void set_start_shape_connected_to(Shape* shape) noexcept override {
        start_shape_ = shape;
        reroute();
    }

    /// Returns the connection site index at the start shape.
    [[nodiscard]] std::uint32_t start_shape_connection_site_index() const noexcept override {
        return start_site_index_;
    }
    /// Sets the connection site index at the start shape and reroutes.
    void set_start_shape_connection_site_index(std::uint32_t idx) noexcept override {
        start_site_index_ = idx;
        reroute();
    }

    /// Returns the shape connected to the end of this connector.
    [[nodiscard]] Shape* end_shape_connected_to() const noexcept override {
        return end_shape_;
    }
    /// Sets the shape connected to the end and reroutes.
    void set_end_shape_connected_to(Shape* shape) noexcept override {
        end_shape_ = shape;
        reroute();
    }

    /// Returns the connection site index at the end shape.
    [[nodiscard]] std::uint32_t end_shape_connection_site_index() const noexcept override {
        return end_site_index_;
    }
    /// Sets the connection site index at the end shape and reroutes.
    void set_end_shape_connection_site_index(std::uint32_t idx) noexcept override {
        end_site_index_ = idx;
        reroute();
    }

    /// Reroutes the connector based on connected shapes and site indices.
    void reroute() override;

    // -- XML-backed internal helpers -------------------------------------------

    /// Find the p:cNvCxnSpPr element in the connector XML.
    /// @return The element node, or an empty node if not found.
    [[nodiscard]] pugi::xml_node get_c_nv_cxn_sp_pr() const;

    /// Get or create the p:cNvCxnSpPr element.
    /// @throws std::runtime_error if the connector has no XML element or nvCxnSpPr.
    [[nodiscard]] pugi::xml_node ensure_c_nv_cxn_sp_pr();

    /// Search parent slide shapes for a shape with the given cNvPr@id.
    /// @return Pointer to the matching shape, or nullptr if not found.
    [[nodiscard]] Shape* find_shape_by_id(std::uint32_t shape_id) const;

    /// Returns (x, y) in points for a connection site on a shape.
    /// 4-site model: 0=top-center, 1=left-center, 2=bottom-center, 3=right-center.
    /// Falls back to shape center for out-of-range indices.
    [[nodiscard]] static std::pair<double, double> get_connection_point(
        const Shape& shape, std::uint32_t site_index) noexcept;

private:
    Shape* start_shape_ = nullptr;
    std::uint32_t start_site_index_ = 0;
    Shape* end_shape_ = nullptr;
    std::uint32_t end_site_index_ = 0;
};

} // namespace Aspose::Slides::Foss
