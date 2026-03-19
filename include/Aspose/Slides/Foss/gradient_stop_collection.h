// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/drawing/color.h>
#include <Aspose/Slides/Foss/gradient_stop.h>
#include <Aspose/Slides/Foss/i_gradient_stop_collection.h>
#include <Aspose/Slides/Foss/preset_color.h>
#include <Aspose/Slides/Foss/scheme_color.h>
#include <pugixml.hpp>

namespace Aspose::Slides::Foss {

/// Represents a collection of gradient stops.
class GradientStopCollection final : public IGradientStopCollection {
public:
    GradientStopCollection() = default;

    // -- XML-backed internal API ------------------------------------------

    /// Initialize XML-backed gradient stop collection.
    /// @param gs_lst_element The \<a:gsLst\> XML element containing gradient stops.
    /// @param save_callback Callback to persist changes (e.g., SlidePart::save).
    void init_internal(pugi::xml_node gs_lst_element,
                       std::function<void()> save_callback);

    /// Save changes via the save callback.
    void save();

    /// Set color on a SimpleColorFormat from a Drawing::Color value.
    static void set_color_from_arg(SimpleColorFormat& cf, const Drawing::Color& color);

    /// Set color on a SimpleColorFormat from a PresetColor value.
    static void set_color_from_arg(SimpleColorFormat& cf, PresetColor preset);

    /// Set color on a SimpleColorFormat from a SchemeColor value.
    static void set_color_from_arg(SimpleColorFormat& cf, SchemeColor scheme);

    // -- Public property API ----------------------------------------------

    /// Returns the number of gradient stops.
    [[nodiscard]] std::size_t size() const noexcept override { return stops_.size(); }

    /// Returns the gradient stop at the given index.
    [[nodiscard]] GradientStop& operator[](std::size_t index) override {
        if (index >= stops_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return stops_[index];
    }
    [[nodiscard]] const GradientStop& operator[](std::size_t index) const {
        if (index >= stops_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return stops_[index];
    }

    /// Adds a gradient stop with the given position and color.
    GradientStop& add(float position, const Drawing::Color& color) {
        stops_.emplace_back(position, color);
        return stops_.back();
    }

    /// Adds a gradient stop with the given position and preset color.
    GradientStop& add(float position, PresetColor preset) {
        stops_.emplace_back(position);
        stops_.back().color().set_preset_color(preset);
        return stops_.back();
    }

    /// Adds a gradient stop with the given position and scheme color.
    GradientStop& add(float position, SchemeColor scheme) {
        stops_.emplace_back(position);
        stops_.back().color().set_scheme_color(scheme);
        return stops_.back();
    }

    /// Inserts a gradient stop at the given index.
    void insert(std::size_t index, float position, const Drawing::Color& color) {
        if (index >= stops_.size()) {
            stops_.emplace_back(position, color);
        } else {
            stops_.emplace(stops_.begin() + static_cast<std::ptrdiff_t>(index),
                           position, color);
        }
    }

    /// Inserts a gradient stop with a preset color at the given index.
    void insert(std::size_t index, float position, PresetColor preset) {
        GradientStop stop(position);
        stop.color().set_preset_color(preset);
        if (index >= stops_.size()) {
            stops_.push_back(std::move(stop));
        } else {
            stops_.insert(stops_.begin() + static_cast<std::ptrdiff_t>(index),
                          std::move(stop));
        }
    }

    /// Inserts a gradient stop with a scheme color at the given index.
    void insert(std::size_t index, float position, SchemeColor scheme) {
        GradientStop stop(position);
        stop.color().set_scheme_color(scheme);
        if (index >= stops_.size()) {
            stops_.push_back(std::move(stop));
        } else {
            stops_.insert(stops_.begin() + static_cast<std::ptrdiff_t>(index),
                          std::move(stop));
        }
    }

    /// Removes the gradient stop at the given index.
    void remove_at(std::size_t index) {
        if (index < stops_.size()) {
            stops_.erase(stops_.begin() + static_cast<std::ptrdiff_t>(index));
        }
    }

    /// Removes all gradient stops.
    void clear() noexcept { stops_.clear(); }

    /// Returns all gradient stops as a vector.
    [[nodiscard]] std::vector<GradientStop> as_i_collection() const { return stops_; }

    /// Returns all gradient stops as a vector (same as as_i_collection).
    [[nodiscard]] std::vector<GradientStop> as_i_enumerable() const { return stops_; }

    // Range-based for loop support.
    using iterator = std::vector<GradientStop>::iterator;
    using const_iterator = std::vector<GradientStop>::const_iterator;
    [[nodiscard]] iterator begin() noexcept { return stops_.begin(); }
    [[nodiscard]] iterator end() noexcept { return stops_.end(); }
    [[nodiscard]] const_iterator begin() const noexcept { return stops_.begin(); }
    [[nodiscard]] const_iterator end() const noexcept { return stops_.end(); }

private:
    std::vector<GradientStop> stops_;
    pugi::xml_node gs_lst_;
    std::function<void()> save_callback_;
};

} // namespace Aspose::Slides::Foss
