// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <functional>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/fill_format.h>
#include <Aspose/Slides/Foss/i_table_format.h>

namespace Aspose::Slides::Foss {

/// Represents table formatting properties.
class TableFormat final : public ITableFormat {
public:
    TableFormat() = default;

    /// Initialize from a \<a:tblPr\> XML element.
    /// @param tbl_pr_element The XML node for table properties.
    /// @param save_callback  Callback to persist changes.
    void init_internal(pugi::xml_node tbl_pr_element,
                       std::function<void()> save_callback);

    /// Returns the fill format for the table.
    [[nodiscard]] FillFormat& fill_format() override { return fill_format_; }
    [[nodiscard]] const FillFormat& fill_format() const override { return fill_format_; }

private:
    FillFormat fill_format_;
};

} // namespace Aspose::Slides::Foss
