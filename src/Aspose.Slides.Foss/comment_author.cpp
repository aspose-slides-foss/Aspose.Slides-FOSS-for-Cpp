// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/comment_author.h>

#include <memory>
#include <utility>

#include <Aspose/Slides/Foss/_internal/opc/opc_package.h>
#include <Aspose/Slides/Foss/_internal/pptx/comment_authors_part.h>
#include <Aspose/Slides/Foss/comment_author_collection.h>

namespace Aspose::Slides::Foss {

CommentAuthor::CommentAuthor(std::string name, std::string initials)
    : name_(std::move(name)),
      initials_(std::move(initials)),
      comments_(this) {}

void CommentAuthor::init_internal(
    Internal::pptx::AuthorData data,
    Internal::pptx::CommentAuthorsPart& authors_part,
    Internal::opc::OpcPackage& package,
    Presentation* presentation) {
    data_ = std::make_unique<Internal::pptx::AuthorData>(data);
    authors_part_ = &authors_part;
    package_ = &package;
    presentation_ = presentation;

    // Sync the cached strings from the XML-backed data.
    name_ = data_->name();
    initials_ = data_->initials();
}

const std::string& CommentAuthor::name() const noexcept {
    return name_;
}

void CommentAuthor::set_name(std::string value) {
    name_ = std::move(value);
    if (data_) {
        data_->set_name(name_);
    }
}

const std::string& CommentAuthor::initials() const noexcept {
    return initials_;
}

void CommentAuthor::set_initials(std::string value) {
    initials_ = std::move(value);
    if (data_) {
        data_->set_initials(initials_);
    }
}

CommentCollection& CommentAuthor::comments() noexcept { return comments_; }
const CommentCollection& CommentAuthor::comments() const noexcept {
    return comments_;
}

void CommentAuthor::remove() {
    comments_.clear();
    if (owner_) {
        owner_->remove(*this);
    }
}

bool CommentAuthor::has_internal_data() const noexcept {
    return data_ != nullptr;
}

Internal::pptx::AuthorData* CommentAuthor::internal_data() noexcept {
    return data_.get();
}

Internal::pptx::CommentAuthorsPart* CommentAuthor::authors_part() noexcept {
    return authors_part_;
}

Internal::opc::OpcPackage* CommentAuthor::package() noexcept {
    return package_;
}

Presentation* CommentAuthor::presentation() noexcept {
    return presentation_;
}

} // namespace Aspose::Slides::Foss
