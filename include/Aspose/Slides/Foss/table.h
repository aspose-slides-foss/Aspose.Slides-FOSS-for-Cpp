// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/column_collection.h>
#include <Aspose/Slides/Foss/i_table.h>
#include <Aspose/Slides/Foss/row_collection.h>
#include <Aspose/Slides/Foss/table_format.h>
#include <Aspose/Slides/Foss/table_style_preset.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class Cell;
class IBaseSlide;
class IPortionFormat;
class IParagraphFormat;
class ITextFrameFormat;

/// Represents a table shape on a slide.
class Table final : public ITable {
public:
    Table() = default;
    Table(Table&&) noexcept = default;
    Table& operator=(Table&&) noexcept = default;
    ~Table() override = default;

    // Non-copyable (contains unique_ptr members).
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

    // -- XML-backed initialization --------------------------------------------

    /// Initialize this table from an XML element within a slide part.
    /// @param xml_element The XML node representing the graphicFrame (or parent).
    /// @param slide_part  The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node xml_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Returns the collection of rows in this table.
    [[nodiscard]] RowCollection& rows() noexcept override { return rows_; }
    [[nodiscard]] const RowCollection& rows() const noexcept { return rows_; }

    /// Returns the collection of columns in this table.
    [[nodiscard]] ColumnCollection& columns() noexcept override { return columns_; }
    [[nodiscard]] const ColumnCollection& columns() const noexcept { return columns_; }

    /// Returns the cell at the given row and column.
    [[nodiscard]] Cell& cell(std::size_t row, std::size_t col) override;

    /// Returns the TableFormat object. Read-only.
    [[nodiscard]] ITableFormat& table_format() override { return table_format_; }
    [[nodiscard]] const TableFormat& table_format_obj() const noexcept { return table_format_; }

    /// Gets the builtin table style preset.
    [[nodiscard]] TableStylePreset style_preset() const noexcept override { return style_preset_; }

    /// Sets the builtin table style preset.
    void set_style_preset(TableStylePreset value) noexcept override { style_preset_ = value; }

    /// Determines whether the table has right to left reading order.
    [[nodiscard]] bool right_to_left() const noexcept override { return right_to_left_; }
    void set_right_to_left(bool value) noexcept override { right_to_left_ = value; set_bool_attr("rtl", value); }

    /// Determines whether the first row has special formatting.
    [[nodiscard]] bool first_row() const noexcept override { return first_row_; }
    void set_first_row(bool value) noexcept override { first_row_ = value; set_bool_attr("firstRow", value); }

    /// Determines whether the first column has special formatting.
    [[nodiscard]] bool first_col() const noexcept override { return first_col_; }
    void set_first_col(bool value) noexcept override { first_col_ = value; set_bool_attr("firstCol", value); }

    /// Determines whether the last row has special formatting.
    [[nodiscard]] bool last_row() const noexcept override { return last_row_; }
    void set_last_row(bool value) noexcept override { last_row_ = value; set_bool_attr("lastRow", value); }

    /// Determines whether the last column has special formatting.
    [[nodiscard]] bool last_col() const noexcept override { return last_col_; }
    void set_last_col(bool value) noexcept override { last_col_ = value; set_bool_attr("lastCol", value); }

    /// Determines whether even rows have different formatting.
    [[nodiscard]] bool horizontal_banding() const noexcept override { return horizontal_banding_; }
    void set_horizontal_banding(bool value) noexcept override { horizontal_banding_ = value; set_bool_attr("bandRow", value); }

    /// Determines whether even columns have different formatting.
    [[nodiscard]] bool vertical_banding() const noexcept override { return vertical_banding_; }
    void set_vertical_banding(bool value) noexcept override { vertical_banding_ = value; set_bool_attr("bandCol", value); }

    /// Returns nullptr — graphical object locks are not yet implemented.
    [[nodiscard]] IGraphicalObjectLock* graphical_object_lock() const noexcept override { return nullptr; }

    /// Returns base IGraphicalObject interface.
    [[nodiscard]] IGraphicalObject& as_i_graphical_object() override { return *this; }

    /// Returns base IBulkTextFormattable interface.
    [[nodiscard]] IBulkTextFormattable& as_i_bulk_text_formattable() override { return *this; }

    /// Merges two cells, expanding cell1 to cover the area of both cells.
    Cell& merge_cells(Cell& cell1, Cell& cell2, bool allow_splitting) override;

    /// IBulkTextFormattable overrides (no-op stubs for the interface).
    void set_text_format(const IPortionFormat& source) override;
    void set_text_format(const IParagraphFormat& source) override;
    void set_text_format(const ITextFrameFormat& source) override;

    // -- XML-backed internal helpers ------------------------------------------

    /// Returns the cached <a:tblPr> node, or an empty node if not present.
    [[nodiscard]] pugi::xml_node get_tbl_pr() const;

    /// Returns the <a:tblPr> node, creating it as the first child of <a:tbl> if absent.
    [[nodiscard]] pugi::xml_node ensure_tbl_pr();

    /// Reads a boolean attribute from <a:tblPr> ("1" = true, absent/"0" = false).
    [[nodiscard]] bool get_bool_attr(std::string_view attr_name) const;

    /// Sets or removes a boolean attribute on <a:tblPr>, then saves.
    void set_bool_attr(std::string_view attr_name, bool value);

    /// Finds the table style element — <a:tableStyleId> or legacy <a:tblStyle>.
    [[nodiscard]] pugi::xml_node find_style_element(pugi::xml_node tbl_pr) const;

    /// Reads the GUID string from a style element (text content or val attribute).
    [[nodiscard]] std::string read_style_guid(pugi::xml_node style_el) const;

    /// Returns the backing XML element.
    [[nodiscard]] pugi::xml_node xml_element() const { return xml_element_; }

    /// Returns the <a:tbl> element.
    [[nodiscard]] pugi::xml_node tbl() const { return tbl_; }

private:
    RowCollection rows_;
    ColumnCollection columns_;
    TableFormat table_format_;
    TableStylePreset style_preset_ = TableStylePreset::NONE;
    bool right_to_left_ = false;
    bool first_row_ = false;
    bool first_col_ = false;
    bool last_row_ = false;
    bool last_col_ = false;
    bool horizontal_banding_ = false;
    bool vertical_banding_ = false;

    // Position offset (used for in-memory tables without XML backing).
    double offset_x_ = 0;
    double offset_y_ = 0;

    // XML-backed state
    pugi::xml_node xml_element_;
    pugi::xml_node tbl_;
    pugi::xml_node tbl_pr_;
    pugi::xml_node tbl_grid_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;

    friend class Presentation;
    friend class ShapeCollection;
};

} // namespace Aspose::Slides::Foss
