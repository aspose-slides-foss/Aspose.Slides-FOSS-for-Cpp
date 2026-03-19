// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/i_master_layout_slide_collection.h>
#include <Aspose/Slides/Foss/layout_slide_collection.h>

namespace Aspose::Slides::Foss {

class LayoutSlide;

/// Represents a collection of all layout slides of a defined master slide.
///
/// Extends LayoutSlideCollection with methods for adding/inserting/removing/
/// cloning/reordering layout slides in the context of the individual
/// collections of master's layout slides.
class MasterLayoutSlideCollection final
    : public LayoutSlideCollection,
      public IMasterLayoutSlideCollection {
public:
    MasterLayoutSlideCollection() = default;
    ~MasterLayoutSlideCollection() override = default;
    MasterLayoutSlideCollection(MasterLayoutSlideCollection&&) noexcept = default;
    MasterLayoutSlideCollection& operator=(MasterLayoutSlideCollection&&) noexcept = default;

    /// Internal initialization with a list of non-owning layout slide pointers.
    void init_internal(std::vector<ILayoutSlide*> layouts) {
        layouts_ = std::move(layouts);
    }

    /// Returns the number of layout slides.
    [[nodiscard]] std::size_t size() const noexcept override {
        return layouts_.size();
    }

    /// Returns the layout slide at the given index.
    [[nodiscard]] ILayoutSlide& operator[](std::size_t index) override {
        if (index >= layouts_.size())
            throw std::out_of_range("MasterLayoutSlideCollection index out of range");
        return *layouts_[index];
    }

    [[nodiscard]] const ILayoutSlide& operator[](std::size_t index) const override {
        if (index >= layouts_.size())
            throw std::out_of_range("MasterLayoutSlideCollection index out of range");
        return *layouts_[index];
    }

    /// Returns a non-owning snapshot of all layout slides as a vector.
    [[nodiscard]] std::vector<ILayoutSlide*> as_i_collection() override {
        return layouts_;
    }

    /// Returns a non-owning snapshot of all layout slides (const) as a vector.
    [[nodiscard]] std::vector<const ILayoutSlide*> as_i_enumerable() const override {
        return {layouts_.begin(), layouts_.end()};
    }

    /// Finds the first layout slide matching the given type, or nullptr if none.
    [[nodiscard]] ILayoutSlide* get_by_type(SlideLayoutType type) override {
        for (auto* s : layouts_) {
            if (s->layout_type() == type)
                return s;
        }
        return nullptr;
    }

    /// Adds a non-owning reference to a layout slide.
    void add(ILayoutSlide* layout) { layouts_.push_back(layout); }

    // Iterator support for range-based for loops.
    class iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = ILayoutSlide;
        using pointer = ILayoutSlide*;
        using reference = ILayoutSlide&;
        using iterator_category = std::random_access_iterator_tag;

        iterator() = default;
        explicit iterator(std::vector<ILayoutSlide*>::iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return *it_; }
        iterator& operator++() { ++it_; return *this; }
        iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        iterator& operator--() { --it_; return *this; }
        iterator operator--(int) { auto tmp = *this; --it_; return tmp; }
        bool operator==(const iterator& other) const = default;

    private:
        std::vector<ILayoutSlide*>::iterator it_;
    };

    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const ILayoutSlide;
        using pointer = const ILayoutSlide*;
        using reference = const ILayoutSlide&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() = default;
        explicit const_iterator(std::vector<ILayoutSlide*>::const_iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return *it_; }
        const_iterator& operator++() { ++it_; return *this; }
        const_iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        const_iterator& operator--() { --it_; return *this; }
        const_iterator operator--(int) { auto tmp = *this; --it_; return tmp; }
        bool operator==(const const_iterator& other) const = default;

    private:
        std::vector<ILayoutSlide*>::const_iterator it_;
    };

    [[nodiscard]] iterator begin() noexcept { return iterator(layouts_.begin()); }
    [[nodiscard]] iterator end() noexcept { return iterator(layouts_.end()); }
    [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(layouts_.begin()); }
    [[nodiscard]] const_iterator end() const noexcept { return const_iterator(layouts_.end()); }
    [[nodiscard]] const_iterator cbegin() const noexcept { return const_iterator(layouts_.cbegin()); }
    [[nodiscard]] const_iterator cend() const noexcept { return const_iterator(layouts_.cend()); }

private:
    std::vector<ILayoutSlide*> layouts_;
};

} // namespace Aspose::Slides::Foss
