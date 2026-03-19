// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <Aspose/Slides/Foss/comment_author_collection.h>
#include <Aspose/Slides/Foss/document_properties.h>
#include <Aspose/Slides/Foss/global_layout_slide_collection.h>
#include <Aspose/Slides/Foss/i_presentation.h>
#include <Aspose/Slides/Foss/image_collection.h>
#include <Aspose/Slides/Foss/master_slide_collection.h>
#include <Aspose/Slides/Foss/notes_size.h>
#include <Aspose/Slides/Foss/slide_collection.h>
#include <Aspose/Slides/Foss/source_format.h>

namespace Aspose::Slides::Foss::Internal::opc { class OpcPackage; class InMemoryOpcPackage; }
namespace Aspose::Slides::Foss::Internal::pptx { class CommentAuthorsPart; }

namespace Aspose::Slides::Foss {

class LayoutSlide;
class MasterSlide;

/// Represents a Microsoft PowerPoint presentation.
class Presentation final : public IPresentation {
public:
    /// Constructs a new empty presentation with one blank slide.
    Presentation();

    /// Constructs a presentation by loading from a PPTX file.
    /// @param path Path to a .pptx file.
    /// @throws std::runtime_error if the file cannot be opened or parsed.
    explicit Presentation(std::string_view path);

    ~Presentation() override;

    // Non-copyable, non-movable (due to internal back-references).
    Presentation(const Presentation&) = delete;
    Presentation& operator=(const Presentation&) = delete;

    // -- IPresentationComponent --

    /// Returns a pointer to this presentation.
    [[nodiscard]] IPresentation* presentation() override;
    [[nodiscard]] const IPresentation* presentation() const override;

    // -- IPresentation --

    /// Returns date and time for datetime field substitution.
    [[nodiscard]] std::chrono::system_clock::time_point current_date_time() const override;
    /// Sets date and time for datetime field substitution.
    void set_current_date_time(std::chrono::system_clock::time_point value) override;

    /// Returns the collection of slides. Read-only.
    [[nodiscard]] SlideCollection& slides() noexcept override;
    [[nodiscard]] const SlideCollection& slides() const noexcept override;

    /// Returns the collection of comment authors. Read-only.
    [[nodiscard]] CommentAuthorCollection& comment_authors() noexcept override;
    [[nodiscard]] const CommentAuthorCollection& comment_authors() const noexcept override;

    /// Returns the collection of images. Read-only.
    [[nodiscard]] ImageCollection& images() noexcept override;
    [[nodiscard]] const ImageCollection& images() const noexcept override;

    /// Returns the document properties. Read-only.
    [[nodiscard]] DocumentProperties& document_properties() noexcept override;
    [[nodiscard]] const DocumentProperties& document_properties() const noexcept override;

    /// Returns the collection of layout slides. Read-only.
    [[nodiscard]] GlobalLayoutSlideCollection& layout_slides() noexcept override;
    [[nodiscard]] const GlobalLayoutSlideCollection& layout_slides() const noexcept override;

    /// Returns the collection of master slides. Read-only.
    [[nodiscard]] MasterSlideCollection& masters() noexcept override;
    [[nodiscard]] const MasterSlideCollection& masters() const noexcept override;

    /// Returns the notes slide size. Read-only.
    [[nodiscard]] NotesSize& notes_size() noexcept override;
    [[nodiscard]] const NotesSize& notes_size() const noexcept override;

    /// Returns source format information. Read-only.
    [[nodiscard]] SourceFormat source_format() const override;

    /// Returns the first slide number in the presentation.
    [[nodiscard]] int first_slide_number() const override;
    /// Sets the first slide number in the presentation.
    void set_first_slide_number(int value) override;

    /// Returns a pointer to this as IPresentationComponent.
    [[nodiscard]] IPresentationComponent* as_i_presentation_component() override;
    [[nodiscard]] const IPresentationComponent* as_i_presentation_component() const override;

    /// Saves the presentation to a file path with the given format.
    void save(std::string_view path, int format) override;

    /// Releases all resources used by this Presentation.
    void dispose() override;

    // -- Internal helpers for OPC-based loading --

    /// Detect source format from a file extension.
    void detect_source_format(std::string_view path);

    /// Parse all master slides and layout slides from the OPC package on first access.
    void ensure_layout_slides_parsed();

    /// Resolve a layout slide part name to a LayoutSlide pointer.
    /// @return The LayoutSlide, or nullptr if not found.
    [[nodiscard]] LayoutSlide* resolve_layout_slide(std::string_view part_name);

    /// Resolve a master slide part name to a MasterSlide pointer.
    /// @return The MasterSlide, or nullptr if not found.
    [[nodiscard]] MasterSlide* resolve_master_slide(std::string_view part_name);

    /// Set the OPC package pointer (used during file loading).
    void set_opc_package(Internal::opc::OpcPackage* package) noexcept { opc_package_ = package; }

    /// Get the OPC package pointer.
    [[nodiscard]] Internal::opc::OpcPackage* opc_package() const noexcept { return opc_package_; }

    /// Set the presentation part name (used during file loading).
    void set_presentation_part_name(std::string_view name) { presentation_part_name_ = name; }

private:
    CommentAuthorCollection comment_authors_;
    DocumentProperties document_properties_;
    GlobalLayoutSlideCollection layout_slides_;
    ImageCollection images_;
    MasterSlideCollection masters_;
    NotesSize notes_size_;
    SlideCollection slides_;
    SourceFormat source_format_ = SourceFormat::PPTX;
    int first_slide_number_ = 1;
    std::chrono::system_clock::time_point current_date_time_ =
        std::chrono::system_clock::now();
    bool disposed_ = false;

    // Owned OPC package (when loaded from file).
    std::unique_ptr<Internal::opc::InMemoryOpcPackage> owned_opc_package_;

    // Owned comment authors part (when loaded from file).
    std::unique_ptr<Internal::pptx::CommentAuthorsPart> owned_authors_part_;

    // OPC-level state for lazy parsing of master/layout slides.
    Internal::opc::OpcPackage* opc_package_ = nullptr;
    std::string presentation_part_name_;

    // Lazily-populated maps keyed by part name.
    // nullptr means "not yet parsed"; empty map means "parsed but empty".
    std::unique_ptr<std::unordered_map<std::string, MasterSlide*>> master_slides_map_;
    std::unique_ptr<std::unordered_map<std::string, LayoutSlide*>> layout_slides_map_;

    // Owning storage for lazily-parsed layout slides (master slides are owned
    // by masters_ collection, layout slides need separate ownership).
    std::vector<std::unique_ptr<LayoutSlide>> owned_layout_slides_;
    std::vector<std::unique_ptr<MasterSlide>> owned_master_slides_;
};

} // namespace Aspose::Slides::Foss
