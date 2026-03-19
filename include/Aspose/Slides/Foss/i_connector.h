// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>

namespace Aspose::Slides::Foss {

class Shape;

/// Interface for connector shapes.
class IConnector {
public:
    virtual ~IConnector() = default;

    [[nodiscard]] virtual Shape* start_shape_connected_to() const = 0;
    virtual void set_start_shape_connected_to(Shape* shape) = 0;
    [[nodiscard]] virtual uint32_t start_shape_connection_site_index() const = 0;
    virtual void set_start_shape_connection_site_index(uint32_t idx) = 0;
    [[nodiscard]] virtual Shape* end_shape_connected_to() const = 0;
    virtual void set_end_shape_connected_to(Shape* shape) = 0;
    [[nodiscard]] virtual uint32_t end_shape_connection_site_index() const = 0;
    virtual void set_end_shape_connection_site_index(uint32_t idx) = 0;
    virtual void reroute() = 0;
};

} // namespace Aspose::Slides::Foss
