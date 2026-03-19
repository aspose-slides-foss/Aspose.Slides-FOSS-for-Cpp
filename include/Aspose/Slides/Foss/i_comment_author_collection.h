// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace Aspose::Slides::Foss {

class CommentAuthor;

/// Interface for a collection of comment authors.
class ICommentAuthorCollection {
public:
    virtual ~ICommentAuthorCollection() = default;

    /// Adds a new author with the given name and initials.
    virtual CommentAuthor& add_author(const std::string& name,
                                      const std::string& initials) = 0;

    /// Returns a copy of all authors as a vector of non-owning pointers.
    [[nodiscard]] virtual std::vector<CommentAuthor*> to_array() = 0;

    /// Finds authors whose name matches the given value.
    [[nodiscard]] virtual std::vector<CommentAuthor*> find_by_name(
        const std::string& name) = 0;

    /// Finds authors whose name and initials both match.
    [[nodiscard]] virtual std::vector<CommentAuthor*> find_by_name_and_initials(
        const std::string& name, const std::string& initials) = 0;

    /// Removes the author at the given index, clearing its comments first.
    virtual void remove_at(std::size_t index) = 0;

    /// Removes the specified author from the collection.
    virtual void remove(CommentAuthor& author) = 0;

    /// Removes all authors from the collection, clearing their comments first.
    virtual void clear() = 0;

    /// Returns the number of authors.
    [[nodiscard]] virtual std::size_t size() const = 0;

    /// Returns the author at the given index.
    [[nodiscard]] virtual CommentAuthor& operator[](std::size_t index) = 0;
};

} // namespace Aspose::Slides::Foss
