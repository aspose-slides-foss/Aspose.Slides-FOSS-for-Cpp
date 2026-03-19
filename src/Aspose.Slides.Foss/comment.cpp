// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/comment.h>

#include <algorithm>
#include <utility>

#include <Aspose/Slides/Foss/comment_collection.h>

namespace Aspose::Slides::Foss {

Comment::Comment(std::string text, Slide* slide, CommentAuthor* author,
                 Drawing::PointF position,
                 std::chrono::system_clock::time_point created_time)
    : text_(std::move(text)),
      position_(position),
      created_time_(created_time),
      slide_(slide),
      author_(author) {}

const std::string& Comment::text() const noexcept { return text_; }
void Comment::set_text(std::string value) { text_ = std::move(value); }

std::chrono::system_clock::time_point Comment::created_time() const noexcept {
    return created_time_;
}
void Comment::set_created_time(
    std::chrono::system_clock::time_point value) noexcept {
    created_time_ = value;
}

Slide* Comment::slide() const noexcept { return slide_; }
CommentAuthor* Comment::author() const noexcept { return author_; }

Drawing::PointF Comment::position() const noexcept { return position_; }
void Comment::set_position(Drawing::PointF value) noexcept {
    position_ = value;
}

IComment* Comment::parent_comment() const noexcept { return parent_comment_; }
void Comment::set_parent_comment(IComment* value) noexcept {
    parent_comment_ = value;
}

std::uint32_t Comment::idx() const noexcept { return idx_; }

void Comment::remove() {
    if (!owner_) return;

    // Collect replies (comments in same collection with this as parent).
    std::vector<Comment*> replies;
    for (std::size_t i = 0; i < owner_->size(); ++i) {
        if (&(*owner_)[i] != this && (*owner_)[i].parent_comment() == this) {
            replies.push_back(&(*owner_)[i]);
        }
    }

    // Remove replies first.
    for (auto* reply : replies) {
        owner_->remove_comment(reply);
    }

    // Remove this comment.
    owner_->remove_comment(this);
}

} // namespace Aspose::Slides::Foss
