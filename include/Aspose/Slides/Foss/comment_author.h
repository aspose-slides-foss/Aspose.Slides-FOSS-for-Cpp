// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <memory>
#include <string>

#include <Aspose/Slides/Foss/comment_collection.h>
#include <Aspose/Slides/Foss/i_comment_author.h>

namespace Aspose::Slides::Foss {

class CommentAuthorCollection;
class Presentation;

namespace Internal::pptx {
class AuthorData;
class CommentAuthorsPart;
} // namespace Internal::pptx

namespace Internal::opc {
class OpcPackage;
} // namespace Internal::opc

/// Represents the author of a comment.
class CommentAuthor final : public ICommentAuthor {
public:
    /// Constructs an author with the given name and initials.
    CommentAuthor(std::string name, std::string initials);

    /// Initializes the internal PPTX persistence layer for this author.
    ///
    /// Links the public CommentAuthor to its XML-backed AuthorData so that
    /// property accessors (name, initials) delegate to the underlying XML node.
    ///
    /// @param data        The XML-backed author data.
    /// @param authors_part The comment authors part managing the XML document.
    /// @param package     The OPC package containing the presentation.
    /// @param presentation Optional pointer to the owning Presentation.
    void init_internal(Internal::pptx::AuthorData data,
                       Internal::pptx::CommentAuthorsPart& authors_part,
                       Internal::opc::OpcPackage& package,
                       Presentation* presentation = nullptr);

    /// Returns the author's name.
    [[nodiscard]] const std::string& name() const noexcept override;
    /// Sets the author's name.
    void set_name(std::string value) override;

    /// Returns the author's initials.
    [[nodiscard]] const std::string& initials() const noexcept override;
    /// Sets the author's initials.
    void set_initials(std::string value) override;

    /// Returns the collection of comments by this author.
    [[nodiscard]] CommentCollection& comments() noexcept override;
    /// Returns the collection of comments by this author (const).
    [[nodiscard]] const CommentCollection& comments() const noexcept override;

    /// Removes the author from the parent collection, clearing all comments first.
    void remove() override;

    /// Returns whether this author is backed by internal PPTX data.
    [[nodiscard]] bool has_internal_data() const noexcept;

    /// Returns the internal author data, if initialized.
    [[nodiscard]] Internal::pptx::AuthorData* internal_data() noexcept;

    /// Returns the internal authors part, if initialized.
    [[nodiscard]] Internal::pptx::CommentAuthorsPart* authors_part() noexcept;

    /// Returns the OPC package, if initialized.
    [[nodiscard]] Internal::opc::OpcPackage* package() noexcept;

    /// Returns the owning presentation, if set.
    [[nodiscard]] Presentation* presentation() noexcept;

private:
    friend class CommentAuthorCollection;

    std::string name_;
    std::string initials_;
    CommentCollection comments_;
    CommentAuthorCollection* owner_ = nullptr;

    // Internal PPTX persistence state (set via init_internal).
    std::unique_ptr<Internal::pptx::AuthorData> data_;
    Internal::pptx::CommentAuthorsPart* authors_part_ = nullptr;
    Internal::opc::OpcPackage* package_ = nullptr;
    Presentation* presentation_ = nullptr;
};

} // namespace Aspose::Slides::Foss
