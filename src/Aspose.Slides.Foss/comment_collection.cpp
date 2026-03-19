// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/comment_collection.h>

#include <algorithm>
#include <stdexcept>

#include <Aspose/Slides/Foss/comment.h>

namespace Aspose::Slides::Foss {

CommentCollection::CommentCollection(CommentAuthor* author) noexcept
    : author_(author) {}

CommentCollection::~CommentCollection() = default;
CommentCollection::CommentCollection(CommentCollection&&) noexcept = default;
CommentCollection& CommentCollection::operator=(CommentCollection&&) noexcept = default;

Comment& CommentCollection::add_comment(
    const std::string& text, Slide& slide, Drawing::PointF position,
    std::chrono::system_clock::time_point created_time) {
    auto comment =
        std::make_unique<Comment>(text, &slide, author_, position, created_time);
    comment->owner_ = this;
    comment->idx_ = next_idx_++;
    comments_.push_back(std::move(comment));
    return *comments_.back();
}

Comment& CommentCollection::insert_comment(
    std::size_t index, const std::string& text, Slide& slide,
    Drawing::PointF position,
    std::chrono::system_clock::time_point created_time) {
    if (index > comments_.size()) {
        throw std::out_of_range("CommentCollection::insert_comment: index out of range");
    }
    auto comment =
        std::make_unique<Comment>(text, &slide, author_, position, created_time);
    comment->owner_ = this;
    comment->idx_ = next_idx_++;
    auto it = comments_.begin() + static_cast<std::ptrdiff_t>(index);
    it = comments_.insert(it, std::move(comment));
    return **it;
}

void CommentCollection::remove_at(std::size_t index) {
    if (index >= comments_.size()) {
        throw std::out_of_range("CommentCollection::remove_at: index out of range");
    }
    comments_.erase(comments_.begin() + static_cast<std::ptrdiff_t>(index));
}

void CommentCollection::clear() noexcept { comments_.clear(); }

std::size_t CommentCollection::size() const noexcept {
    return comments_.size();
}

Comment& CommentCollection::operator[](std::size_t index) {
    return *comments_.at(index);
}

const Comment& CommentCollection::operator[](std::size_t index) const {
    return *comments_.at(index);
}

void CommentCollection::remove(Comment& comment) {
    comment.remove();
}

std::vector<Comment*> CommentCollection::to_array() const {
    std::vector<Comment*> result;
    result.reserve(comments_.size());
    for (const auto& c : comments_) {
        result.push_back(c.get());
    }
    return result;
}

std::vector<Comment*> CommentCollection::to_array(std::size_t start,
                                                   std::size_t count) const {
    std::vector<Comment*> result;
    auto end = std::min(start + count, comments_.size());
    if (start >= comments_.size()) return result;
    result.reserve(end - start);
    for (auto i = start; i < end; ++i) {
        result.push_back(comments_[i].get());
    }
    return result;
}

Comment* CommentCollection::find_comment_by_idx(std::uint32_t idx) const {
    auto it = std::ranges::find_if(
        comments_, [idx](const auto& ptr) { return ptr->idx() == idx; });
    return it != comments_.end() ? it->get() : nullptr;
}

void CommentCollection::remove_comment(Comment* comment) {
    auto it = std::ranges::find_if(
        comments_, [comment](const auto& ptr) { return ptr.get() == comment; });
    if (it != comments_.end()) {
        comments_.erase(it);
    }
}

} // namespace Aspose::Slides::Foss
