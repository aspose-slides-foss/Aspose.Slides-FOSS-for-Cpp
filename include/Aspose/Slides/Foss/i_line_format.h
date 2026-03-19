// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <vector>

#include <Aspose/Slides/Foss/i_line_param_source.h>
#include <Aspose/Slides/Foss/line_alignment.h>
#include <Aspose/Slides/Foss/line_arrowhead_length.h>
#include <Aspose/Slides/Foss/line_arrowhead_style.h>
#include <Aspose/Slides/Foss/line_arrowhead_width.h>
#include <Aspose/Slides/Foss/line_cap_style.h>
#include <Aspose/Slides/Foss/line_dash_style.h>
#include <Aspose/Slides/Foss/line_join_style.h>
#include <Aspose/Slides/Foss/line_style.h>

namespace Aspose::Slides::Foss {

class ILineFillFormat;

/// Represents format of a line.
class ILineFormat : public ILineParamSource {
public:
    ~ILineFormat() override = default;

    /// Returns true if line format is not defined (as just created, default). Read-only.
    [[nodiscard]] virtual bool is_format_not_defined() const = 0;

    /// Returns the fill format of a line. Read-only.
    [[nodiscard]] virtual ILineFillFormat& fill_format() = 0;
    /// Returns the fill format of a line (const). Read-only.
    [[nodiscard]] virtual const ILineFillFormat& fill_format() const = 0;

    /// Returns the width of a line. Read/write.
    [[nodiscard]] virtual double width() const = 0;
    /// Sets the width of a line.
    virtual void set_width(double value) = 0;

    /// Returns the line dash style. Read/write.
    [[nodiscard]] virtual LineDashStyle dash_style() const = 0;
    /// Sets the line dash style.
    virtual void set_dash_style(LineDashStyle value) = 0;

    /// Returns the custom dash pattern. Read/write.
    [[nodiscard]] virtual std::vector<float> custom_dash_pattern() const = 0;
    /// Sets the custom dash pattern.
    virtual void set_custom_dash_pattern(std::vector<float> value) = 0;

    /// Returns the line cap style. Read/write.
    [[nodiscard]] virtual LineCapStyle cap_style() const = 0;
    /// Sets the line cap style.
    virtual void set_cap_style(LineCapStyle value) = 0;

    /// Returns the line style. Read/write.
    [[nodiscard]] virtual LineStyle style() const = 0;
    /// Sets the line style.
    virtual void set_style(LineStyle value) = 0;

    /// Returns the line alignment. Read/write.
    [[nodiscard]] virtual LineAlignment alignment() const = 0;
    /// Sets the line alignment.
    virtual void set_alignment(LineAlignment value) = 0;

    /// Returns the lines join style. Read/write.
    [[nodiscard]] virtual LineJoinStyle join_style() const = 0;
    /// Sets the lines join style.
    virtual void set_join_style(LineJoinStyle value) = 0;

    /// Returns the miter limit of a line. Read/write.
    [[nodiscard]] virtual double miter_limit() const = 0;
    /// Sets the miter limit of a line.
    virtual void set_miter_limit(double value) = 0;

    /// Returns the arrowhead style at the beginning of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadStyle begin_arrowhead_style() const = 0;
    /// Sets the arrowhead style at the beginning of a line.
    virtual void set_begin_arrowhead_style(LineArrowheadStyle value) = 0;

    /// Returns the arrowhead style at the end of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadStyle end_arrowhead_style() const = 0;
    /// Sets the arrowhead style at the end of a line.
    virtual void set_end_arrowhead_style(LineArrowheadStyle value) = 0;

    /// Returns the arrowhead width at the beginning of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadWidth begin_arrowhead_width() const = 0;
    /// Sets the arrowhead width at the beginning of a line.
    virtual void set_begin_arrowhead_width(LineArrowheadWidth value) = 0;

    /// Returns the arrowhead width at the end of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadWidth end_arrowhead_width() const = 0;
    /// Sets the arrowhead width at the end of a line.
    virtual void set_end_arrowhead_width(LineArrowheadWidth value) = 0;

    /// Returns the arrowhead length at the beginning of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadLength begin_arrowhead_length() const = 0;
    /// Sets the arrowhead length at the beginning of a line.
    virtual void set_begin_arrowhead_length(LineArrowheadLength value) = 0;

    /// Returns the arrowhead length at the end of a line. Read/write.
    [[nodiscard]] virtual LineArrowheadLength end_arrowhead_length() const = 0;
    /// Sets the arrowhead length at the end of a line.
    virtual void set_end_arrowhead_length(LineArrowheadLength value) = 0;

protected:
    ILineFormat() = default;
};

} // namespace Aspose::Slides::Foss
