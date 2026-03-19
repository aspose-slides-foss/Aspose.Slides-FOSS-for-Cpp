// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <span>
#include <vector>

#include <Aspose/Slides/Foss/shape_type.h>

namespace Aspose::Slides::Foss {

class AutoShape;
class Connector;
class IGroupShape;
class PPImage;
class PictureFrame;
class Shape;
class Table;

/// Interface for a collection of shapes.
class IShapeCollection {
public:
    virtual ~IShapeCollection() = default;

    /// Returns the parent group shape, or nullptr if top-level.
    [[nodiscard]] virtual IGroupShape* parent_group() const = 0;

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] virtual IShapeCollection& as_i_collection() = 0;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] virtual IShapeCollection& as_i_enumerable() = 0;

    /// Returns the number of shapes.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the shape at the given index.
    [[nodiscard]] virtual Shape& operator[](std::size_t index) = 0;

    /// Returns all shapes as a vector of non-owning pointers.
    [[nodiscard]] virtual std::vector<Shape*> to_array() = 0;

    /// Returns shapes in the specified range as non-owning pointers.
    [[nodiscard]] virtual std::vector<Shape*> to_array(std::size_t start_index,
                                                       std::size_t count) = 0;

    /// Moves a shape to the specified z-order position.
    virtual void reorder(std::size_t index, Shape& shape) = 0;

    /// Moves multiple shapes to the specified z-order position.
    virtual void reorder(std::size_t index, std::span<Shape*> shapes) = 0;

    /// Adds an AutoShape to the collection.
    virtual AutoShape& add_auto_shape(ShapeType type, double x, double y,
                                      double width, double height) = 0;

    /// Adds an AutoShape, optionally creating from a template.
    virtual AutoShape& add_auto_shape(ShapeType type, double x, double y,
                                      double width, double height,
                                      bool create_from_template) = 0;

    /// Inserts an AutoShape at the specified index.
    virtual AutoShape& insert_auto_shape(std::size_t index, ShapeType type,
                                         double x, double y,
                                         double width, double height) = 0;

    /// Inserts an AutoShape at the specified index, optionally from a template.
    virtual AutoShape& insert_auto_shape(std::size_t index, ShapeType type,
                                         double x, double y,
                                         double width, double height,
                                         bool create_from_template) = 0;

    /// Adds a Connector to the collection.
    virtual Connector& add_connector(ShapeType type, double x, double y,
                                     double width, double height) = 0;

    /// Adds a Connector, optionally creating from a template.
    virtual Connector& add_connector(ShapeType type, double x, double y,
                                     double width, double height,
                                     bool create_from_template) = 0;

    /// Inserts a Connector at the specified index.
    virtual Connector& insert_connector(std::size_t index, ShapeType type,
                                        double x, double y,
                                        double width, double height) = 0;

    /// Inserts a Connector at the specified index, optionally from a template.
    virtual Connector& insert_connector(std::size_t index, ShapeType type,
                                        double x, double y,
                                        double width, double height,
                                        bool create_from_template) = 0;

    /// Returns the zero-based index of a shape, or -1 if not found.
    [[nodiscard]] virtual std::ptrdiff_t index_of(const Shape& shape) const = 0;

    /// Adds a PictureFrame to the collection.
    virtual PictureFrame& add_picture_frame(ShapeType type, double x, double y,
                                            double width, double height,
                                            PPImage& image) = 0;

    /// Inserts a PictureFrame at the specified index.
    virtual PictureFrame& insert_picture_frame(std::size_t index, ShapeType type,
                                               double x, double y,
                                               double width, double height,
                                               PPImage& image) = 0;

    /// Adds a Table to the collection.
    virtual Table& add_table(double x, double y,
                             std::span<const double> column_widths,
                             std::span<const double> row_heights) = 0;

    /// Inserts a Table at the specified index.
    virtual Table& insert_table(std::size_t index, double x, double y,
                                std::span<const double> column_widths,
                                std::span<const double> row_heights) = 0;

    /// Removes the shape at the given index.
    virtual void remove_at(std::size_t index) = 0;

    /// Removes a shape from the collection by reference.
    virtual void remove(const Shape& shape) = 0;

    /// Removes all shapes.
    virtual void clear() = 0;

protected:
    IShapeCollection() = default;
};

} // namespace Aspose::Slides::Foss
