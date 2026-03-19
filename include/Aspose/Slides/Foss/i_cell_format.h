// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class FillFormat;
class LineFormat;

/// Interface for cell formatting.
class ICellFormat {
public:
    virtual ~ICellFormat() = default;

    [[nodiscard]] virtual FillFormat& fill_format() = 0;
    [[nodiscard]] virtual LineFormat& border_left() = 0;
    [[nodiscard]] virtual LineFormat& border_top() = 0;
    [[nodiscard]] virtual LineFormat& border_right() = 0;
    [[nodiscard]] virtual LineFormat& border_bottom() = 0;
    [[nodiscard]] virtual LineFormat& border_diagonal_down() = 0;
    [[nodiscard]] virtual LineFormat& border_diagonal_up() = 0;
};

} // namespace Aspose::Slides::Foss
