// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_portion_collection.h>
#include <Aspose/Slides/Foss/portion.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Manages a collection of text portions within a paragraph.
class PortionCollection final : public IPortionCollection {
public:
    PortionCollection();
    PortionCollection(const PortionCollection&) = delete;
    PortionCollection& operator=(const PortionCollection&) = delete;
    ~PortionCollection() override;
    PortionCollection(PortionCollection&&) noexcept;
    PortionCollection& operator=(PortionCollection&&) noexcept;

    /// Initialize from XML, entering XML-backed mode.
    /// @param p_element The `<a:p>` XML node containing `<a:r>` children.
    /// @param txbody_element The `<a:txBody>` XML node that contains the paragraph.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node p_element,
                       pugi::xml_node txbody_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Returns the number of portions.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the number of portions (alias for size()).
    [[nodiscard]] std::size_t count() const noexcept override;

    /// Returns whether the collection is read-only.
    [[nodiscard]] bool is_read_only() const noexcept override;

    /// Returns the portion at the given index.
    [[nodiscard]] Portion& operator[](std::size_t index) override;
    [[nodiscard]] const Portion& operator[](std::size_t index) const override;

    /// Adds a portion to the end of the collection.
    Portion& add(Portion portion) override;

    /// Returns the index of the given portion, or std::nullopt if not found.
    [[nodiscard]] std::optional<std::size_t> index_of(const Portion& item) const override;

    /// Inserts a portion at the given index.
    Portion& insert(std::size_t index, Portion portion) override;

    /// Removes all portions.
    void clear() noexcept override;

    /// Returns true if the collection contains the given portion.
    [[nodiscard]] bool contains(const Portion& item) const override;

    /// Removes the given portion from the collection.
    /// @return true if the portion was found and removed.
    bool remove(const Portion& item) override;

    /// Removes the portion at the given index.
    void remove_at(std::size_t index) override;

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] IPortionCollection& as_i_enumerable() override;
    [[nodiscard]] const IPortionCollection& as_i_enumerable() const override;

    /// Iterator support for range-based for loops.
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Portion;
        using difference_type = std::ptrdiff_t;
        using pointer = Portion*;
        using reference = Portion&;

        Iterator() = default;
        explicit Iterator(std::vector<std::unique_ptr<Portion>>::iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        Iterator& operator++() { ++it_; return *this; }
        Iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return it_ != other.it_; }

    private:
        std::vector<std::unique_ptr<Portion>>::iterator it_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const Portion;
        using difference_type = std::ptrdiff_t;
        using pointer = const Portion*;
        using reference = const Portion&;

        ConstIterator() = default;
        explicit ConstIterator(std::vector<std::unique_ptr<Portion>>::const_iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        ConstIterator& operator++() { ++it_; return *this; }
        ConstIterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        bool operator==(const ConstIterator& other) const { return it_ == other.it_; }
        bool operator!=(const ConstIterator& other) const { return it_ != other.it_; }

    private:
        std::vector<std::unique_ptr<Portion>>::const_iterator it_;
    };

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

private:
    /// Ensures portions are loaded from XML when in XML-backed mode.
    void load_portions() const;

    mutable std::vector<std::unique_ptr<Portion>> portions_;
    pugi::xml_node p_element_;
    pugi::xml_node txbody_element_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    IBaseSlide* parent_slide_ = nullptr;
    mutable bool cache_valid_ = true;
};

} // namespace Aspose::Slides::Foss
