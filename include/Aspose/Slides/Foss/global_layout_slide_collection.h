// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/i_global_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide.h>
#include <Aspose/Slides/Foss/layout_slide_collection.h>

namespace Aspose::Slides::Foss {

/// Represents a collection of all layout slides in a presentation.
/// Extends LayoutSlideCollection with methods for adding/cloning layout slides
/// in the context of uniting the individual collections of master's layout slides.
class GlobalLayoutSlideCollection final
    : public LayoutSlideCollection,
      public IGlobalLayoutSlideCollection {
public:
    GlobalLayoutSlideCollection() {
        // A new presentation starts with one default layout slide.
        layouts_.push_back(std::make_unique<LayoutSlide>());
    }
    ~GlobalLayoutSlideCollection() override = default;
    GlobalLayoutSlideCollection(GlobalLayoutSlideCollection&&) noexcept = default;
    GlobalLayoutSlideCollection& operator=(GlobalLayoutSlideCollection&&) noexcept = default;

    /// Internal initialization with a list of all layout slides.
    void init_internal(std::vector<std::unique_ptr<LayoutSlide>> layouts) {
        layouts_ = std::move(layouts);
    }

    /// Returns this collection viewed as an ILayoutSlideCollection.
    [[nodiscard]] ILayoutSlideCollection& as_i_layout_slide_collection() noexcept override {
        return *this;
    }
    /// Returns this collection viewed as an ILayoutSlideCollection (const).
    [[nodiscard]] const ILayoutSlideCollection& as_i_layout_slide_collection() const noexcept override {
        return *this;
    }

    /// Returns the number of layout slides.
    [[nodiscard]] std::size_t size() const noexcept override { return layouts_.size(); }

    /// Returns the layout slide at the given index.
    [[nodiscard]] LayoutSlide& operator[](std::size_t index) {
        return *layouts_.at(index);
    }
    [[nodiscard]] const LayoutSlide& operator[](std::size_t index) const {
        return *layouts_.at(index);
    }

    /// Creates a new layout slide, adds it to the collection, and returns a reference.
    LayoutSlide& add(std::unique_ptr<LayoutSlide> layout) {
        auto& ref = *layout;
        layouts_.push_back(std::move(layout));
        return ref;
    }

    // Iterator support for range-based for loops.
    class iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = LayoutSlide;
        using pointer = LayoutSlide*;
        using reference = LayoutSlide&;
        using iterator_category = std::random_access_iterator_tag;

        iterator() = default;
        explicit iterator(std::vector<std::unique_ptr<LayoutSlide>>::iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        iterator& operator++() { ++it_; return *this; }
        iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        iterator& operator--() { --it_; return *this; }
        iterator operator--(int) { auto tmp = *this; --it_; return tmp; }
        bool operator==(const iterator& other) const = default;

    private:
        std::vector<std::unique_ptr<LayoutSlide>>::iterator it_;
    };

    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const LayoutSlide;
        using pointer = const LayoutSlide*;
        using reference = const LayoutSlide&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() = default;
        explicit const_iterator(std::vector<std::unique_ptr<LayoutSlide>>::const_iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        const_iterator& operator++() { ++it_; return *this; }
        const_iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        const_iterator& operator--() { --it_; return *this; }
        const_iterator operator--(int) { auto tmp = *this; --it_; return tmp; }
        bool operator==(const const_iterator& other) const = default;

    private:
        std::vector<std::unique_ptr<LayoutSlide>>::const_iterator it_;
    };

    [[nodiscard]] iterator begin() noexcept { return iterator(layouts_.begin()); }
    [[nodiscard]] iterator end() noexcept { return iterator(layouts_.end()); }
    [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(layouts_.begin()); }
    [[nodiscard]] const_iterator end() const noexcept { return const_iterator(layouts_.end()); }
    [[nodiscard]] const_iterator cbegin() const noexcept { return const_iterator(layouts_.cbegin()); }
    [[nodiscard]] const_iterator cend() const noexcept { return const_iterator(layouts_.cend()); }

private:
    std::vector<std::unique_ptr<LayoutSlide>> layouts_;
};

} // namespace Aspose::Slides::Foss
