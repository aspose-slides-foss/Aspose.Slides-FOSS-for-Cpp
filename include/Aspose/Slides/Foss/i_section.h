// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

/// Interface representing a section in a presentation.
class ISection {
public:
    virtual ~ISection() = default;

protected:
    ISection() = default;
    ISection(const ISection&) = default;
    ISection& operator=(const ISection&) = default;
};

} // namespace Aspose::Slides::Foss
