// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/i_graphical_object.h>
#include <Aspose/Slides/Foss/shape.h>

namespace Aspose::Slides::Foss {

/// Abstract base class for graphical objects on a slide.
///
/// Combines Shape (concrete shape properties) with IGraphicalObject
/// (graphical object lock interface). Remains abstract because
/// IGraphicalObject::graphical_object_lock() is deferred to derived classes.
class GraphicalObject : public Shape, public IGraphicalObject {
public:
    ~GraphicalObject() override = default;

protected:
    GraphicalObject() = default;
    GraphicalObject(ShapeType type, double x, double y, double w, double h)
        : Shape(type, x, y, w, h) {}
};

} // namespace Aspose::Slides::Foss
