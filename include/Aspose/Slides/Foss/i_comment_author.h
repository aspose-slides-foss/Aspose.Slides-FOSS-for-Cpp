// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <string>

namespace Aspose::Slides::Foss {

class CommentCollection;

/// Interface for a comment author.
class ICommentAuthor {
public:
    virtual ~ICommentAuthor() = default;

    /// Returns the author's name.
    [[nodiscard]] virtual const std::string& name() const = 0;
    /// Sets the author's name.
    virtual void set_name(std::string value) = 0;

    /// Returns the author's initials.
    [[nodiscard]] virtual const std::string& initials() const = 0;
    /// Sets the author's initials.
    virtual void set_initials(std::string value) = 0;

    /// Returns the collection of comments by this author.
    [[nodiscard]] virtual CommentCollection& comments() = 0;
    /// Returns the collection of comments by this author (const).
    [[nodiscard]] virtual const CommentCollection& comments() const = 0;

    /// Removes the author from the parent collection.
    virtual void remove() = 0;
};

} // namespace Aspose::Slides::Foss
