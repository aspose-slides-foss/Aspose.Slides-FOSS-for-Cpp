// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/portion_collection.h>

#include <Aspose/Slides/Foss/_internal/pptx/constants.h>

#include <algorithm>
#include <stdexcept>

namespace Aspose::Slides::Foss {

PortionCollection::PortionCollection() = default;
PortionCollection::~PortionCollection() = default;
PortionCollection::PortionCollection(PortionCollection&&) noexcept = default;
PortionCollection& PortionCollection::operator=(PortionCollection&&) noexcept = default;

void PortionCollection::init_internal(pugi::xml_node p_element,
                                      pugi::xml_node txbody_element,
                                      Internal::pptx::SlidePart* slide_part,
                                      IBaseSlide* parent_slide) {
    p_element_ = p_element;
    txbody_element_ = txbody_element;
    slide_part_ = slide_part;
    parent_slide_ = parent_slide;
    cache_valid_ = false;
    portions_.clear();
}

void PortionCollection::load_portions() const {
    if (cache_valid_) return;
    cache_valid_ = true;

    portions_.clear();
    if (!p_element_) return;

    for (auto r_elem = p_element_.first_child(); r_elem; r_elem = r_elem.next_sibling()) {
        std::string_view name = r_elem.name();
        if (name != Internal::pptx::Elements::kAR && name != "a:r") continue;
        auto portion = std::make_unique<Portion>();
        portion->init_internal(r_elem, p_element_, txbody_element_, slide_part_, parent_slide_);
        // Extract text from <a:t> children.
        std::string text;
        for (auto sub = r_elem.first_child(); sub; sub = sub.next_sibling()) {
            std::string_view sub_name = sub.name();
            if (sub_name == "a:t" || sub_name == Internal::pptx::Elements::kAT) {
                text += sub.text().as_string("");
            }
        }
        portion->set_text(std::move(text));
        portions_.push_back(std::move(portion));
    }
}

std::size_t PortionCollection::size() const noexcept {
    load_portions();
    return portions_.size();
}

std::size_t PortionCollection::count() const noexcept {
    load_portions();
    return portions_.size();
}

bool PortionCollection::is_read_only() const noexcept {
    return false;
}

Portion& PortionCollection::operator[](std::size_t index) {
    load_portions();
    return *portions_.at(index);
}

const Portion& PortionCollection::operator[](std::size_t index) const {
    load_portions();
    return *portions_.at(index);
}

Portion& PortionCollection::add(Portion portion) {
    load_portions();
    portions_.push_back(std::make_unique<Portion>(std::move(portion)));
    return *portions_.back();
}

std::optional<std::size_t> PortionCollection::index_of(const Portion& item) const {
    load_portions();
    for (std::size_t i = 0; i < portions_.size(); ++i) {
        if (portions_[i].get() == &item) {
            return i;
        }
    }
    return std::nullopt;
}

Portion& PortionCollection::insert(std::size_t index, Portion portion) {
    load_portions();
    if (index > portions_.size()) {
        throw std::out_of_range("PortionCollection::insert index out of range");
    }
    auto it = portions_.insert(
        portions_.begin() + static_cast<std::ptrdiff_t>(index),
        std::make_unique<Portion>(std::move(portion)));
    return **it;
}

void PortionCollection::clear() noexcept {
    portions_.clear();
    cache_valid_ = true;
}

bool PortionCollection::contains(const Portion& item) const {
    return index_of(item).has_value();
}

bool PortionCollection::remove(const Portion& item) {
    load_portions();
    for (auto it = portions_.begin(); it != portions_.end(); ++it) {
        if (it->get() == &item) {
            portions_.erase(it);
            return true;
        }
    }
    return false;
}

void PortionCollection::remove_at(std::size_t index) {
    load_portions();
    if (index >= portions_.size()) {
        throw std::out_of_range("PortionCollection::remove_at index out of range");
    }
    portions_.erase(portions_.begin() + static_cast<std::ptrdiff_t>(index));
}

IPortionCollection& PortionCollection::as_i_enumerable() {
    return *this;
}

const IPortionCollection& PortionCollection::as_i_enumerable() const {
    return *this;
}

PortionCollection::Iterator PortionCollection::begin() {
    load_portions();
    return Iterator(portions_.begin());
}

PortionCollection::Iterator PortionCollection::end() {
    load_portions();
    return Iterator(portions_.end());
}

PortionCollection::ConstIterator PortionCollection::begin() const {
    load_portions();
    return ConstIterator(portions_.begin());
}

PortionCollection::ConstIterator PortionCollection::end() const {
    load_portions();
    return ConstIterator(portions_.end());
}

} // namespace Aspose::Slides::Foss
