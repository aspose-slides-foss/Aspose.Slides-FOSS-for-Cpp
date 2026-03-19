// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>

namespace Aspose::Slides::Foss {

class GradientStop;

/// Interface for a collection of gradient stops.
class IGradientStopCollection {
public:
    virtual ~IGradientStopCollection() = default;

    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual GradientStop& operator[](std::size_t index) = 0;
};

} // namespace Aspose::Slides::Foss
