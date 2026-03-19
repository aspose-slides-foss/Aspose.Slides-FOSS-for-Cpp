// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IPortionFormat;
class IParagraphFormat;
class ITextFrameFormat;

/// Represents an object with possibility of bulk setting child text elements' formats.
class IBulkTextFormattable {
public:
    virtual ~IBulkTextFormattable() = default;

    /// Sets the portion format for all child portions.
    virtual void set_text_format(const IPortionFormat& source) = 0;

    /// Sets the paragraph format for all child paragraphs.
    virtual void set_text_format(const IParagraphFormat& source) = 0;

    /// Sets the text frame format for all child text frames.
    virtual void set_text_format(const ITextFrameFormat& source) = 0;
};

} // namespace Aspose::Slides::Foss
