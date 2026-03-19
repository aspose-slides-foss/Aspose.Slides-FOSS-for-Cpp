// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <Aspose/Slides/Foss/i_comment_author_collection.h>

namespace Aspose::Slides::Foss {

class CommentAuthor;
class Presentation;

namespace Internal::pptx {
class AuthorData;
class CommentAuthorsPart;
} // namespace Internal::pptx

namespace Internal::opc {
class OpcPackage;
} // namespace Internal::opc

/// Manages a collection of comment authors in a presentation.
class CommentAuthorCollection final : public ICommentAuthorCollection {
public:
    CommentAuthorCollection();
    CommentAuthorCollection(const CommentAuthorCollection&) = delete;
    CommentAuthorCollection& operator=(const CommentAuthorCollection&) = delete;
    ~CommentAuthorCollection() override;
    CommentAuthorCollection(CommentAuthorCollection&&) noexcept;
    CommentAuthorCollection& operator=(CommentAuthorCollection&&) noexcept;

    /// Initializes the internal PPTX persistence layer for this collection.
    ///
    /// Links the collection to its XML-backed CommentAuthorsPart so that
    /// authors are loaded from the underlying XML document.
    ///
    /// @param authors_part The comment authors part managing the XML document.
    /// @param package      The OPC package containing the presentation.
    /// @param presentation Optional pointer to the owning Presentation.
    void init_internal(Internal::pptx::CommentAuthorsPart& authors_part,
                       Internal::opc::OpcPackage& package,
                       Presentation* presentation = nullptr);

    /// Adds a new author with the given name and initials.
    CommentAuthor& add_author(const std::string& name,
                              const std::string& initials) override;

    /// Returns a copy of all authors as a vector of non-owning pointers.
    [[nodiscard]] std::vector<CommentAuthor*> to_array() override;
    [[nodiscard]] std::vector<const CommentAuthor*> to_array() const;

    /// Finds authors whose name matches the given value.
    [[nodiscard]] std::vector<CommentAuthor*> find_by_name(const std::string& name) override;

    /// Finds authors whose name and initials both match.
    [[nodiscard]] std::vector<CommentAuthor*> find_by_name_and_initials(
        const std::string& name, const std::string& initials) override;

    /// Removes the author at the given index, clearing its comments first.
    void remove_at(std::size_t index) override;

    /// Removes the specified author from the collection.
    void remove(CommentAuthor& author) override;

    /// Removes all authors from the collection, clearing their comments first.
    void clear() override;

    /// Returns the number of authors.
    [[nodiscard]] std::size_t size() const noexcept override;

    /// Returns the author at the given index.
    [[nodiscard]] CommentAuthor& operator[](std::size_t index) override;
    [[nodiscard]] const CommentAuthor& operator[](std::size_t index) const;

    /// Returns a reference to this collection as a generic collection interface.
    [[nodiscard]] CommentAuthorCollection& as_i_collection() noexcept { return *this; }
    [[nodiscard]] const CommentAuthorCollection& as_i_collection() const noexcept { return *this; }

    /// Returns a reference to this collection as a generic enumerable interface.
    [[nodiscard]] CommentAuthorCollection& as_i_enumerable() noexcept { return *this; }
    [[nodiscard]] const CommentAuthorCollection& as_i_enumerable() const noexcept { return *this; }

    // Iterator support for range-based for loops.
    [[nodiscard]] auto begin() noexcept { return authors_.begin(); }
    [[nodiscard]] auto end() noexcept { return authors_.end(); }
    [[nodiscard]] auto begin() const noexcept { return authors_.begin(); }
    [[nodiscard]] auto end() const noexcept { return authors_.end(); }

private:
    /// Builds a CommentAuthor from XML-backed AuthorData and links it
    /// to the internal PPTX persistence layer.
    std::unique_ptr<CommentAuthor> build_author(Internal::pptx::AuthorData data);

    std::vector<std::unique_ptr<CommentAuthor>> authors_;

    // Internal PPTX persistence state (set via init_internal).
    Internal::pptx::CommentAuthorsPart* authors_part_ = nullptr;
    Internal::opc::OpcPackage* package_ = nullptr;
    Presentation* presentation_ = nullptr;
};

} // namespace Aspose::Slides::Foss
