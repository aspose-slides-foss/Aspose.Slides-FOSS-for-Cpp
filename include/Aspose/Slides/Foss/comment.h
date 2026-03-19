// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

#include <Aspose/Slides/Foss/drawing/point_f.h>
#include <Aspose/Slides/Foss/i_comment.h>

namespace Aspose::Slides::Foss {

class CommentAuthor;
class CommentCollection;
class Slide;

/// Represents a comment on a slide.
class Comment final : public IComment {
public:
    /// Constructs a comment with the given properties.
    Comment(std::string text, Slide* slide, CommentAuthor* author,
            Drawing::PointF position,
            std::chrono::system_clock::time_point created_time);

    // -- IComment overrides --

    /// Returns the plain text of a slide comment.
    [[nodiscard]] const std::string& text() const noexcept override;
    /// Sets the plain text of a slide comment.
    void set_text(std::string value) override;

    /// Returns the time of comment creation.
    [[nodiscard]] std::chrono::system_clock::time_point created_time() const noexcept override;
    /// Sets the time of comment creation.
    void set_created_time(std::chrono::system_clock::time_point value) noexcept override;

    /// Returns the parent slide of this comment. Read-only.
    [[nodiscard]] Slide* slide() const noexcept override;

    /// Returns the author of this comment. Read-only.
    [[nodiscard]] CommentAuthor* author() const noexcept override;

    /// Returns the position of this comment on the slide.
    [[nodiscard]] Drawing::PointF position() const noexcept override;
    /// Sets the position of this comment on the slide.
    void set_position(Drawing::PointF value) noexcept override;

    /// Returns the parent comment, or nullptr if none.
    [[nodiscard]] IComment* parent_comment() const noexcept override;
    /// Sets the parent comment. Pass nullptr to clear.
    void set_parent_comment(IComment* value) noexcept override;

    /// Returns the unique index of this comment within its author's scope.
    [[nodiscard]] std::uint32_t idx() const noexcept;

    /// Removes this comment and all its replies from the parent collection.
    void remove() override;

private:
    friend class CommentCollection;

    std::string text_;
    Drawing::PointF position_;
    std::chrono::system_clock::time_point created_time_;
    Slide* slide_;
    CommentAuthor* author_;
    IComment* parent_comment_ = nullptr;
    CommentCollection* owner_ = nullptr;
    std::uint32_t idx_ = 0;
};

} // namespace Aspose::Slides::Foss
