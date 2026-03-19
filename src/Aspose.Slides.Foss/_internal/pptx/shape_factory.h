// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

/// @file shape_factory.h
/// @brief Factory for creating the correct shape type from PPTX XML elements.

#include <memory>
#include <variant>

#include <pugixml.hpp>

namespace Aspose::Slides::Foss {
class Shape;
class Table;
class IBaseSlide;
} // namespace Aspose::Slides::Foss

namespace Aspose::Slides::Foss::Internal::pptx {
class SlidePart;
} // namespace Aspose::Slides::Foss::Internal::pptx

namespace Aspose::Slides::Foss::Internal::pptx::shape_factory {

/// Result of shape creation from XML. Holds either nothing (monostate),
/// a Shape-derived object, or a Table.
using ShapeVariant = std::variant<
    std::monostate,
    std::unique_ptr<Shape>,
    std::unique_ptr<Table>>;

/// Create the appropriate shape object based on the XML element type.
///
/// Maps XML tags to C++ shape classes:
/// - `p:sp`           → AutoShape
/// - `p:pic`          → PictureFrame
/// - `p:grpSp`        → GroupShape
/// - `p:cxnSp`        → Connector
/// - `p:graphicFrame` → delegates to create_graphical_object()
///
/// @param xml_element The XML element representing the shape.
/// @param slide_part  The SlidePart containing the slide XML.
/// @param parent_slide The parent slide object.
/// @return A ShapeVariant holding the created object, or monostate if unknown.
ShapeVariant create_shape(pugi::xml_node xml_element,
                          SlidePart* slide_part,
                          IBaseSlide* parent_slide);

/// Create the appropriate graphical object from a `p:graphicFrame` element.
///
/// Inspects the `a:graphicData` URI to determine the object type:
/// - URI containing "table" → Table
/// - URI containing "chart" → not yet implemented (returns monostate)
/// - URI containing "smartart" or "diagram" → not yet implemented (returns monostate)
///
/// @param xml_element The graphicFrame XML element.
/// @param slide_part  The SlidePart containing the slide XML.
/// @param parent_slide The parent slide object.
/// @return A ShapeVariant holding the created object, or monostate if unrecognised.
ShapeVariant create_graphical_object(pugi::xml_node xml_element,
                                     SlidePart* slide_part,
                                     IBaseSlide* parent_slide);

} // namespace Aspose::Slides::Foss::Internal::pptx::shape_factory
