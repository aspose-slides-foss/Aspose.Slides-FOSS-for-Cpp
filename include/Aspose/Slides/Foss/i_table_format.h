// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class FillFormat;

/// Represents format of a table.
///
/// Provides access to table fill properties.
class ITableFormat {
public:
    virtual ~ITableFormat() = default;

    /// Returns the fill format for the table. Read-only.
    [[nodiscard]] virtual FillFormat& fill_format() = 0;
    /// Returns the fill format for the table (const). Read-only.
    [[nodiscard]] virtual const FillFormat& fill_format() const = 0;

protected:
    ITableFormat() = default;
};

} // namespace Aspose::Slides::Foss
