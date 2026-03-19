// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

#include <Aspose/Slides/Foss/drawing/point_f.h>

namespace Aspose::Slides::Foss {

class Comment;
class Slide;

/// Interface for a collection of comments of one author.
class ICommentCollection {
public:
    virtual ~ICommentCollection() = default;

    /// Returns the number of comments in this collection.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the comment at the given index.
    [[nodiscard]] virtual Comment& operator[](std::size_t index) = 0;

    /// Returns the comment at the given index (const).
    [[nodiscard]] virtual const Comment& operator[](std::size_t index) const = 0;

    /// Returns a vector of non-owning pointers to all comments.
    [[nodiscard]] virtual std::vector<Comment*> to_array() const = 0;

    /// Returns a vector of comments in the specified range.
    [[nodiscard]] virtual std::vector<Comment*> to_array(std::size_t start,
                                                         std::size_t count) const = 0;

    /// Adds a new comment and returns a reference to it.
    virtual Comment& add_comment(const std::string& text, Slide& slide,
                                 Drawing::PointF position,
                                 std::chrono::system_clock::time_point created_time) = 0;

    /// Inserts a comment at the given index and returns a reference to it.
    virtual Comment& insert_comment(std::size_t index, const std::string& text,
                                    Slide& slide, Drawing::PointF position,
                                    std::chrono::system_clock::time_point created_time) = 0;

    /// Removes the comment at the given index.
    virtual void remove_at(std::size_t index) = 0;

    /// Removes the given comment (and its replies) from the collection.
    virtual void remove(Comment& comment) = 0;

    /// Removes all comments from this collection.
    virtual void clear() = 0;

    /// Returns a reference to this collection as a generic collection interface.
    [[nodiscard]] virtual ICommentCollection& as_i_collection() = 0;

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] virtual ICommentCollection& as_i_enumerable() = 0;
};

} // namespace Aspose::Slides::Foss
