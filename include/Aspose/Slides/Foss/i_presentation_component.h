// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

namespace Aspose::Slides::Foss {

class IPresentation;

/// Represents a component of a presentation.
class IPresentationComponent {
public:
    virtual ~IPresentationComponent() = default;

    /// Returns the presentation. Read-only.
    [[nodiscard]] virtual IPresentation* presentation() = 0;
    [[nodiscard]] virtual const IPresentation* presentation() const = 0;
};

} // namespace Aspose::Slides::Foss
