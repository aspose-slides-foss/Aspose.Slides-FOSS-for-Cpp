// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/comment_author_collection.h>

#include <algorithm>
#include <stdexcept>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/pptx/comment_authors_part.h>
#include <Aspose/Slides/Foss/comment_author.h>

namespace Aspose::Slides::Foss {

namespace pptx = Internal::pptx;

CommentAuthorCollection::CommentAuthorCollection() = default;
CommentAuthorCollection::~CommentAuthorCollection() = default;
CommentAuthorCollection::CommentAuthorCollection(CommentAuthorCollection&&) noexcept = default;
CommentAuthorCollection& CommentAuthorCollection::operator=(CommentAuthorCollection&&) noexcept = default;

void CommentAuthorCollection::init_internal(
    pptx::CommentAuthorsPart& authors_part,
    Internal::opc::OpcPackage& package,
    Presentation* presentation) {
    authors_part_ = &authors_part;
    package_ = &package;
    presentation_ = presentation;

    // Populate the in-memory collection from the XML-backed data.
    authors_.clear();
    for (auto& data : authors_part_->get_authors()) {
        authors_.push_back(build_author(data));
    }
}

std::unique_ptr<CommentAuthor> CommentAuthorCollection::build_author(
    pptx::AuthorData data) {
    auto ca = std::make_unique<CommentAuthor>(data.name(), data.initials());
    ca->init_internal(data, *authors_part_, *package_, presentation_);
    ca->owner_ = this;
    return ca;
}

CommentAuthor& CommentAuthorCollection::add_author(
    const std::string& name, const std::string& initials) {
    if (authors_part_) {
        auto data = authors_part_->add_author(name, initials);
        authors_.push_back(build_author(data));
    } else {
        authors_.push_back(std::make_unique<CommentAuthor>(name, initials));
        authors_.back()->owner_ = this;
    }
    return *authors_.back();
}

std::vector<CommentAuthor*> CommentAuthorCollection::to_array() {
    std::vector<CommentAuthor*> result;
    result.reserve(authors_.size());
    for (auto& a : authors_) {
        result.push_back(a.get());
    }
    return result;
}

std::vector<const CommentAuthor*> CommentAuthorCollection::to_array() const {
    std::vector<const CommentAuthor*> result;
    result.reserve(authors_.size());
    for (auto& a : authors_) {
        result.push_back(a.get());
    }
    return result;
}

std::vector<CommentAuthor*> CommentAuthorCollection::find_by_name(
    const std::string& name) {
    std::vector<CommentAuthor*> result;
    for (auto& a : authors_) {
        if (a->name() == name) {
            result.push_back(a.get());
        }
    }
    return result;
}

std::vector<CommentAuthor*> CommentAuthorCollection::find_by_name_and_initials(
    const std::string& name, const std::string& initials) {
    std::vector<CommentAuthor*> result;
    for (auto& a : authors_) {
        if (a->name() == name && a->initials() == initials) {
            result.push_back(a.get());
        }
    }
    return result;
}

void CommentAuthorCollection::remove_at(std::size_t index) {
    if (index < authors_.size()) {
        authors_[index]->comments().clear();
        if (authors_part_ && authors_[index]->has_internal_data()) {
            authors_part_->remove_author(authors_[index]->internal_data()->id());
        }
        authors_.erase(authors_.begin() + static_cast<std::ptrdiff_t>(index));
    }
}

void CommentAuthorCollection::remove(CommentAuthor& author) {
    auto it = std::ranges::find_if(
        authors_,
        [&author](const auto& ptr) { return ptr.get() == &author; });
    if (it != authors_.end()) {
        (*it)->comments().clear();
        if (authors_part_ && (*it)->has_internal_data()) {
            authors_part_->remove_author((*it)->internal_data()->id());
        }
        authors_.erase(it);
    }
}

void CommentAuthorCollection::clear() {
    for (auto& a : authors_) {
        a->comments().clear();
    }
    if (authors_part_) {
        authors_part_->clear();
    }
    authors_.clear();
}

std::size_t CommentAuthorCollection::size() const noexcept {
    return authors_.size();
}

CommentAuthor& CommentAuthorCollection::operator[](std::size_t index) {
    if (index >= authors_.size()) {
        throw std::out_of_range(
            "Index " + std::to_string(index) + " out of range");
    }
    return *authors_[index];
}

const CommentAuthor& CommentAuthorCollection::operator[](
    std::size_t index) const {
    if (index >= authors_.size()) {
        throw std::out_of_range(
            "Index " + std::to_string(index) + " out of range");
    }
    return *authors_[index];
}

} // namespace Aspose::Slides::Foss
