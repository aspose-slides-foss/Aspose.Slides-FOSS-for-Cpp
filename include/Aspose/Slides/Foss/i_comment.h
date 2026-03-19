// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <string>

#include <Aspose/Slides/Foss/drawing/point_f.h>

namespace Aspose::Slides::Foss {

class CommentAuthor;
class Slide;

/// Interface for a slide comment.
class IComment {
public:
    virtual ~IComment() = default;

    /// Returns the plain text of a slide comment.
    [[nodiscard]] virtual const std::string& text() const = 0;
    /// Sets the plain text of a slide comment.
    virtual void set_text(std::string value) = 0;

    /// Returns the time of comment creation.
    [[nodiscard]] virtual std::chrono::system_clock::time_point created_time() const = 0;
    /// Sets the time of comment creation.
    virtual void set_created_time(std::chrono::system_clock::time_point value) = 0;

    /// Returns the parent slide of this comment. Read-only.
    [[nodiscard]] virtual Slide* slide() const = 0;

    /// Returns the author of this comment. Read-only.
    [[nodiscard]] virtual CommentAuthor* author() const = 0;

    /// Returns the position of this comment on the slide.
    [[nodiscard]] virtual Drawing::PointF position() const = 0;
    /// Sets the position of this comment on the slide.
    virtual void set_position(Drawing::PointF value) = 0;

    /// Returns the parent comment, or nullptr if none.
    [[nodiscard]] virtual IComment* parent_comment() const = 0;
    /// Sets the parent comment. Pass nullptr to clear.
    virtual void set_parent_comment(IComment* value) = 0;

    /// Removes this comment and all its replies from the parent collection.
    virtual void remove() = 0;
};

} // namespace Aspose::Slides::Foss
