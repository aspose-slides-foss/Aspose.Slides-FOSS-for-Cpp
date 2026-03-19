// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <Aspose/Slides/Foss/bevel_preset_type.h>

namespace Aspose::Slides::Foss {

/// Interface for shape bevel properties.
class IShapeBevel {
public:
    virtual ~IShapeBevel() = default;

    /// Returns the bevel preset type.
    [[nodiscard]] virtual BevelPresetType bevel_type() const = 0;
    virtual void set_bevel_type(BevelPresetType value) = 0;

    /// Returns the bevel width.
    [[nodiscard]] virtual double width() const = 0;
    virtual void set_width(double value) = 0;

    /// Returns the bevel height.
    [[nodiscard]] virtual double height() const = 0;
    virtual void set_height(double value) = 0;

protected:
    IShapeBevel() = default;
};

} // namespace Aspose::Slides::Foss
