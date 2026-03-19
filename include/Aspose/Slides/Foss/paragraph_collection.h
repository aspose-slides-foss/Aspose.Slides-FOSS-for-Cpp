// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include <pugixml.hpp>

#include <Aspose/Slides/Foss/i_paragraph_collection.h>
#include <Aspose/Slides/Foss/paragraph.h>

namespace Aspose::Slides::Foss::Internal::pptx { class SlidePart; }

namespace Aspose::Slides::Foss {

/// Manages a collection of paragraphs within a text frame.
class ParagraphCollection final : public IParagraphCollection {
public:
    ParagraphCollection();
    ParagraphCollection(const ParagraphCollection&) = delete;
    ParagraphCollection& operator=(const ParagraphCollection&) = delete;
    ~ParagraphCollection() override;
    ParagraphCollection(ParagraphCollection&&) noexcept;
    ParagraphCollection& operator=(ParagraphCollection&&) noexcept;

    /// Initialize from XML, entering XML-backed mode.
    /// @param txbody_element The `<a:txBody>` XML node containing `<a:p>` children.
    /// @param slide_part The SlidePart containing the slide XML. May be nullptr.
    /// @param parent_slide The parent slide object. May be nullptr.
    void init_internal(pugi::xml_node txbody_element,
                       Internal::pptx::SlidePart* slide_part,
                       IBaseSlide* parent_slide);

    /// Returns the number of paragraphs.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the paragraph at the given index.
    [[nodiscard]] Paragraph& operator[](std::size_t index) override;
    [[nodiscard]] const Paragraph& operator[](std::size_t index) const override;

    /// Adds a paragraph to the end of the collection.
    Paragraph& add(Paragraph paragraph) override;

    /// Inserts a paragraph at the given index.
    Paragraph& insert(std::size_t index, Paragraph paragraph) override;

    /// Removes the paragraph at the given index.
    void remove_at(std::size_t index) override;

    /// Removes the given paragraph from the collection.
    /// @return true if the paragraph was found and removed.
    bool remove(const Paragraph& item) override;

    /// Removes all paragraphs.
    void clear() noexcept override;

    /// Returns whether the collection is read-only (always false).
    [[nodiscard]] bool is_read_only() const noexcept override;

    /// Returns the index of the given paragraph, or std::nullopt if not found.
    [[nodiscard]] std::optional<std::size_t> index_of(const Paragraph& item) const override;

    /// Returns whether the collection contains the given paragraph.
    [[nodiscard]] bool contains(const Paragraph& item) const override;

    /// Allows to get base ISlideComponent interface. Read-only.
    [[nodiscard]] ISlideComponent* as_i_slide_component() override;
    [[nodiscard]] const ISlideComponent* as_i_slide_component() const override;

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] IParagraphCollection& as_i_enumerable() override;
    [[nodiscard]] const IParagraphCollection& as_i_enumerable() const override;

    // -- ISlideComponent --
    [[nodiscard]] IBaseSlide* slide() override;
    [[nodiscard]] const IBaseSlide* slide() const override;
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    // -- IPresentationComponent --
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    /// Sets the parent slide for this collection.
    void set_slide(IBaseSlide* slide);

    /// Iterator support for range-based for loops.
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Paragraph;
        using difference_type = std::ptrdiff_t;
        using pointer = Paragraph*;
        using reference = Paragraph&;

        Iterator() = default;
        explicit Iterator(std::vector<std::unique_ptr<Paragraph>>::iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        Iterator& operator++() { ++it_; return *this; }
        Iterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return it_ != other.it_; }

    private:
        std::vector<std::unique_ptr<Paragraph>>::iterator it_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const Paragraph;
        using difference_type = std::ptrdiff_t;
        using pointer = const Paragraph*;
        using reference = const Paragraph&;

        ConstIterator() = default;
        explicit ConstIterator(std::vector<std::unique_ptr<Paragraph>>::const_iterator it) : it_(it) {}

        reference operator*() const { return **it_; }
        pointer operator->() const { return it_->get(); }
        ConstIterator& operator++() { ++it_; return *this; }
        ConstIterator operator++(int) { auto tmp = *this; ++it_; return tmp; }
        bool operator==(const ConstIterator& other) const { return it_ == other.it_; }
        bool operator!=(const ConstIterator& other) const { return it_ != other.it_; }

    private:
        std::vector<std::unique_ptr<Paragraph>>::const_iterator it_;
    };

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

private:
    /// Ensures paragraphs are loaded from XML when in XML-backed mode.
    void load_paragraphs() const;

    mutable std::vector<std::unique_ptr<Paragraph>> paragraphs_;
    IBaseSlide* slide_ = nullptr;
    pugi::xml_node txbody_element_;
    Internal::pptx::SlidePart* slide_part_ = nullptr;
    mutable bool cache_valid_ = true;
};

} // namespace Aspose::Slides::Foss
