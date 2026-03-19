// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/cell_format.h>
#include <Aspose/Slides/Foss/text_anchor_type.h>
#include <Aspose/Slides/Foss/text_frame.h>
#include <Aspose/Slides/Foss/text_vertical_type.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

class Column;
class IBaseSlide;
class Presentation;
class Row;
class Slide;
class Table;

/// EMU (English Metric Units) per point. 1 point = 12700 EMU.
inline constexpr double kEmuPerPoint = 12700.0;

/// Default left/right margin in EMU (91440 EMU = 7.2 pt).
inline constexpr double kDefaultMarginLR = 91440.0 / kEmuPerPoint;

/// Default top/bottom margin in EMU (45720 EMU = 3.6 pt).
inline constexpr double kDefaultMarginTB = 45720.0 / kEmuPerPoint;

/// Represents a cell in a table.
class Cell final {
public:
    Cell()
        : margin_left_(kDefaultMarginLR),
          margin_right_(kDefaultMarginLR),
          margin_top_(kDefaultMarginTB),
          margin_bottom_(kDefaultMarginTB),
          text_frame_(std::make_unique<TextFrame>()) {}

    virtual ~Cell() = default;

    // -- XML-backed initialization --------------------------------------------

    /// Initialize this cell from an XML <a:tc> element.
    /// @param tc_element  The XML node representing the table cell (<a:tc>).
    /// @param row_index   The row index within the table.
    /// @param col_index   The column index within the table.
    /// @param slide_part  The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    /// @param table       The parent table. May be nullptr.
    void init_internal(pugi::xml_node tc_element,
                       int row_index,
                       int col_index,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide,
                       Table* table);

    /// Returns the <a:tcPr> child node, or an empty node if not present.
    [[nodiscard]] pugi::xml_node get_tc_pr() const;

    /// Returns the <a:tcPr> child node, creating it if absent.
    [[nodiscard]] pugi::xml_node ensure_tc_pr();

    /// Returns the backing XML element (<a:tc>).
    [[nodiscard]] pugi::xml_node tc_element() const { return tc_element_; }

    /// Returns the x offset of the cell (distance from left side of table).
    [[nodiscard]] double offset_x() const noexcept { return offset_x_; }
    void set_offset_x(double value) noexcept { offset_x_ = value; }

    /// Returns the y offset of the cell (distance from top side of table).
    [[nodiscard]] double offset_y() const noexcept { return offset_y_; }
    void set_offset_y(double value) noexcept { offset_y_ = value; }

    /// Returns the index of the first row covered by this cell. Read-only.
    [[nodiscard]] int first_row_index() const noexcept { return first_row_index_; }
    void set_first_row_index(int value) noexcept { first_row_index_ = value; }

    /// Returns the index of the first column covered by this cell. Read-only.
    [[nodiscard]] int first_column_index() const noexcept { return first_column_index_; }
    void set_first_column_index(int value) noexcept { first_column_index_ = value; }

    /// Returns the width of the cell.
    [[nodiscard]] double width() const noexcept { return width_; }
    void set_width(double value) noexcept { width_ = value; }

    /// Returns the height of the cell.
    [[nodiscard]] double height() const noexcept { return height_; }
    void set_height(double value) noexcept { height_ = value; }

    /// Returns the minimal height of the cell.
    [[nodiscard]] double minimal_height() const noexcept { return minimal_height_; }
    void set_minimal_height(double value) noexcept { minimal_height_ = value; }

    /// Returns the left margin in a TextFrame. Read/write.
    [[nodiscard]] double margin_left() const noexcept { return margin_left_; }
    void set_margin_left(double value) noexcept { margin_left_ = value; }

    /// Returns the right margin in a TextFrame. Read/write.
    [[nodiscard]] double margin_right() const noexcept { return margin_right_; }
    void set_margin_right(double value) noexcept { margin_right_ = value; }

    /// Returns the top margin in a TextFrame. Read/write.
    [[nodiscard]] double margin_top() const noexcept { return margin_top_; }
    void set_margin_top(double value) noexcept { margin_top_ = value; }

