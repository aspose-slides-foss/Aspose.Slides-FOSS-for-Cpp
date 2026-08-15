// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_shape_collection.h>
#include <Aspose/Slides/Foss/shape.h>
#include <Aspose/Slides/Foss/shape_type.h>
#include <Aspose/Slides/Foss/table.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class AutoShape;
class Connector;
class IBaseSlide;
class IGroupShape;
class PPImage;
class PictureFrame;
class Table;

/// Manages the collection of shapes on a slide.
///
/// Operates in two modes:
/// - **Simple mode** (default): shapes are managed in-memory only.
/// - **XML-backed mode** (after init_internal): shapes are loaded from and
///   persisted to the slide's spTree XML, with lazy caching.
class ShapeCollection final : public IShapeCollection {
public:
    ShapeCollection() = default;
    ShapeCollection(const ShapeCollection&) = delete;
    ShapeCollection& operator=(const ShapeCollection&) = delete;
    ~ShapeCollection() override;
    ShapeCollection(ShapeCollection&&) noexcept;
    ShapeCollection& operator=(ShapeCollection&&) noexcept;

    // -- Internal initialization ------------------------------------------------

    /// Initialize from a slide part, entering XML-backed mode.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    // -- IShapeCollection implementation ----------------------------------------

    /// Returns the parent group shape, or nullptr if top-level.
    [[nodiscard]] IGroupShape* parent_group() const noexcept override;

    /// Returns this collection as a generic collection interface.
    [[nodiscard]] IShapeCollection& as_i_collection() noexcept override;

    /// Returns this collection as a generic enumerable interface.
    [[nodiscard]] IShapeCollection& as_i_enumerable() noexcept override;

    /// Returns the number of shapes.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the shape at the given index.
    [[nodiscard]] Shape& operator[](std::size_t index) override;
    [[nodiscard]] const Shape& operator[](std::size_t index) const;

    /// Returns all shapes as non-owning pointers.
    [[nodiscard]] std::vector<Shape*> to_array() override;

    /// Returns shapes in the specified range as non-owning pointers.
    [[nodiscard]] std::vector<Shape*> to_array(std::size_t start_index,
                                               std::size_t count) override;

    /// Moves a shape to the specified position (z-order).
    void reorder(std::size_t new_index, Shape& shape) override;

    /// Moves multiple shapes to the specified z-order position.
    void reorder(std::size_t index, std::span<Shape*> shapes) override;

    /// Adds an AutoShape to the collection.
    AutoShape& add_auto_shape(ShapeType type, double x, double y,
                              double width, double height) override;

    /// Adds an AutoShape, optionally creating from a template.
    AutoShape& add_auto_shape(ShapeType type, double x, double y,
                              double width, double height,
                              bool create_from_template) override;

    /// Inserts an AutoShape at the specified index.
    AutoShape& insert_auto_shape(std::size_t index, ShapeType type,
                                 double x, double y,
                                 double width, double height) override;

    /// Inserts an AutoShape at the specified index, optionally from a template.
    AutoShape& insert_auto_shape(std::size_t index, ShapeType type,
                                 double x, double y,
                                 double width, double height,
                                 bool create_from_template) override;

    /// Adds a Connector to the collection.
    Connector& add_connector(ShapeType type, double x, double y,
                             double width, double height) override;

    /// Adds a Connector, optionally creating from a template.
    Connector& add_connector(ShapeType type, double x, double y,
                             double width, double height,
                             bool create_from_template) override;

    /// Inserts a Connector at the specified index.
    Connector& insert_connector(std::size_t index, ShapeType type,
                                double x, double y,
                                double width, double height) override;

    /// Inserts a Connector at the specified index, optionally from a template.
    Connector& insert_connector(std::size_t index, ShapeType type,
                                double x, double y,
                                double width, double height,
                                bool create_from_template) override;

    /// Returns the zero-based index of a shape, or -1 if not found.
    [[nodiscard]] std::ptrdiff_t index_of(const Shape& shape) const override;

    /// Adds a PictureFrame to the collection.
    PictureFrame& add_picture_frame(ShapeType type, double x, double y,
                                    double width, double height,
                                    PPImage& image) override;

