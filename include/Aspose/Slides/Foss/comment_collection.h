// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/i_comment_collection.h>

namespace Aspose::Slides::Foss {

class Comment;
class CommentAuthor;
class Slide;

/// Manages a collection of comments belonging to a single author.
class CommentCollection final : public ICommentCollection {
public:
    /// Constructs a collection owned by the given author.
    explicit CommentCollection(CommentAuthor* author) noexcept;
    CommentCollection(const CommentCollection&) = delete;
    CommentCollection& operator=(const CommentCollection&) = delete;
    ~CommentCollection() override;
    CommentCollection(CommentCollection&&) noexcept;
    CommentCollection& operator=(CommentCollection&&) noexcept;

    /// Adds a new comment and returns a reference to it.
    Comment& add_comment(const std::string& text, Slide& slide,
                         Drawing::PointF position,
                         std::chrono::system_clock::time_point created_time) override;

    /// Inserts a comment at the given index and returns a reference to it.
    Comment& insert_comment(std::size_t index, const std::string& text,
                            Slide& slide, Drawing::PointF position,
                            std::chrono::system_clock::time_point created_time) override;

    /// Removes the comment at the given index.
    void remove_at(std::size_t index) override;

    /// Removes the given comment (and its replies) from the collection.
    void remove(Comment& comment) override;

    /// Removes all comments from this collection.
    void clear() noexcept override;

    /// Returns the number of comments.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the comment at the given index.
    [[nodiscard]] Comment& operator[](std::size_t index) override;
    [[nodiscard]] const Comment& operator[](std::size_t index) const override;

    /// Returns a vector of non-owning pointers to all comments.
    [[nodiscard]] std::vector<Comment*> to_array() const override;

    /// Returns a vector of comments in the specified range.
    [[nodiscard]] std::vector<Comment*> to_array(std::size_t start, std::size_t count) const override;

    /// Finds a comment by its unique per-author index, or nullptr if not found.
    [[nodiscard]] Comment* find_comment_by_idx(std::uint32_t idx) const;

    /// Returns a reference to this collection as a generic collection interface.
    [[nodiscard]] ICommentCollection& as_i_collection() noexcept override { return *this; }

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] ICommentCollection& as_i_enumerable() noexcept override { return *this; }

    /// Removes a specific comment by pointer (used internally by Comment::remove).
    void remove_comment(Comment* comment);

private:
    CommentAuthor* author_;
    std::vector<std::unique_ptr<Comment>> comments_;
    std::uint32_t next_idx_ = 1;
};

} // namespace Aspose::Slides::Foss
