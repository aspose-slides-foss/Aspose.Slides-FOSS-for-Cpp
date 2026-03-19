// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Aspose/Slides/Foss/i_layout_slide.h>
#include <Aspose/Slides/Foss/i_layout_slide_collection.h>
#include <Aspose/Slides/Foss/slide_layout_type.h>

namespace Aspose::Slides::Foss {

class LayoutSlide;

/// Manages a collection of layout slides belonging to a master slide.
class LayoutSlideCollection : public virtual ILayoutSlideCollection {
public:
    LayoutSlideCollection() = default;
    ~LayoutSlideCollection() override = default;
    LayoutSlideCollection(LayoutSlideCollection&&) noexcept = default;
    LayoutSlideCollection& operator=(LayoutSlideCollection&&) noexcept = default;

    /// Returns the number of layout slides.
    [[nodiscard]] std::size_t size() const noexcept override {
        return slides_.size();
    }

    /// Returns the layout slide at the given index.
    [[nodiscard]] ILayoutSlide& operator[](std::size_t index) override {
        if (index >= slides_.size())
            throw std::out_of_range("LayoutSlideCollection index out of range");
        return *slides_[index];
    }

    [[nodiscard]] const ILayoutSlide& operator[](std::size_t index) const override {
        if (index >= slides_.size())
            throw std::out_of_range("LayoutSlideCollection index out of range");
        return *slides_[index];
    }

    /// Returns a non-owning snapshot of all layout slides as a vector.
    [[nodiscard]] std::vector<ILayoutSlide*> as_i_collection() override {
        std::vector<ILayoutSlide*> result;
        result.reserve(slides_.size());
        for (auto& s : slides_)
            result.push_back(s.get());
        return result;
    }

    /// Returns a non-owning snapshot of all layout slides (const) as a vector.
    [[nodiscard]] std::vector<const ILayoutSlide*> as_i_enumerable() const override {
        std::vector<const ILayoutSlide*> result;
        result.reserve(slides_.size());
        for (auto& s : slides_)
            result.push_back(s.get());
        return result;
    }

    /// Finds the first layout slide matching the given type, or nullptr if none.
    [[nodiscard]] ILayoutSlide* get_by_type(SlideLayoutType type) override {
        for (auto& s : slides_) {
            if (s->layout_type() == type)
                return s.get();
        }
        return nullptr;
    }

    /// Adds a layout slide to the collection. Takes ownership.
    void add(std::unique_ptr<ILayoutSlide> slide) {
        slides_.push_back(std::move(slide));
    }

private:
    std::vector<std::unique_ptr<ILayoutSlide>> slides_;
};

} // namespace Aspose::Slides::Foss
