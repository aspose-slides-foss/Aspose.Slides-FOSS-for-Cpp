// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/i_slide_component.h>

namespace Aspose::Slides::Foss {

class IPortionFormat;

/// Interface for a text portion within a paragraph.
class IPortion : public virtual ISlideComponent {
public:
    ~IPortion() override = default;

    /// Returns formatting object which contains explicitly set formatting
    /// properties of the text portion with no inheritance applied. Read-only.
    [[nodiscard]] virtual IPortionFormat& portion_format() = 0;
    [[nodiscard]] virtual const IPortionFormat& portion_format() const = 0;

    /// Returns the text content of the portion.
    [[nodiscard]] virtual const std::string& text() const = 0;
    virtual void set_text(std::string value) = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;
    [[nodiscard]] virtual const ISlideComponent* as_i_slide_component() const = 0;

protected:
    IPortion() = default;
};

} // namespace Aspose::Slides::Foss
