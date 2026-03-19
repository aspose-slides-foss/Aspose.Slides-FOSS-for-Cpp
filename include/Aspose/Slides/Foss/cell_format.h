// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>
#include <string_view>

#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/line_format.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents formatting for a table cell.
class CellFormat final {
public:
    CellFormat() = default;
    virtual ~CellFormat() = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed cell format from a <a:tcPr> element.
    /// @param tc_pr_element The XML node representing table cell properties.
    /// @param save_callback Callback to persist changes.
    void init_internal(pugi::xml_node tc_pr_element,
                       std::function<void()> save_callback);

    /// Returns the fill format for this cell.
    [[nodiscard]] FillFormat& fill_format() noexcept { return fill_format_; }
    [[nodiscard]] const FillFormat& fill_format() const noexcept { return fill_format_; }

    /// Returns the left border line format.
    [[nodiscard]] LineFormat& border_left() noexcept { return border_left_; }
    [[nodiscard]] const LineFormat& border_left() const noexcept { return border_left_; }

    /// Returns the top border line format.
    [[nodiscard]] LineFormat& border_top() noexcept { return border_top_; }
    [[nodiscard]] const LineFormat& border_top() const noexcept { return border_top_; }

    /// Returns the right border line format.
    [[nodiscard]] LineFormat& border_right() noexcept { return border_right_; }
    [[nodiscard]] const LineFormat& border_right() const noexcept { return border_right_; }

    /// Returns the bottom border line format.
    [[nodiscard]] LineFormat& border_bottom() noexcept { return border_bottom_; }
    [[nodiscard]] const LineFormat& border_bottom() const noexcept { return border_bottom_; }

    /// Returns the diagonal-down border line format.
    [[nodiscard]] LineFormat& border_diagonal_down() noexcept { return border_diag_down_; }
    [[nodiscard]] const LineFormat& border_diagonal_down() const noexcept { return border_diag_down_; }

    /// Returns the diagonal-up border line format.
    [[nodiscard]] LineFormat& border_diagonal_up() noexcept { return border_diag_up_; }
    [[nodiscard]] const LineFormat& border_diagonal_up() const noexcept { return border_diag_up_; }

private:
    FillFormat fill_format_;
    LineFormat border_left_;
    LineFormat border_top_;
    LineFormat border_right_;
    LineFormat border_bottom_;
    LineFormat border_diag_down_;
    LineFormat border_diag_up_;
};

} // namespace Aspose::Slides::Foss
