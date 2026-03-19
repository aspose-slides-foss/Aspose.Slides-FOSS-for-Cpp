// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/drawing/size_f.h>

namespace Aspose::Slides::Foss {

/// Interface for notes slide size.
class INotesSize {
public:
    virtual ~INotesSize() = default;

    /// Returns the width of the notes slide in points.
    [[nodiscard]] virtual double width() const = 0;
    /// Sets the width of the notes slide in points.
    virtual void set_width(double value) = 0;

    /// Returns the height of the notes slide in points.
    [[nodiscard]] virtual double height() const = 0;
    /// Sets the height of the notes slide in points.
    virtual void set_height(double value) = 0;

    /// Returns the size of the notes slide in points. Read/write.
    [[nodiscard]] virtual Drawing::SizeF size() const = 0;
    /// Sets the size of the notes slide in points.
    virtual void set_size(Drawing::SizeF value) = 0;

protected:
    INotesSize() = default;
};

} // namespace Aspose::Slides::Foss
