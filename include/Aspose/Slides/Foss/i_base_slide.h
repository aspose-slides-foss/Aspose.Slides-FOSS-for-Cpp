// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstdint>
#include <string>

namespace Aspose::Slides::Foss {

class IPresentation;
class ShapeCollection;

/// Interface for base slide properties.
class IBaseSlide {
public:
    virtual ~IBaseSlide() = default;

    [[nodiscard]] virtual ShapeCollection& shapes() = 0;
    [[nodiscard]] virtual const ShapeCollection& shapes() const = 0;
    [[nodiscard]] virtual const std::string& name() const = 0;
    virtual void set_name(std::string value) = 0;
    [[nodiscard]] virtual uint32_t slide_id() const = 0;

    /// Returns the parent presentation. Read-only.
    [[nodiscard]] virtual IPresentation* presentation() = 0;
    [[nodiscard]] virtual const IPresentation* presentation() const = 0;
};

} // namespace Aspose::Slides::Foss