    /// Inserts a PictureFrame at the specified index.
    PictureFrame& insert_picture_frame(std::size_t index, ShapeType type,
                                       double x, double y,
                                       double width, double height,
                                       PPImage& image) override;

    /// Adds a Table to the collection.
    Table& add_table(double x, double y,
                     std::span<const double> column_widths,
                     std::span<const double> row_heights) override;

    /// Inserts a Table at the specified index.
    Table& insert_table(std::size_t index, double x, double y,
                        std::span<const double> column_widths,
                        std::span<const double> row_heights) override;

    /// Removes a shape from the collection by reference.
    void remove(const Shape& shape) override;

    /// Removes the shape at the given index.
    void remove_at(std::size_t index) override;

    /// Removes all shapes.
    void clear() noexcept override;

    /// Returns the number of tables in the collection.
    [[nodiscard]] std::size_t table_count() const { load_shapes(); return tables_.size(); }

    /// Returns the table at the given index.
    [[nodiscard]] Table& table_at(std::size_t index) { load_shapes(); return *tables_.at(index); }
    [[nodiscard]] const Table& table_at(std::size_t index) const { load_shapes(); return *tables_.at(index); }

    // Range-based for loop support.
    using iterator = std::vector<std::unique_ptr<Shape>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Shape>>::const_iterator;
    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;
    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;

    // -- XML-backed internal API ------------------------------------------------

    /// Get the spTree element from the slide XML.
    [[nodiscard]] pugi::xml_node get_sp_tree() const;

    /// Load all shapes from the XML, populating the internal cache.
    /// No-op if the cache is already valid.
    void load_shapes() const;

    /// Invalidate the shapes cache, forcing a reload on next access.
    void invalidate_cache();

    /// Save changes to the slide part.
    void save_to_part();

    /// Find the next available shape ID in the spTree.
    [[nodiscard]] int next_shape_id() const;

    /// Build XML content for a new AutoShape element.
    /// @param sp The pre-created p:sp node to populate.
    void build_auto_shape_xml(pugi::xml_node sp, int shape_id,
                              std::string_view name, ShapeType type,
                              double x, double y, double w, double h,
                              bool create_from_template);

    /// Build XML content for a new connector (cxnSp) element.
    /// @param cxn_sp The pre-created p:cxnSp node to populate.
    void build_connector_xml(pugi::xml_node cxn_sp, int shape_id,
                             std::string_view name, ShapeType type,
                             double x, double y, double w, double h,
                             bool create_from_template);

    /// Build XML content for a new picture (pic) element.
    /// @param pic The pre-created p:pic node to populate.
    /// @param embed_id The relationship id of the image, for a:blip/@r:embed.
    static void build_picture_frame_xml(pugi::xml_node pic, int shape_id,
                                        std::string_view name, ShapeType type,
                                        double x, double y, double w, double h,
                                        std::string_view embed_id);

    /// Core implementation for add_auto_shape and insert_auto_shape.
    AutoShape& add_auto_shape_impl(std::optional<std::size_t> index,
                                   ShapeType type, double x, double y,
                                   double w, double h,
                                   bool create_from_template);

    /// Core implementation for add_connector and insert_connector.
    Connector& add_connector_impl(std::optional<std::size_t> index,
                                  ShapeType type, double x, double y,
                                  double w, double h,
                                  bool create_from_template);

    /// Core implementation for add_picture_frame and insert_picture_frame.
    PictureFrame& add_picture_frame_impl(std::optional<std::size_t> index,
                                         ShapeType type, double x, double y,
                                         double w, double h,
                                         PPImage& image);

    /// Core implementation for add_table and insert_table.
    Table& add_table_impl(std::optional<std::size_t> index,
                          double x, double y,
                          std::span<const double> column_widths,
                          std::span<const double> row_heights);

    /// Reorder a single shape to a new position in XML and cache.
    void reorder_single(std::size_t new_index, Shape& shape);

private:
    /// Insert a child element into sp_tree at the given shape index, or append.
    pugi::xml_node insert_or_append(pugi::xml_node sp_tree,
                                    std::optional<std::size_t> index,
                                    const char* element_name);

    mutable std::vector<std::unique_ptr<Shape>> shapes_;
    mutable std::vector<std::unique_ptr<Table>> tables_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;
    mutable bool cache_valid_ = true;
};

} // namespace Aspose::Slides::Foss
