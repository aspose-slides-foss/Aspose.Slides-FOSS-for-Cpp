// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

namespace Aspose::Slides::Foss {

/// Interface for a geometry shape adjustment value.
class IAdjustValue {
public:
    virtual ~IAdjustValue() = default;

    [[nodiscard]] virtual const std::string& name() const = 0;
    [[nodiscard]] virtual int raw_value() const = 0;
    virtual void set_raw_value(int value) = 0;
    [[nodiscard]] virtual double angle_value() const = 0;
    virtual void set_angle_value(double value) = 0;
};

} // namespace Aspose::Slides::Foss
