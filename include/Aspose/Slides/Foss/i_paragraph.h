// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

#include <Aspose/Slides/Foss/i_slide_component.h>

namespace Aspose::Slides::Foss {

class IParagraphFormat;
class IPortionCollection;

/// Represents a paragraph of a text.
class IParagraph : public virtual ISlideComponent {
public:
    ~IParagraph() override = default;

    /// Returns the collection of text portions. Read-only.
    [[nodiscard]] virtual IPortionCollection& portions() = 0;
    [[nodiscard]] virtual const IPortionCollection& portions() const = 0;

    /// Returns the formatting object for this paragraph. Read-only.
    [[nodiscard]] virtual IParagraphFormat& paragraph_format() = 0;
    [[nodiscard]] virtual const IParagraphFormat& paragraph_format() const = 0;

    /// Gets the plain text of a paragraph.
    [[nodiscard]] virtual std::string text() const = 0;

    /// Sets the plain text of a paragraph.
    virtual void set_text(std::string value) = 0;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] virtual ISlideComponent* as_i_slide_component() = 0;
    [[nodiscard]] virtual const ISlideComponent* as_i_slide_component() const = 0;

protected:
    IParagraph() = default;
};

} // namespace Aspose::Slides::Foss