    /// Returns the bottom margin in a TextFrame. Read/write.
    [[nodiscard]] double margin_bottom() const noexcept { return margin_bottom_; }
    void set_margin_bottom(double value) noexcept { margin_bottom_ = value; }

    /// Returns the type of vertical text. Read/write.
    [[nodiscard]] TextVerticalType text_vertical_type() const noexcept { return text_vertical_type_; }
    void set_text_vertical_type(TextVerticalType value) noexcept { text_vertical_type_ = value; }

    /// Returns the text anchor type. Read/write.
    [[nodiscard]] TextAnchorType text_anchor_type() const noexcept { return text_anchor_type_; }
    void set_text_anchor_type(TextAnchorType value) noexcept { text_anchor_type_ = value; }

    /// Determines whether text box is centered inside the cell. Read/write.
    [[nodiscard]] bool anchor_center() const noexcept { return anchor_center_; }
    void set_anchor_center(bool value) noexcept { anchor_center_ = value; }

    /// Returns the first row of this cell. Requires table to be set.
    [[nodiscard]] Row* first_row() const noexcept;

    /// Returns the first column of this cell. Requires table to be set.
    [[nodiscard]] Column* first_column() const noexcept;

    /// Returns the number of grid columns spanned by this cell.
    [[nodiscard]] int col_span() const noexcept { return col_span_; }
    void set_col_span(int value) noexcept { col_span_ = value; }

    /// Returns the number of rows spanned by this cell.
    [[nodiscard]] int row_span() const noexcept { return row_span_; }
    void set_row_span(int value) noexcept { row_span_ = value; }

    /// Returns the text frame for this cell.
    [[nodiscard]] TextFrame* text_frame() noexcept { return text_frame_.get(); }
    [[nodiscard]] const TextFrame* text_frame() const noexcept { return text_frame_.get(); }

    /// Returns the parent table for this cell.
    [[nodiscard]] Table* table() const noexcept { return table_; }
    void set_table(Table* value) noexcept { table_ = value; }

    /// Returns true if the cell is merged with any adjacent cell.
    [[nodiscard]] bool is_merged_cell() const noexcept {
        return col_span_ > 1 || row_span_ > 1 || h_merge_ || v_merge_;
    }

    /// Returns whether this cell is horizontally merged (continuation cell).
    [[nodiscard]] bool h_merge() const noexcept { return h_merge_; }
    void set_h_merge(bool value) noexcept { h_merge_ = value; }

    /// Returns whether this cell is vertically merged (continuation cell).
    [[nodiscard]] bool v_merge() const noexcept { return v_merge_; }
    void set_v_merge(bool value) noexcept { v_merge_ = value; }

    /// Returns the cell format.
    [[nodiscard]] CellFormat& cell_format() noexcept { return cell_format_; }
    [[nodiscard]] const CellFormat& cell_format() const noexcept { return cell_format_; }

    /// Returns the parent slide for this cell.
    [[nodiscard]] Slide* slide() const noexcept { return slide_; }
    void set_slide(Slide* value) noexcept { slide_ = value; }

    /// Returns the parent presentation for this cell.
    [[nodiscard]] Presentation* presentation() const noexcept;

private:
    double offset_x_ = 0;
    double offset_y_ = 0;
    double width_ = 0;
    double height_ = 0;
    double minimal_height_ = 0;
    double margin_left_;
    double margin_right_;
    double margin_top_;
    double margin_bottom_;
    TextVerticalType text_vertical_type_ = TextVerticalType::NOT_DEFINED;
    TextAnchorType text_anchor_type_ = TextAnchorType::NOT_DEFINED;
    bool anchor_center_ = false;
    bool h_merge_ = false;
    bool v_merge_ = false;
    int col_span_ = 1;
    int row_span_ = 1;
    int first_row_index_ = 0;
    int first_column_index_ = 0;
    std::unique_ptr<TextFrame> text_frame_;
    CellFormat cell_format_;
    Table* table_ = nullptr;
    Slide* slide_ = nullptr;

    // XML-backed state
    pugi::xml_node tc_element_;
    pugi::xml_node tc_pr_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;
};

} // namespace Aspose::Slides::Foss
