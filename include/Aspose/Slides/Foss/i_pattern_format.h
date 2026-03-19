// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/pattern_style.h>

namespace Aspose::Slides::Foss {

class SimpleColorFormat;

/// Interface for pattern fill format.
class IPatternFormat {
public:
    virtual ~IPatternFormat() = default;

    /// Returns the pattern style.
    [[nodiscard]] virtual PatternStyle pattern_style() const = 0;
    virtual void set_pattern_style(PatternStyle value) = 0;

    /// Returns the foreground color.
    [[nodiscard]] virtual SimpleColorFormat& fore_color() = 0;

    /// Returns the background color.
    [[nodiscard]] virtual SimpleColorFormat& back_color() = 0;

protected:
    IPatternFormat() = default;
};

} // namespace Aspose::Slides::Foss
