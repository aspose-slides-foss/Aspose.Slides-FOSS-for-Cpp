// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <optional>

namespace Aspose::Slides::Foss {

class Portion;

/// Interface for a collection of text portions.
class IPortionCollection {
public:
    virtual ~IPortionCollection() = default;

    /// Returns the number of portions.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the number of portions (alias for size()).
    [[nodiscard]] virtual std::size_t count() const = 0;

    /// Returns whether the collection is read-only.
    [[nodiscard]] virtual bool is_read_only() const noexcept = 0;

    /// Returns the portion at the given index.
    [[nodiscard]] virtual Portion& operator[](std::size_t index) = 0;

    /// Returns the portion at the given index (const).
    [[nodiscard]] virtual const Portion& operator[](std::size_t index) const = 0;

    /// Adds a portion to the end of the collection.
    virtual Portion& add(Portion portion) = 0;

    /// Returns the index of the given portion, or std::nullopt if not found.
    [[nodiscard]] virtual std::optional<std::size_t> index_of(const Portion& item) const = 0;

    /// Inserts a portion at the given index.
    virtual Portion& insert(std::size_t index, Portion portion) = 0;

    /// Removes all portions.
    virtual void clear() = 0;

    /// Returns true if the collection contains the given portion.
    [[nodiscard]] virtual bool contains(const Portion& item) const = 0;

    /// Removes the given portion from the collection.
    /// @return true if the portion was found and removed.
    virtual bool remove(const Portion& item) = 0;

    /// Removes the portion at the given index.
    virtual void remove_at(std::size_t index) = 0;

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] virtual IPortionCollection& as_i_enumerable() = 0;
    [[nodiscard]] virtual const IPortionCollection& as_i_enumerable() const = 0;

protected:
    IPortionCollection() = default;
};

} // namespace Aspose::Slides::Foss
