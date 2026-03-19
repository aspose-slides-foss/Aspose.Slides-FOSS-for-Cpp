// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/paragraph_collection.h>

#include <Aspose/Slides/Foss/i_base_slide.h>
#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

#include <stdexcept>

namespace Aspose::Slides::Foss {

ParagraphCollection::ParagraphCollection() = default;
ParagraphCollection::~ParagraphCollection() = default;
ParagraphCollection::ParagraphCollection(ParagraphCollection&&) noexcept = default;
ParagraphCollection& ParagraphCollection::operator=(ParagraphCollection&&) noexcept = default;

void ParagraphCollection::init_internal(pugi::xml_node txbody_element,
                                        Internal::pptx::SlidePart* slide_part,
                                        IBaseSlide* parent_slide) {
    txbody_element_ = txbody_element;
    slide_part_ = slide_part;
    slide_ = parent_slide;
    cache_valid_ = false;
    paragraphs_.clear();
}

void ParagraphCollection::load_paragraphs() const {
    if (cache_valid_) return;
    cache_valid_ = true;

    paragraphs_.clear();
    if (!txbody_element_) return;

    for (auto p_elem = txbody_element_.first_child(); p_elem; p_elem = p_elem.next_sibling()) {
        std::string_view name = p_elem.name();
        if (name != Internal::pptx::Elements::kAP && name != "a:p") continue;
        auto para = std::make_unique<Paragraph>();
        para->init_internal(p_elem, txbody_element_, slide_part_, slide_);
        paragraphs_.push_back(std::move(para));
    }
}

std::size_t ParagraphCollection::size() const noexcept {
    load_paragraphs();
    return paragraphs_.size();
}

Paragraph& ParagraphCollection::operator[](std::size_t index) {
    load_paragraphs();
    return *paragraphs_.at(index);
}

const Paragraph& ParagraphCollection::operator[](std::size_t index) const {
    load_paragraphs();
    return *paragraphs_.at(index);
}

Paragraph& ParagraphCollection::add(Paragraph paragraph) {
    load_paragraphs();
    paragraphs_.push_back(std::make_unique<Paragraph>(std::move(paragraph)));
    return *paragraphs_.back();
}

Paragraph& ParagraphCollection::insert(std::size_t index, Paragraph paragraph) {
    load_paragraphs();
    if (index > paragraphs_.size()) {
        throw std::out_of_range("ParagraphCollection::insert index out of range");
    }
    auto it = paragraphs_.insert(
        paragraphs_.begin() + static_cast<std::ptrdiff_t>(index),
        std::make_unique<Paragraph>(std::move(paragraph)));
    return **it;
}

void ParagraphCollection::remove_at(std::size_t index) {
    load_paragraphs();
    if (index >= paragraphs_.size()) {
        throw std::out_of_range("ParagraphCollection::remove_at index out of range");
    }
    paragraphs_.erase(paragraphs_.begin() + static_cast<std::ptrdiff_t>(index));
}

bool ParagraphCollection::remove(const Paragraph& item) {
    load_paragraphs();
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it) {
        if (it->get() == &item) {
            paragraphs_.erase(it);
            return true;
        }
    }
    return false;
}

void ParagraphCollection::clear() noexcept {
    paragraphs_.clear();
    cache_valid_ = true;
}

bool ParagraphCollection::is_read_only() const noexcept {
    return false;
}

std::optional<std::size_t> ParagraphCollection::index_of(const Paragraph& item) const {
    load_paragraphs();
    for (std::size_t i = 0; i < paragraphs_.size(); ++i) {
        if (paragraphs_[i].get() == &item) {
            return i;
        }
    }
    return std::nullopt;
}

bool ParagraphCollection::contains(const Paragraph& item) const {
    return index_of(item).has_value();
}

ISlideComponent* ParagraphCollection::as_i_slide_component() {
    return this;
}

const ISlideComponent* ParagraphCollection::as_i_slide_component() const {
    return this;
}

IParagraphCollection& ParagraphCollection::as_i_enumerable() {
    return *this;
}

const IParagraphCollection& ParagraphCollection::as_i_enumerable() const {
    return *this;
}

IBaseSlide* ParagraphCollection::slide() {
    return slide_;
}

const IBaseSlide* ParagraphCollection::slide() const {
    return slide_;
}

IPresentationComponent* ParagraphCollection::as_i_presentation_component() {
    return this;
}

const IPresentationComponent* ParagraphCollection::as_i_presentation_component() const {
    return this;
}

IPresentation* ParagraphCollection::presentation() {
    return slide_ ? slide_->presentation() : nullptr;
}

const IPresentation* ParagraphCollection::presentation() const {
    return slide_ ? slide_->presentation() : nullptr;
}

void ParagraphCollection::set_slide(IBaseSlide* slide) {
    slide_ = slide;
}

ParagraphCollection::Iterator ParagraphCollection::begin() {
    load_paragraphs();
    return Iterator(paragraphs_.begin());
}

ParagraphCollection::Iterator ParagraphCollection::end() {
    load_paragraphs();
    return Iterator(paragraphs_.end());
}

ParagraphCollection::ConstIterator ParagraphCollection::begin() const {
    load_paragraphs();
    return ConstIterator(paragraphs_.begin());
}

ParagraphCollection::ConstIterator ParagraphCollection::end() const {
    load_paragraphs();
    return ConstIterator(paragraphs_.end());
}

} // namespace Aspose::Slides::Foss
