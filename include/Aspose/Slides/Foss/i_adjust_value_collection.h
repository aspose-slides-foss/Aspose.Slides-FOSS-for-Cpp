// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <vector>

namespace Aspose::Slides::Foss {

class AdjustValue;

/// Interface for a collection of adjustment values.
class IAdjustValueCollection {
public:
    virtual ~IAdjustValueCollection() = default;

    /// Returns the number of adjustment values in the collection.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the adjustment value at the given index.
    [[nodiscard]] virtual AdjustValue& operator[](std::size_t index) = 0;
    [[nodiscard]] virtual const AdjustValue& operator[](std::size_t index) const = 0;

    /// Returns a snapshot of all adjustment values as a vector.
    [[nodiscard]] virtual std::vector<AdjustValue> to_array() const = 0;
};

} // namespace Aspose::Slides::Foss
