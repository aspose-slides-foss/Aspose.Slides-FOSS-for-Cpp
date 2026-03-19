// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/adjust_value.h>
#include <Aspose/Slides/Foss/i_adjust_value_collection.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Represents a collection of shape's adjustments.
///
/// The collection can operate in two modes:
///   - **Manual mode**: values added via add(). Used for programmatic construction.
///   - **XML-backed mode**: after init_internal() is called, the collection reads
///     `<a:gd>` child elements from the backing `<a:avLst>` XML node.
class AdjustValueCollection final : public IAdjustValueCollection {
public:
    AdjustValueCollection() = default;

    /// Initialize this collection from an XML `<a:avLst>` element.
    /// Populates the internal storage from child `<a:gd>` elements.
    /// @param av_lst_element The XML node for the avLst element. May be null.
    /// @param slide_part The owning SlidePart. May be nullptr.
    void init_internal(pugi::xml_node av_lst_element,
                       Internal::pptx::SlidePart* slide_part);

    /// Returns the `<a:gd>` child elements of the backing avLst node.
    /// Returns an empty vector if the collection is not XML-backed or the node is null.
    [[nodiscard]] std::vector<pugi::xml_node> get_gd_elements() const;

    /// Returns the number of adjustment values.
    [[nodiscard]] std::size_t size() const noexcept override { return values_.size(); }

    /// Returns the adjustment value at the given index.
    [[nodiscard]] AdjustValue& operator[](std::size_t index) override {
        return values_.at(index);
    }
    [[nodiscard]] const AdjustValue& operator[](std::size_t index) const override {
        return values_.at(index);
    }

    /// Returns a snapshot of all adjustment values as a vector.
    [[nodiscard]] std::vector<AdjustValue> to_array() const override {
        return values_;
    }

    /// Adds an adjustment value to the collection.
    void add(AdjustValue value) { values_.push_back(std::move(value)); }

    /// Removes all adjustment values.
    void clear() noexcept { values_.clear(); }

    // Range-based for loop support.
    using iterator = std::vector<AdjustValue>::iterator;
    using const_iterator = std::vector<AdjustValue>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return values_.begin(); }
    [[nodiscard]] iterator end() noexcept { return values_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return values_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return values_.end(); }

private:
    std::vector<AdjustValue> values_;
    pugi::xml_node av_lst_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
};

} // namespace Aspose::Slides::Foss
