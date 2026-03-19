// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

namespace Aspose::Slides::Foss {

/// Represents a 'Heading pair' property of the document.
/// It indicates the group name of document parts and the number of parts in group.
class IHeadingPair {
public:
    virtual ~IHeadingPair() = default;

    /// Returns the group name of document parts. Read-only.
    [[nodiscard]] virtual const std::string& name() const = 0;

    /// Returns the number of parts in group. Read-only.
    [[nodiscard]] virtual int count() const = 0;

protected:
    IHeadingPair() = default;
};

} // namespace Aspose::Slides::Foss
